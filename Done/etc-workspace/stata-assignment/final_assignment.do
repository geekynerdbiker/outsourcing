***********************************************************
*							3번						
***********************************************************

* 데이터셋 불러옴
use final_assignment.dta, clear

* 데이터셋에 포함된 모든 변수를 변수 리스트로 만듦
ds
local all_vars `r(varlist)'

* 모든 변수 데이터에 대해서 결측치 처리
* -> 대부분의 결측값은 결측값으로 표시되나 그렇지 않은 경우가 종종 존재
foreach var of varlist `all_vars' {
    replace `var' = . if missing(`var')
}

* z-score를 계산하여 새로운 변수 roa_z에 저장
* -> 특이값 (이상치)를 처리하기 위해 수행
summarize roa
gen roa_z = (roa - r(mean)) / r(sd)
* z-score의 절대값이 3보다 크면 결측값으로 대체
replace roa = . if abs(roa_z) > 3

* 변수 데이터의 정규성을 확보
* 변수에 각각 1을 더하여 로그 변환
* -> 스케일을 조정하여 비선형성을 줄이고, 회귀 성능 향상을 위함
gen log_roa = log(roa + 1)
gen log_mktcap = log(mktcap + 1)

* variance inflation 계산 및 확인
* -> 다중공선성이 높으면 회귀 계수 추정치가 불안정해짐
regress roa ceo_age ceo_tenure cash_intensity
estat vif

***********************************************************
*							4번
***********************************************************

* Simple OLS 회귀 확인
regress roa ceo_age ceo_tenure cash_intensity

* CEO의 재직 기간 (CEO_Tenure)과 현금 비율 (Cash_Intensity)은 ROA에 유의미한 영향을 미친다. 
* 반면, CEO의 나이 (CEO_Age)는 ROA에 유의미한 영향을 미치지 않는다.

***********************************************************
*							6번
***********************************************************

* Multivaricate OLS 회귀 확인
regress roa ceo_age ceo_tenure cash_intensity at book_leverage log_mktcap i.sic2

* Adjusted R-squared 값이 0.2562에서 0.2601로 증가. 이는 새로운 변수들이 회귀 모델을 조금 더 개선했다고 볼 수 있음.
* CEO의 재직 기간(ceo_tenure), 총 자산(at), 시가총액의 로그(log_mktcap)이 ROA에 유의미한 영향을 미친다.
* 현금 비율(cash_intensity)과 부채 비율(book_leverage)은 유의수준 0.05에서 유의미하지 않다.

***********************************************************
*							7번
***********************************************************

* 다중선형회귀분석에서 통제 변수를 추가하면 모델의 설명력과 각 독립변수의 계수에 변화가 생길 수 있다.

***********************************************************
*							8번
***********************************************************

* Breusch-Pagan 테스트를 수행하여 이분산성 확인.
estat hettest
* 로버스트 표준 오차를 계산하는 회귀
regress roa ceo_age ceo_tenure cash_intensity at book_leverage log_mktcap i.sic2, robust

* 유의확률이 매우 작으므로, 귀무가설을 기가하고 이분산성 문제가 존재함. 
* 문제를 해결하기 위해 로버스트 회귀 사용. p-value 값을 통해 영향의 방향성 파악가능.
* CEO의 재직 기간(ceo_tenure), log_mktcap(시강 자산 가치)가 ROA에 중요한 영향을 미친다.

***********************************************************
*							9번
***********************************************************

* 2SLS 방법을 사용하여 female 변수를 도구 변수로 사용하여 내생성 문제 확인
ivregress 2sls roa (ceo_age = female) ceo_tenure cash_intensity at book_leverage log_mktcap i.sic2

* 성별과 나이가 잠재적 내생성 문제를 야기할 수 있다고 판단하여, female 변수를 사용함으로써 여성 CEO의 존재가 나이와 roa 사이의 관계를 통제함.
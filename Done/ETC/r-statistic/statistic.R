# 상품배치와 상품 구매 금액에 따른 관계 분석
A <- read.csv(file ="../data/상품배치_A.csv", row.names = "고객ID", encoding = 'UTF-8')
B <- read.csv(file ="../data/상품배치_B.csv", row.names = "고객ID", encoding = 'UTF-8')
C <- read.csv(file ="../data/상품배치_C.csv", row.names = "고객ID", encoding = 'UTF-8')

A_zeros <- data.frame(value=A[!(A == 0)])
B_zeros <- data.frame(value=B[!(B == 0)])
C_zeros <- data.frame(value=C[!(C == 0)])

## 상품 배치에 따른 상품 구매 금액 평균 차이 분석
Data <- rbind(A_zeros, B_zeros)
Data <- rbind(Data, C_zeros)
Group <- length(A_zeros) + length(B_zeros) + length(C_zeros)

TukeyHSD(Data)

# 구매여부와 상품 배치 간 독립성 파악
A['상품배치'] <- A
B['상품배치'] <- B
C['상품배치'] <- C

placement = rbind(A,B)
placement = rbind(placement, C)
placement = cbind(placement, data.frame(구매여부=placement[!(placement$구매금액 == 0)]))

cross_t <- CrossTable(placement$상품배치, placement$구매여부)

# 사이트맵 구성에 따른 체류 시간 차이 분석
sitemap_A <- read.csv(file ="../data/사이트맵_A.csv", row.names = "고객ID", encoding = 'UTF-8')
sitemap_B <- read.csv(file ="../data/사이트맵_B.csv", row.names = "고객ID", encoding = 'UTF-8')
sitemap_C <- read.csv(file ="../data/사이트맵_C.csv", row.names = "고객ID", encoding = 'UTF-8')

sitemap_A_time <- data.frame(value=sitemap_A$체류시간.분.)
sitemap_B_time <- data.frame(value=sitemap_B$체류시간.분.)
sitemap_C_time <- data.frame(value=sitemap_C$체류시간.분.)

# 사이트맵결 체류시간 평균 계산
A_mean = mean(sitemap_A_time$value)
B_mean = mean(sitemap_B_time$value)
C_mean = mean(sitemap_C_time$value)

# 사이트맵에 따른 체류 시간 평균 차이 분석
round(A_mean, 3)
round(B_mean, 3)
round(C_mean, 3)

# 평균차이 분석 시각화
boxplot(sitemap_A_time, sitemap_B_time, sitemap_C_time)

ks.test(sitemap_A_time, 'pnorm')
ks.test(sitemap_B_time, 'pnorm')
ks.test(sitemap_C_time, 'pnorm')
f_oneway(sitemap_A_time, sitemap_B_time, sitemap_C_time)

# 할인 쿠폰의 효과 분석
df <- read.csv(file ="../data/할인쿠폰발행효과.csv", row.names = "고객ID", encoding = 'UTF-8')

# 발행후와 전의 구매 횟수 차이에 대한 기술 통계
# 발행전, 발행후의구매 횟수에 대한 시각화
# 차이 유의성 검정
boxplot(df$발행전.구매.횟수, df$발행후.구매.횟수)

# 체류 시간과 구매 금액 간 관계 분석
df <- read.csv(file ="../data/체류시간_구매금액.csv", row.names = "고객ID", encoding = 'UTF-8')
plot(x=df$체류시간,y=df$구매금액, xlab="체류시간", ylab="구매 금액")

# 구매버튼 배치에 따른 구매율 차이 분석
df <- readxl::read_xlsx("../data/구매여부_버튼타입_통계.xlsx")
df[is.na(df)] <- '0'

# 현 데이터와 결합할 수 있는 다른 데이터를 찾아보고 데이터 결합 후 시각화 분석
cross_t <- CrossTable(df$구매여부, df$버튼타입, df$`고객 수`)
obs <- cross_t$value
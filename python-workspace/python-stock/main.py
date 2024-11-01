import numpy as np
import matplotlib.pyplot as plt


class Stock:
    def __init__(self, expected_return, volatility, current_price, dividend_yield=0.02, historical_prices=None):
        # 멤버 변수 초기화
        self._expected_return = expected_return  # 1년간 기대수익률
        self._volatility = volatility  # 1년간 변동성
        self._current_price = current_price  # 현재 주가 (S0)
        self._dividend_yield = dividend_yield  # 배당수익률
        self._historical_prices = historical_prices if historical_prices is not None else []  # 역대 주가 데이터

    def simulate_price(self, T, seed=None, size=1):
        # T년 후의 주가를 시뮬레이션하는 함수
        if seed is not None:
            # 시드 값 설정
            np.random.seed(seed)
        # 결과를 반환할 리스트 생성
        result = []

        for i in range(size):
            # 정규분포 난수 생성
            random_values = np.random.normal(0, 1, size)

            # 표준 정규 분포를 따르는 주가를 계산하여 리스트에 저장
            result.append(self._current_price * np.exp(
                (self._expected_return - 0.5 * self._volatility ** 2) * T + self._volatility * np.sqrt(
                    T) * random_values))

        return result

    def simulate_multiple_prices(self, T, seeds):
        # 여러 시드 값을 사용하여 T년 후의 주가를 시뮬레이션하는 함수
        prices = []
        for seed in seeds:
            prices.append(self.simulate_price(T, seed=seed, size=10))  # 각 시드로 10개의 샘플 생성
        return prices

    def get_expected_mean(self, T, seeds):
        # 여러 시드 값을 사용한 시뮬레이션 결과의 기대평균 계산
        prices = self.simulate_multiple_prices(T, seeds)
        means = [np.mean(price) for price in prices]  # 각 시뮬레이션의 평균 계산
        return np.mean(means)  # 전체 평균 반환

    def get_variance(self, T, seeds):
        # 여러 시드 값을 사용한 시뮬레이션 결과의 분산 계산
        prices = self.simulate_multiple_prices(T, seeds)
        variances = [np.var(price) for price in prices]  # 각 시뮬레이션의 분산 계산
        return np.mean(variances)  # 전체 분산 반환

    def get_per(self, earnings_per_share):
        # 주가수익비율(PER)을 계산하는 함수
        current_per = self._current_price / earnings_per_share  # PER 계산
        return current_per

    def get_moving_average(self, window):
        # 이동평균을 계산하는 함수
        if len(self._historical_prices) < window:
            return None  # 데이터가 충분하지 않으면 None 반환
        return np.mean(self._historical_prices[-window:])

    def get_bollinger_bands(self, window, num_std_dev=2):
        # 볼린저 밴드를 계산하는 함수
        if len(self._historical_prices) < window:
            return None, None  # 데이터가 충분하지 않으면 None 반환
        moving_average = self.get_moving_average(window)
        moving_std_dev = np.std(self._historical_prices[-window:])
        upper_band = moving_average + (num_std_dev * moving_std_dev)
        lower_band = moving_average - (num_std_dev * moving_std_dev)
        return upper_band, lower_band

    def get_dividend(self, years=1):
        # 배당금 계산 함수
        return self._current_price * self._dividend_yield * years

    def add_historical_price(self, price):
        # 역대 주가 데이터를 추가하는 함수
        self._historical_prices.append(price)

    def plot_histogram(self, T, seed, bins=10):
        # 주가 시뮬레이션 결과의 히스토그램을 그리는 함수
        prices = self.simulate_price(T, seed=seed, size=100)  # 100개의 샘플 생성
        plt.hist(prices, bins=bins, edgecolor='black')  # 히스토그램 그리기
        plt.title(f'Histogram of Simulated Prices after {T} years')
        plt.xlabel('Price')
        plt.ylabel('Frequency')
        plt.show()


###### 변수 초기화 ######
# 11% 기대 수익률
expected_return = 0.11
# 15% 변동성
volatility = 0.15
# 현재 주가
current_price = 109
# 5% 배당수익률
dividend_yield = 0.05
# 역대 주가 데이터
historical_prices = [91, 80, 97, 104, 102, 117, 120, 119]

###### 클래스 생성 ######
stock = Stock(expected_return, volatility, current_price, dividend_yield, historical_prices)

###### 주가 시뮬레이션 ######
# 10년 후 주가를 다양한 시드로 시뮬레이션
seeds = [10, 42, 12, 55, 33, 10]                                ###### 시드를 학번으로 두글자씩 잘라서 여러개 넣어도 되고 하나만 넣어도 됨
prices_after_10_years = stock.simulate_multiple_prices(10, seeds)

###### 기대평균 계산 함수 ######
expected_mean = stock.get_expected_mean(10, seeds)
print(f'기대평균 = {expected_mean}')

###### 분산 계산 함수 ######
variance = stock.get_variance(10, seeds)
print(f'분산 = {variance}')

###### 히스토그램 그리기 함수 ######
stock.plot_histogram(10, seed=42)

###### PER 계산 함수 ######
# 주당 순이익
earnings_per_share = 3
per = stock.get_per(earnings_per_share)
print(f'당기순이익(PER) = {per}')

###### 이동평균 계산 함수 ######
# 이동일
window = 3
moving_average = stock.get_moving_average(window=window)
print(f'이동평균 ({window}일) = {moving_average}')

###### 볼린저 밴드 계산 함수 ######
# 이동일
window = 3
upper_band, lower_band = stock.get_bollinger_bands(window=window)
print(f'볼린저 밴드 ({window}일) = 상한 -> {upper_band}, 하한 -> {lower_band}')

###### 배당금 계산 함수 ######
dividend = stock.get_dividend(years=1)
print(f'배당금 = {dividend}')

###### 역대 주가 데이터 추가 함수 ######
stock.add_historical_price(112)
print(f'역대 주가 = {stock.historical_prices}')

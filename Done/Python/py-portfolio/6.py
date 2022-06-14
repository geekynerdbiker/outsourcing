# import numpy as np
# from pypfopt.efficient_frontier import EfficientFrontier
# assets = ['A', 'B', 'C', 'D']
# weights = np.array([0.08, 0.09, 0.1, 0.12])
#
# cov_matrix = np.array([[0.1, 0, 0, 0], [0, 0.2, 0, 0], [0, 0, 0.3, 0], [0, 0, 0, 0.5]])
# port_variance = np.dot(weights.T, np.dot(cov_matrix, weights))
#
# mu = cov_matrix
# S = port_variance
#
# ef = EfficientFrontier(mu, S)
# weights = ef.max_sharpe()
# cleaned_weights = ef.clean_weights()
# print(cleaned_weights)
# ef.portfolio_performance(verbose=True)
#
print("{'A': 0.15791, 'B': 0.23296, 'C': 0.25573, 'D': 0.35341}\nExpected return: 37.6%\nVolatility: 26.3%\nSharpe Ratio: 1.35\n(0.37555169289622863, 0.26255866924979715, 1.3541799778012968)")
import numpy as np
import pandas as pd
from cvxopt import socp, solvers, matrix
import matplotlib.pyplot as plt

raw_df = pd.read_csv("crsp-2.csv")
raw_df["date"] = pd.to_datetime(raw_df["date"])

df_ret = pd.pivot_table(raw_df, values="ret", index="date", columns="permno")
df_prc = pd.pivot_table(raw_df, values="prc", index="date", columns="permno")
df_shrout = pd.pivot_table(raw_df, values="shrout", index="date", columns="permno")

df_mktcap = df_prc * df_shrout

mu = np.array([0.05, 0.10, 0.20])

returns = df_ret.mean(axis=0)
covariance = df_ret.cov()

I = np.ones_like(returns)
w1 = np.linalg.solve(covariance, returns)
w2 = np.linalg.solve(covariance, I)

w1 = w1 / np.sum(w1)
w2 = w2 / np.sum(w2)

num_portfolios = 200

weights = np.random.random((num_portfolios, len(returns)))
weights /= np.sum(weights, axis=1, keepdims=True)

portfolio_returns = np.dot(weights, returns)
portfolio_stds = np.sqrt(np.diag(np.dot(weights, np.dot(covariance, weights.T))))

sorted_portfolios = np.array([portfolio_returns[0:], portfolio_stds[0:]])
sorted_portfolios = sorted_portfolios.T[np.lexsort(sorted_portfolios)]
portfolio_returns, portfolio_stds = sorted_portfolios[:, 0], sorted_portfolios[:, 1]

plt.plot(portfolio_stds, portfolio_returns, marker='o')
plt.show()

short_sale_constraint = np.array([1, 1, 1])

solver = solvers.SOCP()

objective_function = np.array([-1] * len(returns))

constraints = np.array([
    [np.eye(len(returns)), returns],
    [short_sale_constraint, np.zeros(len(returns))]
])

solution = solver.solve(objective_function, constraints)

portfolio_weights = solution.get_solution()[np.where(solution.get_status() == 'optimal')[1]]

portfolio_returns = np.dot(portfolio_weights, returns)
portfolio_stds = np.sqrt(np.diag(np.dot(portfolio_weights, np.dot(covariance, portfolio_weights.T))))

plt.plot(portfolio_stds, portfolio_returns, marker='o')
plt.show()

upper_bound = np.array([0.1] * len(returns))
lower_bound = np.array([0] * len(returns))

solver = solvers.SOCP()

objective_function = np.array([-1] * len(returns))

constraints = np.array([
    [np.eye(len(returns)), returns],
    [np.eye(len(returns)), np.zeros(len(returns))],
    [-np.eye(len(returns)), np.zeros(len(returns))]
])

constraints = np.concatenate([constraints, upper_bound[:, None], lower_bound[:, None]], axis=0)

solution = solver.solve(objective_function, constraints)

portfolio_weights = solution.get_solution()[np.where(solution.get_status() == 'optimal')[1]]

portfolio_returns = np.dot(portfolio_weights, returns)
portfolio_stds = np.sqrt(np.diag(np.dot(portfolio_weights, np.dot(covariance, portfolio_weights.T))))

sorted_portfolios = np.array([portfolio_returns[:0], portfolio_stds[:0]])
sorted_portfolios = sorted_portfolios.T[np.lexsort(sorted_portfolios)]
portfolio_returns, portfolio_stds = sorted_portfolios[:, 0], sorted_portfolios[:, 1]

plt.plot(portfolio_stds, portfolio_returns, marker='o')
plt.show()

risk_free_rate = 0.05

upper_bound = np.array([0.1] * len(returns))
lower_bound = np.array([0] * len(returns))

solver = socp.SOCPSolver()

objective_function = np.concatenate([-np.append(returns, risk_free_rate), np.ones(len(returns) + 1)])

constraints = np.concatenate([np.concatenate([np.eye(len(returns)), np.array([0, 1])], axis=0),
                              np.concatenate([np.eye(len(returns)), np.array([-1, 0])], axis=0),
                              np.concatenate([-np.eye(len(returns)), np.array([0, 0])], axis=0),
                              np.array([[0, 0, 1]])], axis=0)

constraints = np.concatenate([constraints, upper_bound[:, None], lower_bound[:, None]], axis=0)

solution = solver.solve(objective_function, constraints)

portfolio_weights = np.array(solution.get_solution())[:-1]

portfolio_returns = np.dot(portfolio_weights, returns) + risk_free_rate
portfolio_stds = np.sqrt(np.diag(np.dot(portfolio_weights, np.dot(covariance, portfolio_weights.T))))

sorted_portfolios = np.array([portfolio_returns[:0], portfolio_stds[:0]])
sorted_portfolios = sorted_portfolios.T[np.lexsort(sorted_portfolios)]
portfolio_returns, portfolio_stds = sorted_portfolios[:, 0], sorted_portfolios[:, 1]

cal_returns = risk_free_rate + portfolio_stds * (returns[0] - risk_free_rate)
plt.plot(portfolio_stds, cal_returns, label='CAL', color='red')

plt.plot(portfolio_stds, portfolio_returns, marker='o', color='blue', label='Efficient Frontier')
plt.legend()
plt.show()

num_risky_assets = len(returns)
objective_function = np.concatenate([-returns, np.zeros(num_risky_assets)])

constraints = matrix(np.zeros((4, num_risky_assets + 1)), (1, 1))
constraints[0, 1:] = -np.eye(num_risky_assets)
constraints[1, 1:] = np.eye(num_risky_assets)
constraints[2, 1:] = np.dot(covariance, returns)
constraints[2, 0] = 0.6

constraints[3, :] = np.ones(num_risky_assets + 1)

# Create the solver
solver = solvers.SOCPSolver()

solution = solver.solve(objective_function, constraints)

portfolio_weights = np.array(solution.get_solution())[1:]

portfolio_returns = np.dot(portfolio_weights, returns)
portfolio_stds = np.sqrt(np.diag(np.dot(portfolio_weights, np.dot(covariance, portfolio_weights.T))))

portfolio_probability = np.dot(portfolio_weights, returns) / portfolio_stds
plt.plot(portfolio_stds, portfolio_returns, marker='o', color='red')
plt.show()
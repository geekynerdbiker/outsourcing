library(fpp3)
library(dplyr)
library(ggplot2)


#* 16 ----
# The population of Switzerland from 1960 to 2017 is in data set global_economy.

popu_switz <- global_economy %>%
  filter(Country == "Switzerland") %>%
  select(Year, Population) %>%
  mutate(Population = Population/1e6)


#** 16.a ----
# Produce a time plot of the data.

popu_switz %>% autoplot(Population)


#** 16.b ----
# You decide to fit the following model to the series: 
# y[t] = c + y[t−1] + ϕ[1](y[t−1] − y[t−2]) + ϕ[2](y[t−2] − y[t−3]) + ϕ[3](y[t−3] − y[t−4]) + ε[t]
# where yt is the Population in year t and εt is a white noise series.
# What sort of ARIMA model is this (i.e., what are p, d, and q)?

#   Model - ARIMA(3,1,0)


#** 16.c ----
# Explain why this model was chosen using the ACF and PACF of the differenced series.

popu_switz %>% gg_tsdisplay(Population %>% difference(), plot_type = "partial")

# ACF plot is sinusoidal and the PACF has a spike at lag 3 and none after.
# Therefore the model is appropriate.


#** 16.d ----
# The last five values of the series are given below.
# Year 	                    2013 	      2014 	      2015 	      2016 	      2017
# Population (millions)     8.09 	      8.19 	      8.28 	      8.37 	      8.47
# The estimated parameters are c=0.0053, ϕ1=1.64, ϕ2=−1.17, and ϕ3=0.45.
# Without using the forecast() function, calculate forecasts for the next three years (2018–2020).


# c=0.0053, ϕ1=1.64, ϕ2=−1.17, and ϕ3=0.45

# y[t]  = c + y[t−1] + ϕ[1](y[t−1] − y[t−2]) + ϕ[2](y[t−2] − y[t−3]) + ϕ[3](y[t−3] − y[t−4]) + ε[t]
#       = 0.0053 + y[t−1] + 1.64*(y[t−1] − y[t−2]) − 1.17(y[t−2] − y[t−3]) + 0.45(y[t−3] − y[t−4])

# y[2018] = 0.0053 + y[2017] + 1.64*(y[2017] − y[2016]) − 1.17(y[2016] − y[2015]) + 0.45(y[2015] − y[2014])
#         = 0.0053 + 8.47 + 1.64*(8.47 − 8.37) − 1.17(8.37 − 8.28) + 0.45(8.28 − 8.19)
#         = 8.5745

# Similarly 2019 = 8.6747, 2020 = 8.7670


#** 16.e ----
# Now fit the model in R and obtain the forecasts from the same model.
# How are they different from yours?
# Why?

popu_switz %>%
  model(ARIMA(Population ~ pdq(3,1,0))) %>%
  forecast(h = 3) %>%
  hilo() %>%
  select(Year, .mean, "95%")

# 2018 = 8.5585, 2019 = 8.6475, 2020 = 8.7317

# The forecasted numbers are slightly lower as the manually calculated numbers are using rounded off coefficients rather than the actual ones.
# Also, as the future forecasted numbers are based on the past forecasted values, the differences in the past values get compounded as the future values are calculated.

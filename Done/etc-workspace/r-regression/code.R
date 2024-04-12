library('dplyr')

# 전처리
Adata = data10[c('ind10_17', 'epq3002', 'epq3008', 'epq4002', 'epq4008', 'epq5002', 'epq5008', 'epq8031', 'fpq2001', 'fpq2015', 'fpq4002', 'fpq4030')]
Adata<-subset(Adata, ind10_17 >= 25 & ind10_17 <= 29 & ind10_17 != 27)
Adata = na.omit(Adata)

# 1 -> 4번
count(Adata, ind10_17)

# 2 -> 2번
tapply(Adata$epq3002, Adata$ind10_17, mean)['26']

# 3 -> 2번
tapply(Adata$epq5002, Adata$ind10_17, mean)['26']

# 4 -> 4번
# 5 -> 3번
Adata %>% group_by(ind10_17) %>% summarise(cor(epq4002, epq5002))

# 6 -> 3번
Adata %>% group_by(ind10_17) %>% summarise(mean(epq8031/epq4008))

# 7 -> 4번
Adata %>% group_by(ind10_17) %>% summarise(mean(epq4008/epq3008))

# 8 -> 2번, 3번
Adata['turnover'] = Adata$epq4008 / Adata$epq8031
Adata$turnover[is.infinite(Adata$turnover)] <- 0

Adata['parts'] = 0
Adata[Adata$ind10_17 == 26, 'parts'] = 1

Adata['devices'] = 0
Adata[Adata$ind10_17 == 28, 'devices'] = 1

Adata['etcs'] = 0
Adata[Adata$ind10_17 == 29, 'etcs'] = 1

Adata['permanent'] = Adata$epq4008 / Adata$epq3008

model <- lm(turnover ~ parts + devices + etcs + permanent, data = Adata)
p_value_threshold <- 0.1
significant_vars <- names(model$coefficients[model$coefficients < p_value_threshold])
summary(model)

# 9 -> 2번
tmp <- c(1, 0, 1, 0, .95)
sum(model$coefficients*tmp)

# 10 -> 2번
tmp <- c(1, 0, 0, 0, .95)
sum(model$coefficients*tmp)

# 11 -> 2번
tmp <- c(1, 1, 0, 0, .95)
sum(model$coefficients*tmp)

# 전처리 2
Adata <- rename(Adata, 매출액=fpq2001, 영업이익=fpq2015, 자산=fpq4002, 부채=fpq4030)

# 12 -> 3번
Adata %>% group_by(ind10_17) %>% summarise(mean(매출액/epq3008))

# 13 -> 3번
Adata %>% group_by(ind10_17) %>% summarise(mean(영업이익/epq3008))

# 14 -> 1번
Adata %>% group_by(ind10_17) %>% summarise(mean(영업이익/매출액))

# 15 -> 3번
Adata %>% group_by(ind10_17) %>% summarise(mean(매출액/자산))

# 16 -> 2번
Adata %>% group_by(ind10_17) %>% summarise(mean(부채/(자산-부채)*100))

# 17 -> 1번
# 코드 없음

# 18 -> 2번
Adata['ROE'] = 1/(Adata$영업이익 / Adata$매출액)*(Adata$매출액 / Adata$자산)*(Adata$부채 / ((Adata$자산)-(Adata$부채))*100)
Adata['영업이익률'] = Adata$영업이익 / Adata$매출액
Adata['자산회전율'] = Adata$매출액 / Adata$자산
Adata['부채비율'] = Adata$부채 / ((Adata$자산)-(Adata$부채))*100

model2 <- lm(ROE ~ 영업이익률 + 자산회전율 + 부채비율 + turnover + parts + devices + etcs, data = Adata)
p_value_threshold <- 0.1
significant_vars <- names(model2$coefficients[model$coefficients < p_value_threshold])
summary(model2)

# 19 -> 3번
# 코드 없음

# 20 -> 1번
tmp <- c(0, 0.5, 0.5, 0.5, 0.5, 1, 0, 0)
sum(model2$coefficients*tmp)

# 21 -> 4번
tmp <- c(1, 0.5, 0.5, 0.5, 0.5, 0, 0, 0)
sum(model2$coefficients*tmp)

# 22 -> 1번
# 코드 없음

# 23 -> 2번, 4번
Adata_elec<-subset(Adata, ind10_17 == 28)
model3 <- lm(ROE ~ 영업이익률 + 자산회전율 + 부채비율 + turnover, data = Adata_elec)
p_value_threshold <- 0.1
significant_vars <- names(model3$coefficients[model$coefficients < p_value_threshold])
summary(model3)

# 24 -> 3번
# 코드 없음

library(dplyr)
library(ggplot2)
library(readr)
library(haven)

# Q1
data <- read_rds("census_pop_2019.rds")
data <- data %>% 
  filter(MET2013 != 0)

avg <- data %>%
  summarise(ave_age = mean(AGE), pop=sum(PERWT))

# Q2
cities <- data %>%
  group_by(MET2013) %>%
  summarise(pop=sum(PERWT)) %>%
  filter(pop >= 1000000) %>%
  arrange(pop) %>%
  top_n(10)

# Q3
ages <- data %>%
  group_by(AGE) %>%
  summarise(pop=sum(PERWT)) %>%
  arrange(AGE)

ggplot(ages, aes(x=AGE, y=pop)) + 
  geom_point() +
  geom_line() +
  scale_x_discrete()

# Q4
ages <- subset(data, AGE >= 31 & AGE <= 55 & OCC != 0)
ages <-  transform(ages,
                   age_group = ifelse(AGE >= 31 & AGE <= 35, "31-35",
                                      ifelse(AGE >= 36 & AGE <= 40, "36-40",
                                             ifelse(AGE >= 41 & AGE <= 45, "41-45",
                                                    ifelse(AGE >= 46 & AGE <= 50, "46-50",
                                                           "51-55"
                                                    ))))
)

ages <- ages %>%
  group_by(age_group, OCC) %>%
  count(name="NUM") %>%
  arrange(age_group, desc(NUM))

result <- ages %>%
  filter(age_group == "31-35") %>% head(3)

result <- rbind(result, ages %>%
                  filter(age_group == "36-40") %>% head(3))

result <- rbind(result, ages %>%
                  filter(age_group == "41-45") %>% head(3))

result <- rbind(result, ages %>%
                  filter(age_group == "46-50") %>% head(3))

result <- rbind(result, ages %>%
                  filter(age_group == "51-55") %>% head(3))

print(result)

# Q5
ages <- subset(data, AGE >= 31 & AGE <= 55 & OCC != 0)
ages <-  transform(ages,
                   age_group = ifelse(AGE >= 31 & AGE <= 35, "31-35",
                                      ifelse(AGE >= 36 & AGE <= 40, "36-40",
                                             ifelse(AGE >= 41 & AGE <= 45, "41-45",
                                                    ifelse(AGE >= 46 & AGE <= 50, "46-50",
                                                           "51-55"
                                                    ))))
)


ages <- ages %>%
  group_by(age_group, INCTOT) %>%
  arrange(age_group, desc(INCTOT))

result <- ages %>%
  filter(age_group == "31-35") %>% head(3)

result <- rbind(result, ages %>%
                  filter(age_group == "36-40") %>% head(3))

result <- rbind(result, ages %>%
                  filter(age_group == "41-45") %>% head(3))

result <- rbind(result, ages %>%
                  filter(age_group == "46-50") %>% head(3))

result <- rbind(result, ages %>%
                  filter(age_group == "51-55") %>% head(3))

result <- result %>%
  select(age_group, OCC, INCTOT)

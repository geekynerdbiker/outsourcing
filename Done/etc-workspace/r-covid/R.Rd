library(COVID19)
library(dplyr)
library(tidyr)
library(ggplot2)

# 1
data = COVID19::covid19()
data_select = data %>% select(date, confirmed, deaths, recovered, tests, people_vaccinated, people_fully_vaccinated, vent, population, key_apple_mobility, key_gadm)
data_select

# 2
data_select_Macao = data_select %>% filter(key_apple_mobility == "Macao")
data_select_Macao

# 3
data_select = data_select %>% filter(!is.na(key_apple_mobility))
data_select = data_select %>% group_by(key_apple_mobility)
data_select = data_select %>% arrange(key_apple_mobility, date)
data_select = data_select %>% fill(confirmed, deaths, recovered, tests, people_vaccinated, people_fully_vaccinated, vent, population, .direction="up")
data_select

# 4
data_select = data_select %>% mutate(confirm_ratio = confirmed / population)
data_select = data_select %>% mutate(deaths_ratio = deaths / population)
data_select = data_select %>% mutate(vent_ratio = vent / population)
data_select = data_select %>% mutate(vacc_not_fully_ratio = people_vaccinated / population)
data_select = data_select %>% mutate(vacc_fully_ratio = people_fully_vaccinated / population)
data_select

# 5
data_select2 = data_select %>% filter(date == "2020-04-10")
data_select2 = data_select2 %>% select(key_apple_mobility, confirm_ratio, deaths_ratio)
data_select2 = data_select2 %>% arrange(desc(confirm_ratio))
data_select2

# 6
data_select2 = data_select %>% filter(date == "2020-04-10")
data_select2 = data_select2 %>% select(key_apple_mobility, vacc_fully_ratio, deaths_ratio)

ggplot(data=data_select2, aes(x=vacc_fully_ratio, y=deaths_ratio)) + geom_point(aes(color = key_apple_mobility), size = 10) + geom_smooth(method = 'lm', se = FALSE) + geom_text(aes(label=key_apple_mobility), size = 3) + theme(legend.position="none")

# 7
data_select = data_select %>% mutate(country = if_else(key_apple_mobility %in% c('Albania', 'Argentina', 'Brazil', 'Bulgaria', 'Cambodia', 'Chile', 'Colombia', 'Egypt', 'Estonia', 'Georgia', 'Greece', 'India', 'Indonesia', 'Latvia', 'Lithuania', 'Malaysia', 'Mexico', 'Philippines', 'Puerto Rico', 'Romania', 'Serbia', 'Slovakia', 'Slovenia', 'South Africa', 'Thailand', 'Turkey', 'Ukraine', 'Uruguay', 'Vietnam' 
), '선진국', '신흥국'))

data_select2 = data_select %>% filter(date == "2020-04-10")
data_select2 = data_select2 %>% select(key_apple_mobility, country, vacc_fully_ratio, deaths_ratio)


ggplot(data=data_select2, aes(x=vacc_fully_ratio, y=deaths_ratio)) + geom_point(aes(color = country), size = 10) + geom_text(aes(label=key_apple_mobility), size = 3)

# 8
ggplot(data=data_select, aes(roup=key_apple_mobility, x=date, y=vacc_fully_ratio)) + geom_line(aes(color = country))

# 9
data_select = data_select %>% mutate(korea = if_else(key_apple_mobility == 'Republic of Korea', 'Korea', 'Other'))

ggplot(data=data_select, aes(group=key_apple_mobility, x=date, y=deaths_ratio)) + geom_line(aes(color = korea)) + geom_text(data=data_select %>% group_by(key_apple_mobility) %>% filter(date==last(date)), aes(label=key_apple_mobility, x=date+0.5, y=deaths_ratio), size=2)

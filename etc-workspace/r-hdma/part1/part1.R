library(dplyr)
library(ggplot2)

# Q1
sample <-read.csv("hmda_2014_ca_all-records_codes.csv")
sample <- sample %>% 
  filter(loan_purpose == "1" & property_type == "1" & loan_amount_000s < 1000 & (action_taken %in% c("1") | action_taken %in% c("3")))
sample %>% arrange(desc(loan_amount_000s))
sample <- sample %>% mutate(ap=if_else(action_taken==1,1,0))

# Q2
sample = subset(sample, select=c(applicant_race_1, ap, loan_amount_000s, denial_reason_1, applicant_income_000s))
q2 = sample %>% 
  group_by(applicant_race_1) %>% 
  summarise(result = sum(ap), count=n())

# Q3
ggplot(data=q2) + geom_col(aes(x=applicant_race_1, result/count))

# Q4
# sample %>% filter(!is.na(denial_reason_1)) %>%  ==>   filter from data(sample) which selects rows only if denial_reason_1 is not NA value.
#  count(denial_reason_1) %>%  ==> return number of rows from denial_reason_1 filtered above 
#  mutate(share=n/sum(n)) %>%  ==> mutate new column name share with data n number of total rows divide by sum of variable n
#  ggplot(aes(denial_reason_1, share)) +  ==> create new plot graph frame x-axis value is denial_reason_1 and y-axis value is share
#  geom_bar(stat="identity") + scale_x_discrete(limits=c(1:9))  ==> add bar graph which based on y-axis height, ordered in column index 1 to 9

# Q5
 sample %>% filter(applicant_race_1 == "3") %>% # 3 is "Black or African American" value.
  count(denial_reason_1) %>%
  mutate(share=n/sum(n)) %>%
  ggplot(aes(denial_reason_1, share)) +
  geom_bar(stat="identity") + scale_x_discrete(limits=c(1:9))
 
 sample %>% filter(applicant_race_1 == "5") %>% # 5 is "White" value.
   count(denial_reason_1) %>%
   mutate(share=n/sum(n)) %>%
   ggplot(aes(denial_reason_1, share)) +
   geom_bar(stat="identity") + scale_x_discrete(limits=c(1:9))
 
# main difference is rate of value 3 of deinal_reason_1 is credit history




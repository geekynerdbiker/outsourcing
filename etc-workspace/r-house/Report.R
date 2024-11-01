library(dplyr)
library(ggplot2)
library(readxl)

df<-read_excel("2014년도 주거실태조사_공표자료(시군구 명칭 수정).xlsx")
df2 <- df %>% select(Stype, sido, dq1, q4, q6, q7, q9_1, q18, q23_13, q24_1, q24_2, q26_1, q26_2, dq2_1, q41, q41_1, dq2_3, q40_2, q40_3, q49_5, q48, q8_1, q47_a2_1, q23_9, q42_2, q47_a3_1)

df2 <- rename(df2, house_type = q4,
              house_location = q6,
              house_money = q7,
              no_house_time = q9_1,
              house_when = q18,
              friendly = q23_13,
              satisfy = q24_1,
              satisfy2 = q24_2,
              camera = q26_1,
              ring = q26_2,
              job = dq2_1,
              thinking = q41,
              thinking2 = q41_1,
              vihicle = dq2_3,
              school = dq1,
              money1 = q40_2,
              money2 = q40_3,
              earn = q49_5,
              poor = q48,
              when = q8_1,
              age = q47_a2_1,
              danger = q23_9, 
              want = q42_2,
              master = q47_a3_1) 

df2$sido<-ifelse(df2$sido==11,"서울특별시",ifelse(df2$sido==21,"부산광역시",ifelse(df2$sido==22,"대구광역시",ifelse(df2$sido==23,"인천광역시",ifelse(df2$sido==24,"광주광역시",ifelse(df2$sido==25,"대전광역시",ifelse(df2$sido==26,"울산광역시",ifelse(df2$sido==29,"세종특별자치시",ifelse(df2$sido==31,"경기도",ifelse(df2$sido==32,"강원도", ifelse(df2$sido==33,"충청북도",ifelse(df2$sido==34,"충청남도",ifelse(df2$sido==35,"전라북도",ifelse(df2$sido==36,"전라남도",ifelse(df2$sido==37,"경상북도",ifelse(df2$sido==38,"경상남도",ifelse(df2$sido==39,"제주도","기타")))))))))))))))))

df2$house_type <- ifelse(df2$house_type == 1, '일반단독주택', ifelse(df2$house_type == 2, "다가구단독주택", ifelse(df2$house_type == 3, '영업겸용단독주택', ifelse(df2$house_type == 4, '아파트',  ifelse(df2$house_type == 5, '연립주택', ifelse(df2$house_type == 6, '다세대주택', ifelse(df2$house_type == 7, "비거주용건물", ifelse(df2$house_type == 8, "오피스텔", ifelse(df2$house_type == 9, "판잣집", '기타')))))))))

table(df2$house_type)
qplot(df2$house_type)+coord_flip()

count_sido <- df2 %>% filter(df2$house_type == '아파트') %>%
  group_by(sido) %>%
  summarise(n = n()) %>%
  arrange(-n)

sido_satisfy <- df2 %>% filter(df2$house_type == '아파트') %>%
  group_by(sido) %>%
  summarise(satisfy_mean = mean(satisfy),
            satisfy_mean2 = mean(satisfy2)) %>%
  mutate(total = (satisfy_mean + satisfy_mean2) / 2) %>%
  arrange(-total)

ggplot(data = sido_satisfy, aes(x = sido, y = total)) + geom_line()

df2$school<-ifelse(df2$school==1,"초등학교 졸업 이하",
                   ifelse(df2$school==2,"중학교 졸업",
                          ifelse(df2$school==3,"고등학교 졸업","대학 졸업 이상")))
school_df <- df2 %>% 
  group_by(school, house_type) %>% 
  summarise(n = n()) %>%
  mutate(total = sum(n),
         pct = round(n / total * 100, 1))

ggplot(data = school_df, aes(x = house_type, y = pct, fill = school)) + geom_col() + coord_flip()

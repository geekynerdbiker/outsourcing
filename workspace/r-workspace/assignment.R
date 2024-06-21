# 필요한 패키지 설치 및 로드
if(!require(gutenbergr)) install.packages("gutenbergr")
if(!require(tidytext)) install.packages("tidytext")
if(!require(dplyr)) install.packages("dplyr")
if(!require(ggplot2)) install.packages("ggplot2")
if(!require(tidyr)) install.packages("tidyr")

# 이미지 저장 폴더 생성
if(!dir.exists("images")) dir.create("images")

library(gutenbergr)
library(tidytext)
library(dplyr)
library(ggplot2)
library(tidyr)

# 작품 텍스트 가져오기
book <- gutenberg_download(98)
head(book)

# 텍스트를 단어 단위로 나누기
book_words <- book %>%
  mutate(linenumber = row_number()) %>%
  unnest_tokens(word, text) %>%
  anti_join(stop_words)  # 불용어 제거

# 단어 빈도 계산
word_counts <- book_words %>%
  count(word, sort = TRUE)

head(word_counts)

# 주요 인물 리스트
characters <- c("charles", "lucie", "darnay", "carton")

# 주요 인물 등장 빈도 계산
character_counts <- book_words %>%
  filter(word %in% characters) %>%
  count(word, sort = TRUE)

# 시각화
ggplot(character_counts, aes(x = reorder(word, n), y = n)) +
  geom_bar(stat = "identity") +
  coord_flip() +
  labs(title = "주요 인물 등장 빈도", x = "인물", y = "빈도수")
ggsave("images/character_counts.png", plot = last_plot())

# 감정 사전 로드
bing <- get_sentiments("bing")

# 감정 분석
sentiment_analysis <- book_words %>%
  inner_join(bing, by = "word") %>%
  count(index = linenumber %/% 80, sentiment) %>%
  spread(sentiment, n, fill = 0) %>%
  mutate(sentiment = positive - negative)

# 시각화
ggplot(sentiment_analysis, aes(x = index, y = sentiment)) +
  geom_line() +
  labs(title = "감정 변화", x = "문단 인덱스", y = "감정 점수")
ggsave("images/sentiment_analysis.png", plot = last_plot())





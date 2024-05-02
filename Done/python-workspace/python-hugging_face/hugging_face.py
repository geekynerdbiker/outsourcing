# 허깅 페이스 트랜스포머의 파인튠 FinBert를 활용하여 아마존 뉴스의 재무 관련 기사 데이터를 감정 분석한 프로그램.
#
# 입력 데이터는 csv 파일로 각 column은 좌측부터 날짜, 제목, 설명, 소스의 형태로 저장되어 있고,
# 출력 형태는 긍정, 부정, 중립을 표현하는 데이터의 갯수들을 출력한다.
#
# 감정 클래스의 경우, 긍정, 부정, 중립 세가지 단계로 나뉘어진다. 텍스트를 tokenizing 후 input_ids와 attention_mask를 토대로 test output모델을
# 생성하여 예측값을 numpy 형태로 가져온 후에, 예측을 수행한다. 이후 소스 column 이후 설명의 감정을 분석한 결과를 담고있는 column이 추가된 형태의 데이터
# 프레임을 반환하고, 반환된 데이터를 순회하면서 각각의 감정 분석 결과에 해당하는 데이터가 몇개인지 세어 출력한다.
#
# * 프로그램의 테스트 및 실행속도를 위해 데이터의 50번째줄까지만 수행하였으며, 주석처리 후 전체 실행시 전체 데이터에 대한 결과를 알 수 있다.


import numpy as np
import pandas as pd
from transformers import BertTokenizer, TFBertForSequenceClassification
from tqdm import tqdm


def sentScore(dfNews):
    df = dfNews.copy()

    df['pos'] = 0
    df['neg'] = 0
    df['neut'] = 0
    df['pred'] = 0

    MAX_LEN = 160
    class_names = ['positive', 'negative', 'neutral']
    i = 0

    for sentence in tqdm(dfNews['title']):
        encoded_new = tokenizer.encode_plus(
            sentence,
            add_special_tokens=True,
            max_length=MAX_LEN,
            padding=True,
            return_attention_mask=True,
            return_tensors='tf',
        )

        input_idst = (encoded_new['input_ids'])
        attention_maskst = (encoded_new['attention_mask'])

        new_test_output = model(input_idst, token_type_ids=None,
                                attention_mask=attention_maskst)

        predicted = new_test_output[0].numpy()
        flat_predictions = np.concatenate(predicted, axis=0)
        new_predictions = np.argmax(flat_predictions).flatten()

        df.loc[i, 'pos'] = predicted[0][0]
        df.loc[i, 'neg'] = predicted[0][1]
        df.loc[i, 'neut'] = predicted[0][2]
        df.loc[i, 'pred'] = class_names[new_predictions[0]]
        i += 1

    return df


tokenizer = BertTokenizer.from_pretrained('ProsusAI/finbert', from_pt=True)
model = TFBertForSequenceClassification.from_pretrained("ProsusAI/finbert", from_pt=True)

dfNews = pd.read_csv('data/news.csv', index_col=0)
dfNews = dfNews[:50]

result = sentScore(dfNews)

pos, neg, neu = 0, 0, 0
for data in tqdm(result['pred']):
    if data == 'positive':
        pos += 1
    elif data == 'negative':
        neg += 1
    elif data == 'neutral':
        neu += 1

print(result)
print('Positive:', pos)
print('Negative:', neg)
print('Neutral:', neu)
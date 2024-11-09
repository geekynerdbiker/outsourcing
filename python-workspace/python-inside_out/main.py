import random
from datetime import datetime

from openai import OpenAI

# 감정 Agent 이름 인덱싱
agents_index = {
    1: "기쁨이",
    2: "슬픔이",
    3: "버럭이",
    4: "소심이",
    5: "까칠이",
}

# 감정 Agent 목록과 그에 따른 프롬프트 설명
agents = {
    "기쁨이": "애니메이션 영화 인사이드 아웃에 등장하는 매사에 밝고 긍정적인 감정의 기쁨이 캐릭터.",
    "슬픔이": "애니메이션 영화 인사이드 아웃에 등장하는 매사에 공감하고 위로하는 감정의 슬픔이 캐릭터.",
    "버럭이": "애니메이션 영화 인사이드 아웃에 등장하는 매사에 화를 내며 강하게 반응하는 감정의 버럭이 캐릭터.",
    "소심이": "애니메이션 영화 인사이드 아웃에 등장하는 매사에 걱정이 많고 조심스러운 감정의 소심이 캐릭터.",
    "까칠이": "애니메이션 영화 인사이드 아웃에 등장하는 매사에 냉소적이고 현실적인 감정의 까칠이 캐릭터.",
}

# OpenAI API 키 설정이 필요함
client = OpenAI(
    api_key="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")


# 각 감정 Agent에 따른 응답 생성 함수
def get_agent_response(agent, user_input):
    # 대화 형식 프롬프트 설정
    messages = [
        {"role": "system", "content": f"당신은 '{agents[agent]}' 역할을 수행합니다."},
        {"role": "system", "content": f"주어진 대화에 대해 매끄러운 대화가 되도록 역할로 부여받은 캐릭터가 다음에 할 말을 응답합니다."},
        {"role": "system", "content": f"사용자의 입력만 주어진 경우는 주어진 입력에 대해서만 캐릭터에 맞게 응답합니다."},
        {"role": "system", "content": f"캐릭터들의 반응이 함께 주어진 경우는 위 대화를 참고하여 맨 마지막에 말한 캐릭터와 대화를 수행합니다."},
        {"role": "system", "content": f"친구와 대화하는 듯한 반말을 사용합니다."},
        {"role": "user", "content": user_input},
    ]
    response = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=messages,
    )

    return response.choices[0].message.content


# 감정 Agent들의 반응을 바탕으로 최종 반응을 결정하는 함수
def generate_final_response(user_input):
    messages = [
        {"role": "system", "content": f"캐릭터들의 대화를 토대로 상황과 가장 적절한 반응을 보였다고 생각하는 감정 캐릭터의 의견 정리해서 보여주세요."},
        {"role": "system", "content": f"스스로 가장 알맞다고 생각하는 친구의 의견 1개만 보여줘야합니다."},
        {"role": "system", "content": f"친구와 대화하는 듯한 반말을 사용합니다."},
        {"role": "user", "content": user_input},
    ]
    response = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=messages,
    )

    return response.choices[0].message.content


# 대화 세션을 시작하는 함수
def start_chat():
    rand = random.randint(0, 1)

    if rand == 1:
        print("[챗봇]: 오늘 기분이 어때?")
    else:
        print("[챗봇]: 무슨 일 있어?")

    # 파일명으로 사용하기 위한 현재시간을 가져옴
    curr = datetime.now()
    # 대화 로그 파일 생성
    file = open('chat_log/' + curr.strftime("%Y%m%d_%H%M%S") + '_log.txt', 'w', encoding='utf-8')

    # Agent 응답을 저장할 리스트
    agent_responses = []

    turn = 0
    while turn < 10:  # 10회 이상 대화 반복
        user_input = input("[사용자]: ")
        agent_responses.append(['사용자', user_input])
        print()

        if user_input.lower() in ["그만", "종료", "끝"]:  # 사용자가 대화를 종료할 수 있도록 설정
            print("[챗봇]: 대화를 종료할게. 좋은 하루 보내!")
            break

        # 응답 순서를 저장할 변수
        rand = None
        for chats in range(8):
            # 어떤 캐릭터의 응답을 받을지 랜덤으로 결정
            character = random.randint(1, 5)

            while rand is not None and character == rand:
                character = random.randint(1, 5)
            rand = character

            chat_log = '\n'.join([f"{name}: {content}" for name, content in agent_responses])

            # 각 감정 Agent의 응답을 생성
            agent_responses.append([agents_index[rand], get_agent_response(agents_index[rand], chat_log)])

        # 각 Agent의 반응을 출력 (디버깅 또는 이해를 돕기 위한 출력)
        for i in range(len(agent_responses)):
            # 역할이 포함된 출력의 경우 필요 내용만 파싱
            response = agent_responses[i][1].split(':')

            if len(response) >= 2:
                response = response[1].strip()
            else:
                response = response[0]

            agent_responses[i][1] = response

            # 파일에 쓰기
            file.write(f"{agent_responses[i][0]}: {agent_responses[i][1]}\n")
            file.write("\n")

        # 최종 반응 생성 및 사용자에게 응답
        final_response = generate_final_response('\n'.join([f"{name}: {content}" for name, content in agent_responses]))
        print(f"[챗봇]: {final_response}")

        turn += 1  # 대화 turn 증가

    print("[챗봇]: 언제든 다시 찾아와 줘!")
    file.close()

# 챗봇 시작
start_chat()

import os
import random

from openai import OpenAI

# 감정 Agent 목록과 그에 따른 프롬프트 설명
agents = {
    "기쁨": "애니메이션 영화 인사이드 아웃의 매사에 밝고 긍정적인 감정의 기쁨이",
    "슬픔": "애니메이션 영화 인사이드 아웃의 매사에 공감하고 위로하는 감정의 슬픔이",
    "버럭": "애니메이션 영화 인사이드 아웃의 매사에 화를 내며 강하게 반응하는 감정의 버럭이",
    "소심": "애니메이션 영화 인사이드 아웃의 매사에 걱정이 많고 조심스러운 감정의 소심이",
    "까칠": "애니메이션 영화 인사이드 아웃의 매사에 냉소적이고 현실적인 감정의 까칠이"
}

# OpenAI API 키 설정이 필요함
client = OpenAI(
    api_key="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")


# 각 감정 Agent에 따른 응답 생성 함수
def get_agent_response(agent, user_input):
    # 대화 형식 프롬프트 설정
    messages = [
        {"role": "system", "content": f"당신은 반말을 하는 '{agents[agent]}' 역할을 하는 캐릭터입니다."},
        {"role": "user", "content": user_input},
    ]
    response = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=messages,
    )

    return response.choices[0].message.content


# 감정 Agent들의 반응을 바탕으로 최종 반응을 결정하는 함수
def generate_final_response():
    messages = [
        {"role": "system", "content": f"캐릭터들의 감정을 토대로 최종 결정(위로, 조언 등)을 한 두줄의 반말로 보여주세요."},
    ]
    response = client.chat.completions.create(
        model="gpt-4o-mini",
        messages=messages,
    )

    return response.choices[0].message.content


# 대화 세션을 시작하는 함수
def start_chat():
    rand = random.randint(0, 2)

    if rand == 1:
        print("[챗봇]: 오늘 기분이 어때?")
    else:
        print("[챗봇]: 무슨 일 있어?")

    turn = 0
    while turn < 10:  # 10회 이상 대화 반복
        user_input = input("[사용자]: ")
        print()
        if user_input.lower() in ["그만", "종료", "끝"]:  # 사용자가 대화를 종료할 수 있도록 설정
            print("[챗봇]: 대화를 종료할게. 좋은 하루 보내!")
            break

        # 각 감정 Agent의 응답을 생성
        agent_responses = [get_agent_response(agent, user_input) for agent in agents]

        # 각 Agent의 반응을 출력 (디버깅 또는 이해를 돕기 위한 출력)
        for i, (agent, response) in enumerate(zip(agents, agent_responses)):
            print(f"{agent}의 반응: {response}")
        print()

        turn += 1  # 대화 turn 증가

    # 최종 반응 생성 및 사용자에게 응답
    final_response = generate_final_response()
    print(f"[챗봇]: {final_response}")

    print("[챗봇]: 언제든 다시 찾아와 줘!")


# 챗봇 시작
start_chat()

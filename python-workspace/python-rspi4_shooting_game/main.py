from src.game_ready import GameReady
from src.game_status import GameStatus

# 무한 루프 실행
while True:
    # 게임 준비 상태 확인
    if GameStatus.getGameReady():
        # 게임 준비 상태를 False로 변경
        GameStatus.setGameReady(False)
        # GameReady 클래스 인스턴스 생성
        game_ready = GameReady()
        # GameReady 클래스 호출 (호출 가능한 객체로 실행)
        game_ready()

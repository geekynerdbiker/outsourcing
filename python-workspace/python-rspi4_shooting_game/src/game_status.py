class GameStatus:
    # 게임 상태 클래스
    __game_ready = True  # 게임 준비 상태 초기값
    __game_play = False  # 게임 진행 상태 초기값
    __game_text = ''     # 게임 텍스트 초기값

    __player_win = False  # 플레이어 승리 상태 초기값

    @classmethod
    def getGameReady(cls):
        # 게임 준비 상태 반환
        return cls.__game_ready

    @classmethod
    def setGameReady(cls, ready):
        # 게임 준비 상태 설정
        cls.__game_ready = ready

    @classmethod
    def getGamePlay(cls):
        # 게임 진행 상태 반환
        return cls.__game_play

    @classmethod
    def setGamePlay(cls, play):
        # 게임 진행 상태 설정
        cls.__game_play = play

    @classmethod
    def getGameText(cls):
        # 게임 텍스트 반환
        return cls.__game_text

    @classmethod
    def setPlayerWin(cls, win):
        # 플레이어 승리 상태 설정
        cls.__player_win = win

    @classmethod
    def start(cls):
        # 게임 시작
        cls.__game_play = True
        cls.__game_text = ''  # 게임 텍스트 초기화

    @classmethod
    def end(cls):
        # 게임 종료
        cls.__game_play = False

        # 플레이어 승리 여부에 따라 텍스트 설정
        if cls.__player_win:
            cls.__game_text = ' You Win!'
        else:
            cls.__game_text = 'GameOver!'

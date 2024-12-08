from settings import *
from src.object_controller import ObjectController
from src.game_status import GameStatus
from src.button import Button
from src.game_objects import Player, Enemy, Missile, BoomEffect, Item
import random, time


class GameStarter:
    def __init__(self, level, background):
        # 초기화 함수
        self.__level = level          # 게임 레벨 설정
        self.__background = background  # 배경 이미지 설정
        self.__step = 0               # 현재 단계 초기화
        self.__boss = False           # 보스 여부 초기화
        GameStatus.setGamePlay(True)  # 게임 플레이 상태 활성화

    def __next_step(self):
        # 다음 단계로 이동
        self.__step = self.__step + 1
        self.__set_enemy()

    def __set_enemy(self):
        # 적 설정
        if self.__step == 0:
            self.__name = 'enemy1'
            self.__spawn_time = 3
            self.__spawn_number = 5
            self.__direction = 'random'
        if self.__step == 1:
            self.__name = 'enemy2'
            self.__spawn_time = 0.7
            self.__spawn_number = 3
            self.__direction = 'left'
        if self.__step == 2:
            self.__name = 'enemy2-2'
            self.__spawn_time = 0.7
            self.__spawn_number = 3
            self.__direction = 'right'
        if self.__step == 3:
            self.__name = 'enemy2'
            self.__spawn_time = 0.6
            self.__spawn_number = 5
            self.__direction = 'left'
        if self.__step == 4:
            self.__name = 'enemy2-2'
            self.__spawn_time = 0.6
            self.__spawn_number = 5
            self.__direction = 'right'
        if self.__step == 5:
            self.__name = 'enemy3'
            self.__spawn_time = 10
            self.__spawn_number = 1
            self.__direction = 'middle'
        if self.__step == 6:
            self.__name = 'boss'
            self.__spawn_time = 20
            self.__spawn_number = 1
            self.__direction = 'middle'

        # 적의 초기 위치 설정
        self.__position = (random.randint(1, SCREEN_WIDTH - 1), 0)
        if self.__direction == 'left':
            self.__position = (1, 0)
        elif self.__direction == 'right':
            self.__position = (SCREEN_WIDTH - 1, 0)
        elif self.__direction == 'middle':
            self.__position = (SCREEN_WIDTH // 2, 0)

    def __call__(self):
        # 게임 실행
        GameStatus.start()             # 게임 시작 상태 설정
        ObjectController.reset()       # 객체 컨트롤러 초기화
        player = Player(START_POINT)   # 플레이어 생성
        button = Button()              # 버튼 초기화
        self.__set_enemy()             # 적 설정

        prev_time = time.time()        # 이전 시간 초기화
        number = 0                     # 적 생성 카운트 초기화
        paused = False                 # 일시 정지 상태 플래그

        items = []

        while True:
            # 버튼 b 입력에 따른 일시 정지 및 해제
            if button.b:
                paused = not paused    # paused 상태를 토글
                time.sleep(0.2)        # 버튼의 중복 입력 방지 (간단한 디바운스)

            # 게임이 일시 정지된 경우
            if paused:
                DISPLAY.text("Paused", SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2)  # 화면에 'Paused' 표시
                continue  # 게임 로직 정지

        
            # 버튼 입력에 따른 플레이어 이동
            if button.left and player.obj_coord[0] > 5:
                player.move('L')
            elif button.right and player.obj_coord[0] < SCREEN_WIDTH - 5:
                player.move('R')
            elif button.up and player.obj_coord[1] > 5:
                player.move('U')
            elif button.down and player.obj_coord[1] < SCREEN_HEIGHT - 10:
                player.move('D')

            # 버튼 A 입력에 따른 플레이어 발사
            if button.a:
                player.shoot()

            
                
            # 배경 이미지 출력
            DISPLAY.image(self.__background())

            if GameStatus.getGamePlay():
                # 적 스폰 처리
                if time.time() - prev_time > self.__spawn_time:
                    if self.__spawn_number > number:
                        if self.__direction == 'random':
                            self.__position = (random.randint(2, SCREEN_WIDTH - 2), 0)
                        if self.__name == 'boss':
                            self.__boss = True
                        Enemy(self.__position, self.__name)
                        number += 1
                        prev_time = time.time()
                        
                        # 아이템 생성 조건
                        if random.random() < 0.1:  # 10% 확률로 아이템 생성
                            Item(self.__position, self.__name)
                    else:
                        number = 0
                        self.__next_step()

                # 적 객체 상태 확인
                enemy = ObjectController.getEnemyObjects()
                if player.hp <= 0 or (self.__boss and len(list(enemy[0])) <= 0):
                    GameStatus.setPlayerWin(False) if player.hp <= 0 else GameStatus.setPlayerWin(True)
                    GameStatus.end()
                    prev_time = time.time()

            # 게임 종료 후 대기 처리
            if not GameStatus.getGamePlay() and time.time() - prev_time > 3:
                self.__display_game_over_screen()
                GameStatus.setGameReady(True)
                GameStatus.setGamePlay(False)
                break

    # 게임 종료 화면 표시
    def __display_game_over_screen(self): 
        while True:
            # 배경 색상 또는 이미지 표시
            DISPLAY.clear(color="black")
            
            # 승리 또는 패배 메시지 표시
            if GameStatus.getPlayerWin():
                DISPLAY.text("You Win!", SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 - 50, color="green", size=30)
            else:
                DISPLAY.text("Game Over", SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 - 50, color="red", size=30)
            
            DISPLAY.text("Press A to Restart", SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 20, color="white", size=20)
            DISPLAY.text("Press B to Quit", SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2 + 50, color="white", size=20)
            
            # 버튼 입력 처리
            button = Button()
            if button.a:  # R키로 다시 시작
                GameStatus.setGameReady(True)
                GameStatus.setGamePlay(False)
                return  # 종료 화면 루프를 종료
            elif button.b:  # Q키로 종료
                exit()  # 프로그램 종료
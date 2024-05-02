#!/usr/bin/env python
# coding: utf-8

import tkinter as tk
import time
import random


class GameObject:
    # tkinter의 coords, delete, move 함수 참고
    # canvas와 item 초기화
    def __init__(self, canvas, item):
        self.canvas = canvas
        self.item = item
        pass

    # canvas에서 item의 위치값 리턴    
    def get_position(self):
        return self.canvas.coords(self.item)

        # canvas 내에서 item 삭제

    def delete(self):
        self.canvas.delete(self.item)
        pass

    # canvas 내에서 item을 (x, y)만큼 이동
    def move(self, x, y):
        self.canvas.move(self.item, x, y)
        pass


class Quadrangle(GameObject):
    # 부모 클래스 초기화 함수로 canvas와 item 정의(item은 사각형 전달; tkinter의 create_rectangle() 참고)
    # self.x, self.y, self.width, self.height, self.color 정의
    def __init__(self, canvas, x, y, width, height, color):
        item = canvas.create_rectangle(x, y, x + width, y + height, fill=color)
        super().__init__(canvas, item)

        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.color = color
        pass


class Player(Quadrangle):
    # 부모 클래스 초기화 함수를 이용하여 Player 초기화 (문제 출제 내용의 width, height, color 참고)
    def __init__(self, canvas, x, y):
        # 추가 작성
        super().__init__(canvas, x, y, 50, 50, 'blue')
        self.state = 0
        self.is_jumping = False
        self.jump_direction = 'UP'
        pass

    # target object의 position을 받아 Player와의 충돌 여부에 관해 리턴하는 함수 (AABB Collision Detection 참고)
    def check_collision(self, tPos):
        pos = self.get_position()
        if len(tPos) == 0:
            return False
        return pos[0] <= tPos[2] and pos[2] >= tPos[0] and pos[1] <= tPos[3] and pos[3] >= tPos[1]


class Terrain(Quadrangle):
    # 부모 클래스 초기화 함수를 이용하여 Terrain 초기화 (문제 출제 내용의 width, height, color 참고)
    def __init__(self, canvas, x, y):
        super().__init__(canvas, x, y, 250, 200, 'green')
        pass


class Circle(GameObject):
    # 부모 클래스 초기화 함수로 canvas와 item 정의(item은 사각형 전달; tkinter의 create_oval() 참고)
    # self.x, self.y, self.radius, self.color 정의
    def __init__(self, canvas, x, y, radius, color):
        item = canvas.create_oval(x, y, x + radius, y + radius, fill=color)
        super().__init__(canvas, item)
        self.x = x
        self.y = y
        self.radius = radius
        self.color = color
        pass


class Coin(Circle):
    # 부모 클래스 초기화 함수를 이용하여 Coin 초기화 (문제 출제 내용의 radius, color 참고)
    def __init__(self, canvas, x, y):
        super().__init__(canvas, x, y, 10, 'yellow')
        pass


class FireBall(Circle):
    # 부모 클래스 초기화 함수를 이용하여 FireBall 초기화 (문제 출제 내용의 radius, color 참고)
    def __init__(self, canvas, x, y):
        super().__init__(canvas, x, y, 15, 'red')
        pass


# tk.Frame 상속
class Game(tk.Frame):
    # 흰 배경의 기본창 그리기
    def __init__(self, master, width, height):
        super(Game, self).__init__(master)
        self.width = width
        self.height = height
        self.canvas = tk.Canvas(self, bg='white', width=self.width, height=self.height)
        self.canvas.pack(fill="both", expand=True)
        self.pack()

        self.setup_game()

    # 게임 기본 맵 및 기능 세팅
    def setup_game(self):
        self.gameInit()
        self.canvas.bind('<space>', lambda _: self.update_jumping())  # space key 입력시 self.update_jumping() 호출
        self.canvas.focus_set()
        self.game_loop()

    # 게임 맵 및 파라미터 정의
    def gameInit(self):
        self.end_font = ('Helvetica', '40')  # END text의 font로 이용
        self.score_font = ('Helvetica', '15')  # Score text의 font로 이용

        self.score = 0
        self.mapSpeed = -5
        self.jumpSpeed = -3  # jump 스피드

        self.terrains = []
        self.fireballs = []
        self.coins = []

        self.player = Player(self.canvas, 200, 450)  # 주어진대로 그릴 시 안맞아서 약간 조정

        # 작성 필요
        # 초기맵 만들기 (fireballs, coins, terrains, score_text, end_text(빈 텍스트 입력) 오브젝트 생성)
        # score text(text="SCORE: 0"), end text(text=""; empty text) 생성 출력 변수 초기화
        for i in range(7):
            self.terrains.append(Terrain(self.canvas, i * 200, 500))

        self.fireballs.append(FireBall(self.canvas, 1200, self.random_posY()))
        self.coins.append(Coin(self.canvas, 1200, self.random_posY()))

        self.score_text = self.canvas.create_text(1000, 100, text="SCORE: 0", font=self.score_font)
        self.end_text = self.canvas.create_text(600, 350, text="", font=self.end_font)

    def game_loop(self):
        # 게임 종료 상태가 아니면 게임 동작
        if (self.player.state != 2):
            self.gameSystem()
            self.after(10, self.game_loop)  # 10ms(초당 100프레임)마다 game_loop() 실행

    # 전체적인 게임 동작
    def gameSystem(self):
        self.move_map()
        self.manage_map()
        self.check_gameState()

        # 각 오브젝트들의 동작 기능

    def manage_map(self):
        self.manage_terrains()
        self.manage_fireballs()
        self.manage_coins()

    # terrain의 동작 내용
    def manage_terrains(self):
        t1 = self.terrains[0]
        t2 = self.terrains[-1]

        if t1.x < 0:
            self.terrains.remove(t1)
            self.terrains.append(Terrain(self.canvas, t2.x + 200, 500))
        pass

    # fireball의 동작 내용
    def manage_fireballs(self):
        f1 = self.fireballs[0]
        f2 = self.fireballs[-1]

        if f1.x + f1.radius < 0:
            self.fireballs.remove(f1)
            self.fireballs.append(FireBall(self.canvas, 1200, self.random_posY()))

        if self.player.check_collision(self.fireballs[0].get_position()) is True:
            self.player.state = 2
        pass

    # coin의 동작 내용
    def manage_coins(self):
        c = self.coins[0]

        if c.x + c.radius < 0:
            c.delete()
            self.coins.remove(c)
            self.coins.append(Coin(self.canvas, 1200, self.random_posY()))
        if self.player.check_collision(c.get_position()) is True:
            print(c.get_position())
            self.score += 1
            self.canvas.itemconfig(self.score_text, text="SCORE: " + str(self.score))
            c.delete()
            self.coins.remove(c)
            self.coins.append(Coin(self.canvas, 1200, self.random_posY()))


        pass

    # 1/2 확률로 2가지 중 하나의 y값 리턴
    def random_posY(self):
        num = random.randint(0, 1)
        if (num == 0):
            return 400
        else:
            return 450

    # jumping, gameover 상태에 따른 동작
    def check_gameState(self):
        if (self.player.state == 2):  # gameover 상태
            self.canvas.itemconfig(self.end_text, text="END")
        elif (self.player.state == 1):  # jumping 상태
            self.jumping()

            # space 입력시 변수 초기화

    def update_jumping(self):
        self.player.state = 1
        pass

    # 점프 구현
    def jumping(self):
        position = self.player.get_position()

        if self.player.is_jumping is False and self.player.jump_direction == 'UP':
            self.player.is_jumping = True
        if self.player.is_jumping is True and self.player.jump_direction == 'DOWN' and self.player.y == position[1]:
            self.player.is_jumping = False
            self.player.jump_direction = 'UP'
            self.player.state = 0

        if self.player.y - position[1] < 100:
            if self.player.is_jumping is True and self.player.jump_direction == 'UP':
                self.player.move(0, self.jumpSpeed)
            elif self.player.is_jumping is True and self.player.jump_direction == 'DOWN':
                self.player.move(0, self.jumpSpeed * -1)
        else:
            self.player.jump_direction = 'DOWN'
            self.player.move(0, self.jumpSpeed * -1)
        pass

    # terrains, coins는 mapSpeed의 속도로 이동하며, fireball은 mapSpeed의 2배 속도로 이동함
    def move_map(self):
        for t in self.terrains:
            t.x += self.mapSpeed
            t.move(self.mapSpeed, 0)

        for f in self.fireballs:
            f.x += self.mapSpeed * 2
            f.move(self.mapSpeed * 2, 0)

        for c in self.coins:
            c.x += self.mapSpeed
            c.move(self.mapSpeed, 0)

        pass


if __name__ == '__main__':
    root = tk.Tk()
    root.title('Assignment4_ID')
    game = Game(root, 1200, 700)
    game.mainloop()

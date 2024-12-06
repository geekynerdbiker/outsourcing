from settings import *
from src.background import *
from PIL import Image, ImageDraw, ImageFont
from colorsys import hsv_to_rgb
from src.game_starter import GameStarter
from src.button import Button


class GameReady:
    def __init__(self):
        # 초기화 함수
        self.__width = SCREEN_WIDTH              # 화면 너비 설정
        self.__height = SCREEN_HEIGHT            # 화면 높이 설정
        self.__image = Image.new("RGB", (self.__width, self.__height))  # 이미지 생성
        self.__draw = ImageDraw.Draw(self.__image)  # 이미지 그리기 객체 생성
        self.__fnt = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 30)  # 폰트 설정
        self.__background = list(BACKGROUND_INFO)  # 배경 정보 리스트화
        self.__background_index = 0             # 배경 인덱스 초기화
        self.__game_start = True                # 게임 시작 여부 초기화
        self.__level = 1                        # 게임 레벨 초기화

    def __set_text(self, position, txt):
        # 텍스트 설정
        self.__draw.text(position, txt, font=self.__fnt, fill=(255, 255, 255))

    def __set_menu(self, up):
        # 메뉴 설정
        rcolor = tuple(int(x * 255) for x in hsv_to_rgb(random.random(), 1, 1))  # 랜덤 색상 생성
        if up:
            # 위쪽 선택 메뉴 색상 설정
            self.__draw.rectangle((0, 0, self.__width, self.__height // 2), outline=0, fill=rcolor)
            self.__draw.rectangle((0, self.__height // 2 + 1, self.__width, self.__height), outline=0,
                                  fill=(51, 51, 51))
        else:
            # 아래쪽 선택 메뉴 색상 설정
            self.__draw.rectangle((0, 0, self.__width, self.__height // 2), outline=0, fill=(51, 51, 51))
            self.__draw.rectangle((0, self.__height // 2 + 1, self.__width, self.__height), outline=0, fill=rcolor)
        
        # 메뉴 내부 사각형 설정
        self.__draw.rectangle((10, 10, self.__width - 10, self.__height // 2 - 10), outline=0, fill=(102, 102, 153))
        self.__draw.rectangle((10, self.__height // 2 + 11, self.__width - 10, self.__height - 10), outline=0,
                              fill=(102, 204, 204))
        
        # 텍스트 추가
        self.__set_text((20, 20), 'Game Start')  # 게임 시작 텍스트
        self.__set_text((20, self.__height // 2 + 21), 'Exit')  # 종료 텍스트

    def __call__(self):
        # 객체 호출 시 실행
        button = Button()  # 버튼 객체 생성

        while True:
            # 메뉴 표시
            self.__set_menu(self.__game_start)
            DISPLAY.image(self.__image)  # 화면에 이미지 출력

            # 버튼 입력 처리
            if button.up:
                self.__game_start = True  # 위쪽 메뉴 선택
            if button.down:
                self.__game_start = False  # 아래쪽 메뉴 선택
            if button.b:
                if not self.__game_start:
                    exit(0)  # 종료 선택 시 프로그램 종료
                self.gameStart(self.__level, self.__background[0])  # 게임 시작 호출
                break

    def gameStart(self, level, background):
        # 게임 시작
        game_starter = GameStarter(level, Background(background))  # GameStarter 객체 생성
        game_starter()  # 게임 실행

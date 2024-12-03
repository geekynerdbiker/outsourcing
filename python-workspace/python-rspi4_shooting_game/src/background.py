from src.object_controller import ObjectController
from src.game_status import GameStatus
from colorsys import hsv_to_rgb
from PIL import Image, ImageDraw, ImageFont
from settings import *
import random, os

# 배경 정보 설정
BACKGROUND_INFO = {
    'background': {
        'path': os.path.join(IMAGE_PATH, 'background.png'),  # 배경 이미지 경로
        'width': 240,  # 배경 너비
        'height': 240,  # 배경 높이
        'name': 'background'  # 배경 이름
    }
}


class Background:
    def __init__(self, name='background'):
        # 초기화 함수
        self.__name = name
        self.__width = SCREEN_WIDTH
        self.__height = SCREEN_HEIGHT
        self.__scroll_speed = 8  # 스크롤 속도 설정
        self.__crop_point = SCREEN_HEIGHT  # 크롭 시작 지점 초기화
        self.__image = Image.open(BACKGROUND_INFO[self.name]['path']).resize((self.width, self.height))  # 배경 이미지 로드
        self.__fnt = ImageFont.truetype("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 30)  # 폰트 설정

    @property
    def name(self):
        # 배경 이름 반환
        return self.__name

    @property
    def width(self):
        # 배경 너비 반환
        return self.__width

    @property
    def height(self):
        # 배경 높이 반환
        return self.__height

    def __get_image(self):
        # 스크롤된 배경 이미지 생성
        if self.__crop_point - self.__scroll_speed <= 0:
            self.__crop_point = self.height
        else:
            self.__crop_point -= self.__scroll_speed

        image = Image.open(BACKGROUND_INFO[self.name]['path']).resize((self.width, self.height))
        empty_image = Image.new('RGBA', (self.width, self.height))
        cropped_image1 = image.crop((0, self.__crop_point, self.width, self.height))
        cropped_image2 = image.crop((0, 0, self.width, self.__crop_point))
        empty_image.paste(cropped_image1, (0, 0))
        empty_image.paste(cropped_image2, (0, self.height - self.__crop_point))
        self.__image = empty_image
        return self.__image

    def __set_text(self, background, text):
        # 배경에 텍스트 추가
        draw = ImageDraw.Draw(background)
        rcolor = tuple(int(x * 255) for x in hsv_to_rgb(random.random(), 1, 1))  # 랜덤 색상 생성
        draw.text((38, 150), text, font=self.__fnt, fill=rcolor)

    def __call__(self):
        # 배경 생성 및 업데이트
        ObjectController.renew()
        background_image = self.__get_image()

        # 플레이어 객체와 미사일 표시
        objects = ObjectController.getPlayerObjects()
        player, player_missiles = objects
        for info in player.items():
            player_object = info[1]
            new_image = Image.alpha_composite(background_image.crop(player_object.image_coord), player_object.image)
            background_image.paste(new_image, (player_object.image_coord[0], player_object.image_coord[1]))
        for info in player_missiles.items():
            player_missile_object = info[1]
            new_image = Image.alpha_composite(background_image.crop(player_missile_object.image_coord),
                                              player_missile_object.image)
            background_image.paste(new_image,
                                   (player_missile_object.image_coord[0], player_missile_object.image_coord[1]))

        # 적 객체와 미사일 표시
        objects = ObjectController.getEnemyObjects()
        enemy, enemy_missiles = objects
        for info in enemy.items():
            enemy_object = info[1]
            new_image = Image.alpha_composite(background_image.crop(enemy_object.image_coord), enemy_object.image)
            background_image.paste(new_image, (enemy_object.image_coord[0], enemy_object.image_coord[1]))
        for info in enemy_missiles.items():
            enemy_missile_object = info[1]
            new_image = Image.alpha_composite(background_image.crop(enemy_missile_object.image_coord),
                                              enemy_missile_object.image)
            background_image.paste(new_image,
                                   (enemy_missile_object.image_coord[0], enemy_missile_object.image_coord[1]))

        # 효과 객체 표시
        effect_objects = ObjectController.getEffectObjects()
        for info in effect_objects.items():
            effect_object = info[1]
            new_image = Image.alpha_composite(background_image.crop(effect_object.image_coord), effect_object.image)
            background_image.paste(new_image, (effect_object.image_coord[0], effect_object.image_coord[1]))

        # 게임 상태 텍스트 추가
        game_text = GameStatus.getGameText()
        self.__set_text(background_image, game_text)

        return background_image

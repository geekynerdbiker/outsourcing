from settings import *


class Button:
    def __init__(self):
        # 버튼 핀 초기화
        self.__left = BUTTON_L  # 왼쪽 버튼 핀
        self.__right = BUTTON_R  # 오른쪽 버튼 핀
        self.__up = BUTTON_U  # 위쪽 버튼 핀
        self.__down = BUTTON_D  # 아래쪽 버튼 핀
        self.__a = BUTTON_A  # A 버튼 핀
        self.__b = BUTTON_B  # B 버튼 핀
        self.__c = BUTTON_C  # C 버튼 핀

    @property
    def left(self):
        # 왼쪽 버튼 상태 반환 (눌림 여부)
        return False if self.__left.value else True

    @property
    def right(self):
        # 오른쪽 버튼 상태 반환 (눌림 여부)
        return False if self.__right.value else True

    @property
    def up(self):
        # 위쪽 버튼 상태 반환 (눌림 여부)
        return False if self.__up.value else True

    @property
    def down(self):
        # 아래쪽 버튼 상태 반환 (눌림 여부)
        return False if self.__down.value else True

    @property
    def a(self):
        # A 버튼 상태 반환 (눌림 여부)
        return False if self.__a.value else True

    @property
    def b(self):
        # B 버튼 상태 반환 (눌림 여부)
        return False if self.__b.value else True

    @property
    def c(self):
        # C 버튼 상태 반환 (눌림 여부)
        return False if self.__c.value else True

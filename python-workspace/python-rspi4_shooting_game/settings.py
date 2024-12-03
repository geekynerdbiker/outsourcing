import adafruit_rgb_display.st7789 as st7789
from digitalio import DigitalInOut, Direction
import board

# CS 핀 설정 (칩 선택)
PIN_CS = DigitalInOut(board.CE0)
# DC 핀 설정 (데이터/명령 신호)
PIN_DC = DigitalInOut(board.D25)
# 리셋 핀 설정
PIN_RESET = DigitalInOut(board.D24)
# SPI 통신 속도 설정
BAUDRATE = 24000000

# SPI 인터페이스 초기화
SPI = board.SPI()
# ST7789 디스플레이 초기화
DISPLAY = st7789.ST7789(
    SPI,
    height=240,           # 디스플레이 높이 설정
    y_offset=80,          # 디스플레이 Y 오프셋 설정
    rotation=180,         # 화면 회전 각도 설정
    cs=PIN_CS,            # CS 핀 연결
    dc=PIN_DC,            # DC 핀 연결
    rst=PIN_RESET,        # 리셋 핀 연결
    baudrate=BAUDRATE,    # 통신 속도 설정
)

# 버튼 A 핀 설정 및 방향 입력으로 설정
BUTTON_A = DigitalInOut(board.D5)
BUTTON_A.direction = Direction.INPUT

# 버튼 B 핀 설정 및 방향 입력으로 설정
BUTTON_B = DigitalInOut(board.D6)
BUTTON_B.direction = Direction.INPUT

# 버튼 L 핀 설정 및 방향 입력으로 설정
BUTTON_L = DigitalInOut(board.D27)
BUTTON_L.direction = Direction.INPUT

# 버튼 R 핀 설정 및 방향 입력으로 설정
BUTTON_R = DigitalInOut(board.D23)
BUTTON_R.direction = Direction.INPUT

# 버튼 U 핀 설정 및 방향 입력으로 설정
BUTTON_U = DigitalInOut(board.D17)
BUTTON_U.direction = Direction.INPUT

# 버튼 D 핀 설정 및 방향 입력으로 설정
BUTTON_D = DigitalInOut(board.D22)
BUTTON_D.direction = Direction.INPUT

# 버튼 C 핀 설정 및 방향 입력으로 설정
BUTTON_C = DigitalInOut(board.D4)
BUTTON_C.direction = Direction.INPUT

# 백라이트 핀 설정 및 출력으로 전환
BACKLIGHT = DigitalInOut(board.D26)
BACKLIGHT.switch_to_output()
BACKLIGHT.value = True  # 백라이트를 켬

# 화면의 너비와 높이를 저장
SCREEN_WIDTH = DISPLAY.width
SCREEN_HEIGHT = DISPLAY.height
# 시작 좌표 설정
START_POINT = (SCREEN_WIDTH // 2, 4 * (SCREEN_HEIGHT // 5))

# 이미지 경로 설정
IMAGE_PATH = 'images'

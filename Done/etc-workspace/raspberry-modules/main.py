import RPi.GPIO as GPIO
import picamera.PiCamera as PiCamera
import time

camera = PiCamera()  # 카메라 초기화
camera.rotation = 180  # 180도 회전. 카메라 방향에 따라 주석 처리 가능

GPIO.setwarnings(False)  # 불필요한 warning 제거
GPIO.setmode(GPIO.BCM)  # GPIO핀의 번호 모드 설정

GPIO.setup(18, GPIO.OUT)  # 출력: DF9GMS, 18핀
GPIO.setup(23, GPIO.IN)  # 입력: SR501, 23핀
GPIO.setup(24, GPIO.OUT)  # 출력: 부저, 24핀

P = GPIO.PWM(24, 100)  # PWM 인스턴스 P를 만들고 GPIO 18번을 PWM 핀으로 설정, 주파수 = 100Hz
P2 = GPIO.PWM(18, 50)  # 서보모터 동작 주파수

try:
    time.sleep(2)  # 센서 안정화 시간
    while True:
        if GPIO.input(23):  # 센서가 모션을 감지
            P.ChangeFrequency(330)  # 주파수 임의로 변경
            time.sleep(0.5)  # 0.5초간 부저 작동
            P2.ChangeDutyCycle(7.5)  # 서보모터를 90도로 회전
            time.sleep(1)  # 1초동안 이동
            P2.ChangeDutyCycle(3.0)  # 서보모터를 0도로 회전
            time.sleep(1)  # 1초동안 이동
            camera.start_preview()  # 카메라 작동 시작
            time.sleep(5)  # 중복 감지 회피용 딜레이
        elif not GPIO.input(23):
            P.ChangeFrequency(100)  # PWM 인스턴스 재생성
            P2.ChangeDutyCycle(3.0)  # 서보모터를 0도로 회전
            camera.stop_preview()  # 카메라 작동 종료
            time.sleep(1)  # 1초동안 이동
        time.sleep(0.1)  # 반복 딜레이, 감지 딜레이보다 항상 낮아야 함


except KeyboardInterrupt:  # 키보드 Ctrl+C 눌렀을때 예외발생
    pass  # 무한반복을 빠져나와 아래의 코드를 실행 p.stop() # PWM을 종료

GPIO.cleanup()  # GPIO 설정을 초기화

import cv2
import datetime

try:
    video_dev = cv2.VideoCapture(0)

    while True:
        ret, frame = video_dev.read()
        if video_dev is None:
            print('Load failure')
            exit()
        cv2.imshow('Video Screen', frame)

        if cv2.waitKey(0) == ord('q'):
            break

        elif cv2.waitKey(0) == ord('s'):
            file = datetime.datetime.now().strftime("%Y%m%d_%H%M%S%f") + '.jpg'
            cv2.imwrite(file, frame)
            print(file, ' saved')

    video_dev.release()
    cv2.destroyAllWindows()

except KeyboardInterrupt:
    print('User interruption')


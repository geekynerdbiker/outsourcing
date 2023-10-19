import cv2
import os
import numpy as np
import random
import pandas as pd
import tensorflow as tf
import keras.utils as image

from sklearn.metrics import classification_report, confusion_matrix, ConfusionMatrixDisplay
from tensorflow.keras.applications.resnet import ResNet50, preprocess_input
from tensorflow.keras.callbacks import ModelCheckpoint, EarlyStopping
from tensorflow.keras.layers import Dense, Dropout, Flatten
from tensorflow.keras.models import Model

# MPII에서 각 파트 번호, 선으로 연결될 POSE_PAIRS
BODY_PARTS = {"Head": 0, "Neck": 1, "RShoulder": 2, "RElbow": 3, "RWrist": 4,
              "LShoulder": 5, "LElbow": 6, "LWrist": 7, "RHip": 8, "RKnee": 9,
              "RAnkle": 10, "LHip": 11, "LKnee": 12, "LAnkle": 13, "Chest": 14,
              "Background": 15}

POSE_PAIRS = [["Head", "Neck"], ["Neck", "RShoulder"], ["RShoulder", "RElbow"],
              ["RElbow", "RWrist"], ["Neck", "LShoulder"], ["LShoulder", "LElbow"],
              ["LElbow", "LWrist"], ["Neck", "Chest"], ["Chest", "RHip"], ["RHip", "RKnee"],
              ["RKnee", "RAnkle"], ["Chest", "LHip"], ["LHip", "LKnee"], ["LKnee", "LAnkle"]]

# 각 파일 path
protoFile = "pose_deploy_linevec_faster_4_stages.prototxt"
weightsFile = "pose_iter_160000.caffemodel"

# 위의 path에 있는 network 불러오기
net = cv2.dnn.readNetFromCaffe(protoFile, weightsFile)


def preproccessing():
    root_dir = 'dataset/train'  # 디렉토리

    img_path_list = []
    possible_img_extension = ['.jpg', '.jpeg', '.JPG', '.bmp', '.png']  # 이미지 확장자들

    for (root, dirs, files) in os.walk(root_dir):
        if len(files) > 0:
            for file_name in files:
                if os.path.splitext(file_name)[1] in possible_img_extension:
                    img_path = root + '/' + file_name

                    # 경로에서 \를 모두 /로 바꿔줘야함
                    img_path = img_path.replace('\\', '/')  # \는 \\로 나타내야함
                    img_path_list.append(img_path)

    for path in img_path_list:
        # 이미지 읽어오기
        image = cv2.imread(path)

        # frame.shape = 불러온 이미지에서 height, width, color 받아옴
        imageHeight, imageWidth, _ = image.shape

        # network에 넣기위해 전처리
        inpBlob = cv2.dnn.blobFromImage(image, 1.0 / 255, (imageWidth, imageHeight), (0, 0, 0), swapRB=False,
                                        crop=False)

        # network에 넣어주기
        net.setInput(inpBlob)

        # 결과 받아오기
        output = net.forward()

        # output.shape[0] = 이미지 ID, [1] = 출력 맵의 높이, [2] = 너비
        H = output.shape[2]
        W = output.shape[3]
        # print("이미지 ID : ", len(output[0]), ", H : ", output.shape[2], ", W : ", output.shape[3])  # 이미지 ID

        # 키포인트 검출시 이미지에 그려줌
        points = []
        for i in range(0, 15):
            # 해당 신체부위 신뢰도 얻음.
            probMap = output[0, i, :, :]

            # global 최대값 찾기
            minVal, prob, minLoc, point = cv2.minMaxLoc(probMap)

            # 원래 이미지에 맞게 점 위치 변경
            x = (imageWidth * point[0]) / W
            y = (imageHeight * point[1]) / H

            # 키포인트 검출한 결과가 0.1보다 크면(검출한곳이 위 BODY_PARTS랑 맞는 부위면) points에 추가, 검출했는데 부위가 없으면 None으로
            if prob > 0.1:
                cv2.circle(image, (int(x), int(y)), 3, (0, 255, 255), thickness=-1,
                           lineType=cv2.FILLED)  # circle(그릴곳, 원의 중심, 반지름, 색)
                points.append((int(x), int(y)))
            else:
                points.append(None)

        # 이미지에서 포인트가 제대로 검출되지 않았으면 해당 이미지 건너 뜀
        if len(points) != 15:
            continue
        # 이미지 복사
        imageCopy = image

        # 각 POSE_PAIRS별로 선 그어줌 (머리 - 목, 목 - 왼쪽어깨, ...)
        for pair in POSE_PAIRS:
            partA = pair[0]  # Head
            partA = BODY_PARTS[partA]  # 0
            partB = pair[1]  # Neck
            partB = BODY_PARTS[partB]  # 1

            # print(partA," 와 ", partB, " 연결\n")
            if points[partA] and points[partB]:
                cv2.line(imageCopy, points[partA], points[partB], (0, 255, 0), 2)
            else:
                cv2.line(imageCopy, points[partA], points[partB], (0, 0, 0), 2)

        # 이미지 저장
        path = path.replace('train/', 'converted/')
        cv2.imwrite(path, image)
        print(path)


# 시드 배치
np.random.seed(42)
tf.random.set_seed(42)
random.seed(42)

# 데이터 전처리 및 모뎅 생성 시 사용하는 변수
img_size = (224, 224)
input_shape = img_size + (3,)
num_classes = 40
batch_size = 32

def train():
    # 학습 데이터 셋 분할 생성
    train_ds = tf.keras.utils.image_dataset_from_directory(
        directory='dataset/converted',
        validation_split=0.2,
        label_mode="categorical",
        subset="training",
        seed=123,
        image_size=img_size,
        batch_size=batch_size)

    # 검증 데이터 셋 분할 생성
    val_ds = tf.keras.utils.image_dataset_from_directory(
        directory='dataset/converted',
        validation_split=0.2,
        shuffle=False,
        label_mode="categorical",
        subset="validation",
        seed=123,
        image_size=img_size,
        batch_size=batch_size)

    # 분류된 데이터 클래스 네임들 출력
    print(train_ds.class_names)

    # 데이터 입력 형식 지정
    inputs = tf.keras.Input(shape=input_shape)
    # 람다 파라메터 생성
    x = tf.keras.layers.Lambda(preprocess_input)(inputs)

    # 라즈넷50을 활용한 모델 생성
    resnet_model = ResNet50(weights='imagenet',
                            include_top=False,
                            input_shape=input_shape,
                            input_tensor=x)

    # 모델의 레이어 파인 튠 설정
    for layer in resnet_model.layers:
        layer.trainable = False

    # 학습 모델 레이어 설정
    # 2D 평균 풀링 형태
    x = tf.keras.layers.GlobalAveragePooling2D()(resnet_model.output)
    # 레이어 정. 256 유닛, 활성함수 relu
    x = tf.keras.layers.Dense(256, activation='relu')(x)
    # 과적합
    x = tf.keras.layers.Dropout(0.5)(x)
    # 예측 레이어
    predictions = tf.keras.layers.Dense(3, activation='softmax')(x)

    # 모델 생성
    model = tf.keras.models.Model(inputs=inputs, outputs=predictions)
    # 옵티마이저 생성
    optimizer = tf.keras.optimizers.Adam(learning_rate=0.001)

    # 모델 컴파일
    model.compile(loss='categorical_crossentropy',
                  optimizer=optimizer,
                  metrics=['accuracy'])
    # 체크 포인트 생성
    checkpoint_path = "models/best_resnet.h5"
    model_checkpoint = ModelCheckpoint(
        checkpoint_path,
        save_best_only=True,
        monitor='val_accuracy',
        mode='max',
        verbose=1
    )

    # 밸류 정확도에 따른 학습 빠른 종료
    early_stopping = EarlyStopping(monitor='val_accuracy', patience=5)

    # 모델 피팅(학습) 시작
    history = model.fit(train_ds, validation_data=val_ds, epochs=5, callbacks=[model_checkpoint, early_stopping])
    # 데이터프레임으로 변환 후 csv 파일로 저장
    hist_df = pd.DataFrame(history.history)
    hist_df.to_csv("history/history_resnet.csv", index=False)

    # 모델 저장
    model.save('models')

# 이미지 전처리 함수. 최초 1회만 실행하면 됩니다. 데이터 추가시마다 실행
preproccessing()
# 학습 함수. 마찬가지로 전처리 함수 실행 후에만 실행하면됩니다.
train()

# 저장된 모델 불러오기
final_model = tf.keras.models.load_model("models")
# 저장된 히스토리 불러오기
history_df = pd.read_csv("history/history_resnet.csv")



# 새 이미지 파일 경로

# path = '아미지_경로/이미지.jpg'
# img = image.load_img(path, target_size=(224, 224))

# x = image.img_to_array(img)
# x = np.expand_dims(x, axis=0)
# images = np.vstack([x])
# classes = final_model.predict(images, batch_size=10)

# print(classes[0][0]) # 플랭크
# print(classes[0][1]) # 사이드 스쿼트
# print(classes[0][2]) # 스쿼트

from tensorflow.keras.layers import Conv2D, Input, Concatenate, MaxPool2D, UpSampling2D
from tensorflow.keras.models import Model

import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import cv2
import os


# 다운 샘플링 함수
def down_block(x, filters, kernel_size=(3, 3), padding="same", strides=1):
    c = Conv2D(filters, kernel_size, padding=padding, strides=strides, activation="relu")(x)
    c = Conv2D(filters, kernel_size, padding=padding, strides=strides, activation="relu")(c)
    p = MaxPool2D((2, 2), (2, 2))(c)
    return c, p


# 업 샘플링 함수
def up_block(x, skip, filters, kernel_size=(3, 3), padding="same", strides=1):
    us = UpSampling2D((2, 2))(x)
    concat = Concatenate()([us, skip])
    c = Conv2D(filters, kernel_size, padding=padding, strides=strides, activation="relu")(concat)
    c = Conv2D(filters, kernel_size, padding=padding, strides=strides, activation="relu")(c)
    return c


# 네트워크 보틀넥 컨볼루션 함수
def bottleneck(x, filters, kernel_size=(3, 3), padding="same", strides=1):
    c = Conv2D(filters, kernel_size, padding=padding, strides=strides, activation="relu")(x)
    c = Conv2D(filters, kernel_size, padding=padding, strides=strides, activation="relu")(c)
    return c


# 네트워크 모델 생성 함수
def UNet():
    f = [16, 32, 64, 128, 256]
    inputs = Input((224, 224, 3))

    p0 = inputs
    c1, p1 = down_block(p0, f[0])
    c2, p2 = down_block(p1, f[1])
    c3, p3 = down_block(p2, f[2])
    c4, p4 = down_block(p3, f[3])

    bn = bottleneck(p4, f[4])

    u1 = up_block(bn, c4, f[3])
    u2 = up_block(u1, c3, f[2])
    u3 = up_block(u2, c2, f[1])
    u4 = up_block(u3, c1, f[0])

    outputs = Conv2D(1, (1, 1), padding="same", activation="sigmoid")(u4)
    model = Model(inputs, outputs, name="U-Net")
    return model


# Accuracy 반환 함수
def accuracy(groundtruth_mask, pred_mask):
    intersect = np.logical_and(pred_mask, groundtruth_mask)
    union = np.logical_or(pred_mask, groundtruth_mask)
    return round(np.sum(intersect) / np.sum(union), 3)


# Recall 반환 함수
def recall(groundtruth_mask, pred_mask):
    intersect = np.sum(pred_mask * groundtruth_mask)
    total_pixel_truth = np.sum(groundtruth_mask)
    return round(np.mean(intersect / total_pixel_truth), 3)


# F1 반환 함수
def f1(groundtruth_mask, pred_mask):
    intersect = np.sum(pred_mask * groundtruth_mask)
    total_sum = np.sum(pred_mask) + np.sum(groundtruth_mask)
    return round(np.mean(2 * intersect / total_sum), 3)


# Precision 반환 함수
def precision(groundtruth_mask, pred_mask):
    intersect = np.sum(pred_mask * groundtruth_mask)
    total_pixel_pred = np.sum(pred_mask)
    return round(np.mean(intersect / total_pixel_pred), 3)

# 이미지 및 마스크 경로 지정
image_path = 'image_and_mask/image'
mask_path = 'image_and_mask/mask'

images_ = os.listdir(image_path)
masks_ = os.listdir(mask_path)

# 이미지 리사이즈
for i in range(len(images_)):
    img = cv2.imread(os.path.join(image_path, images_[i]))
    img = cv2.resize(img, (224, 224))
    cv2.imwrite(os.path.join(image_path, images_[i]), img)

# 마스크 리사이즈
for m in range(len(masks_)):
    mask = cv2.imread(os.path.join(mask_path, masks_[m]))
    mask = cv2.resize(mask, (224, 224))
    cv2.imwrite(os.path.join(mask_path, masks_[m]), mask)

image = []
mask = []

# 리사이즈 된 이미지 리스트에 추가
for i in range(len(images_)):
    img = cv2.imread(os.path.join(image_path, images_[i]))
    image.append(img)

# 리사이즈 된 마스크 리스트에 추가
for m in range(len(masks_)):
    msk = cv2.imread(os.path.join(mask_path, masks_[m]), 0)
    mask.append(msk)

# Normalization
image = np.array(image, dtype=np.float32) / 255
mask = np.array(mask, dtype=np.float32) / 255

# 네트워크 모델 생성
model = UNet()
model.compile(optimizer="adam", loss="binary_crossentropy", metrics=["acc"])

# 학습, 검증, 테스트 데이터 분리. 비율은 8:1:1
x_train = image[:int(0.8 * len(image))]
Y_train = mask[:int(0.8 * len(mask))]
x_val = image[int(0.8 * len(image)):int(0.9 * len(image))]
Y_val = mask[int(0.8 * len(mask)):int(0.9 * len(mask))]
x_test = image[int(0.9 * len(image)):]
Y_test = mask[int(0.9 * len(mask)):]

# 모델 학숩
history = model.fit(x_train, Y_train, batch_size=32, epochs=50, validation_data=(x_val, Y_val))

a_res, r_res, f_res, p_res = 0, 0, 0, 0
l = Y_test.shape[0]
Y_pred = model.predict(x_test)
# accuracy, recall, f1, precision 평균 계산
for y, p in zip(Y_test, Y_pred):
    a_res += accuracy(y, p)
    r_res += recall(y, p)
    f_res += f1(y, p)
    p_res += precision(y, p)

# accuracy, recall, f1, precision 출력
print('accuracy:', a_res / l)
print('recall:', r_res / l)
print('f1:', f_res / l)
print('precision:', p_res / l)

# Confusion Matrix
FP = len(np.where(Y_pred - Y_val == 1)[0])
FN = len(np.where(Y_pred - Y_val == -1)[0])
TP = len(np.where(Y_pred + Y_val == 2)[0])
TN = len(np.where(Y_pred + Y_val == 0)[0])
cmat = [[TP, FN], [FP, TN]]

plt.figure(figsize=(6, 6))
sns.heatmap(cmat / np.sum(cmat), cmap="Reds", annot=True, fmt='.2%', square=1, linewidth=2.)
plt.xlabel("prediction")
plt.ylabel("groundtruth")
plt.show()

# Epoch - Accuracy 그래프
plt.plot(history.history["acc"], label="accuracy")
# Epoch - Loss 그래프
plt.plot(history.history["loss"], label="loss")

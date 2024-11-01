import os
import matplotlib.image as mpimg
import matplotlib.pyplot as plt
import tensorflow as tf
from tensorflow.keras.optimizers.legacy import RMSprop
from tensorflow.keras.preprocessing.image import ImageDataGenerator

# 기본 경로
base_dir = 'data'

train_dir = os.path.join(base_dir, 'train')
test_dir = os.path.join(base_dir, 'test')

# 훈련에 사용되는 이미지 경로
train_1_dir = os.path.join(train_dir, '1')
train_2_dir = os.path.join(train_dir, '2')
train_3_dir = os.path.join(train_dir, '3')
train_4_dir = os.path.join(train_dir, '4')
train_n_dir = os.path.join(train_dir, 'n')

# 경로 확인
print(train_1_dir)
print(train_2_dir)
print(train_3_dir)
print(train_4_dir)
print(train_n_dir)

# 테스트에 사용되는 이미지 경로
test_1_dir = os.path.join(test_dir, '1')
test_2_dir = os.path.join(test_dir, '2')
test_3_dir = os.path.join(test_dir, '3')
test_4_dir = os.path.join(test_dir, '4')
test_n_dir = os.path.join(test_dir, 'n')

# 경로 확인
print(test_1_dir)
print(test_2_dir)
print(test_3_dir)
print(test_4_dir)
print(test_n_dir)

# 트레이닝 파일 이름
train_1_fnames = os.listdir(train_1_dir)
train_2_fnames = os.listdir(train_2_dir)
train_3_fnames = os.listdir(train_3_dir)
train_4_fnames = os.listdir(train_4_dir)
train_n_fnames = os.listdir(train_n_dir)

# 테스트 파일 이름
test_1_fnames = os.listdir(test_1_dir)
test_2_fnames = os.listdir(test_2_dir)
test_3_fnames = os.listdir(test_3_dir)
test_4_fnames = os.listdir(test_4_dir)
test_n_fnames = os.listdir(test_n_dir)

# 트레이닝, 테스트 이미지 갯수 확인
print('Total training no.1 images :', len(os.listdir(train_1_dir)))
print('Total training no.2 images :', len(os.listdir(train_2_dir)))
print('Total training no.3 images :', len(os.listdir(train_3_dir)))
print('Total training no.4 images :', len(os.listdir(train_4_dir)))
print('Total training none images :', len(os.listdir(train_n_dir)))

print('Total testing no.1 images :', len(os.listdir(test_1_dir)))
print('Total testing no.2 images :', len(os.listdir(test_2_dir)))
print('Total testing no.3 images :', len(os.listdir(test_3_dir)))
print('Total testing no.4 images :', len(os.listdir(test_4_dir)))
print('Total testing none images :', len(os.listdir(test_n_dir)))

# 이미지 확인
nrows, ncols = 4, 5
idx = 0

# 피규어 생성
figure = plt.gcf()
figure.set_size_inches(ncols * 3, nrows * 3)

idx += 4

# 각각의 항목 별로 4장의 이미지씩 선별
next_1_pics = [os.path.join(train_1_dir, fname) for fname in train_1_fnames[idx - 4:idx]]
next_2_pics = [os.path.join(train_2_dir, fname) for fname in train_2_fnames[idx - 4:idx]]
next_3_pics = [os.path.join(train_3_dir, fname) for fname in train_3_fnames[idx - 4:idx]]
next_4_pics = [os.path.join(train_4_dir, fname) for fname in train_4_fnames[idx - 4:idx]]
next_n_pics = [os.path.join(train_n_dir, fname) for fname in train_n_fnames[idx - 4:idx]]

# # 출력
# for i, img_path in enumerate(next_1_pics + next_2_pics + next_3_pics + next_4_pics + next_n_pics):
#     sp = plt.subplot(nrows, ncols, i + 1)
#     sp.axis('Off')
#
#     img = mpimg.imread(img_path)
#     plt.imshow(img)
# plt.show()

# 합성곱 신경망 모델 구성
model = tf.keras.models.Sequential([
    tf.keras.layers.Conv2D(16, (3, 3), activation='relu', input_shape=(150, 150, 3)),
    tf.keras.layers.MaxPooling2D(2, 2),
    tf.keras.layers.Conv2D(32, (3, 3), activation='relu'),
    tf.keras.layers.MaxPooling2D(2, 2),
    tf.keras.layers.Conv2D(64, (3, 3), activation='relu'),
    tf.keras.layers.MaxPooling2D(2, 2),
    tf.keras.layers.Flatten(),
    tf.keras.layers.Dense(512, activation='relu'),
    tf.keras.layers.Dense(1, activation='sigmoid')
])

# 구조 확인
print(model.summary())

# 모델 컴파일
model.compile(optimizer=RMSprop(learning_rate=0.001), loss='binary_crossentropy', metrics=['accuracy'])

# 이미지 데이터 전처리
train_datagen = ImageDataGenerator(rescale=1.0 / 255.)
test_datagen = ImageDataGenerator(rescale=1.0 / 255.)

train_generator = train_datagen.flow_from_directory(train_dir,
                                                    batch_size=20,
                                                    class_mode='binary',
                                                    target_size=(150, 150))
test_generator = test_datagen.flow_from_directory(test_dir,
                                                  batch_size=20,
                                                  class_mode='binary',
                                                  target_size=(150, 150))

# 모델 훈련
history = model.fit(train_generator,
                    validation_data=test_generator,
                    steps_per_epoch=100,
                    epochs=100,
                    validation_steps=50,
                    verbose=2)

# 정확도 및 손실 확인

acc = history.history['accuracy']
test_acc = history.history['test_accuracy']
loss = history.history['loss']
test_loss = history.history['test_loss']

epochs = range(len(acc))

plt.plot(epochs, acc, 'bo', label='Training accuracy')
plt.plot(epochs, test_acc, 'b', label='Validation accuracy')
plt.title('Training and test accuracy')
plt.legend()

plt.figure()

plt.plot(epochs, loss, 'go', label='Training Loss')
plt.plot(epochs, test_loss, 'g', label='Validation Loss')
plt.title('Training and test loss')
plt.legend()

plt.show()

import os
import shutil

from PIL import Image
from tqdm import tqdm

from tensorflow.keras import layers, models
from sklearn.model_selection import train_test_split
from tensorflow.keras.preprocessing.image import ImageDataGenerator


# 이미지 변환 함수
def augment_image(image):
    augmented_images = []
    augmented_images.append(image)  # 원본 이미지

    # 상하 대칭
    augmented_images.append(image.transpose(Image.FLIP_TOP_BOTTOM))

    # 좌우 대칭
    augmented_images.append(image.transpose(Image.FLIP_LEFT_RIGHT))

    # 원점 대칭 (180도 회전)
    augmented_images.append(image.rotate(180))
    # 45도 회전
    augmented_images.append(image.rotate(45, expand=True))
    return augmented_images


# 증강 이미지 저장 함수
def save_augmented_images(src_dir, dest_dir):
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)

    images = os.listdir(src_dir)
    for img_name in tqdm(images):
        img_path = os.path.join(src_dir, img_name)
        img = Image.open(img_path)
        augmented_images = augment_image(img)

        for i, aug_img in enumerate(augmented_images):
            new_img_name = f"{os.path.splitext(img_name)[0]}_aug{i}.jpg"
            aug_img.save(os.path.join(dest_dir, new_img_name))


def copy_files(file_list, src_dir, dst_dir):
    for file_name in file_list:
        shutil.copy(os.path.join(src_dir, file_name), os.path.join(dst_dir, file_name))


def create_lenet5():
    model = models.Sequential()
    model.add(layers.Conv2D(6, (5, 5), activation='relu', input_shape=(32, 32, 3)))
    model.add(layers.AveragePooling2D(pool_size=(2, 2)))

    model.add(layers.Conv2D(16, (5, 5), activation='relu'))
    model.add(layers.AveragePooling2D(pool_size=(2, 2)))

    model.add(layers.Flatten())
    model.add(layers.Dense(120, activation='relu'))
    model.add(layers.Dense(84, activation='relu'))
    model.add(layers.Dense(1, activation='sigmoid'))  # 이진 분류를 위해 sigmoid 활성화 함수 사용

    return model


cat_original_dir = 'training_set/cats'
dog_original_dir = 'training_set/dogs'

# 데이터셋 디렉토리 설정
cat_dir = 'data/cats'
dog_dir = 'data/dogs'

# 타겟 디렉토리 설정
train_dir = 'data/train'
validation_dir = 'data/validation'
test_dir = 'data/test'

# 디렉토리 생성
for dir_path in [train_dir, validation_dir, test_dir]:
    if not os.path.exists(dir_path):
        os.makedirs(os.path.join(dir_path, 'cats'))
        os.makedirs(os.path.join(dir_path, 'dogs'))

# 고양이와 강아지 데이터 증강 및 저장
save_augmented_images(cat_original_dir, cat_dir)
save_augmented_images(dog_original_dir, dog_dir)

# 이미지 리스트 생성
cat_files = os.listdir(cat_dir)
dog_files = os.listdir(dog_dir)

# 데이터를 학습, 검증, 테스트 세트로 나누기
train_cats, test_cats = train_test_split(cat_files, test_size=0.2, random_state=42)
train_dogs, test_dogs = train_test_split(dog_files, test_size=0.2, random_state=42)

train_cats, val_cats = train_test_split(train_cats, test_size=0.25, random_state=42)  # 0.25 x 0.8 = 0.2
train_dogs, val_dogs = train_test_split(train_dogs, test_size=0.25, random_state=42)

# 파일 복사 함수 정의

# 파일 복사
copy_files(train_cats, cat_dir, os.path.join(train_dir, 'cats'))
copy_files(val_cats, cat_dir, os.path.join(validation_dir, 'cats'))
copy_files(test_cats, cat_dir, os.path.join(test_dir, 'cats'))

copy_files(train_dogs, dog_dir, os.path.join(train_dir, 'dogs'))
copy_files(val_dogs, dog_dir, os.path.join(validation_dir, 'dogs'))
copy_files(test_dogs, dog_dir, os.path.join(test_dir, 'dogs'))

# 데이터 전처리 및 증강 설정
train_datagen = ImageDataGenerator(rescale=1. / 255,
                                   rotation_range=20,
                                   width_shift_range=0.2,
                                   height_shift_range=0.2,
                                   shear_range=0.2,
                                   zoom_range=0.2,
                                   horizontal_flip=True)

test_datagen = ImageDataGenerator(rescale=1. / 255)

# 데이터 제너레이터 설정
train_generator = train_datagen.flow_from_directory(
    train_dir,
    target_size=(32, 32),
    batch_size=32,
    class_mode='binary')

validation_generator = test_datagen.flow_from_directory(
    validation_dir,
    target_size=(32, 32),
    batch_size=32,
    class_mode='binary')

test_generator = test_datagen.flow_from_directory(
    test_dir,
    target_size=(32, 32),
    batch_size=32,
    class_mode='binary')

model = create_lenet5()

model.compile(optimizer='adam',
              loss='binary_crossentropy',
              metrics=['accuracy'])

history = model.fit(
    train_generator,
    steps_per_epoch=train_generator.samples // train_generator.batch_size,
    epochs=30,
    validation_data=validation_generator,
    validation_steps=validation_generator.samples // validation_generator.batch_size)

test_loss, test_accuracy = model.evaluate(test_generator, steps=test_generator.samples // test_generator.batch_size)
print(f'Test accuracy: {test_accuracy:.4f}')
print(f'Test loss: {test_loss:.4f}')

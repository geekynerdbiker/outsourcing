import tensorflow as tf
import tensorflow.keras as keras
import tensorflow_datasets as tfds
from keras.preprocessing.image import ImageDataGenerator

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

trainDataGen = ImageDataGenerator(rescale=1. / 255,
                                  rotation_range=30,
                                  width_shift_range=0.1,
                                  height_shift_range=0.1,
                                  shear_range=0.2,
                                  zoom_range=0.2,
                                  horizontal_flip=False,
                                  vertical_flip=False,
                                  fill_mode='nearest'
                                  )
testDataGen = ImageDataGenerator(rescale=1. / 255)
ds_train = trainDataGen.flow_from_directory(
    'rsp/train',
    batch_size=32,
    target_size=(28, 28),
    class_mode='categorical'
)

ds_test = testDataGen.flow_from_directory(
    'rsp/test',
    target_size=(28, 28),
    batch_size=32,
    class_mode='categorical'
)

# Hyper Parameter Configuration
EPOCHS = 30
BATCH_SIZE = 32

CLASS_NUM = ds_info.features['label'].num_classes  # = 3
CLASS_NAMES = ['rock', 'paper', 'scissors']

INPUT_IMG_SIZE = 100


def normalize_img(image, label):
    image = tf.cast(image, tf.float32)
    image = image / 255.
    image = tf.image.resize(image, [INPUT_IMG_SIZE, INPUT_IMG_SIZE])
    return image, label


model = keras.models.Sequential()
model.add(keras.layers.Conv2D(32, 3, padding='same', activation='relu',
                              input_shape=(INPUT_IMG_SIZE, INPUT_IMG_SIZE, 3)))
model.add(keras.layers.MaxPooling2D((2, 2)))

model.add(keras.layers.Conv2D(32, 3, padding='same', activation='relu'))
model.add(keras.layers.MaxPooling2D((2, 2)))

model.add(keras.layers.Conv2D(32, 3, padding='same', activation='relu'))
model.add(keras.layers.MaxPooling2D((2, 2)))

model.add(keras.layers.Conv2D(64, 3, padding='same', activation='relu'))
model.add(keras.layers.MaxPooling2D((2, 2)))

model.add(keras.layers.Conv2D(64, 3, padding='same', activation='relu'))
model.add(keras.layers.MaxPooling2D((2, 2)))

model.add(keras.layers.Flatten())
model.add(keras.layers.Dropout(0.5))
model.add(keras.layers.Dense(512, activation='relu'))
model.add(keras.layers.Dropout(0.5))
model.add(keras.layers.Dense(CLASS_NUM, activation='softmax'))

model.summary()
keras.utils.plot_model(model, show_shapes=True, dpi=70)
model.compile(optimizer='sgd', loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])
history = model.fit(ds_train, epochs=EPOCHS, validation_data=ds_test)

test_loss, test_acc = model.evaluate(ds_test, verbose=2)

print(f'\n테스트 정확도: {test_acc * 100:.2f}%')

predictions = model.predict(ds_test)

df_hist = pd.DataFrame(history.history)
df_hist['epoch'] = range(1, EPOCHS + 1)

plt.figure(figsize=(15, 5))

plt.subplot(1, 2, 1)
plt.title('Loss according to Epoch')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.plot(df_hist['epoch'], df_hist['loss'], label='train')
plt.plot(df_hist['epoch'], df_hist['val_loss'], label='validation')
plt.grid(True)
plt.legend()

plt.subplot(1, 2, 2)
plt.title('Accuracy according to Epoch')
plt.xlabel('Epoch')
plt.ylabel('Accuracy')
plt.plot(df_hist['epoch'], df_hist['accuracy'], label='train')
plt.plot(df_hist['epoch'], df_hist['val_accuracy'], label='validation')
plt.ylim(0, 1.05)
plt.grid(True)
plt.legend()

plt.show()

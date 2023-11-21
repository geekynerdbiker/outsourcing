from PIL import Image
import pillow_heif
import os

directory = '/users/jacoban/downloads/rsp/rock'
files = [f for f in os.listdir(directory) if f.endswith('.HEIC')]

# Convert each file to JPEG
idx = 1
for filename in files:
    heif_file = pillow_heif.read_heif(os.path.join(directory, filename))
    image = Image.frombytes(
        heif_file.mode,
        heif_file.size,
        heif_file.data,
        "raw",
    )
    image.save(os.path.join(directory, 'rock') + str(idx) + '.jpg')
    idx += 1

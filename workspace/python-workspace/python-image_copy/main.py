from PIL import Image
from PIL.ExifTags import TAGS, GPSTAGS
import piexif
import os


def get_exif_data(image):
    exif_data = {}
    info = image.getexif()

    for tag, value in info.items():
        tag_name = TAGS.get(tag, tag)
        exif_data[tag_name] = value

    return exif_data


def remove_software_tag(exif_dict):
    if piexif.ImageIFD.Software in exif_dict['0th']:
        del exif_dict['0th'][piexif.ImageIFD.Software]
    return exif_dict


def copy_images_with_metadata(input_folder, output_folder):
    # 입력 폴더 내의 모든 파일에 대해 작업 수행
    for filename in os.listdir(input_folder):
        input_path = os.path.join(input_folder, filename)

        img = Image.open(input_path)
        info = img.info
        exif_bytes = img.info.get('exif')

        # EXIF 데이터 추출 및 수정
        exif_dict = piexif.load(exif_bytes)
        exif_dict = remove_software_tag(exif_dict)
        new_exif_bytes = piexif.dump(exif_dict)

        # EXIF 데이터 추출
        exif_data = get_exif_data(img)

        # 찍은 날짜, 프로그램 이름 등의 EXIF 데이터 출력 (존재하는 경우)
        date_taken = exif_data.get('DateTimeOriginal', 'N/A')
        software = exif_data.get('Software', 'N/A')
        print(f"File: {filename}, Date Taken: {date_taken}, Software: {software}")

        # 이미지를 복사하고 메타 데이터를 추가하여 저장
        new_img = img.copy()
        new_img.info.update(info)

        output_path = os.path.join(output_folder, filename)
        new_img.save(output_path, exif=new_exif_bytes, icc_profile=info.get('icc_profile'))
        print(f"Copied {filename} with metadata to {output_path}")


# 예제 사용
input_folder = 'test'
output_folder = 'test_out'

# 출력 폴더가 존재하지 않으면 생성
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

copy_images_with_metadata(input_folder, output_folder)

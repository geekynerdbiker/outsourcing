from PIL import Image


def copy_image(input_path, output_path):
    try:
        # 이미지 열기
        img = Image.open(input_path)

        # 이미지 복사하기 (새로운 객체 생성)
        copied_img = img.copy()

        # 새로운 이미지 저장
        copied_img.save(output_path)

        print(f"이미지가 {output_path}에 복사되었습니다.")

    except IOError as e:
        print(f"이미지를 열 수 없습니다: {e}")


# 사용 예시
input_image = "input.jpg"
output_image = "output.jpg"

copy_image(input_image, output_image)

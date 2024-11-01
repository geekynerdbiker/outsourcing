import json
import os
from shutil import copyfile

def convert_coco_to_yolo(coco_json, output_dir, image_dir):
    with open(coco_json) as f:
        data = json.load(f)

    images = {img['id']: img for img in data['images']}
    annotations = data['annotations']

    for ann in annotations:
        img_id = ann['image_id']
        img_info = images[img_id]

        img_path = os.path.join(image_dir, img_info['file_name'])
        if not os.path.exists(img_path):
            continue

        bbox = ann['bbox']

        yolo_bbox = [
            (bbox[0] + bbox[2]) / img_info['width'],
            (bbox[1] + bbox[3]) / img_info['height'],
            bbox[2] / img_info['width'],
            bbox[3] / img_info['height'],
        ]

        label_path = os.path.join(output_dir, 'labels', img_info['file_name'].replace('.jpg', '.txt'))
        os.makedirs(os.path.dirname(label_path), exist_ok=True)
        with open(label_path, 'a') as f:
            f.write(f"{0} {' '.join(map(str, yolo_bbox))}\n")

        image_dest_path = os.path.join(output_dir, 'images', img_info['file_name'])
        os.makedirs(os.path.dirname(image_dest_path), exist_ok=True)
        copyfile(img_path, image_dest_path)


train_image_dir = 'data/train'
train_annotation_file = os.path.join(train_image_dir, '_annotations.coco.json')
output_dir = 'data/yolo_train'
convert_coco_to_yolo(train_annotation_file, output_dir, train_image_dir)

valid_image_dir = 'data/valid'
valid_annotation_file = os.path.join(valid_image_dir, '_annotations.coco.json')
output_dir = 'data/yolo_valid'
convert_coco_to_yolo(valid_annotation_file, output_dir, valid_image_dir)

test_image_dir = 'data/test'
test_annotation_file = os.path.join(test_image_dir, '_annotations.coco.json')
output_dir = 'data/yolo_test'
convert_coco_to_yolo(test_annotation_file, output_dir, test_image_dir)

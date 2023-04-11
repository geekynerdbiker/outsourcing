#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int c;
    int x1;
    int y1;
    int x2;
    int y2;
    float confidence;
} BBox;

///////////////////////////////
// �Լ��� �ʿ��� ��� �� ���� �ۼ�
///////////////////////////////


///////////////////////////////

int main(void) {
    // ���� ����� �Է� ������ ������ ������ �迭
    int num_boxes = 0;
    BBox bboxes[1000];

    ///////////////////////////////////////////////
    // �׽�Ʈ ������ �����ϱ� ���� ���� ����� �ڵ� //
    ///////////////////////////////////////////////
    const char* file_path = "samples.txt";
    FILE* file = fopen(file_path, "r");

    if (file == NULL) {
        perror("Opening file fails\n");
        return 1;
    }

    fscanf(file, "%d", &num_boxes);
    for (int n = 0; n < num_boxes; n++) {
        fscanf(file, "%d %d %d %d %d %f", &bboxes[n].c,
            &bboxes[n].x1, &bboxes[n].y1,
            &bboxes[n].x2, &bboxes[n].y2,
            &bboxes[n].confidence);
    }

    fclose(file);
    ///////////////////////////////////////////////

    //////////////////////////////
    // ������ ó���� ���� ���� �� //
    //////////////////////////////
    float conf_threshold = 0.7;
    float iou_threshold = 0.5;

    // �˰��� �ۼ� �� ��� ���






    return 0;
}
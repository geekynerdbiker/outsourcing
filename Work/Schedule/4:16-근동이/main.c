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
// 함수가 필요할 경우 이 곳에 작성
///////////////////////////////


///////////////////////////////

int main(void) {
    // 검출 결과의 입력 개수와 정보를 저장할 배열
    int num_boxes = 0;
    BBox bboxes[1000];

    ///////////////////////////////////////////////
    // 테스트 샘플을 실행하기 위한 파일 입출력 코드 //
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
    // 데이터 처리를 위한 기준 값 //
    //////////////////////////////
    float conf_threshold = 0.7;
    float iou_threshold = 0.5;

    // 알고리즘 작성 및 결과 출력






    return 0;
}
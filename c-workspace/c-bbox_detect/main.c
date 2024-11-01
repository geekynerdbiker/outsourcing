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

int min(int x, int y) {
    return x < y ? x : y;
}

int max(int x, int y) {
    return x > y ? x : y;
}

void swap(BBox *b1, BBox *b2) {
    BBox tmp = *b1;
    *b1 = *b2;
    *b2 = tmp;
}

int isOverlaped(BBox b1, BBox b2) {
    return (b1.x1 <= b2.x1 && b1.x2 >= b2.x1 && b1.y1 <= b2.y1 && b1.y2 >= b2.y1) || (b2.x1 <= b1.x1 && b2.x2 >= b1.x1 && b2.y1 <= b1.y1 && b2.y2 >= b1.y1);
}
void quickSort(BBox data[], int left, int right) {
    int begin = left, end = right;
    BBox pivot = data[(left+right) / 2];
    
    
    do {
        while (pivot.confidence < data[begin].confidence)
            begin++;
        while (pivot.confidence > data[end].confidence)
            end--;
        
        if (begin <= end)
            swap(&data[begin++], &data[end--]);
    } while (begin <= end);
    
    if (left < end)
        quickSort(data, left, end);
    if (begin < right)
        quickSort(data, begin, right);
    
}

int main(void) {
    int num_boxes = 0;
    BBox bboxes[1000];

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

    float conf_threshold = 0.7;
    float iou_threshold = 0.5;

    quickSort(bboxes, 0, num_boxes - 1);
    
    
    for (int i = 0; i < num_boxes; i++) {
        float iou;
        
        for (int j = 0; j < num_boxes; j++) {
            if (i == j)
                continue;
            
            if (isOverlaped(bboxes[i], bboxes[j])) {
                int A = abs(bboxes[i].x2-bboxes[i].x1) * abs(bboxes[i].y2-bboxes[i].y1);
                int C = abs(bboxes[j].x2-bboxes[j].x1) * abs(bboxes[j].y2-bboxes[j].y1);
                
                int Bx = abs(max(bboxes[i].x1, bboxes[j].x1) - min(bboxes[i].x2, bboxes[j].x2));
                int By = abs(max(bboxes[i].y1, bboxes[j].y1) - min(bboxes[i].y2, bboxes[j].y2));
                
                iou = Bx * By / (float)(A - Bx * By + C);
                
                if (iou >= iou_threshold) {
                    if (bboxes[i].confidence < 1 && bboxes[j].confidence < 1) {
                        if (bboxes[i].confidence > bboxes[j].confidence)
                            bboxes[j].confidence = 2;
                        else
                            bboxes[i].confidence = 2;
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < num_boxes; i++) {
        if (bboxes[i].confidence <= 1 && bboxes[i].confidence >= conf_threshold)
            printf("%d %d %d %d %d %f\n", bboxes[i].c,
                   bboxes[i].x1, bboxes[i].y1,
                   bboxes[i].x2, bboxes[i].y2,
                   bboxes[i].confidence);
    }
    
    return 0;
}

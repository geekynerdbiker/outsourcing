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
    
    int display;
} BBox;

int get_min(int n1, int n2) {
    if (n1 < n2)
        return n1;
    else
        return n2;
}

int get_max(int n1, int n2) {
    if (n1 > n2)
        return n1;
    else
        return n2;
}

void swap_BBox(BBox *box1, BBox *box2) {
    BBox box = *box2;
    *box2 = *box1;
    *box1 = box;
}

int check_status(BBox box1, BBox box2) {
    if (box1.x1 <= box2.x1 && box1.y1 <= box2.y1 && box1.x2 >= box2.x1 && box1.y2 >= box2.y1)
        return 1;
    else if (box2.x1 <= box1.x1 && box2.y1 <= box1.y1 && box2.x2 >= box1.x1 && box2.y2 >= box1.y1)
        return 1;
    else
        return 0;
}

void bubble_sort(BBox data[], int num) {
    for (int i = 0; i < num - 1; i++)
        for (int j = 0; j < num - 1 - i; j++)
            if (data[j].confidence < data[j + 1].confidence)
                swap_BBox(&data[j], &data[j+1]);
    return;
}

void print(BBox data[], int num) {
    for (int i = 0; i < num; i++) {
        if (data[i].display && data[i].confidence >= 0.7)
            printf("%d %d %d %d %d %f\n", data[i].c,
                   data[i].x1, data[i].y1,
                   data[i].x2, data[i].y2,
                   data[i].confidence);
    }
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
        bboxes[n].display = 1;
    }

    fclose(file);

    float conf_threshold = 0.7;
    float iou_threshold = 0.5;

    bubble_sort(bboxes, num_boxes);
    
    for (int i = 0; i < num_boxes; i++) {
        float iou;
        
        for (int j = 0; j < num_boxes; j++) {
            if (i == j)
                continue;
            
            if (check_status(bboxes[i], bboxes[j])) {
                int A = abs(bboxes[i].x2-bboxes[i].x1) * abs(bboxes[i].y2-bboxes[i].y1);
                int B = abs(get_max(bboxes[i].x1, bboxes[j].x1) - get_min(bboxes[i].x2, bboxes[j].x2)) * abs(get_max(bboxes[i].y1, bboxes[j].y1) - get_min(bboxes[i].y2, bboxes[j].y2));
                int C = abs(bboxes[j].x2-bboxes[j].x1) * abs(bboxes[j].y2-bboxes[j].y1);
                
                
                
                iou = B / (float)(A - B + C);
                
                if (iou >= iou_threshold) {
                    if (bboxes[i].confidence < 1 && bboxes[j].confidence < 1) {
                        if (bboxes[i].confidence > bboxes[j].confidence)
                            bboxes[j].display = 0;
                        else
                            bboxes[i].display = 0;
                    }
                }
            }
        }
    }
    
    print(bboxes, num_boxes);
    
    return 0;
}

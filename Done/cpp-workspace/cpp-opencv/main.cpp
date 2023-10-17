#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main(int ac, char** av)
{
    // 이미지 불러옴
    Mat img = imread("1.jpg");
    Mat img_hsv;

    // BGR ->HSV 변환
    cvtColor(img, img_hsv, COLOR_BGR2HSV);

    // 노란색 검출을 위한 이미지 변수
    Mat yellow_mask, yellow_image;

    // 임계값 설정
    Scalar lower_yellow = Scalar(20, 20, 100);
    Scalar upper_yellow = Scalar(32, 255, 255);

    // 이진화된 이미지를 yellow_mask에 저장
    inRange(img_hsv, lower_yellow, upper_yellow, yellow_mask);
    // 원본 이미지에 yellow_mask와 비트연산하여 yellow_image에 저장
    bitwise_and(img, img, yellow_image, yellow_mask);
    
    // 원본 출력
    imshow("img", img);
    // 노란색 검출 이미지 출력
    imshow("yellow_image", yellow_image);
    waitKey(0);
    
    return 0;
}

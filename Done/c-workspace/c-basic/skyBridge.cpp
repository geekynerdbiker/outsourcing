//
//  main.cpp
//  c-basic
//
//  Created by Jacob An on 2022/03/24.
//

#include <iostream>

using namespace std;

int skyBridge(int *x, int y) {
    int cnt = 0;
    int curr = 0;
    
    while (curr < y) {
        curr += *(x + curr);
        cnt++;
    }
    return cnt;
}

int main() {
    int arr[] = {1, 1, 2, 3, 5};
    
    cout << "구름다리 숫자만큼 구름다리를 건넙니다." << endl;
    cout << "구름다리 숫자: ";
    
    for (int i = 0; i < 5; i++)
        cout << arr[i] << " ";
    
    cout << endl;
    cout << "점프 횟수: " << skyBridge(arr, 5) << endl;
    
    return 0;
}

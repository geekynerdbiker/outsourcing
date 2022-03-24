//
//  main.c
//  c-basic
//
//  Created by Jacob An on 2022/03/24.
//

#include <stdio.h>
#pragma warning(disable:4996)

float getCelsius() {
    float c;
    
    printf("섭씨 온도를 입력하시오 : ");
    scanf("%f", &c);
    
    return c;
}
float celsiusToFahrenheit(float c) {
    return (c + 40) * 1.8 - 40;
}
void printCelsius(float c) {
    printf("섭씨 온도는 %.2f 입니다\n", c);
}

float getFahrenheit() {
    float f;
    
    printf("화씨 온도를 입력하시오 : ");
    scanf("%f", &f);
    
    return f;
}
float fahrenheitToCelsius(float f) {
    return (f + 40) / 1.8 - 40;
}
void printFahrenheit(float f) {
    printf("화씨 온도는 %.2f 입니다\n", f);
}

int main() {
    printFahrenheit(celsiusToFahrenheit(getCelsius()));
    printf("\n");
    
    printCelsius(fahrenheitToCelsius(getFahrenheit()));
    
    return 0;
}

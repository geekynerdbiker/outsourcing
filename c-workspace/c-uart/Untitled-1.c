#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> 

uint8_t value;
uint8_t *values;

void func1() {
    printf("Enter a value (0-255): ");
    scanf("%" SCNu8, &value);

    uint8_t result = ~value;
    printf("Received: 0x%02X, Inverted: 0x%02X\n\n", value, result);
}

void func2() {
    printf("Enter a value (0-255): ");
    scanf("%" SCNu8, &value);

    uint8_t result = 0x01 << value;
    printf("0x01 shifted left by %d: 0x%02X\n\n", value, result);
}

void func3() {
    printf("Enter a value (0-255): ");
    scanf("%" SCNu8, &value);

    uint8_t result = 0x80 << value;
    printf("0x80 shifted left by %d: 0x%02X\n\n", value, result);
}

void func4() {
    printf("Enter a value (0-255): ");
    scanf("%" SCNu8, &value);

    uint8_t result = 0x0F & value;
    printf("Received: 0x%02X, Result after AND with 0x0F: 0x%02X\n\n", value, result);
}

void func5() {
    uint8_t temp = value;

    printf("Enter a value (0-255): ");
    scanf("%" SCNu8, &value);

    if (temp != value)
        printf("Received: 0x%02X, Previous: 0x%02X\n", value, temp);
    printf("\n");
}

void func6() {
    values = (uint8_t *)malloc(sizeof(uint8_t) * 2);

    for (int i = 0; i < 2; i++) {
        printf("Enter a value %d (0-255): ", i+1);
        scanf("%" SCNu8, &values[i]);
    }

    uint8_t result = values[0] > values[1] ? values[0] : values[1];
    printf("Larger Value: 0x%02X\n\n", result);

    free(values);
}

void func7() {
    values = (uint8_t *)malloc(sizeof(uint8_t) * 5);

    for (int i = 0; i < 5; i++) {
        printf("Enter a value %d (0-255): ", i+1);
        scanf("%" SCNu8, &values[i]);
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (values[j] < values[j + 1]) {
                uint8_t temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < 5; i++)
        printf("[%d] 0x%02X\n", i+1, values[i]);
    printf("\n");
}

void func9() {
    printf("Enter a value (0-255): ");
    scanf("%" SCNu8, &value);

    printf("Received: 0x%02X, Address: 0x%p\n\n", value, &value);
}

void func10() {
    printf("Enter a value (0-255): ");
    scanf("%" SCNu8, &value);

    for (int i = 0; i < 5; i++) {
        printf("Received: 0x%02X \n", value);
        _sleep(1000);
    }
    printf("\n");
}

void func11() {
    while(1) {
        printf("Enter a value (0-10): ");
        scanf("%" SCNu8, &value);
        
        if (value > 10)
            continue;
        if (value == 0)
        break;
        _sleep(1000 / (value * value));
        printf("Received: 0x%02X \n", value);
    }
    printf("\n");
}

int main() {
    func1();
    func2();
    func3();
    func4();
    func5();
    func6();
    func7();
    func9();
    func10();
    func11();
    return 0;
}

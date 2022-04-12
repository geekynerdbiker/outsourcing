#include <iostream>
using namespace std;
// you are NOT allowed to include any additional library
const int ARRAY_MAX_SIZE = 12;

// given; do NOT modify; please refer to the webpage description
void printArray(int array[], int arraySize, int currentPosition)
{
    cout << array[currentPosition];
    if (currentPosition < arraySize - 1) {
        if (array[currentPosition + 1] > 0)
            cout << "+";
        printArray(array, arraySize, currentPosition + 1);
    } else
        cout << endl;
}

// given; do NOT modify; please refer to the webpage description
void printArray(int array[], int arraySize)
{
    printArray(array, arraySize, 0);
}


//***** Only write your code below this line, remember that NO loop is allowed! *****
int strlen(const char str[], int currentPosition) {
    if (str[currentPosition] == '\0') {
        return currentPosition;
    }
    return strlen(str, currentPosition + 1);
}

int strlen(const char str[]) { return strlen(str, 0); }

void swap(int arr[], int i, int j, int n) {
    if (j >= n) {
        return;
    }
    if (arr[i] > arr[j]) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    swap(arr, i + 1, j + 1, n);
}
void bubbleSort(int arr[], int i) {
    if (i == 0) {
        return;
    }
    swap(arr, 0, 1, i);
    bubbleSort(arr, i - 1);
}

int arraySum(int array[], int arraySize, int currentPosition)
{
    if (currentPosition == arraySize)
        return 0;
    else
        return array[currentPosition] +
        arraySum(array, arraySize, currentPosition + 1);
}

int arraySum(int array[], int arraySize) {
    
    return arraySum(array, arraySize, 0); // change this line if you want
}

bool solveRecursive(int input[], int size, int currentValue, int targetValue,
                    int currentPosition, int result[], int &resultSize) {
    if (currentValue == targetValue) {
        return true;
    }
    if (currentPosition == size) {
        return false;
    } else {
        result[resultSize] = input[currentPosition];
        resultSize += 1;
        if (solveRecursive(input, size, currentValue + input[currentPosition],
                           targetValue, currentPosition + 1, result, resultSize)) {
            return true;
        }
        result[resultSize - 1] = 0;
        resultSize -= 1;
        
        result[resultSize] = -input[currentPosition];
        resultSize += 1;
        if (solveRecursive(input, size, currentValue - input[currentPosition],
                           targetValue, currentPosition + 1, result, resultSize)) {
            return true;
        }
        result[resultSize - 1] = 0;
        resultSize -= 1;
        
        if (solveRecursive(input, size, currentValue, targetValue,
                           currentPosition + 1, result, resultSize)) {
            return true;
        }
    }
    return false;
}

bool solve(int input[], int size, int target, int result[], int &resultSize) {
    return solveRecursive(input, size, 0, target, 0, result, resultSize);
}

void printString(const char str[], int currentPosition) {
    cout << str[currentPosition];
    if (currentPosition < strlen(str) - 1)
        printString(str, currentPosition + 1);
    else
        cout << endl;
}

void printString(const char str[]) {
    printString(str, 0);
}

int getintValueRecursive(const char str[], int start, int end,
                         int &currentPosition) {
    if (currentPosition < start || currentPosition > end) {
        return 0;
    }
    if (str[currentPosition] >= '0' && str[currentPosition] <= '9') {
        int result = str[currentPosition] - '0';
        currentPosition -= 1;
        return result + 10 * getintValueRecursive(str, start, end, currentPosition);
    }
    return 0;
}
int getIntValue(const char str[], int start, int end) {
    int currentPosition = end;
    return getintValueRecursive(str, start, end, currentPosition);
}

void evaluateRecursive(const char str[], int atomStart, int atomEnd, int &currentPosition, int &result, const int length, int sign) {
    if (currentPosition > length) {
        return;
    }
    if (str[currentPosition] == '+') {
        atomEnd = currentPosition - 1;
        result += sign * getIntValue(str, atomStart, atomEnd);
    
        sign = 1;
        currentPosition += 1;
        atomStart = currentPosition;
        evaluateRecursive(str, atomStart, atomEnd, currentPosition, result, length, sign);
    } else if (str[currentPosition] == '-' ) {
        atomEnd = currentPosition - 1;
        result += sign * getIntValue(str, atomStart, atomEnd);
    
        sign = -1;
        currentPosition += 1;
        atomStart = currentPosition;
        evaluateRecursive(str, atomStart, atomEnd, currentPosition, result, length, sign);
    } else if (currentPosition == length) {
        atomEnd = currentPosition;
        result += sign * getIntValue(str, atomStart, atomEnd-1);
    
        return;
    } else {
        currentPosition += 1;
        evaluateRecursive(str, atomStart, atomEnd, currentPosition, result, length, sign);
    }
}

int evaluate(const char str[]) {
    int result = 0;
    int currentPosition = 0;
    int length = strlen(str);
    int sign = 1;
    int atomStart = 0;
    int atomEnd = 0;
    
    evaluateRecursive(str, atomStart, atomEnd, currentPosition, result, length, sign);
    return result;
}

//***** Only write your code above this line, remember that NO loop is allowed!
//*****

int main() {
    int testCase;
    cout << "Hi, recursion master! Which test case do you want to run?" << endl;
    cin >> testCase;
    
    cout << endl << "Test case " << testCase << " output:" << endl;
    cout << "===================================" << endl;
    
    if (testCase ==
        0) // this test case is used to show you how printArray works; it is NOT
        // used to grade your work and it is NOT on ZINC; no mark is allocated
        // to this; try it on your own computer if you want
    {
        int array1[] = {1, 2, 3};
        printArray(array1, 3);
        int array2[] = {1, 2, 3, -4};
        printArray(array2, 4);
        int array3[] = {-8, 2, 1, -4};
        printArray(array3, 4);
        int array4[] = {99};
        printArray(array4, 1);
        int array5[] = {-1199};
        printArray(array5, 1);
    }
    
    else if (testCase == 1) // test arraySum
    {
        int array[] = {1, 2, 3};
        cout << arraySum(array, 3) << endl;
    } else if (testCase == 2) // test arraySum
    {
        int array[] = {-1, -234, 33, 5};
        cout << arraySum(array, 4) << endl;
    }
    
    else if (testCase == 3) // test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = 2;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        cout << target << endl;
        printArray(input, size);
        if (solve(input, size, target, result, resultSize)) {
            cout << "solved: ";
            printArray(result, resultSize);
        } else
            cout << "no solution!" << endl;
    } else if (testCase == 4) // test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = -2;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        cout << target << endl;
        printArray(input, size);
        if (solve(input, size, target, result, resultSize)) {
            cout << "solved: ";
            printArray(result, resultSize);
        } else
            cout << "no solution!" << endl;
    } else if (testCase == 5) // test solve
    {
        int input[] = {1, 2, 3, 4};
        int size = 4;
        int target = 9;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        cout << target << endl;
        printArray(input, size);
        if (solve(input, size, target, result, resultSize)) {
            cout << "solved: ";
            printArray(result, resultSize);
        } else
            cout << "no solution!" << endl;
    } else if (testCase == 6) // test solve
    {
        int input[] = {8, 13, 1, 3, 5, 9};
        int size = 6;
        int target = 9;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        cout << target << endl;
        printArray(input, size);
        if (solve(input, size, target, result, resultSize)) {
            cout << "solved: ";
            printArray(result, resultSize);
        } else
            cout << "no solution!" << endl;
    } else if (testCase == 7) // test solve
    {
        int input[] = {88, 13, 1, 3, 5, 9};
        int size = 6;
        int target = 9;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        cout << target << endl;
        printArray(input, size);
        if (solve(input, size, target, result, resultSize)) {
            cout << "solved: ";
            printArray(result, resultSize);
        } else
            cout << "no solution!" << endl;
    } else if (testCase == 8) // test solve
    {
        int input[] = {888, 13333, 20000, 1, 99, 3, 5, 9, 33, 44, 55, 100};
        int size = 12;
        int target = -165;
        int result[ARRAY_MAX_SIZE] = {}; // filled with '\0'
        int resultSize = 0;
        cout << target << endl;
        printArray(input, size);
        if (solve(input, size, target, result, resultSize)) {
            cout << "solved: ";
            printArray(result, resultSize);
        } else
            cout << "no solution!" << endl;
    }
    
    else if (testCase == 9) // test printString
    {
        printString("1+1-2+1234");
    } else if (testCase == 10) // test printString
    {
        printString("Wow this assignment is so much fun!!!");
    }
    
    else if (testCase == 11) // test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 2) << endl;
    } else if (testCase == 12) // test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 1) << endl;
    } else if (testCase == 13) // test getIntValue
    {
        char str[] = "567";
        cout << getIntValue(str, 0, 0) << endl;
    } else if (testCase == 14) // test getIntValue
    {
        char str[] = "abc567abc";
        cout << getIntValue(str, 4, 5) << endl;
    }
    
    else if (testCase == 15) // test evaluate
    {
        cout << evaluate("172") << endl;
    } else if (testCase == 16) // test evaluate
    {
        cout << evaluate("3+2") << endl;
    } else if (testCase == 17) // test evaluate
    {
        cout << evaluate("1+2-4") << endl;
    } else if (testCase == 18) // test evaluate
    {
        cout << evaluate("11+21-43") << endl;
    } else if (testCase == 19) // test evaluate
    {
        cout << evaluate("11+21-43+888") << endl;
    } else if (testCase == 20)
    {
        cout << evaluate("-21") << endl;
    }
    cout << "===================================" << endl;
    
    return 0;
}

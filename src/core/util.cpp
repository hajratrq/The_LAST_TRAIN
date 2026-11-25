#include "util.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
using namespace std;
// Primitive helper utilities, clamping, and screen control
int clampInt(int val, int minVal, int maxVal) {
    if (val < minVal) {
        return minVal;
    }
    if (val > maxVal) {
        return maxVal;
    }
    return val;
}
void trimWhitespace(char* str) {
    int start = -1, end = -1;
    int size = strlen(str);
    for (int i = 0;i < size;i++) {
        if (isspace(str[i]) == 0) {
            start = i;
            break;
        }
    }
    //isspace will find the white space at the given index if it is not 1 then our actual index starts
    for (int i = size - 1;i >= 0;i--) {
        if (isspace(str[i]) == 0) {
            end = i;
            break;
        }
    }
    //in case of empty string start and end both -1 rahien gy so set the 0th index to null terminator
    if (start == -1 || end == -1) {
        *str = '\0';
        return;
    }
    //why added 1 because end -start will give only the difference but actual characters are one more than it
    size = end - start + 1;
    for (int i = 0;i < size;i++) {
        str[i] = str[start];
        start++;
    }
    //after shifting the remaining index will still be occupied by the previously stored characters here so ignr them 
    str[size] = '\0';
}
bool stringEquals(const char* a, const char* b) {
    int size1, size2;
    size1 = strlen(a);
    size2 = strlen(b);
    if (size1 == size2) {
        for (int i = 0;i < size1;i++) {
            if (a[i] != b[i]) {
                return 0;
            }
        }
        return 1;
    }
    else {
        return 0;
    }
}
void printHeader(const char* title) {
    cout << "\t" << title << "\t" << endl;
}
void clearScreen() {
    system("clear");
}
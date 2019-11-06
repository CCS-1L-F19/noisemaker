#include <iostream>
#include "fileFuncs.h"

using namespace std;

int main() {
    sample s[100000];
    for (int i = 0; i < sizeof(s) / sizeof(sample); i++) {
        s[i] = INT16_MAX;
    }
    writeWavFile(fopen("test.wav", "w"), s, sizeof(s) / sizeof(sample), 10000);
}
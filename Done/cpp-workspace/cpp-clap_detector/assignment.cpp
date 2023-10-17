#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "wav-file.h"

using namespace std;

double ampleitude(string input, size_t msec, const short *samples) {
    double curr = 0;
    size_t t = msec * wav_file_sampling_rate(input) / 100;

    while (t < (msec + 1) * wav_file_sampling_rate(input) / 100) {
        if (curr < abs(samples[t]))
            curr = abs(samples[t]);
            t++;
    }
    curr = curr / SHRT_MAX;
    
    return curr;
}

int main() {
    string input = "inp.wav";
    
    short samples[wav_file_sampling_rate(input)];
    double prev = 0, curr = 0;
    
    size_t msec = 0, sec = 0;
    while (sec < wav_file_length(input) / wav_file_sampling_rate(input)) {
        fill_n(samples, wav_file_sampling_rate(input), 0);
        wav_file_data(input, samples, sec * wav_file_sampling_rate(input), wav_file_sampling_rate(input));
        
        for (msec = 0; msec < 100; msec++) {
            curr = ampleitude(input, msec, samples);
            if (curr >= prev * 8 && curr >= 0.03)
                cout << setw(8) << fixed << setprecision(2) << sec + double(msec) / 100 << endl;
            prev = curr;
        }
        sec++;
    }
    
    return 0;
}

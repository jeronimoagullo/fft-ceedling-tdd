#include "fft.h"

#define M_PI 3.14159265358979323846

void fft_radix2(complex_t *x, int N) {
    if (N < 2) return;

    complex_t *even = (complex_t *)malloc(N / 2 * sizeof(complex_t));
    complex_t *odd = (complex_t *)malloc(N / 2 * sizeof(complex_t));

    for (int i = 0; i < N / 2; i++) {
        even[i] = x[2 * i];
        odd[i] = x[2 * i + 1];
    }

    fft_radix2(even, N / 2);
    fft_radix2(odd, N / 2);

    for (int k = 0; k < N / 2; k++) {
        complex_t t = {
            cos(-2 * M_PI * k / N),
            sin(-2 * M_PI * k / N)
        };
        complex_t prod = {
            odd[k].real * t.real - odd[k].imag * t.imag,
            odd[k].real * t.imag + odd[k].imag * t.real
        };
        x[k] = (complex_t){
            even[k].real + prod.real,
            even[k].imag + prod.imag
        };
        x[k + N / 2] = (complex_t){
            even[k].real - prod.real,
            even[k].imag - prod.imag
        };
    }

    free(even);
    free(odd);
}

void fft_generate_sine_wave(complex_t *signal, int num_samples, int freq_bin) {
    for (int i = 0; i < num_samples; i++) {
        signal[i].real = sin(2 * M_PI * freq_bin * i / num_samples);
        signal[i].imag = 0.0f;
    }
}
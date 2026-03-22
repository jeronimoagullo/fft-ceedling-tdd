#ifndef FFT_H_
#define FFT_H_

#include <math.h>
#include <stdlib.h>

// Estructura para representar numeros complejos
typedef struct {
    float real;
    float imag;
} complex_t;

// Prototipo de la funcion principal
void fft_radix2(complex_t *data, int N);

void fft_generate_sine_wave(complex_t* singal, int num_samples, int freq_bin);

#endif /* FFT_H_ */
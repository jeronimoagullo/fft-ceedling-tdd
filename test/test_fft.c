#include "unity.h"
#include "fft.h"

#define N_SAMPLES 256
#define FLOAT_TOLERANCE 1e-6f

void setUp(void) {}
void tearDown(void) {}

void test_fft_of_an_impulse_should_be_flat(void) {
    static complex_t test_signal[N_SAMPLES] = {0};
    test_signal[0].real = 1.0f;

    fft_radix2(test_signal, N_SAMPLES);
    for (int i = 0; i < N_SAMPLES; i++) {
        TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 1.0f, test_signal[i].real);
        TEST_ASSERT_FLOAT_WITHIN(FLOAT_TOLERANCE, 0.0f, test_signal[i].imag);
    }
}

void test_fft_sine(void) {
    static complex_t test_signal[N_SAMPLES];
    int signal_freq_bin = 20;
    fft_generate_sine_wave(test_signal, N_SAMPLES, signal_freq_bin);

    fft_radix2(test_signal, N_SAMPLES);

    float max_magnitude = -1.0f;
    int peak_index = 0;

    for (int i = 0; i < N_SAMPLES / 2; i++) {
        float mag = sqrt(test_signal[i].real * test_signal[i].real +
                         test_signal[i].imag * test_signal[i].imag);

        if (mag > max_magnitude) {
            max_magnitude = mag;
            peak_index = i;
        }
    }
    TEST_ASSERT_EQUAL_INT(signal_freq_bin, peak_index);
}
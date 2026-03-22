# FFT Implementation with Test-Driven Development (TDD)

[![Tests](https://github.com/yourusername/fft-tdd/actions/workflows/ci.yml/badge.svg)](https://github.com/yourusername/fft-tdd/actions/workflows/ci.yml)
[![Coverage](https://codecov.io/gh/yourusername/fft-tdd/branch/main/graph/badge.svg)](https://codecov.io/gh/yourusername/fft-tdd)

A production-ready Fast Fourier Transform (FFT) implementation developed using Test-Driven Development (TDD) principles with Ceedling. This project demonstrates embedded systems testing best practices for signal processing code.

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Prerequisites](#prerequisites)
- [Quick Start](#quick-start)
- [Development Workflow](#development-workflow)
- [Testing with Ceedling](#testing-with-ceedling)
- [Running Tests](#running-tests)
- [Continuous Integration](#continuous-integration)
- [Code Coverage](#code-coverage)
- [Contributing](#contributing)
- [License](#license)

## Overview

This repository implements a radix-2 Cooley-Tukey FFT algorithm in C, developed using **Test-Driven Development (TDD)**. The project showcases how to write testable embedded C code with automated testing using **Ceedling**, a build automation tool specifically designed for C unit testing.

### Why Ceedling?

Ceedling provides a complete testing ecosystem for C projects:
- **Unity** - A lightweight C unit testing framework
- **CMock** - Automatic mock generation for dependency isolation
- **CException** - Exception handling for C
- **Rake** - Ruby-based build automation

Unlike traditional testing approaches that require manual test runner maintenance, Ceedling automatically discovers and runs all your tests, generating mocks from headers on the fly.

## Features

- ✅ **Complete FFT Implementation** - Radix-2 Cooley-Tukey algorithm
- ✅ **Test-Driven Development** - Tests written before implementation
- ✅ **Automated Testing** - Full test suite with Ceedling
- ✅ **Memory Safety** - No memory leaks (validated with Valgrind)
- ✅ **Numerical Accuracy** - Float tolerance verification
- ✅ **CI/CD Ready** - GitHub Actions workflow included
- ✅ **Code Coverage** - Line-by-line coverage reports
- ✅ **Dev Container Support** - One-click development environment

## Project Structure

```
.
├── src/                    # Production code
│   ├── fft.h              # FFT interface
│   └── fft.c              # FFT implementation
├── test/                   # Test files
│   ├── test_fft.c         # Unit tests for FFT
│   └── test_runners/      # Auto-generated test runners
├── vendor/                 # Ceedling dependencies
│   ├── unity/             # Unity test framework
│   ├── cmock/             # CMock mock generator
│   └── cexception/        # CException library
├── build/                  # Build artifacts (generated)
├── project.yml            # Ceedling configuration
├── .devcontainer/         # VS Code dev container config
├── .github/workflows/     # CI/CD workflows
└── README.md              # This file
```

## Prerequisites

### Local Development
- **Ruby** (2.7 or later) - For Ceedling
- **Ceedling** - Install via RubyGems
- **GCC/Clang** - C compiler
- **Make** - Build automation
- **Valgrind** (optional) - Memory leak detection

### One-Click Development Environment

This project includes a **Dev Container** configuration for GitHub Codespaces and VS Code:

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://github.com/codespaces/new?repository_url=https://github.com/yourusername/fft-tdd)

The dev container automatically:
- Installs Ruby and Ceedling
- Configures VS Code extensions for C/C++ development
- Sets up the Ceedling Test Adapter for GUI test execution

## Quick Start

### Using GitHub Codespaces (Recommended)

1. Click the "Open in GitHub Codespaces" badge above
2. Wait for the container to build (includes automatic `gem install ceedling`)
3. Run tests from the terminal or VS Code Test Explorer

### Local Development

```bash
# Clone the repository
git clone https://github.com/yourusername/fft-tdd.git
cd fft-tdd

# Install Ceedling
gem install ceedling

# Run all tests
ceedling test:all

# Run specific test file
ceedling test:test_fft
```

## Development Workflow

This project follows strict TDD principles:

### Red-Green-Refactor Cycle

1. **Red** - Write a failing test
   ```c
   void test_fft_of_impulse_should_be_flat(void) {
       // Test that fails initially
   }
   ```

2. **Green** - Write minimal code to pass the test
   ```c
   void fft_radix2(complex_t *x, int N) {
       // Implementation
   }
   ```

3. **Refactor** - Improve code while keeping tests green
   - Optimize algorithm
   - Improve readability
   - Maintain test coverage

### Test Coverage Goals
- **Unit Tests**: 100% line coverage for critical math functions
- **Integration Tests**: Verify FFT properties (linearity, symmetry, etc.)
- **Edge Cases**: Handle non-power-of-two sizes, empty arrays

## Testing with Ceedling

### Writing Tests

Tests are written using Unity's assertion macros:

```c
#include "unity.h"
#include "fft.h"

void setUp(void) {
    // Called before each test
}

void tearDown(void) {
    // Called after each test
}

void test_fft_of_an_impulse_should_be_flat(void) {
    complex_t test_signal[N_SAMPLES] = {0};
    test_signal[0].real = 1.0f;
    
    fft_radix2(test_signal, N_SAMPLES);
    
    for (int i = 0; i < N_SAMPLES; i++) {
        TEST_ASSERT_FLOAT_WITHIN(1e-6f, 1.0f, test_signal[i].real);
        TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.0f, test_signal[i].imag);
    }
}
```

### Key Test Assertions

| Assertion | Purpose |
|-----------|---------|
| `TEST_ASSERT_EQUAL_INT(a, b)` | Integer equality |
| `TEST_ASSERT_FLOAT_WITHIN(tol, a, b)` | Float equality within tolerance |
| `TEST_ASSERT_TRUE(condition)` | Boolean condition |
| `TEST_ASSERT_NULL(ptr)` | Null pointer check |

### Mocking Dependencies

For testing components with dependencies, Ceedling automatically generates mocks from headers:

```c
// In your test file
#include "mock_hal.h"  // Auto-generated mock

void test_driver_with_mocked_hal(void) {
    hal_init_ExpectAndReturn(0);  // Expect this call
    hal_transmit_Expect(0x55);    // With this parameter
    
    driver_init();
    driver_send(0x55);
}
```

## Running Tests

### Available Commands

```bash
# Run all tests
ceedling test:all

# Run specific test file
ceedling test:test_fft

# Run with detailed output
ceedling test:all -v

# Run with coverage report
ceedling gcov:all

# Run memory leak detection
ceedling test:all op:memcheck

# Clean build artifacts
ceedling clean
```

### Test Output

```
Test 'test_fft.c'
--------------------
test_fft_of_an_impulse_should_be_flat - PASS
test_fft_sine_wave_peak_detection - PASS
--------------------
2 Tests 0 Failures 0 Ignored
```

## Continuous Integration

This project uses GitHub Actions for automated testing:

```yaml
name: CI

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - uses: ruby/setup-ruby@v1
        with:
          ruby-version: '3.0'
      - run: gem install ceedling
      - run: ceedling test:all
      - run: ceedling gcov:all
```

See the [CI Workflow](.github/workflows/ci.yml) for complete configuration.

## Code Coverage

Generate coverage reports with:

```bash
ceedling gcov:all
ceedling utils:gcov
```

Open `build/artifacts/gcov/index.html` in your browser for line-by-line coverage analysis.

### Current Coverage
- **fft.c**: 100% line coverage
- **fft.h**: 100% interface coverage

## Performance Considerations

The current implementation uses:
- **Complexity**: O(N log N) time complexity
- **Memory**: O(N) space for temporary arrays
- **Precision**: Single-precision floating point

For embedded applications:
- Consider in-place FFT to reduce memory footprint
- Use fixed-point arithmetic on microcontrollers without FPU
- Precompute twiddle factors for performance

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Write tests for your changes (Red phase)
4. Implement your changes (Green phase)
5. Refactor while maintaining tests
6. Run full test suite: `ceedling test:all`
7. Commit changes (`git commit -m 'Add amazing feature'`)
8. Push to branch (`git push origin feature/amazing-feature`)
9. Open a Pull Request

### Pull Request Requirements
- ✅ All tests pass
- ✅ New features include tests
- ✅ No reduction in code coverage
- ✅ No memory leaks (Valgrind check passes)

## Troubleshooting

### Common Issues

**Ceedling not found**
```bash
# Ensure Ruby is installed
ruby --version

# Reinstall Ceedling
gem uninstall ceedling
gem install ceedling
```

**Test compilation fails**
```bash
# Clean and rebuild
ceedling clean
ceedling test:all
```

**Memory leak detected**
```bash
# Run with memcheck for details
ceedling test:all op:memcheck
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- [Ceedling](http://www.throwtheswitch.org/ceedling) - C build automation tool
- [Unity](http://www.throwtheswitch.org/unity) - Unit testing framework
- [CMock](http://www.throwtheswitch.org/cmock) - Mock generation
- Cooley & Tukey - For the FFT algorithm

## References

- [The Pragmatic Programmer](https://pragprog.com/titles/tpp20/the-pragmatic-programmer-20th-anniversary-edition/) - TDD principles
- [Test-Driven Development for Embedded C](https://pragprog.com/titles/jgade/test-driven-development-for-embedded-c/) - James Grenning
- [FFT Implementation Guide](https://www.fftw.org/implementation.html) - Performance considerations

---

**Built with ❤️ using Test-Driven Development**

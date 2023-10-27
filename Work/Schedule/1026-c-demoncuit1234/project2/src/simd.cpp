//
// Created by Yang Yufan on 2023/10/07.
// Email: yufanyang1@link.cuhk.edu.cn
//
// SIMD + Reordering Matrix Multiplication
//

#include <immintrin.h>
#include <stdexcept>
#include <chrono>
#include "matrix.hpp"

struct simd_float {
    __m256 value;

    simd_float() {}
    simd_float(__m256 value) : value(value) {}

    simd_float operator+(const simd_float& other) const {
        return simd_float(_mm256_add_ps(value, other.value));
    }

    simd_float operator*(const simd_float& other) const {
        return simd_float(_mm256_mul_ps(value, other.value));
    }

    static simd_float load(const float* data) {
        return simd_float(_mm_loadu_ps(data));
    }

    void store(float* data) const {
        _mm_storeu_ps(data, value);
    }
};

Matrix matrix_multiply_simd(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.getCols() != matrix2.getRows()) {
        throw std::invalid_argument(
            "Matrix dimensions are not compatible for multiplication.");
    }

    size_t M = matrix1.getRows(), K = matrix1.getCols(), N = matrix2.getCols();

    Matrix result(M, N);

    const size_t size = 32;

    for (size_t i = 0; i < M; i += size) {
        for (size_t k = 0; k < K; k += size) {
            for (size_t j = 0; j < N; j += size) {
                for (size_t i_block = i; i_block < i + size; i_block += simd_width) {
                    for (size_t k_block = k; k_block < k + size; k_block += simd_width) {
                        for (size_t j_block = j; j_block < j + size; j_block += simd_width) {
                            simd_float a = _mm_loadu_ps(matrix1.data + i_block * K + k_block);
                            simd_float b = _mm_loadu_ps(matrix2.data + k_block * N + j_block);
                            simd_float c = _mm_dp_ps(a, b, simd_width);

                            _mm_storeu_ps(result.data() + i_block * N + j_block, c);
                        }
                    }
                }
            }
        }
    }
    
    return result;
}

int main(int argc, char** argv) {
    // Verify input argument format
    if (argc != 4) {
        throw std::invalid_argument(
            "Invalid argument, should be: ./executable "
            "/path/to/matrix1 /path/to/matrix2 /path/to/multiply_result\n");
    }

    const std::string matrix1_path = argv[1];

    const std::string matrix2_path = argv[2];

    const std::string result_path = argv[3];

    Matrix matrix1 = Matrix::loadFromFile(matrix1_path);

    Matrix matrix2 = Matrix::loadFromFile(matrix2_path);

    auto start_time = std::chrono::high_resolution_clock::now();

    Matrix result = matrix_multiply_simd(matrix1, matrix2);

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);

    result.saveToFile(result_path);

    std::cout << "Output file to: " << result_path << std::endl;

    std::cout << "Multiplication Complete!" << std::endl;
    std::cout << "Execution Time: " << elapsed_time.count() << " milliseconds"
              << std::endl;

    return 0;
}

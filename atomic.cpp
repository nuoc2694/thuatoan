#include <iostream>
#include <vector>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()
#include <omp.h>

int main() {
    const int NUM_ARRAYS = 3;
    const int SIZE = 10000000;  // Kích thước mỗi dãy
    const int TARGET = 42;      // Phần tử cần đếm số lần xuất hiện

    // Tạo 3 dãy số ngẫu nhiên
    std::vector<std::vector<int>> arrays(NUM_ARRAYS, std::vector<int>(SIZE));
    std::srand(std::time(0));

    // Khởi tạo giá trị ngẫu nhiên cho các dãy
    for (int i = 0; i < NUM_ARRAYS; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            arrays[i][j] = std::rand() % 100;  // Các phần tử ngẫu nhiên trong khoảng từ 0 đến 99
        }
    }

    int count = 0;  // Biến đếm số lần xuất hiện của phần tử TARGET

    // Đếm số lần xuất hiện của phần tử TARGET sử dụng OpenMP và chỉ thị atomic
    double start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(4)
    for (int i = 0; i < NUM_ARRAYS; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (arrays[i][j] == TARGET) {
                #pragma omp atomic
                count++;
            }
        }
    }
    double end_time = omp_get_wtime();

    std::cout << "Số lần phần tử " << TARGET << " xuất hiện: " << count << "\n";
    std::cout << "Thời gian thực hiện: " << (end_time - start_time) << " giây\n";

    return 0;
}

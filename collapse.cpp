#include <iostream>
#include <vector>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()
#include <omp.h>

int main() {
    const int NUM_ARRAYS = 3;
    const int SIZE = 5000000;
    
    // Tạo 3 dãy số ngẫu nhiên
    std::vector<std::vector<int>> arrays(NUM_ARRAYS, std::vector<int>(SIZE));
    std::srand(std::time(0));

    for (int i = 0; i < NUM_ARRAYS; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            arrays[i][j] = std::rand();
        }
    }

    long long total_sum = 0;

    // Tính tổng song song sử dụng chỉ thị collapse(2)
    double start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(4) collapse(2)
    for (int i = 0; i < NUM_ARRAYS; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            #pragma omp atomic
            total_sum += arrays[i][j];
        }
    }
    double end_time = omp_get_wtime();

    std::cout << "Tổng (sử dụng collapse): " << total_sum << "\n";
    std::cout << "Thời gian (sử dụng collapse): " << (end_time - start_time) << " giây\n";

    return 0;
}

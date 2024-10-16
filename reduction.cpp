#include <iostream>
#include <vector>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()
#include <omp.h>

int main() {
    const int SIZE = 10000000;
    std::vector<int> data(SIZE);

    // Tạo dữ liệu ngẫu nhiên
    std::srand(std::time(0));
    for (int i = 0; i < SIZE; ++i) {
        data[i] = std::rand();
    }

    long long total_sum = 0;

    // Tính tổng song song sử dụng chỉ thị reduction
    double start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(4) reduction(+:total_sum)
    for (int i = 0; i < SIZE; i++) {
        total_sum += data[i];
    }
    double end_time = omp_get_wtime();

    std::cout << "Tổng (reduction): " << total_sum << "\n";
    std::cout << "Thời gian (reduction): " << (end_time - start_time) << " giây\n";

    return 0;
}

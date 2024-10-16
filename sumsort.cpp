#include <iostream>
#include <vector>
#include <numeric>  // for std::accumulate
#include <algorithm> // for std::sort
#include <omp.h>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()

// Hàm tính tổng tuần tự
long long sequential_sum(const std::vector<int>& data) {
    return std::accumulate(data.begin(), data.end(), 0LL);
}

// Hàm tính tổng song song bằng OpenMP với 4 thread
long long parallel_sum(const std::vector<int>& data) {
    long long total_sum = 0;
    #pragma omp parallel for num_threads(4) reduction(+:total_sum)
    for (int i = 0; i < data.size(); i++) {
        total_sum += data[i];
    }
    return total_sum;
}

// Hàm sắp xếp song song (được thực hiện trong thread 5)
void sort_in_thread(std::vector<int>& data) {
    #pragma omp parallel num_threads(5)
    {
        if (omp_get_thread_num() == 4) {
            std::sort(data.begin(), data.end());
        }
    }
}

int main() {
    const int SIZE = 10000000;
    std::vector<int> data(SIZE);
    
    // Tạo dữ liệu ngẫu nhiên
    std::srand(std::time(0));
    for (int i = 0; i < SIZE; ++i) {
        data[i] = std::rand();
    }
    
    // Tính tổng và đo thời gian thực hiện thuật toán tuần tự
    double start_time = omp_get_wtime();
    long long sum_seq = sequential_sum(data);
    double end_time = omp_get_wtime();
    std::cout << "Tổng tuần tự: " << sum_seq << "\n";
    std::cout << "Thời gian tuần tự: " << (end_time - start_time) << " giây\n";

    // Tính tổng và đo thời gian thực hiện thuật toán song song
    start_time = omp_get_wtime();
    long long sum_par = parallel_sum(data);
    end_time = omp_get_wtime();
    std::cout << "Tổng song song: " << sum_par << "\n";
    std::cout << "Thời gian song song: " << (end_time - start_time) << " giây\n";

    // Sắp xếp dãy số bằng 1 thread riêng (thread 5)
    start_time = omp_get_wtime();
    sort_in_thread(data);
    end_time = omp_get_wtime();
    std::cout << "Thời gian sắp xếp song song (thread 5): " << (end_time - start_time) << " giây\n";

    return 0;
}

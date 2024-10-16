#include <iostream>
#include <vector>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()
#include <omp.h>

int main() {
    const int m = 500;  // số hàng của ma trận
    const int n = 500;  // số cột của ma trận

    // Tạo ma trận A và B ngẫu nhiên
    std::vector<std::vector<int>> A(m, std::vector<int>(n));
    std::vector<std::vector<int>> B(n, std::vector<int>(m));  // Kích thước của B là n x m
    std::vector<std::vector<int>> C(m, std::vector<int>(m, 0));  // Ma trận kết quả C có kích thước m x m

    std::srand(std::time(0));

    // Khởi tạo giá trị ngẫu nhiên cho A và B
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            A[i][j] = std::rand() % 100;
            B[j][i] = std::rand() % 100;  // B được khởi tạo với kích thước ngược
        }
    }

    // Tính tích ma trận C = A x B theo cách tuần tự
    double start_time = omp_get_wtime();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double end_time = omp_get_wtime();

    std::cout << "Thời gian tính tuần tự: " << (end_time - start_time) << " giây\n";

    return 0;
}

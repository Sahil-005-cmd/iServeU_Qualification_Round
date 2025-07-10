#include <iostream>
#include <vector>
using namespace std;

const int MAX = 10000;
vector<bool> prime(MAX + 1, true);

void precompute_sieve() {
    prime[0] = prime[1] = false;
    for (int i = 2; i * i <= MAX; ++i) {
        if (prime[i]) {
            for (int j = i * i; j <= MAX; j += i)
                prime[j] = false;
        }
    }
}

int compute_zigzag_sum(int** matrix, int n) {
    int i = 0, j = 0;
    bool up = true;
    int sum = 0;

    for (int cnt = 0; cnt < n * n; ++cnt) {
        int val = matrix[i][j];
        sum += prime[val] ? -val : val;

        if (up) {
            if (j == n - 1) {
                ++i;
                up = false;
            } else if (i == 0) {
                ++j;
                up = false;
            } else {
                --i;
                ++j;
            }
        } else {
            if (i == n - 1) {
                ++j;
                up = true;
            } else if (j == 0) {
                ++i;
                up = true;
            } else {
                ++i;
                --j;
            }
        }
    }

    return sum;
}

int main() {
    int n = 3;
    int** matrix = new int*[n];
    int data[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; ++j)
            matrix[i][j] = data[i][j];
    }

    precompute_sieve();  // Sieve only once
    cout << compute_zigzag_sum(matrix, n) << endl;

    for (int i = 0; i < n; ++i) delete[] matrix[i];
    delete[] matrix;

    return 0;
}
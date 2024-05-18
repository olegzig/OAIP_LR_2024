#include <iostream>
#include <vector>

double StirlingRec(int N, int K)
{
    if (N == K) return 1;
    else
        if (K == 0 or N == 0 or N < K) return 0;
        else
            return StirlingRec(N - 1, K - 1) + K * StirlingRec(N - 1, K);

}

double StrirlingIter(int n, int k) {
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            dp[i][j] = dp[i - 1][j - 1] + j * dp[i - 1][j];
        }
    }

    return dp[n][k];
}

int main()
{
    int n = 5;
    int k = 2;
    std::cout << "Input N: ";
    std::cin >> n;
    std::cout << "Input K: ";
    std::cin >> k;

    std::cout << "stirling recursive: "<< StirlingRec(n,k) << "\n";
    std::cout << "stirling iterative: " << StrirlingIter(n, k) << "\n";

    std::cin;
}

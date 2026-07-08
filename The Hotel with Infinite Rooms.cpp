#include<bits/stdc++.h>
using namespace std;

// 判斷 S + (S + 1) + ... + E 是否 >= D
bool Enough(long long S, long long E, long long D) {
    long long term = E - S + 1; // 項數
    long long sum = E + S;      // 首項 + 末項

    // 等差級數：(首項 + 末項) * 項數 / 2
    // 先除以 2，降低乘法大小
    if (sum % 2 == 0) {
        sum /= 2;
    } else {
        term /= 2;
    }

    // 要判斷 sum * term >= D
    // 但不直接乘，避免 overflow
    return sum >= (D + term - 1) / term;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long S, D;

    while (cin >> S >> D) {
        // 開區間二分：
        // left 一定不夠，right 一定足夠
        long long left = S - 1;
        long long right = S + D;

        while (left + 1 < right) {
            long long mid = left + (right - left) / 2;

            // 如果加到 mid 已經涵蓋第 D 天，
            // 答案可能是 mid 或更小
            if (Enough(S, mid, D)) {
                right = mid;
            }
            // 否則代表 mid 還不夠大
            else {
                left = mid;
            }
        }

        cout << right << '\n';
    }

    return 0;
}

/*
題目:
給你兩個數 S 和 D：
    S：第一組客人的人數。
    D：問第 D 天住在旅館的是幾人團。
規則是：
    第一組有 S 人，會住 S 天。
    下一組有 S + 1 人，會住 S + 1 天。
    再下一組有 S + 2 人，會住 S + 2 天。
    依此類推。
    輸入有多筆資料，讀到 EOF 為止。

思路:
1.假設答案是 n，代表第 D 天住的是 n 人團。
2. S + (S + 1) + ... + n >= D
3.這題 D < 10^15，不能用一天一天模擬，但可以用等差級數公式：
    sum(S ~ n) = (S + n) * (n - S + 1) / 2
使用二分去找答案

Note:
sum * term >= D
=> sum >= D / term ，但是 C++ 除法會無條件捨去 
因此需要 sum >= ceil(D / term) => (D + term - 1) / term
(term - 1 是用來補足「只要有餘數，就要往上多算一格」)
*/
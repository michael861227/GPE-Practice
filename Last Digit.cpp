#include <bits/stdc++.h>
using namespace std;

int powerLastDigit(int base, int exp) {
    int result = 1;
    base %= 10;

    while (exp > 0) {
        if (exp & 1) {
            result = result * base % 10;
        }
        base = base * base % 10;
        exp >>= 1;
    }

    return result;
}

int getMod100(const string& s) {
    int mod = 0;

    for (char c : s) {
        mod = (mod * 10 + (c - '0')) % 100;
    }

    return mod;
}

int main() {
    vector<int> ans(100, 0);

    for (int i = 1; i < 100; i++) {
        ans[i] = (ans[i - 1] + powerLastDigit(i, i)) % 10;
    }

    string n;

    while (cin >> n && n != "0") {
        int index = getMod100(n);
        cout << ans[index] << '\n';
    }

    return 0;
}

/*
題目: 給定一個很大的 N ，要求 1^1 + 2^2 + 3^3 + ... + N^N 的最後一個位數是多少

1. 由於 N 很大，用 long long 也不夠，因此要用 string 來存
2. i^i 的最後一位只跟兩件事有關，因此取兩者的最小公倍數 (20 次循環)
    a. i % 10
    b. 指數 i 的循環位置 (i % 4)
3. S(20) 的最後一個位數是 4，所以 20 項不是完整歸零週期，因此五輪後會歸零，也就是每 100 次累加會循環一次 
4. 處理 i^i 次方，使用快速冪的方法，將指數使用二進位來算
    Ex: 3^12 => 12: 1100(2)，所以可以看成 3^8 * 3^4，只要看 8 跟 4 的尾數相乘就好

*/
#include <bits/stdc++.h>
using namespace std;

struct Line {
    long long A, B, C;

    bool operator<(const Line& other) const {
        if (A != other.A) return A < other.A;
        if (B != other.B) return B < other.B;
        return C < other.C;
    }
};

long long gcd3(long long a, long long b, long long c) {
    return gcd(gcd(abs(a), abs(b)), abs(c));
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        vector<pair<long long, long long>> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i].first >> p[i].second;
        }

        set<Line> lines;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                long long x1 = p[i].first;
                long long y1 = p[i].second;
                long long x2 = p[j].first;
                long long y2 = p[j].second;

                long long A = y2 - y1;
                long long B = x1 - x2;
                long long C = x2 * y1 - x1 * y2;

                long long g = gcd3(A, B, C);
                A /= g;
                B /= g;
                C /= g;

                // 統一符號：讓第一個非 0 係數為正
                if (A < 0 || (A == 0 && B < 0) || (A == 0 && B == 0 && C < 0)) {
                    A = -A;
                    B = -B;
                    C = -C;
                }

                lines.insert({A, B, C});
            }
        }

        cout << lines.size() << '\n';
    }

    return 0;
}

/*

題目: 給定 N 個點，要求這些點可以形成幾個 Unique lines

1. 由 (x1, y1) (x2, y2) 組成的方程式: Ax + By + C = 0
    A = y2 - y1;
    B = x1 - x2;
    C = x2 * y1 - x1 * y2;

2. 要計算 gcd 避免 x + y + 1 = 0 跟 2x + 2y + 2 = 0，這兩個被判定為不一樣的線
3. 使用 set 而不是 unordered_set 的原因:
    a. 兩者的底層實作不同，一個是 RedBlack Tree 另一個是 hash
    b. 這題如果使用 unordered_set 要判斷 a == b，以及 hash(a)，比較麻煩
    c. 反之，set 只需要判定 operator< 就好
*/
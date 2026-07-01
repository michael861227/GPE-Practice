#include<bits/stdc++.h>
using namespace std;

double getWidth(const vector<double>&r){
    int n = r.size();
    vector<double> x(n, 0.0);

    // 按照目前排列順序，依序放置每一個圓
    for (int i = 1; i < n; i++){
        double pos = 0.0;

        // 第 i 個圓必須和前面所有圓都不重疊
        for (int j = 0; j < i; j++){
            double dist = 2.0 * sqrt(r[i] * r[j]);
            pos = max(pos, dist + x[j]);
        }

        x[i] = pos;
    }

    double left = 1e100;
    double right = -1e100;

    // 計算包住所有圓的最左與最右邊界
    for (int i = 0; i < n; i++){
        left = min(left, x[i] - r[i]);
        right = max(right, x[i] + r[i]);
    }

    return right - left;
}

int main(){
    int T;
    cin >> T;

    // Output 小數後三位，fixed:小數點後
    cout << fixed << setprecision(3);

    while (T--){
        int n;
        cin >> n;

        vector<double> r(n);
        for (int i = 0; i < n; i++){
            cin >> r[i];
        }

        // 為了方便使用 next_permutation，確保每個排列都有被列到
        sort(r.begin(), r.end());

        double ans = 1e100;

        // 枚舉所有可能的排列順序
        do {
            ans = min(ans, getWidth(r));
        } while (next_permutation(r.begin(), r.end()));

        cout << ans << '\n';
    }
    return 0;
}

/*
題目：給你 n 個圓的半徑，要把這些圓全部放在同一條水平線上，也就是每個圓都貼著地面。圓之間不能重疊，可以互相相切。
目標是找出一種排列方式，使得包住所有圓的矩形寬度最小。
輸出最小寬度，四捨五入到小數點後三位

假設有兩個圓，半徑分別是 r1 和 r2
1. 圓心距離: r1 + r2
2. 圓心垂直距離: |r1 - r2|
3. 水平距離 dx => dx^2 + (r1 - r2)^2 = (r1 + r2)^2
              => dx = 2 * sqrt(r1 * r2)


思路:
1. n 很小，通常 n <= 8，所以可以暴力枚舉所有圓的排列順序
2. 再放第 i 個圓的時候，它要避開前面每一個圓，否則會讓兩個圓有重疊，因此每個前面的圓都會提出一個最低要求。最後必須選所有要求中最嚴格的那個。
    x[i] 至少要 >= A
    x[i] 至少要 >= B
    x[i] 至少要 >= C
3.最後整體寬度不是單純看最後一個圓，因為大圓可能往左突出。因此要算所有圓的最左邊界和最右邊界
    left  = min(x[i] - r[i])
    right = max(x[i] + r[i])
    width = right - left
*/
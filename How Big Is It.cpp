#include<bits/stdc++.h>
using namespace std;

double getWidth(vector<double> &r){
    int n = r.size();
    
    // x[i]：第 i 個圓的圓心 x 座標
    vector<double> x(n, 0.0);

    double width = 0;

    for (int i = 0; i < n; i++){
        /*
        圓不能穿過矩形左邊界 x = 0。
        因為圓半徑是 radius[i]，
        所以圓心至少必須位於 x = radius[i]。
         */
        x[i] = r[i];


        /*
        * 檢查所有位於圓 i 前面的圓。
        *
        * 若圓 j 在圓 i 左邊，兩圓圓心所需的最小水平距離是：
        *
        *     2 * sqrt(radius[i] * radius[j])
        *
        * 因此必須有：
        *
        *     x[i] >= x[j] + 2 * sqrt(radius[i] * radius[j])
         */

        for (int j = 0; j < i; j++){
            double dist = 2 * sqrt(r[i] * r[j]);
            x[i] = max(x[i], x[j] + dist);
        }

        // 圓 i 的最右端位置是圓心位置加上半徑
        width = max(width, x[i] + r[i]);
    }

    return width;
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
2. 由於最左邊是牆壁，因此每個圓的初始位置 >= r[i]
3. 再放第 i 個圓的時候，它要避開前面每一個圓，否則會讓兩個圓有重疊，因此每個前面的圓都會提出一個最低要求。最後必須選所有要求中最嚴格的那個。
    x[i] 至少要 >= A
    x[i] 至少要 >= B
    x[i] 至少要 >= C
4. 最後的 width 因為要考慮不同圓的半徑大小，最右邊的位置就是該圓的圓心位置加上半徑，所有園可能的右邊最大值
    right = max(x[i] + r[i])
*/
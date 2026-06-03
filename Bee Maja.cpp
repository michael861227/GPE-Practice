#include <bits/stdc++.h>
using namespace std;

int main(){
    long long n;

    while (cin >> n){
        long long max_x = 1;
        long long r = 0;

        while (max_x < n){
            r++;
            max_x += 6 * r;
        }

        long long x = r;
        long long y = 0;
        long long remain = max_x - n;

        auto move = [&](long long len, long long dx, long long dy){
            long long step = min(len, remain);

            x += step * dx;
            y += step * dy;
            remain -= step;
        };

        move(r, 0, -1);
        move(r, -1, 0);
        move(r, -1, 1);
        move(r, 0, 1);
        move(r, 1, 0);
        move(r, 1 , -1);

        cout << x << " " << y << endl;
    }

    return 0;
}

/*
題目: 給定 willi 的做標系，要轉成對應的 Maja 坐標系

1. 第 0 圈 :  1 -> (0, 0)，第 r 圈有 6 * r 個格子
2. 每一圈的最大編號會落在 (r, 0)
    7 -> (1, 0)
    19 -> (2, 0)
    37 -> (3, 0)
3. max(r) = 1 + 6 * (1 + 2 + ... + r) ，每一層都比上一層多 6 * r
4. 先找到 n 在第幾圈，然後從最大值 (r, 0) 往回走 max(r) - n 步
5. 往回走的六個方向，每個方向最多走 r 步
    (0, -1)
    (-1, 0)
    (-1, 1)
    (0, 1)
    (1, 0)
    (1, -1)
*/
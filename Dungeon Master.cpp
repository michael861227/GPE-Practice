#include <bits/stdc++.h>
using namespace std;

// 用來表示三維空間中的一個位置
// l: layer，第幾層
// r: row，第幾列
// c: column，第幾行
struct Point {
    int l, r, c;
};

int main() {
    int L, R, C;

    // 每次讀入一組地下城大小
    // L: 層數, R: 每層有幾列, C: 每列有幾個字元
    while (cin >> L >> R >> C) {
        // 題目規定 0 0 0 代表輸入結束
        if (L == 0 && R == 0 && C == 0)
            break;

        Point start, end;

        // dungeon[l][r][c]
        // l 表示第幾層
        // r 表示第幾列
        // c 表示第幾行
        //
        // 這裡用 vector<vector<string>> 存三維地圖：
        // dungeon[l] 是第 l 層
        // dungeon[l][r] 是第 l 層的第 r 列字串
        // dungeon[l][r][c] 是該列中的第 c 個字元
        vector<vector<string>> dungeon(L, vector<string>(R));

        // 讀入地下城地圖，同時找出 S 和 E 的位置
        for (int l = 0; l < L; l++) {
            for (int r = 0; r < R; r++) {
                cin >> dungeon[l][r];

                for (int c = 0; c < C; c++) {
                    if (dungeon[l][r][c] == 'S') {
                        start = {l, r, c};
                    } else if (dungeon[l][r][c] == 'E') {
                        end = {l, r, c};
                    }
                }
            }
        }

        // dist[l][r][c] 表示從起點 S 走到這個位置需要幾分鐘
        // 初始值設為 -1，代表還沒有走過
        vector<vector<vector<int>>> dist(
            L, vector<vector<int>>(R, vector<int>(C, -1))
        );

        // 起點距離自己是 0 分鐘
        dist[start.l][start.r][start.c] = 0;

        // BFS 使用 queue，先進先出
        queue<Point> q;
        q.push(start);

        while (!q.empty()) {
            // 取出目前所在位置
            Point cur = q.front();
            q.pop();

            // 六個方向的移動量
            // 要用同一個 index 一起看：
            // i = 0: l + 1，往其中一層移動
            // i = 1: l - 1，往另一層移動
            // i = 2: r + 1，同層往下一列
            // i = 3: r - 1，同層往上一列
            // i = 4: c + 1，同層往右一格
            // i = 5: c - 1，同層往左一格
            int dl[6] = {1, -1, 0, 0, 0, 0};
            int dr[6] = {0, 0, 1, -1, 0, 0};
            int dc[6] = {0, 0, 0, 0, 1, -1};

            // 嘗試往六個方向移動
            for (int i = 0; i < 6; i++) {
                int nl = cur.l + dl[i];
                int nr = cur.r + dr[i];
                int nc = cur.c + dc[i];

                // 如果超出地下城範圍，就不能走
                if (nl < 0 || nl >= L || nr < 0 || nr >= R || nc < 0 || nc >= C)
                    continue;

                // # 代表牆壁，不能走
                if (dungeon[nl][nr][nc] == '#')
                    continue;

                // 如果這個位置已經走過，就不用再走
                // 因為 BFS 第一次走到某格時，一定是最短距離
                if (dist[nl][nr][nc] != -1)
                    continue;

                // 更新新位置的距離
                // 新位置距離 = 目前位置距離 + 1 分鐘
                dist[nl][nr][nc] = dist[cur.l][cur.r][cur.c] + 1;

                // 把新位置加入 queue，之後繼續從這裡往外擴展
                q.push({nl, nr, nc});
            }
        }

        // BFS 結束後，看終點 E 是否有被走到
        int answer = dist[end.l][end.r][end.c];

        if (answer != -1) {
            cout << "Escaped in " << answer << " minute(s)." << endl;
        } else {
            cout << "Trapped!" << endl;
        }
    }

    return 0;
}
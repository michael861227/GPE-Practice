#include<bits/stdc++.h>
using namespace std;

int h, w;
vector<string> grid;
vector<vector<bool>> visited;

// 四個方向：上、下、左、右
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void bfs(int i, int j, char lang){
    queue<pair<int, int>> q;
    visited[i][j] = true;
    q.push({i, j});

    while (!q.empty()){
        auto [row, col] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++){
            int nx = row + dx[i];
            int ny = col + dy[i];

            if (nx < 0 || nx >= h || ny < 0 || ny >= w){
                continue;
            }

            if (grid[nx][ny] != lang || visited[nx][ny])
                continue;
            
            q.push({nx, ny});
            visited[nx][ny] = true;
        }
    }
}

int main(){
    int T;
    cin >> T;

    for (int tc = 1; tc <= T; tc++){
        cin >> h >> w;

        grid.assign(h, "");
        visited.assign(h, vector<bool> (w, false));

        for (int i = 0; i < h; i++){
            cin >> grid[i];
        }

        unordered_map<char, int> count;

        for (int i = 0; i < h; i++){
            for (int j = 0; j < w; j++){
                if (visited[i][j])
                    continue;
                
                char lang = grid[i][j];
                // 找到一個新的連通區域
                count[lang]++;
                // 把這個區域內所有相同語言的格子標記起來
                bfs(i, j, lang);
            }
        }

        vector<pair<char, int>> results;

        for (auto &p : count){
            results.push_back(p);
        }

        sort(results.begin(), results.end(), [](const auto &a, const auto &b){
            if (a.second != b.second){
                return a.second > b.second;
            }
            return a.first < b.first;
        });

        cout << "World #" << tc << endl;

        for (auto &[c, num] : results){
            cout << c << ": " << num << endl;
        }

    }

    return 0;
}

/*
題目: 給你一張由小寫英文字母組成的地圖：
    每個字母代表一種語言。
    相同字母如果在上下左右四個方向相連，就屬於同一個區域。
    對每種語言，統計它有幾個獨立區域。
    最後依照：
        區域數量由大到小排序
        如果數量相同，字母由小到大排序

輸出每個 world 的語言排名。

*/
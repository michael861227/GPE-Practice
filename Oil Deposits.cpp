#include <bits/stdc++.h>
using namespace std;

vector<string> graph;
vector<vector<bool>> visited;

int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};

void bfs(int i, int j){
    queue<pair<int, int>> q;
    q.push({i, j});
    visited[i][j] = true;

    while (!q.empty()){
        auto [r, c] = q.front();
        q.pop();

        for (int i = 0; i < 8; i++){
            int nx = r + dx[i];
            int ny = c + dy[i];

            if (nx < 0 || nx >= visited.size() || ny < 0 || ny >= visited[0].size())
                continue;
            
            if (visited[nx][ny] || graph[nx][ny] != '@')
                continue;
            
            q.push({nx, ny});
            visited[nx][ny] = true;
        }
    }
}

int main(){
    int m, n;

    while (cin >> m >> n){
        if (m == 0 && n == 0)
            break;
        
        graph.assign(m, "");
        visited.assign(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++){
            cin >> graph[i];
        }
        
        int ans = 0;

        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                if (!visited[i][j] && graph[i][j] == '@'){
                    bfs(i, j);
                    ans++;
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}
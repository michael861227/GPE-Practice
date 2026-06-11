#include <bits/stdc++.h>
using namespace std;

// dp[u]：從 u 出發可以走到的最長路徑長度
// finish[u]：從 u 出發走最長路時，最後會停在哪個點
// visited[u]：表示 dfs(u) 是否已經算過，避免重複計算
vector<int> dp, visited, finish;
vector<vector<int>> graph;

int dfs (int u){
    // 如果 u 的答案已經算過，直接回傳
    if (visited[u])
        return dp[u];
    
    visited[u] = 1;
    
    // 終止條件的預設值：
    // 如果 u 沒有任何 outgoing edge，那最長路長度是 0，終點就是自己
    dp[u] = 0;
    finish[u] = u;

    // 嘗試從 u 走到每個鄰居 v
    for (int v : graph[u]){
        // 如果先走 u -> v，長度就是：
        // 這條邊 1 + 從 v 出發的最長路
        int len = 1 + dfs(v);

        // 找到更長的路，直接更新
        if (len > dp[u]){
            dp[u] = len;
            finish[u] = finish[v];
        }
        // 如果長度一樣，題目要求 finishing node 較小者
        else if (len == dp[u] && finish[v] < finish[u]){
            finish[u] = finish[v];
        }
    }

    return dp[u];
}

int main(){
    int n;
    int u, v;
    int start;
    int Case = 1;

    while (cin >> n && n != 0){
        cin >> start;

        graph.assign(n+1, {});
        visited.assign(n+1, 0);
        dp.assign(n+1, 0);
        finish.assign(n+1, 0);

        while (cin >> u >> v){
            if (u == 0 && v == 0)
                break;
            // 題目是有向圖，只能從 u 走到 v
            graph[u].push_back(v); 
        }

        dfs(start);

        cout << "Case " << Case++ << ": The longest path from "
        << start << " has length " << dp[start]
        << ", finishing at " << finish[start] << ".\n\n";
    }

    return 0;
}

/*
題目: 要找的是：從指定起點 start 出發的 最長路徑長度，以及這條最長路徑最後停在哪個點

1. 圖是 有向圖，輸入 u v 代表只能從 u 走到 v
2. BFS 不適合這題，因為 BFS 找的是最短路徑 => 這題適合用 DFS + 記憶化 DP
3. 定義:
    dp[u] = 從 u 出發可以走到的最長路徑長度
    finish[u] = 從 u 出發走最長路時，最後停在哪個點
    dfs(u) = 計算從 u 出發的最長路徑長度
*/
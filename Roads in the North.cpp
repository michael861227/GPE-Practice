#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
    從 start 出發，找出距離 start 最遠的節點。

    回傳：
    first  = 最遠的節點編號
    second = start 到該節點的距離
*/
pair <int, ll> findFarthest(int start, const vector<vector<pair<int, int>>>& graph){
    // dist[i] = start 到 i 的距離
    // -1 代表還沒走過
    vector<ll> dist(graph.size(), -1);
    queue<int> q;

    q.push(start);
    dist[start] = 0;

    int farthestNode = start;
    ll farthestDistance = 0;

    while (!q.empty()){
        int u = q.front();
        q.pop();

        if (dist[u] > farthestDistance){
            farthestDistance = dist[u];
            farthestNode = u;
        }

        for (auto [v, weight] : graph[u]){
            if (dist[v] == -1){
                dist[v] = dist[u] + weight;
                q.push(v);
            }
        }
    }

    return {farthestNode, farthestDistance};
}

//給一棵樹的所有邊，計算樹的直徑。
ll solve(const vector<tuple<int, int, int>> &edges){
    int maxNode = 0;

    // 因為題目沒有給節點數 n，所以自己找最大的節點編號
    for (auto [u, v, w] : edges){
        maxNode = max({maxNode, u, v});
    }
    
    // graph[u] 裡面放 {v, weight}
    vector<vector<pair<int, int>>> graph(maxNode + 1);

     // 建立無向加權圖
    for (auto [u, v, w] : edges){
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }


    // 第一次 BFS：
    // 隨便選一個點出發，找到最遠的點 a。
    // a 會是某條最長路徑的端點。
    // tuple 用 get<0> 取得第一個元素
    int start = get<0>(edges[0]);
    auto [a, distanceFromStart] = findFarthest(start, graph);


    // 第二次 BFS：
    // 從 a 出發，找到距離 a 最遠的點。
    // 這個距離就是樹的直徑。
    auto [b, diameter] = findFarthest(a, graph);

    return diameter;
}

int main(){
    string line;

    // 一筆測資的所有邊
    vector<tuple<int, int, int>> edges;

    /*
        UVA 10308 的輸入特色：
        1. 沒有給節點數 n
        2. 沒有給測資數量
        3. 每筆測資用空白行分隔
        4. 每行格式是：u v w
    */

    while (getline(cin, line)){
        stringstream ss(line);
        int u, v, w;

        if (ss >> u >> v >> w){
        // 讀得到三個數字，代表這一行是一條邊
            edges.push_back({u, v, w});
        }else{
        // 遇到空白開始計算
            if (!edges.empty()){
                cout << solve(edges) << '\n';
                edges.clear();
            }
        }
    }

    // 處理最後一筆測資，因為 EOF 前不一定有空白行
    if (!edges.empty()) {
        cout << solve(edges) << '\n';
    }

    return 0;
}

/*
題目: 給定一堆邊的輸入，要找出任兩點最遠的距離

因為題目說是一顆 Tree，代表任兩點之間只有唯一一條路徑
因此可以透過兩次 DFS / BFS 找到最遠的距離，不需要像一般加權圖那樣用 Dijkstra

1. 第一次 BFS / DFS 是為了找出直徑的一個端點 (先找出從該點最遠可到達的端點)
2. 第二次 BFS / DFS 才是真正算出最長距離
*/
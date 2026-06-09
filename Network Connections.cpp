#include<bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, sz;

    DSU(int n){
        parent.resize(n+1);
        sz.assign(n+1, 1);

        // 一開始每台電腦都是自己的代表，也就是自己一群
        for (int i = 1; i <= n; i++){
            parent[i] = i;
        }
    }

    // 找出 x 所在群組的代表
    int find(int x){
        // 如果 parent[x] == x，代表 x 自己就是這群的老大
        if (x == parent[x])
            return x;
        // 路徑壓縮：
        // 直接把 x 接到最上層代表，讓之後查詢更快
        return parent[x] = find(parent[x]);
    }

    // 合併 a 和 b 所在的群組
    void unite(int a, int b){
        // 注意：要合併的是兩邊的代表，不是直接合併 a 和 b
        int ra = find(a);
        int rb = find(b);

        // 如果代表相同，表示本來就在同一群，不需要合併
        if (ra == rb)
            return;
        
        // union by size：
        // 讓比較大的群當新的代表，避免樹變太高
        if (sz[ra] < sz[rb])
            swap(ra, rb);
        
            // 把小群 rb 接到大群 ra 底下
        parent[rb] = ra;
        
        // 只有新的代表 ra 的 size 需要更新
        sz[ra] += sz[rb];
    }

    // 判斷 a 和 b 是否在同一個群組
    bool same(int a, int b){
        return find(a) == find(b);
    }
};

// 判斷一行是不是空白行
// 空字串、只有空格、tab、\r、\n 都算空白
bool isBlank(const string& s) {
    return s.find_first_not_of(" \t\r\n") == string::npos;
}

int main(){
    int T;
    cin >> T;

    string line;

    // 讀掉 T 後面剩下的換行
    getline(cin, line);

    for (int tc = 0; tc < T; tc++){
        int n;

        // 每組測資前面可能有空白行，所以要跳過空白行
        while(getline(cin, line)){
            if (!isBlank(line)){
                stringstream ss(line);
                ss >> n;
                break;
            }
        }

        DSU dsu(n);

        int success = 0;
        int fail = 0;

        // 讀取這組測資的所有指令
        // 指令格式：
        // c a b：連接 a 和 b
        // q a b：查詢 a 和 b 是否連通
        while (getline(cin, line)){
            // 空白行代表這組測資結束
            if (isBlank(line)) {
                break;
            }

            stringstream ss(line);

            char op;
            int a, b;

            ss >> op >> a >> b;

            if (op == 'c'){
                dsu.unite(a, b);
            }else if (op == 'q'){
                if (dsu.same(a, b)){
                    success++;
                }else{
                    fail++;
                }
            }
        }

        // UVA 793 要求每組輸出中間空一行
        if (tc > 0) {
            cout << '\n';
        }

        cout << success << "," << fail << '\n';
    }

    return 0;
}
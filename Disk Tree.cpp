#include<bits/stdc++.h>
using namespace std;

// map 會自動按照資料夾名稱的字典序排序
struct Node{
    map<string, unique_ptr<Node>> child;
};

// 將一條路徑插入 Trie
void insertPath(Node &root, const string &path){
    Node *cur = &root;
    string dir;
    stringstream ss(path);

     // C++ 中反斜線要寫成 '\\'
    while (getline(ss, dir, '\\')){
        // 如果這個資料夾不存在，就建立新節點
        if (!cur->child[dir]){
            cur->child[dir] = make_unique<Node>();
        }
        // 往下一層走
        // cur 是 Node* 的指標
        // 要從 unique_ptr<Node> 是管理 Node* 的智慧指標，要拿出 Node* 要用 .get()
        cur = cur->child[dir].get();
    }
}

// DFS 輸出目錄樹
void printTree(const Node& node, int depth){
    for (const auto &[name, nextNode] : node.child){
        // depth 代表目前資料夾前面要印幾個空白
        cout << string(depth, ' ') << name << '\n';

        // 子資料夾深度 +1
        // '*nextNode' 是取的 Node 的 reference，而 .get() 是取得 *Node
        printTree(*nextNode, depth + 1);
    }
}

int main(){
    int n;

    // 有些版本是單筆測資，有些 UVA/ICPC 版本會讀到 EOF
    while (cin >> n){
        Node root;

        for (int i = 0; i < n; i++){
            string path;
            cin >> path;
            insertPath(root, path);
        }

        printTree(root, 0);
        cout << '\n';
    }
    return 0;
}

/*
題目: 給你 n 條磁碟路徑
例如：
    WINNT\SYSTEM32\CONFIG
    WINNT\DRIVERS
Output:
    WINNT
      DRIVERS
      SYSTEM32
        CONFIG

每條路徑用反斜線 \ 分隔資料夾。你要把所有路徑整理成一棵目錄樹並輸出：
a.相同資料夾只出現一次
b.同一層的資料夾要依字典序排序
c.每深入一層，前面多一個空白縮排

做法: 利用 Trie 來解
1.建立一個根節點 root，它本身不輸出。
2.對每條路徑，用 \ 切開。
3.從 root 開始，把每個資料夾名稱插入樹中。
4.每個節點的子節點用 map<string, Node> 儲存，因為 map 會自動依字典序排列 key。
5.最後 DFS 輸出整棵樹，深度 depth 就印 depth 個空白。

核心重點就是：用 map 建 Trie，插入時自動合併重複路徑，輸出時自然就是字典序。

Note:
unique_ptr<Node> 不是一種資料結構，它是 C++ 的「智慧指標」
1.代表「一個指向 Node 的指標，而且它獨自擁有這個 Node」
2.unique_ptr 的好處是不用自己 delete。當整棵樹不再使用時，C++ 會自動把這些節點釋放掉。
3.如果要改成 Node*，要自己 delete
struct Node {
    map<string, Node*> child;

    ~Node() {
        for (auto& [name, ptr] : child) {
            delete ptr;
        }
    }
};
*/
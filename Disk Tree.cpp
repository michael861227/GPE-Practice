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
        // '*nextNode' 是取的 Node 的 reference，而 .get() 是取得 Node*
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

/*
不使用 unique_ptr 寫法


一個 Node 代表一個資料夾節點
struct Node {
    """
        key   ：子資料夾名稱
        value ：子資料夾對應的 Node

        map 有兩個作用：
        1. 相同名稱只會保存一份
        2. 自動按照資料夾名稱的字典序排序
    """"
    map<string, Node> child;
};

將一條完整路徑插入目錄樹
void insertPath(Node& root, const string& path) {
    # cur 指向目前走到的節點
    # 一開始位於虛擬根節點 root
    Node* cur = &root;

    string dir;

    # 把字串 path 包裝成輸入串流
    # 之後就能使用 getline 按照 '\' 切割
    stringstream ss(path);

    """"
        例如：
        path = "WINNT\\SYSTEM32\\CONFIG"

        每次 getline 得到：
        第一次：WINNT
        第二次：SYSTEM32
        第三次：CONFIG

        C++ 程式碼中的 '\\' 代表一個反斜線字元
    """"
    while (getline(ss, dir, '\\')) {
        """"
            cur->child[dir]：

            如果 dir 已經存在：
                取得原本的子節點。

            如果 dir 不存在：
                map 的 operator[] 會自動建立：
                dir -> Node{}

            因此不需要自己判斷是否存在，
            也不需要使用 new 建立節點。
        """"
        cur = &cur->child[dir];

        # &cur->child[dir] 的型別是 Node*
        # 所以可以指定給 cur，繼續往下一層移動
    }
}

使用 DFS 輸出整棵目錄樹
void printTree(const Node& node, int depth) {
    """"
        因為 child 是 map，
        所以走訪時會自動按照資料夾名稱的字典序輸出。
    """"
    for (const auto& [name, nextNode] : node.child) {
        # depth 代表前面需要輸出的空白數量
        cout << string(depth, ' ') << name << '\n';

        """"
            nextNode 本身就是 Node 物件，
            不再是 unique_ptr<Node>。

            因此可以直接傳入 nextNode，
            不需要使用 .get() 或 *nextNode。
        """"
        printTree(nextNode, depth + 1);
    }
}

int main() {
    int n;

    持續讀取測資，直到遇到 EOF
    while (cin >> n) {
        """"
            root 是虛擬根節點，本身不輸出。
            所有最外層資料夾都會放在 root.child。
        """"
        Node root;

        # 讀取 n 條路徑
        for (int i = 0; i < n; i++) {
            string path;
            cin >> path;

            insertPath(root, path);
        }

        # 從虛擬根節點開始輸出，最外層深度為 0
        printTree(root, 0);

        # 不同測資之間輸出空行
        cout << '\n';
    }

    return 0;
}
*/

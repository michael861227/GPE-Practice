#include <bits/stdc++.h>
using namespace std;

void buildPostorder(
    const string& preorder,
    int preL,
    int preR,
    const string& inorder,
    int inL,
    int inR,
    const vector<int>& pos,
    string& postorder
) {
    if (preL > preR) return;

    // preorder 的第一個節點就是目前子樹的根
    char root = preorder[preL];

    // 找出 root 在 inorder 中的位置
    int rootIndex = pos[root];

    // inorder 中 root 左邊的節點數，就是左子樹大小
    int leftSize = rootIndex - inL;

    // 遞迴處理左子樹
    buildPostorder(
        preorder,
        preL + 1,
        preL + leftSize,
        inorder,
        inL,
        rootIndex - 1,
        pos,
        postorder
    );

    // 遞迴處理右子樹
    buildPostorder(
        preorder,
        preL + leftSize + 1,
        preR,
        inorder,
        rootIndex + 1,
        inR,
        pos,
        postorder
    );

    // postorder 是左、右、根，所以最後加入 root
    postorder.push_back(root);
}

int main() {

    int m;
    cin >> m;

    while (m--) {
        int n;
        cin >> n;

        string preorder, inorder;
        preorder.resize(n);
        inorder.resize(n);

        // cin >> char 會自動略過空白，所以可處理 "A B C" 或 "ABC"
        for (int i = 0; i < n; i++) {
            cin >> preorder[i];
        }

        for (int i = 0; i < n; i++) {
            cin >> inorder[i];
        }

        // 記錄每個節點在 inorder 中的位置
        vector<int> pos(256, -1);
        for (int i = 0; i < n; i++) {
            pos[inorder[i]] = i;
        }

        string postorder;

        buildPostorder(
            preorder,
            0,
            n - 1,
            inorder,
            0,
            n - 1,
            pos,
            postorder
        );

        cout << postorder << '\n';
    }

    return 0;
}
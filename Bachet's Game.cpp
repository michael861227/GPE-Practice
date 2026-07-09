#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    while (cin >> n >> m){
        vector<int> moves(m);

        for (int i = 0; i < m; i++){
            cin >> moves[i];
        }

        // dp[i] 表示剩下 i 顆石頭時，輪到當前玩家是否必勝
        vector<bool> dp(n + 1, false);

        // dp[0] = false
        // 沒有石頭可拿，表示當前玩家輸
        for (int i = 1; i <= n; i++){
            // 嘗試所有可以拿的數量
            for (int j = 0; j < m; j++){
                int take = moves[j];

                // 若可以拿 take 顆，且拿完後對手會進入必敗狀態
                if (i >= take && dp[i - take] == false){
                    dp[i] = true;
                    break;
                }
            }
        }

        if (dp[n]){
            cout << "Stan wins" << endl;
        }else{
            cout << "Ollie wins" << endl;
        }
    }
}

/*
題目: 有一堆石頭，共 n 顆。Stan 先手，Ollie 後手，兩人輪流拿石頭
    每次玩家只能拿走指定集合中的數量，例如：S = {1, 3, 8}，拿到最後一顆石頭的人獲勝。

    給定 n 和可拿的數量集合，判斷先手 Stan 是否必勝。

博弈 DP
1. dp[i] 表示目前剩下 i 顆石頭時，輪到當前玩家，當前玩家是否必勝
2. 假設現在有 i 顆石頭，玩家可以拿走 move[j] 顆，拿完之後，對手會面對：i - move[j] 顆石頭
    所以如果存在某個拿法，使得對手進入必敗狀態： dp[i - move[j]] == false
    那麼目前玩家就可以選這個拿法，因此：dp[i] = true
3. 初始狀態： dp[0] = false，因為輪到你時已經沒有石頭可拿，代表上一個人剛拿完最後一顆，你輸了。
4. 狀態轉移:
    dp[i] = true  if exists move[j] <= i and dp[i - move[j]] == false
    dp[i] = false otherwise
*/
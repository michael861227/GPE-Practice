#include <bits/stdc++.h>
using namespace std;

int main(){
    int T;
    string line;
    
    cin >> T;
    getline(cin, line); // 吃掉讀完 T 後剩下的換行

    while (T--){
        getline(cin, line);
        stringstream ss(line);
        
        vector<int> luggage;
        int weight;
        int sum = 0;
        
        // 讀入這一組測資的所有行李重量
        while (ss >> weight){
            luggage.push_back(weight);
            sum += weight;
        }

        // 如果總重量是奇數，不可能分成兩堆一樣重
        if (sum %2 != 0){
            cout << "NO" << endl;
            continue;
        }

        int target = sum / 2;
        int n = luggage.size();

        // dp[i][j] 表示：
        //     使用前 i 件行李，是否可以湊出重量 j

        //     i 的範圍：0 ~ n
        //     j 的範圍：0 ~ target

        vector<vector<bool>> dp(n + 1, vector<bool> (target + 1, false));

        // 不拿任何行李時，可以湊出重量 0
        dp[0][0] = true;

        // 一件一件行李處理
        for (int i = 1; i <= n; i++){
            int w = luggage[i - 1];

            for (int j = 0; j <= target; j++){
                // 情況 1：不拿第 i 件行李
                dp[i][j] = dp[i - 1][j];

                // 情況 2：拿第 i 件行李
                // 前提是目前目標重量 j 要裝得下這件行李
                if (j >= w){
                    dp[i][j] = dp[i][j] || dp[i - 1][j - w];
                }
            }
        }

        if (dp[n][target]){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }

    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int toCents(const string &s){
    int dot = s.find('.');

    int dollars = stoi(s.substr(0, dot));
    int cents = (s[dot + 1] - '0') * 10 + (s[dot + 2] - '0');

    return dollars * 100 + cents;
}

int main(){
    vector<int> coins = {
        5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000
    };

    const int MAX = 30000;
    int n = coins.size();

    // dp[i][j] = 使用前 i 種硬幣，湊出 j cents 的方法數
    vector<vector<long long>> dp (n + 1, vector<long long>(MAX + 1, 0));

    // 湊出 0 元永遠有 1 種方法：什麼都不拿
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    for (int i = 1; i <= n; i++){
        int coin = coins[i - 1];

        for (int j = 0; j <= MAX; j++){
            // 情況 1：不用第 i 種硬幣
            dp[i][j] = dp[i - 1][j];
            
            // 情況 2：至少用一枚第 i 種硬幣
            // 先湊出 j - coin，再補上一枚 coin
            if (j >= coin){
                dp[i][j] += dp[i][j - coin];
            }
        }
    }
    
    string s;
    while (cin >> s){
        int cents = toCents(s);
        
        if (cents == 0)
            break;
        
        cout << fixed << setprecision(2)
        << setw(6) << cents / 100.0
        << setw(17) << dp[n][cents] << endl;
        
    }

    return 0;
}
#include<bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin >> T;

    while (T--){
        int N, K;
        cin >> N >> K;
        vector<int> nums(N);

        for (int &v : nums){
            cin >> v;
        }

        vector<bool> dp(K, false);
        vector<bool> newDP(K, false);

        int firstRemain = (nums[0] % K + K) % K;
        dp[firstRemain] = true;

        for (int i = 1; i < N; i++){
            fill(newDP.begin(), newDP.end(), false);

            for(int remain = 0; remain < K; remain++){
                if (!dp[remain])
                    continue;
                
                int value = (nums[i] % K + K) % K;
                
                int addRemain = (remain + value) % K;
                newDP[addRemain] = true;

                int subRemain = (remain - value + K) % K;
                newDP[subRemain] = true;
            }
            
            dp = newDP;
        }

        if (dp[0]){
            cout << "Divisible" << endl;
        }else{
            cout << "Not divisible" << endl;
        }
    }
    return 0;
}

/*
1. 不能用暴力枚舉，因為 2^(N-1) 會超時
2. x 可以被 K 整除 => x mod K == 0，而 K <= 100，可以用動態規劃紀錄目前能產生哪些餘數
3. 利用 dp[r] = true 代表使用目前已處理的數字，可以透過某種 +、- 配置，得到一個除以 K 餘數為 r 的結果
=> dp[3] = true , x mod K = 3
4. Ex: [17 5 -21 15] , K = 7
    a. 17 mod 7 = 3 => {3}
    b. (3 + 5) % 7 = 1 , (3 - 5 + 7) % 7 = 5 => {1, 5}
    c. 因為 -21 % 7 = 0，不用處理
    d. 15 % 7 = 1
        (1 + 1) % 7 = 2
        (1 - 1 + 7) % 7 = 0 => 可以被整除
*/
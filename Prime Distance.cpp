#include <bits/stdc++.h>
using namespace std;

// sqrt(2^31 - 1) 約等於 46340
// 設 50000 比較保守，也沒什麼成本
const int LIMIT = 50000;

vector<int> basePrimes;

void buildBasePrime(){
    vector<bool> isPrime(LIMIT + 1, true);

    // 標準埃拉托斯特尼篩法
    // 只需要處理到 sqrt(LIMIT)，也就是 i * i <= LIMIT
    for (int i = 2; i * i <= LIMIT; i++){
        if (isPrime[i]){
            // 從 i * i 開始篩
            // 因為 i * 2, i * 3, ..., i * (i - 1)
            // 早就被更小的質數篩掉了
            for (int j = i * i; j <= LIMIT; j+=i){
                isPrime[j] = false;
            }
        }
    }

    // 把篩完還是 true 的數收集起來
    for (int i = 2; i <= LIMIT; i++){
        if (isPrime[i]){
            basePrimes.push_back(i);
        }
    }
}

int main(){
    
    buildBasePrime();

    long long L, U;

    while (cin >> L >> U){
        // isPrime[i] 代表 L + i 是否為質數
        // 例如 L = 20:
        // isPrime[0] -> 20
        // isPrime[1] -> 21
        // isPrime[2] -> 22
        vector<bool> isPrime(U - L + 1, true);
        
        // 用 basePrimes 裡的小質數，去篩掉 [L, U] 裡的合數
        for (long long p : basePrimes){
            // 如果 p > sqrt(U)，後面的質數不需要再處理
            // 因為任何 <= U 的合數，一定有一個因數 <= sqrt(U)
            if (p * p > U) break;

            // 找出 [L, U] 裡第一個應該被 p 篩掉的倍數
            //
            // ((L + p - 1) / p) * p
            // 是「大於等於 L 的第一個 p 的倍數」
            //
            // p * p 是 p 自己真正需要開始篩的地方
            // 避免把 p 本身誤刪，也避免重複篩掉更小質數已處理過的數
            long long start = max(p * p, ((L + p - 1) / p) * p);

            // 把 start, start + p, start + 2p ... 都標成合數
            for (long long x = start; x <= U; x += p) {
                isPrime[x - L] = false;
            }
        }

        // 0 和 1 不是質數，需要特別處理
        if (L == 0) {
            isPrime[0] = false;          // 0
            if (U >= 1) 
                isPrime[1] = false; // 1
        } else if (L == 1) {
            isPrime[0] = false;          // 1
        }

        // prev 記錄上一個遇到的質數
        long long prev = -1;

        // closest pair
        long long closeA = -1, closeB = -1;

        // most distant pair
        long long farA = -1, farB = -1;

        long long minDist = LLONG_MAX;
        long long maxDist = -1;

        // 掃過整個區間，找所有相鄰質數的距離
        for (long long i = 0; i <= U - L; i++) {
            if (!isPrime[i]) continue;

            // cur 是目前遇到的質數
            long long cur = L + i;

            // 如果之前已經遇過質數，就可以和目前質數形成一組相鄰質數
            if (prev != -1) {
                long long dist = cur - prev;

                // 更新最近的相鄰質數
                if (dist < minDist) {
                    minDist = dist;
                    closeA = prev;
                    closeB = cur;
                }

                // 更新最遠的相鄰質數
                if (dist > maxDist) {
                    maxDist = dist;
                    farA = prev;
                    farB = cur;
                }
            }

            // 把目前質數記下來，給下一個質數比較
            prev = cur;
        }

        // 如果 closeA 還是 -1，代表沒有找到任何一組相鄰質數
        // 也就是區間內質數少於兩個
        if (closeA == -1) {
            cout << "There are no adjacent primes.\n";
        } else {
            cout << closeA << "," << closeB << " are closest, "
                 << farA << "," << farB << " are most distant.\n";
        }
    }

    return 0;
}


/*
題目: 給一個區間 [L, U]，找出區間內所有相鄰質數 pair：
    距離最小的 pair：closest
    距離最大的 pair：most distant

1. 先用普通篩法建立 basePrimes
2. 從 basePrimes 中找質數對每組 [L, U] 做分段篩，去除合數
3. 掃描質數，找 closest / most distant pair

NOTE:
a. isPrime[i] 代表 L + i
b. ((L + p - 1) / p) * p 
    是在找「大於等於 L 的第一個 p 的倍數」。
c. max(p * p, 第一個 >= L 的 p 倍數) 
    是為了避免把 p 自己誤刪，也跳過前面已經被更小質數處理過的倍數
*/
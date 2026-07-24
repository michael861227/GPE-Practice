#include<bits/stdc++.h>
using namespace std;

int MAX_N = 3501;
int LIMIT = 40000;

vector<int> prime;
vector<bool> isPrime;

void getPrime(){
    isPrime.assign(LIMIT + 1, true);
    
    for (int i = 2; i * i <= LIMIT; i++){
        if (isPrime[i]){
            for (int j = i * i; j <= LIMIT; j+=i){
                isPrime[j] = false;
            }
        }
    }

    for (int num = 2; num <= LIMIT && prime.size() < MAX_N; num++){
        if (isPrime[num]){
            prime.push_back(num);
        }
    }
}

int Joseph(int n){
    int pos = 0;

    /*
     * 只剩一個人時，他在 0-based 座標中的位置必定是 0。
     *
     * 接下來反向還原：
     * 1 個人 → 2 個人 → 3 個人 → ... → n 個人
     */
    for (int i = 2; i <= n; i++){
        /*
         * 正向淘汰時，質數的使用順序是：
         * 2、3、5、7、11...
         *
         * 但我們現在是反向還原，所以要反向使用質數。
         *
         * 例如 n = 6：
         * size = 2 時使用 prime[4] = 11
         * size = 3 時使用 prime[3] = 7
         * ...
         * size = 6 時使用 prime[0] = 2
         */
        int primeIdx = n - i;
        /*
         * Josephus 反向遞推：
         *
         * pos 表示最後存活者在縮小後圓圈中的位置。
         * 加上這一輪的步長後，就能映射回還原前的位置。
         */
        pos = (pos + prime[primeIdx]) % i;
    }
    // pos 是 0-based，題目編號從 1 開始，所以加 1
    return pos + 1;
}

int main(){
    int n;

    getPrime();

    while (cin >> n && n != 0){
        cout << Joseph(n) << endl;
    }

    return 0;
}
#include<bits/stdc++.h>
using namespace std;

const int MX = 10000;
vector<bool> isPrime(MX, true);
vector<int> prime;

void getPrime(){
    isPrime[0] = false;
    isPrime[1] = false;
    
    for (int i = 2; i * i <= MX; i++){
        if (isPrime[i]){
            for (int j = i * i; j <= MX; j += i){
                isPrime[j] = false;
            }
        }
    }

    for (int i = 2; i <= MX; i++){
        if (isPrime[i]){
            prime.push_back(i);
        }
    }
}

int main(){

    getPrime();
    int size = prime.size();
    int num;

    while (cin >> num && num != 0){
        int ans = 0;
        int left = 0;
        int sum = 0;

        for (int right = 0; right < size; right++){
            sum += prime[right];
            while (sum > num){
                sum -= prime[left];
                left++;
            }

            if (sum == num){
                ans++;
            }
        }

        cout << ans << endl;
    }

    return 0;
}
#include<bits/stdc++.h>
using namespace std;

int canFill(vector<int> &vessels, long long k){
    long long remain = k;
    int ans = 1;
    for (int i = 0; i < vessels.size(); i++){
        if (remain >= vessels[i]){
            remain -= vessels[i];
        }else{
            remain = k;
            ans++;
            remain -= vessels[i];
        }
    }
    return ans;
}

int main(){
    int n, m;

    while(cin >> n >> m){
        vector<int> vessels(n, 0);
        
        long long left = 0, right = 0;

        for (int i = 0; i < n; i++){
            cin >> vessels[i];
            left = max(left, (long long)vessels[i]);
            right += vessels[i];
        }

        while (left + 1 < right){
            long long mid = left + (right - left) / 2;
            if (canFill(vessels, mid) > m){
                left = mid;
            }else{
                right = mid;
            }
        }

        if (canFill(vessels, left) <= m){
            cout << left << endl;
        }else if (canFill(vessels, right) <= m){
            cout << right << endl;
        }else{
            cout << -1 << endl;
        }

    }
    return 0;
}

/*
題目：
    n 個 vessel，每個 vessel 有固定容量，且順序不能改變。
    m 個 container，每個 container 的容量都一樣。
    每個 vessel 不能被拆開，只能完整放進某一個 container。
    一個 container 可以裝連續的多個 vessel。

問：container 的最小容量是多少，才能把所有 vessel 依序裝完？
*/
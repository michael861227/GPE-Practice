#include<bits/stdc++.h>
using namespace std;

bool valid(int n, int m){
    vector<int> region(n);

    for (int i = 0; i < n; i++){
        region[i] = i + 1;
    }

    int pos = 0;

    while (region.size() > 1){
        region.erase(region.begin() + pos);

        pos = (pos + (m - 1)) % region.size();
    }

    return region[0] == 13;
}

int main() {
    int n;

    while (cin >> n && n != 0){
        int m = 1;

        while (!valid(n, m)){
            m++;
        }
        
        cout << m << endl;

    }
}

/*
題目: 給定 N 個城市，從第一個城市開始斷電，之後輪到 m 個城市斷電，要求最後一個被斷電的城市是 13 的話，最小 m 為多少

1. 由於 N 很小 (< 100)，因此使用窮舉方法是可以的
2. 由於會刪除，因此下一個輪到的是 pos + (m - 1) 而不是 pos + m
*/
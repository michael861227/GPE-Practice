#include <bits/stdc++.h>
using namespace std;

struct PairSum{
    int sum;
    int i;
    int j;

    bool operator< (const PairSum &p) const {
        return sum < p.sum;
    }
};

int main(){
    int n;

    while (cin >> n && n != 0){
        vector<int> v(n, 0);
        for (int i = 0; i < n; i++){
            cin >> v[i];
        }

        sort(v.begin(), v.end());

        vector<PairSum> pairs;

        for (int i = 0; i < n; i++){
            for (int j = i + 1; j < n; j++){
                pairs.push_back({v[i] + v[j], i, j});
            }
        }
        
        sort(pairs.begin(), pairs.end());
        
        int ans = 0;
        bool found = false;

        for (int d = n - 1; d >= 0 && !found; d--){
            for (int c = 0; c < n && !found; c++){
                if (c == d)
                    continue;
                    
                int target = v[d] - v[c];
                
                PairSum key = {target, 0, 0};
                auto lower = lower_bound(pairs.begin(), pairs.end(), key);
                auto upper = upper_bound(pairs.begin(), pairs.end(), key);

                for (auto it = lower; it != upper; it++){
                    int a = it->i;
                    int b = it->j;

                    if (a != c && a != d && b != c && b != d){
                        ans = v[d];
                        found = true;
                        break;
                    }
                }
            }
        }

        if (found){
            cout << ans << endl;
        }else{
            cout << "no solution" << endl;
        }

    }

    return 0;
}

/*
題目: 要找出給定一個集合中 a + b + c = d 之 d 的最大值，同時 (a, b, c, d) 都要 distinct

1. 核心思路: a + b = d - c
    a. 窮舉所有的 a + b ，之後再看 d - c 能否匹配到
    b. 窮舉 O(n^2)，用二分法匹配 O(log n) => Total : O(n^2 log n)
*/
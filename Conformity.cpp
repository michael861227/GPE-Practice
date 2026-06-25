#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int n;
    while (cin >> n && n != 0){
        map<array<int, 5>, int> freq;

        for (int i = 0; i < n; i++){
            array<int, 5> courses;

            for (int j = 0; j < 5; j++){
                cin >> courses[j];
            }
            
            // 選課順序不重要，排序後才能把相同組合視為同一種
            sort(courses.begin(), courses.end());
            
            // 統計這個組合出現幾次
            freq[courses]++;
        }

        int maxFreq = 0;

        // 找出最多人選的組合出現次數
        for (const auto &entry : freq) {
            maxFreq = max(maxFreq, entry.second);
        }

        int answer = 0;
        // 如果有多個組合並列最多，要把它們的人數全部加起來
        for (const auto &entry : freq) {
            if (entry.second == maxFreq) {
                answer += entry.second;
            }
        }

        cout << answer << '\n';
    }
    return 0; 
}

/*
題目: 每個新生會選 5 門課，要找出「最受歡迎的選課組合」有多少學生選

一個學生的 5 門課順序不重要。
100 101 102 103 488 和 103 102 101 488 100 是同一種組合。
如果有多個組合並列第一名，要把這些組合的學生數全部加起來

思路:
1.因為每個學生固定選 5 門課，所以可以先把這 5 個課號排序，讓同一組合變成同一個標準形式
2.這題用 map 來統計每種組合出現幾次，因為 map 的 key 要可以比大小，而 vector<int> 跟 array<int, 5> 有內建比大小
3.反之，這題如果要用 unordered_map 要自己寫 hash，比較麻煩
*/
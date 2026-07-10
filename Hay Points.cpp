#include<bits/stdc++.h>
using namespace std;

int main(){
    int m, n;

    // 使用 while 可以兼容輸入中存在多組測試資料的情況
    while (cin >> m >> n){
        // salary[word] 表示該單字對應的價值
        unordered_map<string, long long> salary;

        for (int i = 0; i < m; i++){
            string word;
            long long value;

            cin >> word >> value;
            salary[word] = value;
        }

        // 依序處理 n 篇工作描述
        for (int i = 0; i < n; i++){
            long long total = 0;
            string word;

            while (cin >> word && word != "."){
                if (!salary.count(word))
                    continue;
                
                total += salary[word];
            }

            cout << total << endl;
        }
    }


    return 0;
}
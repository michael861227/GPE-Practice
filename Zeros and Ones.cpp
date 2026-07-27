#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int Case = 0;

    while (cin >> s){
        int querynum;

        cin >> querynum;
        // prefix[i] 表示索引 0 到 i-1 之間 '1' 的數量
        vector<int> prefix(s.size() + 1, 0);

        for (int i = 0; i < s.size(); i++){
            prefix[i + 1] = prefix[i] + (s[i] == '1' ? 1 : 0);
        }

        Case++;
        cout << "Case " << Case << ":" << endl;

        while (querynum--){
            int i, j;
            cin >> i >> j;

            int left = min(i, j);
            int right = max(i, j);

            int len = right - left + 1;
            // 計算 [left, right] 之間 '1' 的數量
            int count = prefix[right + 1] - prefix[left];

            if (count == 0 || count == len){
                cout << "Yes" << endl;
            }else{
                cout << "No" << endl;
            }
        }

    }
}

/*
題目:
1.給定一個只包含 0 和 1 的字串，接著有多筆查詢。
2.每筆查詢提供兩個索引 i 和 j，要判斷字串中索引 i 到 j 的所有字元是否完全相同：
    全部都是 0 或全部都是 1，輸出 Yes
    同時包含 0 和 1，輸出 No
注意：
1.索引從 0 開始。
2.i 不一定小於 j，因此需要先找出左右邊界。
3.輸入包含多組測試資料，必須讀到 EOF。
4.每組測試資料輸出 Case X:

思路推導:
1.使用 prefix sum: prefix[k] = 字串索引 0 到 k-1 之間，1 的數量
2. [left, right] = prefix[right + 1] - prefix[left] , length = right - left + 1
    ones == 0：區間全部都是 0
    ones == length：區間全部都是 1
    其他情況：區間同時包含 0 和 1
*/
#include<bits/stdc++.h>
using namespace std;

int main(){
    string a, b;

    while (getline(cin, a) && getline(cin, b)){
        vector<int> cnt_a(26, 0);
        vector<int> cnt_b(26, 0);

        for (char c : a){
            cnt_a[c - 'a']++;
        }

        for (char c : b){
            cnt_b[c - 'a']++;
        }

        for (int i = 0; i < 26; i++){
            int mincnt = min(cnt_a[i], cnt_b[i]);
            char c = 'a' + i;
            while(mincnt--){
                cout << c;
            }
        }

        cout << endl;
    }
    return 0;
}

/*
思路:

題目允許把 x 任意排列後，再判斷它是否為兩個字串的子序列。
因此我們真正關心的不是字元出現的順序，而是：每一個字母分別在兩個字串中出現幾次。

Note:
要用 getline 而不是 cin，因為可能會有空串
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    
    string s;
    while (cin >> s) {
        int n = s.size();
        
        // rev = 反轉的 s
        string rev = s;
        reverse(rev.begin(), rev.end());
        
        // 組合字串：rev(s) + '#' + s
        // '#' 是分隔符，保證 failure function 不會跨過去
        string combined = rev + "#" + s;
        int m = combined.size();
        
        // 建立 KMP failure function（前綴函數）
        // fail[i] = combined[0..i] 的最長「真前綴 = 真後綴」的長度
        vector<int> fail(m, 0);
        for (int i = 1; i < m; i++) {
            int j = fail[i - 1];
            while (j > 0 && combined[i] != combined[j])
                j = fail[j - 1];
            if (combined[i] == combined[j])
                j++;
            fail[i] = j;
        }
        
        // fail 的最後一個值 = s 和 rev(s) 之間的 overlap 長度
        // 意思是：s 的「後綴」有多長已經 match 到 rev(s) 的「前綴」
        // 也就是 s 末尾已經有 fail[m-1] 個字元不需要再補
        int match = fail[m - 1];
        
        // 輸出 s + rev(s)[match..end]
        // rev[match..end] 就是還沒對應到的「前綴的反轉」
        cout << s << rev.substr(match) << "\n";
    }
    
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

vector<long long> parse(int &pos, string &s, int n){
    pos++; // 跳過 '['

    // 讀取常數 m，並處理可能的負號
    long long m = 0;
    int sign = 1;

    if (s[pos] == '-'){
        sign = -1;
        pos++;
    }

    while (isdigit(s[pos])){
        m = m * 10 + (s[pos] - '0');
        pos++;
    }

    m *= sign;

    // 如果直接遇到 ']'，代表是常數序列 [m]
    if (s[pos] == ']'){
        pos++;
        return vector<long long> (n, m); // 回傳長度為 n，且全部為 m 的陣列
    }

    // 否則會遇到 '+' 或 '*' 運算符
    // 跳過 '+' 或 '*'
    char op = s[pos++];

    vector<long long> S = parse(pos, s, n);
    pos++; // 跳過該層結尾的 ']'


    vector<long long> V(n);
    if (op == '+'){
        V[0] = m;
        for (int i = 1; i < n; i++){
            // V_i = V_{i-1} + S_{i-1} (因為陣列索引從 0 開始，這裡 i 對應第 i+1 項)
            V[i] = V[i - 1] + S[i - 1];
        }
    }
    else if (op == '*'){
        V[0] = m * S[0];
        for (int i = 1; i < n; i++){
            // V_i = V_{i-1} * S_i
            V[i] = V[i - 1] * S[i];
        }
    }

    return V;
}

int main(){
    string s;
    int n;

    while (cin >> s >> n){
        int pos = 0;

        vector<long long> ans;
        ans = parse(pos, s, n);
        
        for (int i = 0; i < n; i++){
            cout << ans[i] << (i == n - 1 ? "" : " ");
        }

        cout << endl;
    }

    return 0;
}

/*
題目：要解析遞迴後的 Array

1. [n] (常數序列)：展開後每一項都是常數
    例如：[-2] 展開 5 項就是 -2, -2, -2, -2, -2
2. [m + S] (加法遞迴序列)：
    首項 V_1 = m。
    後續的每一項 V_i = V_{i-1} + S_{i-1}。
3. [m * S] (乘法遞迴序列)：
    首項 V_1 = m * S_1。
    後續的每一項 V_i = V_{i-1} * S_{i}。

設計一個遞迴函式 parse(int &pos, const string &s, int n)，pos 代表當前讀取到字串的哪個字元索引，n 代表我們需要生成的序列長度。
1. 函式回傳值是一個 vector<long long>，儲存該層計算好的 n 個數字。
2. 解析步驟：
    a. 跳過開頭的左括號 [。
    b. 讀取緊接的整數 m（注意處理可能的負號 -）。
    c. 如果下一個字元是 ]，代表此為常數序列，直接回傳填滿 m、長度為 n 的陣列。
    d. 如果遇到的是 + 或 *，則記錄下運算符號，並遞迴呼叫 parse() 函式去取得內層的序列陣列 S。
    e. 取回 S 後，檢查並跳過結尾的右括號 ]。最後，根據運算符號 (+ 或 *)，依照題目的公式生成當前層次的陣列 $V$，並回傳即可。

Note
1. 要注意 parse 中傳進去的 pos 要用 reference
2. 否則當遞迴進行結束時，內部的 pos 不會和當前的 pos 有任何關係，當前的 pos 還是維持原本的，沒有因為遞迴而被更新 
*/
#include <bits/stdc++.h>
using namespace std;

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/" || s == "%";
}

bool isNumber(const string& s) {
    // 題目說數字都是正整數，所以 token 全是 digit 就是數字
    if (s.empty()) return false;

    for (char c : s) {
        if (!isdigit(c)) return false;
    }

    return true;
}

int main() {
    string line;

    while (getline(cin, line)) {
        // 終止條件：單獨一個句點
        if (line == ".") break;

        stringstream ss(line);
        vector<string> tokens;
        string token;

        // 把整行切成一個一個 token
        while (ss >> token) {
            tokens.push_back(token);
        }

        stack<long long> st;
        bool illegal = false;

        // 前序運算式從右往左處理
        for (int i = (int)tokens.size() - 1; i >= 0; i--) {
            string cur = tokens[i];

            if (isNumber(cur)) {
                // 數字直接放進 stack
                st.push(stoll(cur));
            } 
            else if (isOperator(cur)) {
                // 運算子需要兩個 operand
                if (st.size() < 2) {
                    illegal = true;
                    break;
                }

                // 注意順序：
                // prefix: op left right
                // 從右往左掃時，第一個 pop 出來的是 left
                long long left = st.top();
                st.pop();

                long long right = st.top();
                st.pop();

                long long result = 0;

                if (cur == "+") {
                    result = left + right;
                } 
                else if (cur == "-") {
                    result = left - right;
                } 
                else if (cur == "*") {
                    result = left * right;
                } 
                else if (cur == "/") {
                    if (right == 0) {
                        illegal = true;
                        break;
                    }
                    result = left / right;
                } 
                else if (cur == "%") {
                    if (right == 0) {
                        illegal = true;
                        break;
                    }
                    result = left % right;
                }

                // 把子運算式的結果放回 stack
                st.push(result);
            } 
            else {
                // 理論上題目保證不會有其他字元，但保險處理
                illegal = true;
                break;
            }
        }

        // 最後必須剛好剩一個結果
        if (illegal || st.size() != 1) {
            cout << "illegal\n";
        } else {
            cout << st.top() << '\n';
        }
    }

    return 0;
}
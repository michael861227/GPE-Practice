#include <bits/stdc++.h>
using namespace std;

int main(){
    string line;
    vector<string> dict;

    while (getline(cin, line)){
        if (line == "0")
            break;
        
        for (int i = 0; i < line.size();){
            if (isalpha(line[i])){
                string word = "";
                while (i < line.size() && isalpha(line[i])){
                    word += line[i];
                    i++;
                }

                dict.insert(dict.begin(), word);
                cout << word;
            }
            else if (isdigit(line[i])){
                int num = 0;
                while (i < line.size() && isdigit(line[i])){
                    num = num * 10 + (line[i] - '0');
                    i++;
                }

                string word = dict[num - 1];
                dict.erase(dict.begin() + num - 1);
                dict.insert(dict.begin(), word);
                cout << word;
            }else{
                cout << line[i];
                i++;
            }
        
        }

        cout << endl;
    }

    return 0;
}

/*
題目: 將 Compress 的文字還原

核心想法：維護一個「最近使用字典」。遇到英文單字就直接輸出，並放到字典最前面；遇到數字 n，代表輸出字典中第 n 個單字，然後把這個單字移到最前面。

規則
    a. 輸入一行一行讀，直到遇到單獨一行 0 結束。
    b. 連續英文字母 [A-Za-z] 視為一個 word。
    c. 連續數字視為一個 index。
    d. 空白、標點符號、換行都原樣輸出。
    e. 字典位置是 1-based，所以 1 代表目前字典第一個 word。

*/
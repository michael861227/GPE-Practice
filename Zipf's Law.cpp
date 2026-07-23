#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    bool firstCase = true;

    while (cin >> n){
        string line;
        unordered_map<string, int> freq;
        string word = "";

        // 逐行讀取文章
        //
        // 因為 cin >> n 後面的換行仍留在輸入中，
        // 所以第一次 getline 會讀到空字串。
        // 不過空字串不會產生任何單字，因此不影響答案。
        while (getline(cin, line)){
            if (line == "EndOfText")
                break;

            for (char ch : line){
                if (isalpha(ch)){
                    word += tolower(ch);
                }else{
                    if (!word.empty()){
                        freq[word]++;
                        word.clear();
                    }
                }
            }
            // 如果這一行最後是英文字母，
            // for 迴圈中不會遇到分隔符號，
            // 因此需要在行尾另外記錄一次
            if (!word.empty()){
                freq[word]++;
                word.clear();
            }
        }


        vector<string> ans;

        for (auto &[w, cnt] : freq){
            if (cnt == n){
                ans.push_back(w);
            }
        }

        sort(ans.begin(), ans.end());

        if (!firstCase){
            cout << endl;
        }

        firstCase = false;
        if (ans.empty()){
            cout << "There is no such word." << endl;
        }else{
            for (string &str : ans){
                cout << str << endl;
            }
        }
    }
}

/*
題目:

每組資料：
    1.第一行是一個正整數 n。
    2.接下來是數行英文文章。
    3.當讀到單獨一行 EndOfText，代表這組文章結束。
    4.一個「單字」是由連續英文字母組成。
    5.非英文字母，例如空格、標點符號、數字，都是單字的分隔符號。
    6.大小寫視為相同，例如 The、THE、the 都算作 the。

需要找出文章中所有「剛好出現 n 次」的單字，並且：
1.全部轉成小寫。
2.按照字典順序輸出。
3.每個單字輸出一行。
4.如果不存在符合條件的單字，輸出：There is no such word.

Ex:
Hello, WORLD! don't-stop123now
會被拆成:
hello
world
don
t
stop
now

Note:
一行最後的單字要另外記錄
ex: hello world ，掃描結束時，world 後面沒有標點符號，因此離開迴圈後還要再統計一次
*/

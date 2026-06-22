#include <bits/stdc++.h>
using namespace std;

struct Contestant {
    bool appeared = false;        // 是否有出現過提交紀錄
    int solved = 0;               // 解出的題數
    int penalty = 0;              // 總罰時

    bool accepted[10] = {};       // accepted[p]：第 p 題是否已經通過
    int wrong[10] = {};           // wrong[p]：第 p 題通過前錯了幾次
};

// 判斷一行是否為空行
bool isBlankLine(const string& s) {
    return s.find_first_not_of(" \t\r\n") == string::npos;
}

int main() {
    int T;
    cin >> T;

    string line;
    getline(cin, line); // 吃掉 T 後面的換行

    for (int tc = 0; tc < T; tc++) {
        vector<Contestant> contestants(101);

        // 先跳過每筆測資前面的空行
        while (getline(cin, line) && isBlankLine(line)) {
        }

        // 如果成功讀到一行，代表 line 現在是這筆測資的第一筆提交
        if (cin) {
            do {
                stringstream ss(line);

                int id, problem, time;
                char result;
                ss >> id >> problem >> time >> result;

                Contestant& c = contestants[id];
                c.appeared = true;

                if (result == 'C') {
                    // 一題只計算第一次通過
                    if (!c.accepted[problem]) {
                        c.accepted[problem] = true;
                        c.solved++;
                        c.penalty += time + c.wrong[problem] * 20;
                    }
                } else if (result == 'I') {
                    // 只有在尚未通過前的錯誤才需要累積
                    if (!c.accepted[problem]) {
                        c.wrong[problem]++;
                    }
                }

                // R, U, E 不影響分數
                // 但因為有提交，所以 appeared 仍然要設為 true

            } while (getline(cin, line) && !isBlankLine(line));
            // do while 的好處：
            // 先處理目前已經讀到的 line，
            // 再讀下一行，直到遇到空行或 EOF。
        }

        vector<int> ranking;

        // 只輸出有提交過的參賽者
        for (int id = 1; id <= 100; id++) {
            if (contestants[id].appeared) {
                ranking.push_back(id);
            }
        }

        sort(ranking.begin(), ranking.end(), [&](int a, int b) {
            const Contestant& A = contestants[a];
            const Contestant& B = contestants[b];

            if (A.solved != B.solved) {
                return A.solved > B.solved;       // 解題數多的排前面
            }

            if (A.penalty != B.penalty) {
                return A.penalty < B.penalty;     // 罰時少的排前面
            }

            return a < b;                         // 編號小的排前面
        });

        for (int id : ranking) {
            cout << id << ' '
                 << contestants[id].solved << ' '
                 << contestants[id].penalty << '\n';
        }

        // 不同測資之間要空一行
        if (tc != T - 1) {
            cout << '\n';
        }
    }

    return 0;
}

/*
題目: 比賽有很多參賽者提交程式，每筆提交格式是 contestant problem time result

contestant：參賽者編號，1 到 100
problem：題目編號，1 到 9
time：提交時間
result：提交結果
    C：Correct，通過
    I：Incorrect，錯誤
    R / U / E：其他結果，不影響分數

最後要輸出排行榜。

排序規則：
1.解題數多的排前面
2.解題數一樣，罰時少的排前面
3.都一樣，參賽者編號小的排前面

罰時規則：
1.一題只有第一次 C 才算通過
2.通過某題時，罰時加上：通過時間 + 之前這題的錯誤次數 * 20
    a. 沒有通過的題目，不計算罰時
    b. I 只有在該題尚未通過前才會累積
    c. R / U / E 不影響分數，但該參賽者仍然要出現在排行榜上

核心思路: 主要在於狀態紀錄
每個參賽者對每一題，我們需要知道兩件事：
1.這題是否已經通過
2.這題在通過前錯了幾次

每位參賽者記錄：
    appeared          // 是否出現過提交
    solved            // 解了幾題
    penalty           // 總罰時
    accepted[problem] // 某題是否已通過
    wrong[problem]    // 某題通過前錯了幾次

*/
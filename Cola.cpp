#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;

    // 題目有多筆輸入，讀到 EOF 為止
    while (cin >> n) {
        int total = n;   // 已經喝到的可樂數量
        int empty = n;   // 目前手上的空瓶數量

        // 只要空瓶數量 >= 3，就可以繼續換可樂
        while (empty >= 3) {
            int newCola = empty / 3;   // 可以換到的新可樂數
            int remain = empty % 3;    // 換完後剩下的空瓶

            total += newCola;          // 喝掉新換來的可樂
            empty = remain + newCola;  // 剩下空瓶 + 新可樂喝完產生的空瓶
        }

        // 如果最後剩 2 個空瓶，可以借 1 個空瓶再換 1 瓶
        // 喝完後會產生 1 個空瓶，剛好可以還回去
        if (empty == 2) {
            total++;
        }

        cout << total << '\n';
    }

    return 0;
}

/*
題目: 你一開始買了 N 瓶可樂。喝完後，每瓶會變成 1 個空瓶
a. 3 個空瓶可以換 1 瓶新的可樂
b. 特別的是：你可以跟別人借空瓶，但最後必須還得出來。

核心思路:
1.先喝掉原本的 N 瓶。
2.用目前的空瓶數不斷換新可樂。
3.如果最後剩下 2 個空瓶，可以借 1 個空瓶再多喝一瓶。
4.剩下 0 或 1 個空瓶就不能再喝了。
*/
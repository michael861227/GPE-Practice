#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;

    while (cin >> n && n != 0) {
        int top = 1;
        int north = 2;
        int west = 3;
        int east = 4;
        int south = 5;
        int bottom = 6;

        string cmd;

        while (n--) {
            cin >> cmd;

            int oldTop = top;

            if (cmd == "north") {
                top = south;
                south = bottom;
                bottom = north;
                north = oldTop;
            } 
            else if (cmd == "south") {
                top = north;
                north = bottom;
                bottom = south;
                south = oldTop;
            } 
            else if (cmd == "east") {
                top = west;
                west = bottom;
                bottom = east;
                east = oldTop;
            } 
            else if (cmd == "west") {
                top = east;
                east = bottom;
                bottom = west;
                west = oldTop;
            }
        }

        cout << top << '\n';
    }

    return 0;
}

/*
題目: 一顆骰子，透過 north、west、east、south 的指令，最後要求 top 的面是哪一個點
骰子初始設定:
    top = 1
    north = 2
    west = 3
    east = 4
    south = 5
    bottom = 6

核心思路: 只要維持骰子的六個面就好，並且每次滾動只會影響四個面
EX: 往 North 滾
    south -> top
    top -> north
    north -> bottom
    bottom -> south
*/
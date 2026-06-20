#include <bits/stdc++.h>
using namespace std;

struct Segment {
    int l, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int tc = 0; tc < T; tc++) {
        int M;
        cin >> M;

        vector<Segment> segs;

        while (true) {
            int l, r;
            cin >> l >> r;

            if (l == 0 && r == 0) break;

            segs.push_back({l, r});
        }

        // 依左端點排序；左端點相同時，右端點較大的排前面
        sort(segs.begin(), segs.end(), [](const Segment& a, const Segment& b) {
            if (a.l != b.l) return a.l < b.l;
            return a.r > b.r;
        });

        vector<Segment> answer;

        int covered = 0; // 目前已經覆蓋到的位置
        int i = 0;
        int n = segs.size();

        while (covered < M) {
            int bestReach = covered;
            Segment bestSeg;
            bool found = false;

            /*
                找出所有左端點 <= covered 的線段。
                這些線段都可以接在目前覆蓋範圍後面。
                從中選右端點最大的那一條。
            */
            while (i < n && segs[i].l <= covered) {
                if (segs[i].r > bestReach) {
                    bestReach = segs[i].r;
                    bestSeg = segs[i];
                    found = true;
                }
                i++;
            }

            // 沒有任何線段可以讓覆蓋範圍往右延伸，代表失敗
            if (!found) break;

            answer.push_back(bestSeg);
            covered = bestReach;
        }

        if (tc > 0) cout << '\n';

        if (covered < M) {
            cout << 0 << '\n';
        } else {
            cout << answer.size() << '\n';
            for (const auto& seg : answer) {
                cout << seg.l << ' ' << seg.r << '\n';
            }
        }
    }

    return 0;
}

/*
題目:給你一個目標區間 [0, M]，再給你很多條線段 [L, R]。
你要從這些線段裡面挑一些出來，讓它們可以完整覆蓋 [0, M]，而且挑的線段數量要越少越好。

核心是 greedy：每次從「左端點 <= 目前已覆蓋位置」的線段中，選右端點延伸最遠的那一條。

流程：
1.讀入目標長度 M，要覆蓋 [0, M]。
2.讀入所有線段，直到 0 0。
3.依照左端點排序。
4.從 covered = 0 開始，每輪找所有 l <= covered 的線段中 r 最大者。
5.找不到就代表無法完整覆蓋，輸出 0。
6.若 covered >= M，輸出選到的線段。

時間複雜度：O(n log n)，主要來自排序。
*/
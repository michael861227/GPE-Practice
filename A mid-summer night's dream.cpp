#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    while (cin >> n){
        vector<int> arr(n);
        for (int i = 0; i < n; i++){
            cin >> arr[i];
        }

        sort(arr.begin(), arr.end());
        int A, B = 0, C;
        if (n % 2 == 1){
            // 奇數個資料：最佳答案只有真正的中位數
            A = arr[n / 2];

            // 計算輸入中有多少個數字等於 A
            for (int x : arr){
                if (x == A){
                    B++;
                }
            }

            C = 1;
        }else{
            // 偶數個資料：最佳答案是左中位數到右中位數之間所有整數
            int L = arr[n / 2 - 1];
            int R = arr[n / 2];

            A = L;

            // 計算輸入中有多少個數字落在 [L, R]
            for (int x : arr) {
                if (L <= x && x <= R) {
                    B++;
                }
            }

            // [L, R] 之間共有多少個整數
            C = R - L + 1;
        }

        cout << A << " " << B << " " << C << '\n';
    }
    
    return 0;
}

/*
題目: 
給你 n 個整數，找一個整數 A，讓 |x1 - A| + |x2 - A| + ... + |xn - A| 最小 => 找中位數

Output: A B C
A：最小的最佳答案，也就是最小的 median 候選值
B：輸入資料中，有多少個數字也可以當最佳答案
C：總共有多少個整數可以當最佳答案

思路推導:
n 是奇數 => 中位數 = arr[n / 2]
    A = arr[n / 2]
    B = 輸入中等於 A 的數量
    C = 1

n 是偶數 => 左中位數 L = arr[n / 2 - 1]、右中位數 R = arr[n / 2]
    A = L
    B = 輸入中落在 [L, R] 的數量
    C = R - L + 1

*/
#include<bits/stdc++.h>
using namespace std;

long long getnum(string &s){
    long long num = 0;
    for (char c : s){
        num = num * 2 + c - '0';
    }
    return num;
}

bool CheckLove(string &s1, string &s2){
    long long n1, n2;

    n1 = getnum(s1);
    n2 = getnum(s2);

    long long love = gcd(n1, n2);
    if (love > 1){
        return true;
    }
    return false;
}

int main(){
    int n;

    cin >> n;

    for (int i = 1; i <= n; i++){
        string s1, s2;
        cin >> s1 >> s2;
        
        bool isLove;
        isLove = CheckLove(s1, s2);

        if (isLove){
            cout << "Pair #" << i << ": All you need is love!" << endl;
        }else{
            cout << "Pair #" << i << ": Love is not all you need!" << endl;
        }
    }
    return 0;
}
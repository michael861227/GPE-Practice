#include<bits/stdc++.h>
using namespace std;

bool found(vector<int> v, int m){
    v.erase(v.begin());
    int i = 0;
    while (v.size() > 1){
        int size = v.size();
        int idx = (i + m - 1) % size;
        v.erase(v.begin() + idx);

        i = idx;
    }

    return v[0] == 12;
}

int main(){
    int n;
    while (cin >> n && n != 0){
        vector<int> v(n);

        for (int i = 0; i < n; i++){
            v[i] = i;
        }

        int m = 1;
        while (true){
            if (found(v, m)){
                cout << m << endl;
                break;
            }

            m++;
        }
    }
    return 0;
}
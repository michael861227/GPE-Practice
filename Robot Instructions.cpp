#include<bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin >> T;

    int n;

    while(T--){
        // moves[i] 表示第 i 個指令實際造成的位移
        // 因為題目指令編號從 1 開始，所以開 n + 1
        cin >> n;
        cin.ignore(); // 吃掉 n 後面的換行
        
        vector<int> move(n + 1, 0);
        
        int ans = 0;
        string line;
        
        for (int i = 1; i <= n; i++){
            getline(cin, line);
            
            if (line == "LEFT"){
                move[i] = -1;
            }else if (line == "RIGHT"){
                move[i] = 1;
            }else{
                // line 會像是 "SAME AS 3"
                int pos = line.find("AS");

                // 數字從 "AS" 後面的空白之後開始，所以是 pos + 3
                int x = stoi(line.substr(pos + 3));

                move[i] = move[x];
            }

            ans += move[i];
        }

        cout << ans << endl;

    }
    return 0;
}
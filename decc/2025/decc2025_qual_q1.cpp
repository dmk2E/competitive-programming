/*アルゴリズムと工夫点(N君の暇つぶし/CPU: - ms Memory: - KB  Length: - B)
[A, B] の範囲の各整数が条件を満たすか判定しつつ，適切に加算していけばよい．
最悪計算量は，O((B - A) * log2(B)) < 10 ^ 6 となり，十分高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define INPUT_NUMBER 3
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<typename T>
class Outputer{
    vector<T> ans;

public:
    Outputer(){}

    void push(T value){
        ans.push_back(value);
    }

    void output(string prefix = "", string suffix = ""){
        int i;
        if(ans.size() > 0){
            rep(i, ans.size() - 1)cout << prefix << ans[i] << suffix << ',';
            cout << prefix << ans[i] << suffix << '\n';
        }
    }
};

// vector<vector<int> > ipt = {
//     {1,10},
//     {30,39},
//     {100,150}
// };
vector<vector<int> > ipt = {
    {1,100},
    {300,399},
    {12345,54321}
};
Outputer<int> answer;

const int IGNORE_INTERVAL = 3;

int main(){
    int i, j;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto& table = ipt[ipt_id];
        int a = table[0], b = table[1];

        int ans = 0;
        int cnt = 0;
        for(;a <= b;a++){
            auto judge = [](int num) -> bool{
                if(num % 3 == 0)return true;
                while(num > 0){
                    if(num % 10 == 3)return true;
                    num /= 10;
                }
                return false;
            };
            if(judge(/* num = */ a)){
                if(cnt != IGNORE_INTERVAL - 1)ans += a;
                cnt = (cnt + 1) % IGNORE_INTERVAL;
            }
        }
        answer.push(/* value = */ ans);
    }

    answer.output();
    return 0;
}
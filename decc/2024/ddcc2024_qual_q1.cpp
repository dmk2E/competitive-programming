/*アルゴリズムと工夫点(条件を満たす整数は何個？/CPU: - ms Memory: - KB  Length: - B)
与えられた3条件を満たす整数が，[10, X]の範囲内にいくつ存在するかを全探索すればよい．
最悪計算量は，O(X * log10(X)) ≒ 10 ^ 7 となり，高速．
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

// vector<int> ipt = {
//     111,
//     212,
//     1000
// };
vector<int> ipt = {
    11111,
    31415,
    1000000
};
Outputer<int> answer;

int main(){
    int i, j;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto& x = ipt[ipt_id];

        int ans = 0;
        for(i = 10;i <= x;i++){
            auto judge = [](int num) -> bool{
                if(num % 3 != 2)return false;
                if((num / 10) % 10 != 1)return false;
                
                int sum_digit = 0;
                while(num > 0){
                    sum_digit += num % 10;
                    num /= 10;
                }
                return sum_digit <= 7;
            };
            ans += judge(/* num = */ i);
        }
        answer.push(/* value = */ ans);
    }

    answer.output();
    return 0;
}
/*アルゴリズムと工夫点(スペアはいくつ？？/CPU: - ms Memory: - KB  Length: - B)
フレーム毎に，「倒したピン数の合計が10」かつ「1投目に倒したピン数が10でない」かを順次判定すればよい．
最悪計算量は，O(MAX_FRAME) < 10 ^ 2 となり十分高速．
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

    void output(){
        int i;
        if(ans.size() > 0){
            rep(i, ans.size() - 1)cout << ans[i] << ',';
            cout << ans[i] << '\n';
        }
    }
};

// vector<vector<int> > ipt = {
//     {1,4,2,8,0,1,1,9,2,5,7,3,2,6,4,4,9,1,3,5}, 
//     {10,0,1,2,3,5,6,2,10,0,9,1,0,3,2,7,3,5,2,1}, 
//     {0,10,3,7,5,5,2,1,0,10,3,1,6,4,2,1,3,1,3,3}
// };
vector<vector<int> > ipt = {
    {10,0,9,1,8,1,7,3,6,2,5,5,4,5,2,8,2,3,1,8}, 
    {5,5,4,4,3,7,6,4,7,3,9,1,5,2,1,1,0,0,9,0}, 
    {0,10,1,9,10,0,10,0,2,8,0,10,1,9,9,0,1,8,2,2}
};
Outputer<int> answer;

int main(){
    int i, j;

    const int MAX_FRAME = 10;
    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto& table = ipt[ipt_id];

        int ans = 0;
        rep(i, MAX_FRAME)ans +=  table[2 * i] != 10 && (table[2 * i] + table[2 * i + 1]) == 10;
        answer.push(/* value = */ans);
    }

    answer.output();
    return 0;
}
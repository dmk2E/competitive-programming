/*アルゴリズムと工夫点(玉落とし装置/CPU: - ms Memory: - KB  Length: - B)
穴のある地面と装置の相対位置を全探索して解く．
問題文では装置を動かすことになっているが，穴の位置を動かすと考えても解は変わらない．
よって穴の位置を，[-199, 199] だけ横に平行移動した時の，穴に入るボールの個数を計算すればよい．
ボールと穴の位置情報については，座標[1, 200] の位置にそれぞれ存在するかを2配列に分けて保持する．
最悪計算量は，O(MAX_X * MAX_X) < 10 ^ 5 となり，十分高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
#define INPUT_NUMBER 5
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
        rep(i, ans.size() - 1)cout << ans[i] << ',';
        cout << ans[i] << '\n';
    }
};

vector<vector<int> > ipt = {
    {1,2,4,0,3,4,5,6,0}, 
    {1,4,5,0,1,2,0}, 
    {1,2,4,0,1,3,4,0}, 
    {2,3,6,7,9,10,0,5,7,9,11,13,15,0}, 
    {4,11,14,15,23,28,29,36,43,45,48,52,55,62,63,68,91,99,102,108,115,116,122,124,148,163,171,186,190,198,0,5,7,12,14,15,17,38,46,51,52,60,66,67,68,69,72,73,80,93,96,101,102,103,105,107,109,113,115,116,117,119,123,125,132,136,138,141,149,150,154,156,161,170,180,187,189,192,195,198,200,0}
};
Outputer<int> answer;

int main(){
    int i, j;

    const int MAX_X = 200;
    auto parseInput = [&](vector<bool>& balls, vector<bool>& halls, vector<int>& ipt_line) -> void{
        bool is_balls = true;
        for(int x : ipt_line){
            if(is_balls){
                if(x == 0)is_balls = false;
                else balls[x - 1] = true;
            }else if(x != 0)halls[x - 1] = true;
        }
    };
    
    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto& table = ipt[ipt_id];

        vector<bool> balls(MAX_X, false), halls(MAX_X, false);
        parseInput(/* balls = */ balls, /* halls = */ halls, /* ipt_line = */ table);

        auto calcMin = [&]() -> int{
            int i, ans = 0;
            for(int halls_top = -MAX_X + 1;halls_top < MAX_X;halls_top++){
                int sum = 0;
                rep(i, MAX_X){
                    int balls_id = i + halls_top;
                    if(0 <= balls_id && balls_id < MAX_X)
                        sum += halls[i] && balls[balls_id];
                }
                ans = max(ans, sum);
            }
            return ans;
        };
        answer.push(calcMin());
    }

    answer.output();
    return 0;
}
/*アルゴリズムと工夫点(的当ての達人/CPU: - ms Memory: - KB  Length: - B)
再帰を用いた順列全探索で解く．
一度狙った的は，その的を倒すまで他の的を倒すことはできない．
的の数は小さいため，「的をどのような順序で倒すか」を全探索すればよい．
また，残った弾数を点数に加算する場合，新しく的を狙い始める前に「終了」するのが最適である．
最悪計算量は，O(NUM_TARGET!) = O(10!) < 10 ^ 7 となり，高速．
※ 再帰で実装し，枝刈りを行っているため，より高速に動作する．
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
//     {7,1,3,2,5,3,4,5,1,6}, 
//     {12,10,6,5,18,16,8,7,15,12}, 

//     {1,2,3,4,5,6,7,8,9,10}, 
//     {10,9,8,7,6,5,4,3,2,1}, 

//     {11,8,2,10,6,8,2,13,3,9}, 
//     {12,1,3,6,2,1,9,13,10,4}
// };
vector<vector<int> > ipt = {
    {6,3,4,5,8,5,9,3,1,7}, 
    {5,10,6,4,9,1,7,8,4,3}, 

    {10,7,5,7,3,2,4,4,3,8}, 
    {8,1,5,6,9,8,8,4,1,3}, 

    {12,7,6,4,6,11,2,9,2,15}, 
    {2,6,10,1,8,4,2,2,9,5}
};
Outputer<int> answer;
const int MAX_B = 10;
const int NUM_TARGET = 10;

int main(){
    int i, j;

    for(int ipt_id = 0;ipt_id < INPUT_NUMBER;ipt_id++){
        auto& b = ipt[2 * ipt_id];
        auto& p = ipt[2 * ipt_id + 1];
        
        int ans = 0;
        auto rec = [&](auto& func, int is_hit, int sum_point, int num_bullet) -> void{
            int i, j;
            ans = max(ans, sum_point + num_bullet);

            rep(i, MAX_B)if(!((is_hit >> i) & 1) && num_bullet >= b[i]){
                int get_point = p[i], hitted = (1 << i);
                if(i + 2 < MAX_B && !((is_hit >> (i + 1)) & 1) && ((is_hit >> (i + 2)) & 1)){
                    hitted |= (1 << (i + 1));
                    get_point += p[i + 1];
                }
                if(i - 2 >= 0 && !((is_hit >> (i - 1)) & 1) && ((is_hit >> (i - 2)) & 1)){
                    hitted |= (1 << (i - 1));
                    get_point += p[i - 1];
                }

                int lost_bullet = b[i];
                if(num_bullet == b[i])lost_bullet -= get_point;

                func(
                    /* func = */ func, 
                    /* is_hit = */ is_hit | hitted, 
                    /* sum_point = */ sum_point + get_point, 
                    /* num_bullet = */ num_bullet - lost_bullet
                );
            }
        };
        rec(
            /* func = */ rec, 
            /* is_hit = */ 0, 
            /* sum_point = */ 0, 
            /* num_bullet = */ NUM_TARGET
        );

        answer.push(/* value = */ ans);
    }

    answer.output();
    return 0;
}
/*アルゴリズムと工夫点(Yacht/CPU: 164 ms Memory: 5968 KB  Length: 1829 B)
メモ化再帰で解く．
※ 全探索は無理->DPで高速化できないか検討->全パターンをどのような状態に当てはめるか考える
*/
#include<iostream>
#include<vector>
#include<map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_ROLL 6
#define MAX_DICE 5
#define TURN 3
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

template<typename T>
void chMax(T& x,const T& y){x = max(x,y);}

int a[MAX_ROLL];

int main(){
    int i,j;
    rep(i,MAX_ROLL)scanf("%d",&a[i]);
    vector<map<vector<int>,double> > memo(TURN);
    auto rec = [&](auto &func, int rest_turn, vector<int> keep)->double{
        if(rest_turn == 0){
            int i,j;
            double res = 0;
            rep(i,MAX_ROLL){
                int cnt = 0;
                for(int x : keep)if(x == a[i])cnt++;
                chMax(res, (double)cnt*a[i]);
            }
            return res;
        }
        rest_turn--;
        if(memo[rest_turn].count(keep)) return memo[rest_turn][keep];
        auto g = [&](auto& funcG, int rest_dice, vector<int> dice)->double{
            int i;
            if(rest_dice == 0){
                int m = dice.size();
                double res = 0;
                int s;
                rep(s,1<<m){
                    vector<int> kp = keep;
                    rep(i,m)if((s>>i)&1)kp.push_back(dice[i]);
                    chMax(res,func(func,rest_turn,kp));
                }
                return res;
            }
            double res = 0;
            rep(i,MAX_ROLL){
                dice.push_back(a[i]);
                res += funcG(funcG,rest_dice-1,dice);
                dice.pop_back();
            }
            return res/MAX_ROLL;
        };
        double res = g(g,MAX_DICE-keep.size(),{});
        return memo[rest_turn][keep] = res;
    };
    double ans = rec(rec,TURN,{});
    printf("%.10f\n",ans);
    return 0;
}
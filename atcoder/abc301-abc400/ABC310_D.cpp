/*アルゴリズムと工夫点(Peaceful Teams/CPU: 3 ms Memory: 3920 KB  Length: 1291 B)
再帰全探索（ベル数）で解く．
再帰では同じ状態を生成しないよう，次の操作を繰り返す．
1. 今現在存在しているチームの中から，どれか1チームに人_{i}を参加させる．
2. 新しくチームを作り，人_{i}を一人目に指定する
3. 次の人_{i+1} について，同様のことを行う．
最悪計算量は，O(bell(N)*N^(3))=115975000≒ 10^8 となり間に合う．
実際は枝刈り条件により，高速に処理が終了する．
※チーム分けの被りを防ぐため，人1~人Nまで順番に決めていく．
*/
#include<iostream>
#include<vector>
#include<set>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,t,m;

int main(){
    int i,j;
    scanf("%d%d%d",&n,&t,&m);
    set<int> not_friendly;
    while(m--){
        scanf("%d%d",&i,&j);
        i--;j--;
        not_friendly.insert((1<<i)|(1<<j));
    }
    vector<vector<int> > teams;
    auto judge=[&](vector<int>& team)->bool{
        int i;
        rep(i,team.size())rep(j,i)if(not_friendly.find((1<<team[i])|(1<<team[j]))!=not_friendly.end())return false;
        return true;
    };
    auto rec=[&](auto& func,int now,int t)->int{
        if(now==n)return t==0;
        int i,ans=0;
        // join one of existing teams
        if(teams.size()+n-now>t){
            rep(i,teams.size()){
                teams[i].push_back(now);
                if(judge(teams[i]))ans+=func(func,now+1,t);
                teams[i].pop_back();
            }
        }
        // create a new team
        if(t>0){
            teams.push_back(vector<int>(1,now));
            ans+=func(func,now+1,t-1);
            teams.pop_back();
        }
        return ans;
    };
    printf("%d\n",rec(rec,0,t));
    return 0;
}
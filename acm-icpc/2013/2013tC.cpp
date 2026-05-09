/*アルゴリズムと工夫点(双子の読書感想文/CPU: 0 ms Memory: 3572 KB  Length: 1435 B)
貪欲法&動的計画法で解く．考察力が要求されるが，貪欲法が求まれば，典型DP．
※この貪欲法は初見では，思いつけませんでした.....
※上界や下界などの境界値を達成するアルゴリズムが存在するか，また存在するための条件を，考察により求めることを始点とするようにする．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_R 1000
#define MAX_W 1000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    int r_,w_;

    Data(int r=0,int w=0):r_(r),w_(w){}
};

int n;

int main(){
    int i,j,sum_r,sum_w,rest;
    while(1){
        scanf("%d",&n);
        if(!n)break;
        sum_r=sum_w=0;
        vector<Data> ipt(n);
        rep(i,n){
            scanf("%d%d",&ipt[i].r_,&ipt[i].w_);
            sum_r+=ipt[i].r_;
            sum_w+=ipt[i].w_;
        }
        sort(ipt.rbegin(),ipt.rend(),[](const Data& a,const Data& b)->bool{
            return a.r_<b.r_;
        });
        if(2*ipt[0].r_<=sum_r)printf("%d\n",sum_r+sum_w);
        else{
            rest=ipt[0].r_-(sum_r-ipt[0].r_);
            vector<int> dp(rest+1,0); // dp[i]:時間i以下で，感想文に使える最大の時間
            for(i=1;i<n;i++){
                vector<int> now=dp;
                rep(j,rest+1)if(dp[j]+ipt[i].w_<=rest)now[dp[j]+ipt[i].w_]=max(now[dp[j]+ipt[i].w_-1],max(now[dp[j]+ipt[i].w_],dp[j]+ipt[i].w_));
                rep(j,rest)now[j+1]=max(now[j+1],now[j]);
                swap(now,dp);
            }
            //rep(j,rest+1)printf("%d ",dp[j]);puts("");
            printf("%d\n",max(2*ipt[0].r_+sum_w-dp[rest],sum_r+sum_w));
        }
        //cout<<flush;
    }
    return 0;
}
/*アルゴリズムと工夫点(Vitamin Balance/CPU: 38 ms Memory: 4052 KB  Length: 1141 B)
動的計画法により，カロリーを固定した時の，最大摂取量を求めることができる．
その値を元に解の二分探索を行えばよい．
※もっとも摂取量が少ないものがR以上->全てのビタミンがR以上の値になる という判定条件になる
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_A (int)(2e9)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,x,v,a,c;

int main(){
    int i,left,right,mid;
    scanf("%d%d",&n,&x);
    vector<vector<int> > dp(3,vector<int>(x+1,0));
    while(n--){
        vector<vector<int> > now=dp;
        scanf("%d%d%d",&v,&a,&c);
        v--;
        rep(i,x+1)if(i+c<=x)now[v][i+c]=max(dp[v][i+c],dp[v][i]+a);
        swap(dp,now);
    }
    auto judge=[&](int mn)->bool{
        int i,left,right,mid,sum=0;
        rep(i,3){
            left=0;
            right=x+1;
            while(left<right){
                mid=(left+right)/2;
                if(dp[i][mid]<mn)left=mid+1;
                else right=mid;
            }
            sum+=left;
            if(sum>x)return false;
        }
        return true;
    };
    left=0;
    right=MAX_A+1;
    while(left<right){
        mid=(left+right)/2;
        if(judge(mid))left=mid+1;
        else right=mid;
    }
    printf("%d\n",left-1);
    return 0;
}
/*アルゴリズムと工夫点(Changing Jewels/CPU: 1 ms Memory: 3880 KB  Length: 811 B)
相互再帰の実装では，実装が複雑になるのを防ぐため，関数に引数を一つ追加し，どちらの関数として処理するかを定義すると楽らしい．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,x,y;

int main(){
    int i,j;
    scanf("%d%d%d",&n,&x,&y);
    const ll NIL=-1;
    vector<ll> memoR(n,NIL),memoB(n,NIL);
    auto recR=[&](auto& f,auto& recB,int lv)->ll{
        if(lv==0)return memoR[lv]=0;
        return memoR[lv]=(memoR[lv-1]==NIL?f(f,recB,lv-1):memoR[lv-1])+(memoB[lv]==NIL?recB(recB,f,lv):memoB[lv])*x;
    };
    auto recB=[&](auto& f,auto& recR,int lv)->ll{
        if(lv==0)return memoB[lv]=1;
        return memoB[lv]=(memoR[lv-1]==NIL?recR(recR,f,lv-1):memoR[lv-1])+y*(memoB[lv-1]==NIL?f(f,recR,lv-1):memoB[lv-1]);
    };
    printf("%lld\n",recR(recR,recB,n-1));
    return 0;
}
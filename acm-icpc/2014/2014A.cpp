/*アルゴリズムと工夫点(税率変更/CPU: 30 ms Memory: 3548 KB  Length: 515 B)
税率がxの時にsとなり得る2商品の値段の組(a,b)を全探索し，税率yの時の値段を計算，最大値を記録していけばよい．
最悪計算量は，O(s^(2))≒10^6 となり十分高速．

※問題URL：https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1192
*/
//#include<iostream>
//#include<cassert>
#include<bits/stdc++.h>
#define rep(i,n)for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int x,y,s;

/// @brief 指定した税率時の2商品の税込合計価格
/// @param a 1つ目の商品の税抜価格
/// @param b 2つ目の商品の税抜価格
/// @param p 消費税率（パーセント）
/// @return 
int calc(int a,int b,int p){
    return ((a*(100+p))/100)+((b*(100+p))/100);
}

int main(){
    int i,j,ans;
    while(1){
        scanf("%d%d%d",&x,&y,&s);
        if(!(x||y||s))break;
        ans=0;
        for(i=1;i<s;i++)for(j=1;j<=i;j++){
            if(calc(i,j,x)==s)ans=max(ans,abs(calc(i,j,y)));
        }
        printf("%d\n",ans);
    }
    return 0;
}
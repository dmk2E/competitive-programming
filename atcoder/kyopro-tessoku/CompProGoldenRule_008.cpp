/*アルゴリズムと工夫点(Two Dimensional Sum/CPU: 142 ms Memory: 12268 KB  Length: 693 B)
二次元累積和の基本問題．1次元累積和と同様，作成時に標準入力の工夫ができる．
ある矩形の総和を求める式は，関数等で切り離しておいた方が理解しやすいと思う．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w,q;

int main(){
    int i,j,k,l;
    scanf("%d%d",&h,&w);
    vector<vector<int> > sum(h+1,vector<int>(w+1,0));
    rep(i,h)rep(j,w){
        scanf("%d",&sum[i+1][j+1]);
        sum[i+1][j+1]+=sum[i+1][j]+sum[i][j+1]-sum[i][j];
    }
    auto f=[&](int a,int b,int c,int d)->int{
        return sum[c+1][d+1]-sum[c+1][b]-sum[a][d+1]+sum[a][b];
    };
    scanf("%d",&q);
    while(q--){
        scanf("%d%d%d%d",&i,&j,&k,&l);
        i--;j--;k--;l--;
        printf("%d\n",f(i,j,k,l));
    }
    return 0;
}
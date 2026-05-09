/*アルゴリズムと工夫点(Grid Filling/CPU: 234 ms Memory: 113368 KB  Length: 1290 B)
与えられるAijの値の範囲が1以上N以下で，N<=300であるため，前処理で「値毎の累積和」と「Aij上で値毎のその総数」を求めておく．
そうすると，指定された範囲に存在する値の種類数はO(1)で求めることができる．
従って，最悪計算量はO(H*W*N)≒10^7 となり，高速．
※初!バーチャルコンテスト内で初見5完!嬉しい!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w,n,hh,ww;

int main(){
    int i,j,k,cnt;
    scanf("%d%d%d%d%d",&h,&w,&n,&hh,&ww);
    vector<vector<vector<int> > > sumN(n+1,vector<vector<int> >(h+1,vector<int>(w+1,0)));
    vector<int> num(n+1,0);
    rep(i,h)rep(j,w){
        scanf("%d",&k);
        sumN[k][i+1][j+1]++;
        num[k]++;
    }
    rep(k,n+1)rep(i,h)rep(j,w)sumN[k][i+1][j+1]+=sumN[k][i+1][j]+sumN[k][i][j+1]-sumN[k][i][j];
    auto f=[&](int n,int a,int b,int c,int d)->int{
        return sumN[n][c+1][d+1]-sumN[n][c+1][b]-sumN[n][a][d+1]+sumN[n][a][b];
    };
    rep(i,h-hh+1){
        rep(j,w-ww){
            cnt=0;
            //printf("(");
            rep(k,n){
                cnt+=num[k+1]-f(k+1,i,j,i+hh-1,j+ww-1)>0;
                //printf("%d,",f(k+1,i,j,i+hh-1,j+ww-1));
            }
            //printf(")");
            printf("%d ",cnt);
        }
        cnt=0;
        //printf("(");
        rep(k,n){
            cnt+=num[k+1]-f(k+1,i,j,i+hh-1,j+ww-1)>0;
            //printf("%d,",f(k+1,i,j,i+hh-1,j+ww-1));
        }
        //printf(")");
        printf("%d\n",cnt);
    }
    return 0;
}
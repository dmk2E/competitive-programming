/*アルゴリズムと工夫点(Rook Path/CPU: 66 ms Memory: 3900 KB  Length: 933 B)
単純にDPで考えると，
dp[i][j][k]:i回目に(j,k)にいる方法の数
となるが，ゴールとなる(x2,y2)に関係が無いマスの値のほとんどは同じ値になる．
そこで，マス目を行がx2か否か，列がy2か否かの4通りに分ける．そうすることで最悪計算量 O(K)で解くことができる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MOD 998244353 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w,k,x1,y1,x2,y2;

int main(){
    int i,j;
    scanf("%d%d%d%d%d%d%d",&h,&w,&k,&x1,&y1,&x2,&y2);
    vector<vector<ll> > last(2,vector<ll>(2,0));
    last[x1==x2][y1==y2]++;
    rep(i,k){
        vector<vector<ll> > now(2,vector<ll>(2,0));
        rep(j,2){
            now[0][j]=(now[0][j]+(last[0][j]*(h-2))%MOD)%MOD;
            now[1][j]=(now[1][j]+last[0][j])%MOD;
            now[0][j]=(now[0][j]+(last[1][j]*(h-1))%MOD)%MOD;
        }
        rep(j,2){
            now[j][0]=(now[j][0]+(last[j][0]*(w-2))%MOD)%MOD;
            now[j][1]=(now[j][1]+last[j][0])%MOD;
            now[j][0]=(now[j][0]+(last[j][1]*(w-1))%MOD)%MOD;
        }
        swap(last,now);
    }
    printf("%lld\n",last[1][1]);
    return 0;
}
/*アルゴリズムと工夫点(弁当作り/CPU: 2 ms Memory: 85132 KB  Length: 1381 B)
<i>n<=20の場合，作るレシピをbit全探索する．最悪計算量は O(2^(n)*n*m)≒10^8
途中で探索をやめるなどして高速化すれば間に合う．
<ii>n>20の場合，m<25 となるから，DPで解く．
dp[i][j]:レシピ1~i+1まで作るか否か決めて，材料の使用状況jだった時の，最大のレシピ数．
最悪計算量は，O(n*2^(m))≒10^8 となり間に合う．
※変な制約の時は，このように場合分けすることがあることを覚えておこう．
※各材料を偶数個使えばよい->状態をbitで持ち，00...0 の状態で最大の料理数を求めればよい．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 500
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,k,ans;
    const int NIL=-MAX_N*2-1;
    while(1){
        scanf("%d%d",&n,&m);
        if(!(n||m))break;
        if(n<=20){
            ans=0;
            vector<vector<bool> > rcp(n,vector<bool>(m,false));
            rep(i,n)rep(j,m){
                scanf("%1d",&k);
                rcp[i][j]=(k==1);
            }
            rep(i,1<<n){
                vector<int> ids;
                rep(j,n)if((i>>j)&1)ids.push_back(j);
                rep(j,m){
                    bool flag=false;
                    for(int id:ids)flag^=rcp[id][j];
                    if(flag)break;
                }
                if(j==m)ans=max(ans,(int)ids.size());
            }
            printf("%d\n",ans);
            cout<<flush;// 処理経過観察のため，逐次標準出力
        }else{
            vector<int> dp(1<<m,NIL);
            dp[0]=0;
            rep(i,n){
                vector<int> now=dp;
                k=0;
                getchar();
                rep(j,m){
                    k*=2;
                    k+=(getchar()=='1');
                }
                rep(j,1<<m)now[j^k]=max(now[j^k],dp[j]+1);
                swap(now,dp);
            }
            printf("%d\n",dp[0]);
            cout<<flush;// 処理経過観察のため，逐次標準出力
        }
    }
    return 0;
}
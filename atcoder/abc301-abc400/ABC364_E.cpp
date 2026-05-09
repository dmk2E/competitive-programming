/*アルゴリズムと工夫点(Maximum Glutton/CPU: 208 ms Memory: 260212 KB  Length: 1519 B)
dp[i][j][k]:i番目までの料理の中で，j個選んだ時，しょっぱさがk以下の条件下で最小のAの値
を計算し，適切に個数を返すだけ．．．だが，あと5分足りなかった...悔しすぎる．
最悪計算量はO((N^2)*B)<10^7 より，高速．
*/
#include<iostream>
#define MAX_N 80
#define MAX_X 10000
#define MAX_Y 10000
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n,x,y,a,b,dp[MAX_N+1][MAX_N+1][MAX_Y+2];

int main(){
    int i,j,k,mmin,ans=0,ii;
    scanf("%d%d%d",&n,&x,&y);
    rep(i,n+1){
        rep(j,n+1){
            rep(k,MAX_Y+2){
                dp[i][j][k]=j==0?0:MAX_X+1;
            }
        }
    }
    rep(i,n){
        scanf("%d%d",&a,&b);
        rep(j,n){
            mmin=MAX_X+1;
            rep(k,y+1){
                dp[i+1][j+1][k]=dp[i][j+1][k];
                if(k>=b&&dp[i+1][j+1][k]>dp[i][j][k-b]+a){
                    if(dp[i][j][k-b]<=x&&ans<j+1)ans=j+1;
                    dp[i+1][j+1][k]=dp[i][j][k-b]+a;
                }
            }
            rep(k,y+1)
                if(mmin>dp[i][j][k]){
                    mmin=dp[i][j][k];
                }
            dp[i+1][j+1][k]=dp[i][j+1][k];
            if(dp[i+1][j+1][k]>mmin+a){
                if(mmin<=x&&ans<j+1)ans=j+1;
                dp[i+1][j+1][k]=mmin+a;
            }
        }
        //rep(j,n+1){rep(k,y+2){printf("%5d ",dp[i+1][j][k]);}puts("");}printf("ans:%d\n",ans);
    }
    ii=-1;
    rep(j,n+1){
        rep(k,y+1){
            if(dp[i][j][k]<=x){
                if(ii<j)
                    ii=j;
            }
        }
    }
    if(ii==n)
        printf("%d\n",ii);
    else{
        printf("%d\n",ii==ans?ans+1:ans);
    }
    return 0;
}
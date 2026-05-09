/*アルゴリズムと工夫点(AtCoder Janken 3/CPU: 6 ms Memory: 6392 KB  Length: 1109 B)
dp[i][j]:j回目の勝負をした時点で，その時出した手がi(0:パー,1:グー，2:チョキ)である時，勝つことができた最大数
とする動的計画法で解ける．DPテーブルの値の遷移は，与えられた条件通り，前に出した手でなく，負けない手であることに注意して行う．
最悪計算量はO(N+3*N)=N<10^6 より，十分高速．
*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N (int)(2e5)
#define NIL -1
using namespace std;
typedef long long ll;

int c2Int(char c){
    switch(c){
        case 'P':
            return 0;
        case 'R':
            return 1;
        default:
            return 2;
    }
    return 0;
}

int n,dp[3][MAX_N+1]={0},win[3]={2,0,1};
string s;

int main(){
    int i,j,aoki;
    scanf("%d",&n);
    cin>>s;
    rep(j,s.length()){
        aoki=c2Int(s[j]);
        rep(i,3)
            dp[i][j+1]=NIL;
        //printf("aoki:%d,win:%d\n",aoki,win[aoki]);
        rep(i,3){
            if(dp[i][j]!=NIL){
                if(win[aoki]!=i&&dp[win[aoki]][j+1]<dp[i][j]+1){
                    dp[win[aoki]][j+1]=dp[i][j]+1;
                }
                if(aoki!=i&&dp[aoki][j+1]<dp[i][j]){
                    dp[aoki][j+1]=dp[i][j];
                }
            }
        }
    }
    //rep(i,3){rep(j,n+1){printf("%2d ",dp[i][j]);}puts("");}
    printf("%d\n",max(max(dp[0][n],dp[1][n]),dp[2][n]));
    return 0;
}
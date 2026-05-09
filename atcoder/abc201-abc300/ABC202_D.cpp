/*アルゴリズムと工夫点(aab aba baa/CPU: 1 ms Memory: 3928 KB  Length: 818 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_S 60
#define MAX_A 30
#define MAX_B 30
using namespace std;

int a,b;
long long k,dp[MAX_A+1][MAX_B+1]={0};

int main(){
    int i,j;
    long long cnt=0;
    string s;
    scanf("%d%d%lld",&a,&b,&k);
    dp[0][0]=1;
    rep(i,MAX_A+1){
        rep(j,MAX_B+1){
            if(i>0)
                dp[i][j]+=dp[i-1][j];
            if(j>0)
                dp[i][j]+=dp[i][j-1];
        }
    }
    //rep(i,MAX_A+1){rep(j,MAX_B+1)printf("dp[%d][%d]=%lld\n",i,j,dp[i][j]);}
    while(a+b>0){
        if(a>0&&cnt+dp[a-1][b]>=k){
            s+="a";
            a--;
        }else{
            cnt+=dp[a-1][b];
            s+="b";
            b--;
        }
    }
    cout<<s<<endl;
    return 0;
}
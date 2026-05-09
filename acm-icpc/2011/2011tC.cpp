/*アルゴリズムと工夫点(最短ルート/CPU: 4690 ms Memory: 4048 KB  Length: 1269 B)
動的計画法で解けた。現在の状態を、ステージiがクリアされているなら先頭からi番目が「1」、クリアしてないなら「0」とする2進数表記で、クリアしたステージの集合Sを表す。集合Sの部分集合sub(S)とする。
dp[S]:Sの状態における最短クリア時間とすると、dp[S]=min(sub(S)1,sub(S)2,...)となる。したがって最悪計算量は、O(N^2 * 2^N)<10^7 となり、高速。
※初見AC出来た。ダイクストラ法かな？と思ったが、動的計画法で十分であることが分かり、解けた。1.5hかかったので、もっと早く解きたい。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 16
#define MAX 1600001
using namespace std;

int n,equip[MAX_N][MAX_N+1],dp[2<<MAX_N];

int popCount(unsigned int x){//O(log2(x))で、xを2進数表記した時の「1」の数を返す。
    int cnt=0;
    while(x>0){
        cnt+=(x&1);
        x>>=1;
    }
    return cnt;
}

int cal(int sub,int goal){//部分集合subの状態からgoalに遷移するときにかかる最小コストを計算する。O(n)
    int i,min;
    goal^=sub;
    for(i=0;i<n;i++)
        if(goal&(1<<(n-1-i)))
            break;
    goal=i;
    min=equip[goal][0];
    for(i=0;i<n;i++)
        if((sub&(1<<(n-1-i)))&&equip[goal][i+1]<min)
            min=equip[goal][i+1];
    return min;
}

int main(){
    int i,j,sub;
    while(1){
        scanf("%d",&n);
        if(!n)
            break;
        rep(i,n)
            rep(j,n+1)
                scanf("%d",&equip[i][j]);
        rep(i,2<<n)
            dp[i]=MAX;
        dp[0]=0;
        for(i=1;i<(1<<n);i++){
            j=popCount(i);
            sub=i;
            //printf("i:%d\n",i);
            while(sub>0){
                sub=(sub-1)&i;
                if(popCount(sub)!=j-1)
                    continue;
                //printf("sub:%d\n",sub);
                dp[i]=min(dp[i],dp[sub]+cal(sub,i));
            }
            //printf("min:%d\n",dp[i]);
        }
        printf("%d\n",dp[(1<<n)-1]);
    }
    return 0;
}
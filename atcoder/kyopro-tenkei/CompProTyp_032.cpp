/*アルゴリズムと工夫点(AtCoder Ekiden/CPU: 67 ms Memory: 3860 KB  Length: 1246 B)
N=10だから、順列全探索で解ける。ただし、仲の悪い選手同士が隣り合わないように枝狩りをする。最悪計算量は、O(N*N!)<10^8 となり、間に合う。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 10
#define MAX 10001
#define NIL -1
using namespace std;

int n,m,x,y,a[MAX_N][MAX_N];
bool adj[MAX_N][MAX_N]={0};

int dfs(int now,int last,int sum,bool comb[MAX_N]){
    int min=MAX,i,j;
    if(now==n-1){
        rep(i,n)
            if(comb[i]==false&&adj[last][i]==false)
                break;
        return i==n?MAX:sum+a[i][now];
    }
    if(now==0){
        rep(i,n){
            comb[i]=true;
            if(min>(j=dfs(now+1,i,a[i][now],comb)))
                min=j;
            comb[i]=false;
        }
    }else{
        rep(i,n){
            if(comb[i]==false&&adj[last][i]==false){
                comb[i]=true;
                if(min>(j=dfs(now+1,i,sum+a[i][now],comb)))
                    min=j;
                comb[i]=false;
            }
        }
    }
    return min;
}

int main(){
    int i,j;
    bool comb[MAX_N]={0};
    scanf("%d",&n);
    rep(i,n)
        rep(j,n)
            scanf("%d",&a[i][j]);
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&x,&y);
        adj[--x][--y]=true;
        adj[y][x]=true;
    }
    printf("%d\n",MAX==(j=dfs(0,NIL,0,comb))?NIL:j);
    return 0;
}
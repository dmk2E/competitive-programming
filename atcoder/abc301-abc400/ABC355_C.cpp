/*アルゴリズムと工夫点(Bingo 2/CPU: 53 ms Memory: 50736 KB  Length: 907 B)
if文のケアレスミスで1WA．トレースは習慣化したい．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 2000
using namespace std;

typedef pair<int,int> p;

int n,t,mmap[MAX_N][MAX_N],row[MAX_N]={0},cln[MAX_N]={0},lft=0,rgt=0;
p mmmap[MAX_N*MAX_N+1];

void showMap(){
    int i,j;
    rep(i,n){
        rep(j,n)
            printf("%d ",mmap[i][j]);
        puts("");
    }
}

int main(){
    int i,j;
    p now;
    scanf("%d%d",&n,&t);
    rep(i,n)
        rep(j,n){
            mmap[i][j]=n*i+j+1;
            mmmap[n*i+j+1]=p(i,j);
        }
    rep(i,t){
        scanf("%d",&j);
        now=mmmap[j];
        row[now.first]++;cln[now.second]++;
        if(now.first==now.second)
            lft++;
        if(now.second==n-1-now.first)
            rgt++;
        if(row[now.first]==n||cln[now.second]==n||lft==n||rgt==n)
            break;
    }
    printf("%d\n",i==t?-1:i+1);
    return 0;
}
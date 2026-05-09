/*アルゴリズムと工夫点(Make Takahashi Happy/CPU: 10 ms Memory: 3896 KB  Length: 659 B)
右か下の2パターンしかないため，今まで登場した数を連想配列や集合を用いて保持して置き，進んだ先に書いてある整数が既に登場したものであった場合に探索を打ち切る枝刈り全探索解く．
最悪計算量は20!/(10!*10!)<10^7 となり，十分高速．
*/
#include<iostream>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_H 10
#define MAX_W 10
using namespace std;

int h,w,a[MAX_H][MAX_W];
set<int> check;

int dfs(int y,int x){
    if(y==h-1&&x==w-1)
        return 1;
    int cnt=0;
    check.insert(a[y][x]);
    if(y+1<h&&check.find(a[y+1][x])==check.end())
        cnt+=dfs(y+1,x);
    if(x+1<w&&check.find(a[y][x+1])==check.end())
        cnt+=dfs(y,x+1);
    check.erase(a[y][x]);
    return cnt;
}

int main(){
    int i,j;
    scanf("%d%d",&h,&w);
    rep(i,h)
        rep(j,w)
            scanf("%d",&a[i][j]);
    printf("%d\n",dfs(0,0));
    return 0;
}
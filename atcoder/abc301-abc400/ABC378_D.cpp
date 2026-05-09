/*アルゴリズムと工夫点(Count Simple Paths/CPU: 46 ms Memory: 3888 KB  Length: 976 B)
始点を固定して，深さ優先探索をし，条件を満たす経路の回数を数え上げる．
最悪計算量は O(H*W*3^(K+1))=10^(2)*3^(11+1)<10^8 となり間に合う．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w,k;

int main(){
    int i,j,ans=0;
    scanf("%d%d%d",&h,&w,&k);
    vector<string> mmap(h);
    vector<vector<vector<int> > > dp(h,vector<vector<int> >(w,vector<int>(k+1,0)));
    rep(i,h)cin>>mmap[i];
    const int dy[]={-1,0,1,0},dx[]={0,1,0,-1},MAX_D=4;
    auto dfs=[&](auto& f,int sy,int sx,int cnt)->void{
        int i,j,y,x;
        if(cnt==k){
            ans++;
            return ;
        }
        mmap[sy][sx]='#';
        rep(i,MAX_D){
            y=sy+dy[i];
            x=sx+dx[i];
            if(0<=y&&y<h&&0<=x&&x<w&&mmap[y][x]=='.'){
                f(f,y,x,cnt+1);
            }
        }
        mmap[sy][sx]='.';
    };
    rep(i,h)rep(j,w){
        if(mmap[i][j]=='.'){
            dfs(dfs,i,j,0);
        }
    }
    printf("%d\n",ans);
    return 0;
}
/*アルゴリズムと工夫点(Weak Takahashi/CPU: 1 ms Memory: 3912 KB  Length: 1211 B)

*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int h,w;

int main(){
    int i,j;
    scanf("%d%d",&h,&w);
    vector<vector<bool> > mmap(h,vector<bool>(w));
    rep(i,h){
        getchar();
        rep(j,w)mmap[i][j]=(getchar()=='.');
    }
    const int NIL=-1;
    const int dy[]={1,0},dx[]={0,1},MAX_D=2;
    auto bfs=[&]()->int{
        int y,x,i,ans=1;
        queue<P> que;
        P now;
        vector<vector<int> > visited(h,vector<int>(w,NIL));
        que.push(P(0,0));
        visited[0][0]=1;
        while(que.size()){
            now=que.front();que.pop();
            rep(i,MAX_D){
                y=now.first+dy[i];
                x=now.second+dx[i];
                if(0<=y&&y<h&&0<=x&&x<w&&mmap[y][x]&&visited[y][x]==NIL){
                    visited[y][x]=visited[now.first][now.second]+1;
                    if(ans<visited[y][x])ans=visited[y][x];
                    que.push(P(y,x));
                }
            }
        }
        return ans;
    };
    printf("%d\n",bfs());
    return 0;
}
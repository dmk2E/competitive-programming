/*アルゴリズムと工夫点(Loop Railway Plan（★4）/CPU: 17 ms Memory: 12000 KB  Length: 1312 B)
各マスを頂点とみなし，ある頂点iを終点とし，その時まで通った各頂点の集合jとすると，始点を固定した時の生成しうる状態数は，頂点数Vとして，V*2^(V)≒10^6 となる．
従って，状態管理しながらDFSを用いた全探索で解ける．最悪計算量は，O(V^(2)*2^(V))≒10^7 となり，高速．
※何通りかの感覚/バックトラック
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int h,w;

int main(){
    int i,j,mmax,goal;
    scanf("%d%d",&h,&w);
    vector<vector<bool> > mmap(h,vector<bool>(w));
    rep(i,h){
        getchar();
        rep(j,w)mmap[i][j]=getchar()=='.';
    }
    const int MAX_D=4,NIL=-1,dy[]={-1,0,1,0},dx[]={0,1,0,-1};
    vector<vector<int> > visited;
    auto dfs=[&](auto& f,int now,int state)->void{
        int i,y,x;
        //printf("(%d,%d):%d %d\n",now/w,now%w,state,visited[now][state]);
        if(goal==now&&visited[now][state]>=3&&mmax<visited[now][state])mmax=visited[now][state];
        rep(i,MAX_D){
            y=now/w+dy[i];x=now%w+dx[i];
            if(0<=y&&y<h&&0<=x&&x<w&&mmap[y][x]&&(state&(1<<(w*y+x)))==0&&visited[w*y+x][state|(1<<(w*y+x))]==NIL){
                visited[w*y+x][state|(1<<(w*y+x))]=visited[now][state]+1;
                f(f,w*y+x,state|(1<<(w*y+x)));
            }
        }
    };
    mmax=NIL;
    rep(i,h)rep(j,w)
        if(mmap[i][j]){
            visited=vector<vector<int> >(h*w,vector<int>(1<<(h*w),NIL));
            goal=w*i+j;
            visited[goal][0]=0;
            dfs(dfs,goal,0);
        }
    printf("%d\n",mmax==0?NIL:mmax);
    return 0;
}
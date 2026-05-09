/*アルゴリズムと工夫点(Belt Conveyor/CPU: 7 ms Memory: 4396 KB  Length: 1010 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;

int c2Id(char c){
    switch(c){
        case 'U':
            return 0;
        case 'D':
            return 2;
        case 'R':
            return 1;
        default:
            return 3;
    }
    return -1;
}

int main(){
    int i,j,y,x;
    scanf("%d%d",&h,&w);
    vector<string> mmap(h);
    rep(i,h)cin>>mmap[i];
    const int dy[]={-1,0,1,0},dx[]={0,1,0,-1},MAX_D=4;
    vector<vector<bool> > vis(h,vector<bool>(w,false));
    i=j=0;
    while(1){
        vis[i][j]=true;
        y=i+dy[c2Id(mmap[i][j])];
        x=j+dx[c2Id(mmap[i][j])];
        if(0<=y&&y<h&&0<=x&&x<w){
            if(vis[y][x]){
                puts("-1");
                return 0;
            }
            i=y;
            j=x;
        }else
            break;
    }
    printf("%d %d\n",i+1,j+1);
    return 0;
}
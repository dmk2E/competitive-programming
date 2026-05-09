/*アルゴリズムと工夫点(そして，いくつになった？/CPU: 740 ms Memory: 19904 KB  Length: 2881 B)
全ての円盤について、自分の上に重なっている円盤の集合とその数を保持しておき、取り除けるかの判定に用いる。取り除く2つの円盤の選び方について全探索する。渡される円盤の数は最大24個であり、log10(2^24)≒7.2 となり、ビット
表現を用いることができる。
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 24
#define MAX_C 4
using namespace std;

typedef struct circle{
    int x,y,r,c,sum,flag;

    circle():sum(0),flag(0){}

    circle(int xx,int yy,int rr,int cc):x(xx),y(yy),r(rr),c(cc),sum(0),flag(0){}
}Circle;

typedef struct data{
    int exist,cnt;
    Circle c[MAX_N];
}Data;

int n,x,y,r,cc;
bool visited[1<<MAX_N];

int res(Data state){
    int i,j,k,l,mmax=state.cnt;
    vector<int> color[MAX_C];
    Data temp;
    visited[state.exist]=true;
    //puts("");rep(i,n){if((state.exist&(1<<(n-1-i)))==0)continue;printf("id:%d x:%d y:%d r:%d c:%d sum:%d\n",i,state.c[i].x,state.c[i].y,state.c[i].r,state.c[i].c,state.c[i].sum);rep(j,n)printf("%d ",(state.c[i].flag&1<<n-1-j)?1:0);puts("");}
    rep(i,n)
        if((state.exist&(1<<n-1-i))&&state.c[i].sum==0){
            color[state.c[i].c].push_back(i);
        }
    rep(i,MAX_C){
        if(color[i].size()>=2){
            rep(j,color[i].size()){
                for(k=j+1;k<color[i].size();k++){
                    temp=state;
                    temp.cnt+=2;
                    temp.exist&=~((1<<(n-1-color[i][j]))|(1<<(n-1-color[i][k])));
                    //printf("(%d,%d):%d\n",color[i][j],color[i][k],temp.exist);
                    if(visited[temp.exist])
                        continue;
                    rep(l,n){
                        if(temp.exist&(1<<n-1-l)){
                            if(temp.c[l].flag&(1<<(n-1-color[i][j]))){
                                temp.c[l].sum--;
                                temp.c[l].flag&=~(1<<(n-1-color[i][j]));
                            }
                            if(temp.c[l].flag&(1<<(n-1-color[i][k]))){
                                temp.c[l].sum--;
                                temp.c[l].flag&=~((1<<(n-1-color[i][k])));
                            }
                        }
                    }
                    mmax=max(mmax,res(temp));
                }
            }
        }
    }
    return mmax;
}

bool isCommon(int i,int j,Data state){
    return (state.c[i].x-state.c[j].x)*(state.c[i].x-state.c[j].x)+(state.c[i].y-state.c[j].y)*(state.c[i].y-state.c[j].y)<(state.c[i].r+state.c[j].r)*(state.c[i].r+state.c[j].r);
}

int main(){
    int i,j;
    Data state;
    while(1){
        scanf("%d",&n);
        if(!n)
            break;
        state.cnt=0;
        state.exist=(1<<n)-1;
        rep(i,1<<n)
            visited[i]=false;
        rep(i,n){
            scanf("%d%d%d%d",&x,&y,&r,&cc);
            cc--;
            state.c[i]=Circle(x,y,r,cc);
            for(j=i-1;j>=0;j--){
                if(isCommon(i,j,state)){
                    state.c[i].flag|=(1<<(n-1-j));
                    state.c[i].sum++;
                }
            }
        }
        printf("%d\n",res(state));
    }
    return 0;
}
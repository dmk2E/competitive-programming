/*アルゴリズムと工夫点(全チームによるプレーオフ/CPU: 100 ms  Memory: 3544 KB  Length: 1620 B)
また行っていない試合を(チームi,チームj)(i<j) という形で保持する(最大9*8/2=36)。保持した試合毎にどちらが勝つか、各チームの勝利数と敗北数を更新しながら、バックトラックによる枝刈り探索を行う。
枝刈り条件は、「(チームの総数n)/2以上の勝利数または敗北数であるかどうか」となる。
*/
#include<bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 9
using namespace std;

typedef struct game{
    int a,b;

    game(int aa=0,int bb=0):a(aa),b(bb){}

}Game;

typedef struct team{
    int win,lose;

    team(int wwin=0,int llose=0):win(wwin),lose(llose){}
}Team;

int n,m;
bool flag[MAX_N][MAX_N];
Team t[MAX_N];
vector<Game> g;

long long dfs(int now){//dfs(now):(now+1)試合目でどちらのチームを勝たせるか選択するバックトラック
    if(now==g.size()){
        int i;
        rep(i,n)
            if(t[0].win!=t[i].win||t[0].lose!=t[i].lose)
                return 0;
        return 1;
    }
    long long sum=0;
    if(t[g[now].a].win+1<=n/2&&t[g[now].b].lose+1<=n/2){
        t[g[now].a].win++;
        t[g[now].b].lose++;
        sum+=dfs(now+1);
        t[g[now].a].win--;
        t[g[now].b].lose--;
    }
    if(t[g[now].a].lose+1<=n/2&&t[g[now].b].win+1<=n/2){
        t[g[now].a].lose++;
        t[g[now].b].win++;
        sum+=dfs(now+1);
        t[g[now].a].lose--;
        t[g[now].b].win--;
    }
    return sum;
}

int main(){//flag[i][j]:チームiとチームjの試合が既に行われているか否か
    int i,j;
    while(1){
        scanf("%d",&n);
        if(!n)
            break;
        rep(i,n){
            t[i].win=t[i].lose=0;
            rep(j,n)
                flag[i][j]=false;
        }
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&i,&j);
            i--;j--;
            flag[i][j]=true;
            flag[j][i]=true;
            t[i].win++;
            t[j].lose++;
        }
        rep(i,n){
            for(j=0;j<i;j++)
                if(flag[i][j]==false)
                    g.push_back(Game(j,i));
        }
        printf("%lld\n",dfs(0));
        g.clear();
    }
    return 0;
}
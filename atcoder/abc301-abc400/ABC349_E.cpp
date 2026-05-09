/*アルゴリズムと工夫点(Weighted Tic-Tac-Toe/CPU: 2 ms Memory: 3908 KB  Length: 2617 B)
あるゲームをする問題で、どちらのプレイヤーも最適な行動をした結果、勝者の判定を行うプログラムを書く必要がある場合、全ての盤面を読み切ってどの一手が最適か判定する必要がある。実装は再帰を用いたdfsで行う。
ある盤面Cから始めた時の勝者を求める関数をf((盤面Cを引数とする))とする。ある盤面Cの状態で、プレイヤーxが動くとき、行動後の盤面の状態をC'とする。プレイヤーxの行動としてあり得る全てのパターンを調べ、f(C')とすると、
一つでもf(C')=xとなる行動が存在すれば、その行動が最適であり、盤面Cになった時点で勝者がxに確定する。しかし、一つの盤面もf(C')=xとならなければ、その時点で、勝者はxではないことが確定する。
生成される状態数が多い場合、メモ化しておくと高速化できることがある。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define H 3
#define W 3
#define RED -1
#define BLUE 1
#define NIL 0
using namespace std;

int mmap[H][W],painted[H][W]={0};

int judge(){
    int i,j,cntR,cntB;
    cntR=cntB=0;
    rep(i,H){
        if(painted[i][i]==RED)
            cntR++;
        if(painted[i][i]==BLUE)
            cntB++;
    }
    if(cntR==3)
        return RED;
    if(cntB==3)
        return BLUE;
    cntR=cntB=0;
    rep(i,H){
        if(painted[i][W-i-1]==RED)
            cntR++;
        if(painted[i][W-i-1]==BLUE)
            cntB++;
    }
    if(cntR==3)
        return RED;
    if(cntB==3)
        return BLUE;
    rep(i,H){
        cntR=cntB=0;
        rep(j,W){
            if(painted[i][j]==RED)
                cntR++;
            if(painted[i][j]==BLUE)
                cntB++;
        }
        if(cntR==3)
            return RED;
        if(cntB==3)
            return BLUE;
    }
    rep(j,W){
        cntR=cntB=0;
        rep(i,H){
            if(painted[i][j]==RED)
                cntR++;
            if(painted[i][j]==BLUE)
                cntB++;
        }
        if(cntR==3)
            return RED;
        if(cntB==3)
            return BLUE;
    }
    return NIL;
}

bool dfs(long long t,long long a,int turn){
    int i,j;
    //printf("turn:%d t:%lld a:%lld\n",turn,t,a);rep(i,H){rep(j,W)printf("%c ",painted[i][j]==RED?'T':painted[i][j]==BLUE?'A':'.');puts("");};
    if((i=judge())==NIL){
        if(turn==H*W)
            return t>a;
    }else
        return i==RED;
    if(turn%2==0){
        rep(i,H){
            rep(j,W){
                if(painted[i][j]==NIL){
                    painted[i][j]=RED;
                    if(dfs(t+mmap[i][j],a,turn+1)){
                        painted[i][j]=NIL;
                        return true;
                    }
                    painted[i][j]=NIL;
                }
            }
        }
        return false;
    }else{
        rep(i,H){
            rep(j,W){
                if(painted[i][j]==NIL){
                    painted[i][j]=BLUE;
                    if(dfs(t,a+mmap[i][j],turn+1)==false){
                        painted[i][j]=NIL;
                        return false;
                    }
                    painted[i][j]=NIL;
                }
            }
        }
        return true;
    }
}

int main(){
    int i,j;
    rep(i,H){
        rep(j,W){
            scanf("%d",&mmap[i][j]);
        }
    }
    printf("%s\n",dfs(0,0,0)?"Takahashi":"Aoki");
    return 0;
}
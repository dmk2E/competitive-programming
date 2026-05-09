/*アルゴリズムと工夫点(Strange Lunchbox/CPU: 48 ms Memory: 4660 KB  Length: 858 B)
dp[i][j][k]:1~i+1番目までの弁当をいくつか選んだ時の,(x,y)=(j,k)となる時の最小の弁当の数
というような動的計画法で解ける．なお，dp[i][x][y]=(x,y)=(x以上,y以上)となるようにして，計算量を削減する．
最悪計算量はO(NXY)≒2.7*10^7となり，高速．
※初見4完!嬉しい!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n,x,y,a,b;

void show(vector<vector<int> >& last){
    int i,j;
    rep(i,x+1){
        rep(j,y+1)
            printf("%d ",last[i][j]);
        puts("");
    }
}

int main(){
    int i,j,k;
    scanf("%d%d%d",&n,&x,&y);
    vector<vector<int> > last(x+1,vector<int>(y+1,n+1)),now;
    last[0][0]=0;
    rep(i,n){
        //show(last);puts("");
        now=last;
        scanf("%d%d",&a,&b);
        rep(j,x+1){
            rep(k,y+1){
                if(last[j][k]+1<now[min(x,j+a)][min(y,k+b)])
                    now[min(x,j+a)][min(y,k+b)]=last[j][k]+1;
            }
        }
        swap(last,now);
    }
    //show(last);
    printf("%d\n",last[x][y]==n+1?-1:last[x][y]);
    return 0;
}
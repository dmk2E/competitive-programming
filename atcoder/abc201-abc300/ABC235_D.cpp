/*アルゴリズムと工夫点(Multiply and Rotate/CPU: 5 ms Memory: 7328 KB  Length: 1251 B)
N<10^6 より，N>=10^6となる値に関しては考える必要がない．
また2つ目の操作を行う場合，桁数自体は変化しないから，その操作によってできた数値が10^6 を超えないか否かで，その先を考える必要があるか判定できる．
よって，1~10^(6)-1 までの数値を頂点とみなし，各操作による値の遷移を辺で表現した有向重み無しグラフにおけるBFSで解を求める．
最悪計算量はO(N)<10^7 となり高速．
※初見4完
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N (int)(1e6)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,n;

int main(){
    int i,j;
    scanf("%d%d",&a,&n);
    const int NIL=-1;
    vector<int> dist(MAX_N,NIL);
    auto bfs=[&](int s)->int{
        int i,j;
        queue<int> que;
        dist[s]=0;
        que.push(s);
        while(que.size()){
            s=que.front();que.pop();
            if(a<(MAX_N+s-1)/s&&dist[a*s]==NIL){
                //printf("->%d\n",a*s);
                dist[a*s]=dist[s]+1;
                if(a*s==n)break;
                que.push(a*s);
            }
            if(s>=10&&s%10>0){
                j=10;
                while(s>=j){
                    i++;
                    j*=10;
                }
                j/=10;
                i=(s%10)*j+s/10;
                if(i<MAX_N&&dist[i]==NIL){
                    //printf("->>%d\n",i);
                    dist[i]=dist[s]+1;
                    if(i==n)break;
                    que.push(i);
                }
            }
        }
        return dist[n];
    };
    printf("%d\n",bfs(1));
    return 0;
}
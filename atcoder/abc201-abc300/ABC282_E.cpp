/*アルゴリズムと工夫点(Choose Two and Eat One/CPU: 80 ms Memory: 5336 KB  Length: 1574 B)
x^nをmで割った余りの計算は繰り返し自乗法を用いれば十分高速に求めることができる．
ボールの個数nに対して，処理はn-1回行う．ボールを頂点とみなし，一度でも取り出した2つ頂点間に得点の重みをもつ辺を追加する．この処理を行うと，できた形状は木になる．
重みは最大にしたいから，最小全域木のアルゴリズムの最大verを適用すれば解ける．
※sort(.rbegin(),.rend())で降順にソートできる
※状態をグラフとみなし，処理を「辺で繋ぐ」ことで表現するという考え方は斬新...
*/
#include<iostream>
#include<vector>
#include<queue>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int n,m;
vector<int> a;

int power(int x,int a){
    if(a==0)return 1;
    int res=power(((ll)x*x)%m,a/2);
    if(a%2==1)
        res=(int)(((ll)res*x)%m);
    return res;
}

int main(){
    int i,j;
    scanf("%d%d",&n,&m);
    //while(n--){scanf("%d%d",&i,&j);printf("%d\n",power(i,j));}
    a=vector<int>(n);
    vector<vector<int> > adj(n,vector<int>(n,0));
    rep(i,n)
        scanf("%d",&a[i]);
    rep(i,n)rep(j,i){
        //printf("(%d,%d):%d\n",i,j,(power(a[i],a[j])+power(a[j],a[i]))%m);
        adj[i][j]=adj[j][i]=(power(a[i],a[j])+power(a[j],a[i]))%m;
    }
    const int NIL=-1;
    rep(i,n)adj[i][i]=NIL;
    auto prim=[&](int x)->ll{
        int i,cnt=0;
        p now;
        ll sum=0;
        vector<bool> color(n,false);
        priority_queue<p> PQ;
        PQ.push(p(0,x));
        while(PQ.size()){
            do{
                now=PQ.top();PQ.pop();
            }while(PQ.size()&&color[now.second]);
            if(color[now.second])return NIL;
            color[now.second]=true;
            cnt++;
            sum+=now.first;
            if(cnt==n)break;
            rep(i,n){
                if(adj[now.second][i]!=NIL&&color[i]==false)
                    PQ.push(p(adj[now.second][i],i));
            }
        }
        return sum;
    };
    printf("%lld\n",prim(0));
    return 0;
}
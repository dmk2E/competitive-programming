/*アルゴリズムと工夫点(Santa Claus 2/CPU: 289 ms Memory: 45520 KB  Length: 3270 B)
平衡二分探索木の高速消去を活かして，各x,yの値毎に座標管理を行ってシミュレーションすればよい．
・ランダムアクセスイテレータ:任意の値だけアドレスの加算，減算をO(1)で行えるが，一度コンテナ内の要素を消すと，アドレスの値が書き換わってしまう．(vector等)
・双方向イテレータ:隣接するアドレスへの変更しか(±1の変更)はO(1)で行えないが，一度コンテナ内の要素を消しても，アドレス自体は変化しない．
※set.erase(int),set.erase(iterator)と様々なものを引数にでき，eraseの返り値は，削除された要素の次の要素のイテレータとなることは知っておくこと．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct CordinatedCompression{
    bool initiated;
    vector<ll> xs;

    CordinatedCompression(){
        xs=vector<ll>(0);
        initiated=false;
    }

    void init(){
        initiated=true;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }

    void add(ll x){
        initiated=false;
        xs.push_back(x);
    }

    int operator()(ll k){
        if(!initiated)init();
        return lower_bound(xs.begin(),xs.end(),k)-xs.begin();
    }

    ll operator[](int id){
        if(!initiated)init();
        return xs[id];
    }

    int size(){
        return xs.size();
    }
}CC;

int n,m;
ll sx,sy;
char d;

int main(){
    int i,j,ans=0;
    scanf("%d%d%lld%lld",&n,&m,&sx,&sy);
    vector<int> x(n),y(n);
    CC xs,ys;
    rep(i,n){
        scanf("%d%d",&x[i],&y[i]);
        xs.add(x[i]);
        ys.add(y[i]);
    }
    vector<set<ll> > x2y(xs.size()),y2x(ys.size());
    rep(i,n){
        x2y[xs(x[i])].insert(y[i]);
        y2x[ys(y[i])].insert(x[i]);
    }
    set<ll>::iterator it,itS;
    while(m--){
        getchar();
        scanf("%c %d",&d,&j);
        switch(d){
            case 'U':
                i=xs(sx);
                if(i<xs.size()&&xs[i]==sx){
                    itS=x2y[i].lower_bound(sy);
                    it=itS;
                    while(it!=x2y[i].end()&&(*it)<=sy+j){
                        y2x[ys(*it)].erase(sx);
                        it=x2y[i].erase(it);
                        ans++;
                    }
                }
                sy+=j;
                break;
            case 'D':
                i=xs(sx);
                if(i<xs.size()&&xs[i]==sx){
                    itS=x2y[i].lower_bound(sy-j);
                    it=itS;
                    while(it!=x2y[i].end()&&(*it)<=sy){
                        y2x[ys(*it)].erase(sx);
                        it=x2y[i].erase(it);
                        ans++;
                    }
                }
                sy-=j;
                break;
            case 'L':
                i=ys(sy);
                if(i<ys.size()&&ys[i]==sy){
                    itS=y2x[i].lower_bound(sx-j);
                    it=itS;
                    while(it!=y2x[i].end()&&(*it)<=sx){
                        x2y[xs(*it)].erase(sy);
                        it=y2x[i].erase(it);
                        ans++;
                    }
                }
                sx-=j;
                break;
            default:
                i=ys(sy);
                if(i<ys.size()&&ys[i]==sy){
                    itS=y2x[i].lower_bound(sx);
                    it=itS;
                    while(it!=y2x[i].end()&&(*it)<=sx+j){
                        x2y[xs(*it)].erase(sy);
                        it=y2x[i].erase(it);
                        ans++;
                    }
                }
                sx+=j;
                break;
        }
    }
    printf("%lld %lld %d\n",sx,sy,ans);
    return 0;
}
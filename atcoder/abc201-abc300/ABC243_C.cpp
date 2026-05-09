/*アルゴリズムと工夫点(Collision 2/CPU: 99 ms Memory: 16680 KB  Length: 1766 B)
y座標を固定して，各人の座標をx座標の昇順にみていき，衝突するか否かを判定する．
座標の値が大きいから，y座標は座標圧縮し，各y座標毎にx座標を保持する配列を作成すればよい．
最悪計算量は O(N*log2(N))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef struct CordinatedCompression{
    bool initiated;
    vector<int> xs;

    CordinatedCompression(){
        xs=vector<int>(0);
        initiated=false;
    }

    void init(){
        initiated=true;
        sort(xs.begin(),xs.end());
        xs.erase(unique(xs.begin(),xs.end()),xs.end());
    }

    void add(int x){
        initiated=false;
        xs.push_back(x);
    }

    int operator()(int k){
        if(!initiated)init();
        return lower_bound(xs.begin(),xs.end(),k)-xs.begin();
    }

    int operator[](int id){
        if(!initiated)init();
        return xs[id];
    }

    int size(){
        return xs.size();
    }
}CC;

typedef pair<int,bool> P;//(x,<-ならfalse)

int n;
string s;

int main(){
    int i;
    scanf("%d",&n);
    vector<int> x(n),y(n);
    CC ys;
    rep(i,n){
        scanf("%d%d",&x[i],&y[i]);
        ys.add(y[i]);
    }
    cin>>s;
    vector<vector<P> > y2P(ys.size());
    rep(i,n)y2P[ys(y[i])].push_back(P(x[i],s[i]=='R'));
    rep(i,ys.size())sort(y2P[i].begin(),y2P[i].end());
    //rep(i,y2P.size()){int j;rep(j,y2P[i].size())printf("%d ",y2P[i][j].first);puts("");}
    auto judge=[&](int y)->bool{
        int i;
        bool now=false;
        rep(i,y2P[y].size()){
            if(now){if(y2P[y][i].second==false)return true;}
            else if(y2P[y][i].second)now=true;
        }
        return false;
    };
    rep(i,ys.size()){
        if(judge(i)){
            puts("Yes");
            return 0;
        }
    }
    puts("No");
    return 0;
}
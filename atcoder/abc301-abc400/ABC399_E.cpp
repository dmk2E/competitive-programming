/*アルゴリズムと工夫点(Replace/CPU: 16 ms Memory: 4116 KB  Length: 1231 B)
各アルファベットがどのように変化してほしいか->functional graph のようになる->グラフで表現
->連結成分毎に考えてみる->閉路が無ければ，葉から変化させていけばよい．
->閉路がある場合，一旦別の頂点に退避させる
*/
#include<iostream>
#include<set>
#include<atcoder/scc>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
using namespace atcoder;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n;
string s,t;
const int MAX_ALFA=26;

int main(){
    int i,j,ans;
    scanf("%d",&n);
    cin>>s>>t;
    if(s==t){
        puts("0");
        return 0;
    }
    {
        set<char> st(t.begin(),t.end());
        if(st.size()==MAX_ALFA){
            puts("-1");
            return 0;
        }
    }
    set<P> edges;
    rep(i,n)edges.insert(P(s[i]-'a',t[i]-'a'));
    vector<int> indeg(MAX_ALFA),outdeg(MAX_ALFA);
    for(auto e:edges){
        outdeg[e.first]++;
        indeg[e.second]++;
    }
    rep(i,MAX_ALFA)if(outdeg[i]>1){
        puts("-1");
        return 0;
    }

    ans=edges.size();
    scc_graph g(MAX_ALFA);
    for(auto [a,b]:edges){
        if(a==b)ans--;
        else g.add_edge(a,b);
    }
    for(auto grp:g.scc()){
        if(grp.size()>=2){
            bool br=false;
            for(int v:grp)if(indeg[v]>1)br=true;
            if(!br)ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
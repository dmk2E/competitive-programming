/*アルゴリズムと工夫点(Notebook/CPU: 231 ms Memory: 26400 KB  Length: 1147 B)
永続データ構造DSとは，ある時刻でのDSの状態に高速にアクセスできるデータ構造を示す．
永続データ構造は，各状態を頂点とした木構造で表現される．
可変長配列(添え字:状態番号)で各状態を，新しい状態が生成された順に管理して置く．この時(この状態に至る前の状態番号,状態)は保持して置くこと．
連想配列を用いることで，ページ数->状態番号 のようにアクセスできるようにしておく．
最悪計算量は O(Q*log2(Q))<10^7 となり高速．
※unordered_mapはハッシュ関数を用いているため，各要素が文字列で，その長さが長いと遅くなるが，それ以外では基本的にmapより早くなる．
*/
#include<iostream>
#include<vector>
#include<unordered_map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Node{
    int prev,val;
    Node(int pprev=0,int vval=0):prev(pprev),val(vval){}
};

int q;
string query;

int main(){
    int i,j,v;
    scanf("%d",&q);
    vector<Node> ds(1,Node(0,-1));
    unordered_map<int,int> mp;
    vector<int> ans(0);
    v=0;
    while(q--){
        cin>>query;
        if(query[0]=='D'){
            v=ds[v].prev;
        }else{
            scanf("%d",&i);
            switch(query[0]){
                case 'A':
                    ds.push_back(Node(v,i));
                    v=ds.size()-1;
                    break;
                case 'S':
                    mp[i]=v;
                    break;
                default :
                    if(mp.find(i)==mp.end())v=0;
                    else v=mp[i];
                    break;
            }
        }
        ans.push_back(ds[v].val);
    }
    rep(i,ans.size()-1)printf("%d ",ans[i]);
    printf("%d\n",ans[i]);
    return 0;
}
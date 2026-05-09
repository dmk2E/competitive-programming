/*アルゴリズムと工夫点(LCM on Whiteboard/CPU: 167 ms Memory: 25792 KB  Length: 870 B)
LCMの性質を考えると，素因数分解されたN個の値について，いずれか一つでも累乗の数が唯一最大の素因数を持つ場合，その値を1にするとLCMの数が変わる．
そして変化したLCMの値は，他の値を1にして作成することはできない．逆に最大のものを持たない場合，値は変化しない．
従って，唯一最大の素因数を持つか否かを数え上げればよい．
*/
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n,m;

int main(){
    int i,j,k,ans=0;
    scanf("%d",&n);
    vector<bool> is_only_max(n,false);
    map<int,vector<P> > dict;
    rep(i,n){
        scanf("%d",&m);
        while(m--){
            scanf("%d%d",&j,&k);
            dict[j].push_back(P(k,i));
        }
    }
    for(auto d:dict){
        sort(d.second.begin(),d.second.end());
        if(d.second.size()<=1||d.second[d.second.size()-1].first>d.second[d.second.size()-2].first)
            if(is_only_max[d.second.back().second]==false)is_only_max[d.second.back().second]=true,ans++;
    }
    printf("%d\n",ans+(ans<n));
    return 0;
}
/*アルゴリズムと工夫点(MEX/CPU: 53 ms Memory: 4640 KB  Length: 1437 B)
(Ai,Aj,Ak)の値の組み合わせの全探索+動的計画法で解く．
(Ai,Aj,Ak)の値の組み合わせvは，(0,0,0),(0,0,1),...の27通りしかないため，固定して考える．
下記のDPを考える．
dp[i][j]::=(S[0,i]の範囲で，末端が"MEX"[j]である組合せの数)
するとvの組み合わせ全てについて，mex(v)*dp[N-1][2] を加算すればよい．
最悪計算量は，O(N*27)<10^7 となり高速．
※公式解説では，Sj='E' を満たすjを全探索して求めていた．
*/
#include<iostream>
#include<vector>
#include<set>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string s;
const string target="MEX";

/// @brief 与えられた長さ3の集合のMEXを求める
/// @param s 長さ3の集合
/// @return sのMEX
int mex(vector<int>& s){
    set<int> v;
    v.insert(0);v.insert(1);v.insert(2);v.insert(3);
    for(int val:s)if(v.find(val)!=v.end())v.erase(val);
    return *v.begin();
}

/// @brief "MEX"において，何番目の文字か求める
/// @param c アルファベット大文字
/// @return "MEX"[i]==c を満たすi
int char2Id(char c){
    int i;
    rep(i,target.size())if(target[i]==c)break;
    return i;
}

int main(){
    int i,j,k;
    ll ans=0;
    const int LEN=3;
    scanf("%d",&n);
    vector<int> a(n),id_to_val;
    rep(i,n)scanf("%d",&a[i]);
    cin>>s;
    auto calcCases=[&]()->ll{
        int i;
        vector<ll> dp(target.size()+1,0);
        dp[0]=1;
        rep(i,s.size()){
            int id=char2Id(s[i]);
            if(a[i]!=id_to_val[id])continue;
            dp[id+1]+=dp[id];
        }
        return dp[target.size()];
    };
    rep(i,LEN){
        id_to_val.push_back(i);
        rep(j,LEN){
            id_to_val.push_back(j);
            rep(k,LEN){
                id_to_val.push_back(k);
                int tmp=mex(id_to_val);
                if(tmp>0)ans+=tmp*calcCases();
                id_to_val.pop_back();
            }
            id_to_val.pop_back();
        }
        id_to_val.pop_back();
    }
    printf("%lld\n",ans);
    return 0;
}
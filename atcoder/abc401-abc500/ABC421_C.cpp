/*アルゴリズムと工夫点(Alternated/CPU: 36 ms Memory: 10084 KB  Length: 1251 B)
高速化したシミュレーションで解く．
同じ文字が隣り合う個所が無い状態とは，"ABABA..."または"BABAB..."の形になることである．
つまり，どちらかの状態するために必要な最小操作回数を求めればよい．この状態を理想状態とする．
最小回数で理想状態にするためには，|S|の先頭文字から順に走査し，理想状態のi文字目に最も近い，まだ使用していない|S|上の文字を使用する，貪欲法を利用すればよい．
このシミュレーションを高速化するため，以下の情報を持って行う．
・S[i]='A' となっているiの集合 と S[i]='B' となっているiの集合（各集合はiの昇順に保持）
・上の各集合で，現在どこまで使用済みか
・S上の各文字について，使用済みかのフラグ
最悪計算量は，O(N) < 10^7 となり高速．
※バーチャル参加
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_ALFA 2
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string s;
const string target="AB";

int encoder(char c){
    if(c=='A')return 0;
    return 1;
}

int main(){
    int i,j;
    scanf("%d",&n);
    vector<vector<int> > alfa_to_ids(MAX_ALFA,vector<int>());
    cin>>s;
    rep(i,s.length())alfa_to_ids[encoder(s[i])].push_back(i);
    auto calc=[&](int now_t)->ll{
        int i=0,now_s=0;
        ll ans=0;
        vector<int> nxt(MAX_ALFA,0);
        vector<bool> is_used(2*n,false);
        while(i<2*n){
            while(now_s<2*n&&is_used[now_s])now_s++;
            if(s[now_s]==target[now_t]){
                is_used[now_s]=true;
                now_s++;
            }else{
                while(nxt[now_t]<n&&is_used[alfa_to_ids[now_t][nxt[now_t]]])nxt[now_t]++;
                ans+=abs(alfa_to_ids[now_t][nxt[now_t]]-i);
                is_used[alfa_to_ids[now_t][nxt[now_t]]]=true;
            }
            now_t=(now_t+1)%MAX_ALFA;
            i++;
        }
        return ans;
    };
    printf("%lld\n",min(calc(0),calc(1)));
    return 0;
}
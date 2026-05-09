/*アルゴリズムと工夫点(Cover query/CPU: 101 ms Memory: 13480 KB  Length: 1087 B)
順序付き集合（set）を利用して解く．
黒マスが塗られた区間を管理して，白マスの数を数え上げるのだが，与えられた区間と共通範囲を持つ区間の探索は二分探索を用いる．
1回のクエリで，クエリは高々1個しか増えないため，訪問する区間の個数はQ個となる．
従って最悪計算量は，O(Q * log2(Q)) < 10^7 となり高速．
*/
#include<iostream>
#include<set>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

/// @brief 黒マスの範囲を[l, r)で持つ
struct Data{
    int l,r;

    Data(int l = 0, int r = 0):l(l), r(r){}

    bool operator<(const Data& k)const{
        return l == k.l ? r < k.r : l < k.l;
    }
};

int n,q;

int main(){
    int i,j,ans;
    scanf("%d%d",&n,&q);
    set<Data> v;
    ans = n;
    while(q--){
        int l,r;
        scanf("%d%d",&l,&r);r++;
        set<Data>::iterator it = v.lower_bound(Data(l, n + 1));
        int nxt_l = l, nxt_r = r;
        if(it != v.begin() && max(prev(it) -> l, l) < min(prev(it) -> r, r))it--;
        while(it != v.end() && it -> l <= r){
            ans += it -> r - it -> l;
            nxt_l = min(nxt_l, it -> l);
            nxt_r = max(nxt_r, it -> r);
            v.erase(it++);
        }
        ans -= nxt_r - nxt_l;
        v.insert(Data(nxt_l, nxt_r));
        printf("%d\n", ans);
    }
    return 0;
}
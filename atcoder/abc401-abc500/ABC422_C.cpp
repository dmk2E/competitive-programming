/*アルゴリズムと工夫点(AtCoder AAC Contest/CPU: 70 ms Memory: 3856 KB  Length: 913 B)
貪欲法 + 高速シミュレーション（周期性なども含む） で解く．
操作について，以下の貪欲法が成立する．
・Bの数が残っている時は，(A,B,C) で開催
・A,C のみが残っている時は，A > C ならば (A,A,C) A < C ならば (A,C,C) で開催
これを利用し，主に以下の3パターンに分けて，それぞれで高速化して考える．
<i> a>0 && b>0 && c>0
<ii> b<=0 && a>0 && c>0 && a != 0
<iii> a == c が成立した後
1テストケース当たり，O(1) で解けるため，最悪計算量は，O(T) < 10^6 となり十分高速．
※ <iii> においては，(A,A,C)->(A,C,C)を1セットにして，操作を繰り返せばよく，周期性が存在する．
※ バーチャル参加
*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t;

ll solve(int a,int b,int c){
    ll ans = 0;
    int tmp = min(a,min(b,c));
    a -= tmp;b -= tmp;c -= tmp;
    ans += tmp;
    if(a <= 0 || c <= 0)return ans;
    // ここからはa と c のみ
    ll diff = abs(a-c);
    if(a>c)swap(a,c);
    if(a < diff || c <= 2*diff)return ans + min(a,c/2);
    ans += diff;
    a -= diff;c -= 2*diff;
    // ここからはa と c の個数は同数
    ans += 2*(a/3);
    a -= 3*(a/3);
    c -= 3*(c/3);
    if(a>c)swap(a,c);
    ans += (a >= 1 && c >= 2);
    return ans;
}

int main(){
    int i,j;
    scanf("%d",&t);
    while(t--){
        int n_a,n_b,n_c;
        scanf("%d%d%d",&n_a,&n_b,&n_c);
        printf("%lld\n",solve(n_a,n_b,n_c));
    }
    return 0;
}
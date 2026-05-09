/*アルゴリズムと工夫点(Make Geometric Sequence/CPU: 37 ms Memory: 4888 KB  Length: 2605 B)
整数列Aを値の絶対値の昇順に整列し，公比である分数を適切に保持して判定．
ただし，Aが全て同じ要素である時は例外処理を行う．
<i>整数列Aの要素が全て同じである時
負の数を数え上げて，適切に処理．

<ii>整数列Aの要素が全て同じではない時
整数列Aを適切に整列し，等比数列になり得る
=>aを絶対値の昇順に整列した時，公比r=a1/a0 とする等比数列になるはず
公比は分数として分母と分子それぞれを保持する形で持っておき，適切に判定．

1テストケース当たりの最悪計算量は，O(N*log2(max(ai)))<10^7 となり高速．
※例外処理に気づかず1WA マルチテストケースなのに，例外処理で「return 0」を用いているのに気づかず2WA...悔しい
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef class Fraction{
public:
    ll top,btm;

private:
    /// @brief ユークリッドの互除法で最大公約数を求める
    /// @param a 1つ目の整数
    /// @param b 2つ目の整数
    /// @return 2つの整数a,bの最大公約数
    ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}

public:
    /// @brief 分数クラス
    /// @param ttop 分母
    /// @param bbtm 分子
    Fraction(ll ttop=0,ll bbtm=1):top(ttop),btm(bbtm){
        if(btm==0){top=1;return ;}
        if(btm<0)btm=-btm,top=-top;
        ll g=gcd(abs(top),abs(btm));
        if(g!=0)top/=g;btm/=g;
    }

    Fraction operator+(const Fraction& k)const{
        return Fraction(top*k.btm+btm*k.top,btm*k.btm);
    }

    Fraction operator-(const Fraction& k)const{
        return Fraction(top*k.btm-btm*k.top,btm*k.btm);
    }

    Fraction operator*(const ll& k)const{
        return Fraction(top*k,btm);
    }

    Fraction operator*(const Fraction& k)const{
        return Fraction(top*k.top,btm*k.btm);
    }

    Fraction operator/(const Fraction& k)const{
        return Fraction(top*k.btm,btm*k.top);
    }

    bool operator<(const Fraction& k)const{
        return top*k.btm<k.top*btm;
    }

    bool operator==(const Fraction& k)const{
        return top==k.top&&btm==k.btm;
    }

    bool operator!=(const Fraction& k)const{
        return !((*this)==k);
    }

    /// @brief 分数表示
    void show(){
        printf("%lld / %lld\n",top,btm);
    }
}Frac;

int t,n;

int main(){
    int i,j;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        vector<ll> a(n);
        rep(i,n)scanf("%lld",&a[i]);
        rep(i,n-1)if(abs(a[i+1])!=abs(a[i]))break;
        if(i==n-1){
            // Aの要素が全て同じ場合
            int cnt_minus=0;
            rep(i,n)cnt_minus+=(a[i]<0);
            if((n%2==0&&cnt_minus==n/2)
             ||(n%2==1&&(cnt_minus==(n+1)/2||cnt_minus==n/2))
             ||(cnt_minus==n||cnt_minus==0))puts("Yes");
             else puts("No");
        }else{
            sort(a.begin(),a.end(),[](ll& l,ll& r)->bool{
                return abs(l)<abs(r);
            });
            Fraction r(a[1],a[0]);
            rep(i,n-1)if(Fraction(a[i+1],1)!=r*a[i])break;
            if(i==n-1)puts("Yes");
            else puts("No");
        }
    }
    return 0;
}
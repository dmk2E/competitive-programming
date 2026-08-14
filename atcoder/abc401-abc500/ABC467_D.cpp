/*アルゴリズムと工夫点(Concentric Circles/CPU: 33 ms Memory: 3764 KB  Length: 2078 B)
2直線の交点判定を正確に行って解く．
問題を整理すると，下記の2式を満たす (x, y) が存在すればよい（2円の中心座標(x, y)）．
 ・(P_x - C_x) ^ 2 + (P_y - C_y) ^ 2 = (Q_x - C_x) ^ 2 + (Q_y - C_y) ^ 2
 ・(R_x - C_x) ^ 2 + (R_y - C_y) ^ 2 = (S_x - C_x) ^ 2 + (S_y - C_y) ^ 2
上記の2式は直線を表すため，この2直線が交点を持つか否かを正確に判定すれば，解が求まる．
最悪計算量は多めに見積もっても，
O(T * (log2(P_x ^ 2 + P_y ^ 2 + ...) + log2(R_x ^ 2 + ...))) < 10 ^ 7 となり，高速．
※ コンストラクタ内では，メンバ変数と引数の識別子が同じである場合，引数が優先されてしまうことに注意
※ 直線`a * x + b * y + c = 0`の標準形の求め方
   1. a < 0 または (a == 0 かつ b < 0) => a, b, c の正負を反転
   2. a, b, c 全てを，gcd(a, b, c) で割る
*/
#include<iostream>
#include<cassert>
#define rep(i, n) for(i = 0;i < (int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

// a * x + b * y + c
struct Line{
    ll a, b, c;

    Line(ll a = 0, ll b = 0, ll c = 0):a(a), b(b), c(c){
        if(a < 0 || (a == 0 && b < 0)){
            this -> a = -this -> a;
            this -> b = -this -> b;
            this -> c = -this -> c;
        }

        ll tmp = gcd(
            /* num1 = */ abs(this -> a), 
            /* num2 = */ gcd(
                /* num1 = */ abs(this -> b), 
                /* num2 = */ abs(this -> c)
        ));

        this -> a /= tmp;
        this -> b /= tmp;
        this -> c /= tmp;
    }

    bool operator==(const Line& k)const{
        return this -> a == k.a && this -> b == k.b && this -> c == k.c;
    }

    ll gcd(ll num1, ll num2){
        return num2 == 0 ? num1 : gcd(/* num1 = */ num2, /* num2 = */ num1 % num2);
    }

    bool isCommon(const Line& other)const{
        if((*this) == other)return true;
        if(this -> b == 0 || other.b == 0)return !(this -> b == 0 && other.b == 0);
        return this -> a * other.b != other.a * this -> b;
    }
};

int t;

int main(){
    scanf("%d", &t);
    while(t--){
        ll p_x, p_y, q_x, q_y, r_x, r_y, s_x, s_y;
        scanf("%lld%lld%lld%lld%lld%lld%lld%lld", &p_x, &p_y, 
                                                  &q_x, &q_y, 
                                                  &r_x, &r_y, 
                                                  &s_x, &s_y
        );

        Line l1(
            /* a = */ 2 * q_x - 2 * p_x, 
            /* b = */ 2 * q_y - 2 * p_y, 
            /* c = */ p_x * p_x + p_y * p_y - q_x * q_x - q_y * q_y
        );
        Line l2(
            /* a = */ 2 * s_x - 2 * r_x, 
            /* b = */ 2 * s_y - 2 * r_y, 
            /* c = */ r_x * r_x + r_y * r_y - s_x * s_x - s_y * s_y
        );
        printf("%s\n", l1.isCommon(/* other = */ l2) ? "Yes" : "No");
    }
    return 0;
}
/*アルゴリズムと工夫点(Colinear/CPU: 120 ms Memory: 7376 KB  Length: 1041 B)
乱択アルゴリズムで解く．
与えられた点の過半数を通る直線が存在すると仮定すると，その点を選ぶ確率はざっくり 1/2となる．
従って，ランダムで選んだ2点を通る直線が過半数を通る確率は 1/4 となる．
よってC回ランダムで直線を選ぶとき，過半数を通る直線を得られない確率は，(3/4)^(C) 
これが十分小さくなるCだけ，乱択を繰り返すと良い．
最悪計算量は，O(N*C) < 10^8 となり間に合う．
※ 確率保証が重要
*/
#include<iostream>
#include<vector>
#include<random>
#include<time.h>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_RANDOM 50
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,cnt = MAX_RANDOM;
    scanf("%d",&n);
    vector<int> x(n),y(n);
    rep(i,n)scanf("%d%d",&x[i],&y[i]);
    mt19937 mt_for_id(time(NULL));
    auto judge = [&](const ll& a,const ll& b,const ll& c)->bool{
        int i,cnt = 0;
        rep(i,n)if(a*x[i]+b*y[i]+c == 0)cnt++;
        return cnt >= (n+1)/2;
    };
    while(cnt--){
        i = mt_for_id()%n;
        do{
            j = mt_for_id()%n;
        }while(i == j);
        ll a,b,c;
        a = y[j]-y[i];
        b = x[j]-x[i];
        c = y[i]*b-x[i]*a;
        b = -b;
        ll g = gcd(a,gcd(b,c));
        a /= g;b /= g;c /= g;
        if(judge(a,b,c)){
            printf("Yes\n%lld %lld %lld\n",a,b,c);
            return 0;
        }
    }
    puts("No");
    return 0;
}
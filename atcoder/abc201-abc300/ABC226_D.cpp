/*アルゴリズムと工夫点(Teleportation/CPU: 124 ms Memory: 15496 KB  Length: 785 B)
Nの制約が小さいから，N個の内の2つの街の選び方の全列挙を行うことはできる．
だから，各街から他の町への移動に必要な(a,b)の組を列挙し，(a',b')(a=g*a',b=g*b' (g:最大公約数))の形で保持して置き，その種類数を答えればよい．
従って最悪計算量はO(N^2*log2(max(xi,yi)))≒10^6 となり，高速．
※初見ACできた!
*/
#include<iostream>
#include<vector>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> p;

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int n;
set<p> v;

int main(){
    int i,j,k,x,y;
    scanf("%d",&n);
    vector<p> ipt(n);
    rep(i,n)scanf("%d%d",&ipt[i].first,&ipt[i].second);
    rep(i,n){
        rep(j,n){
            if(i==j)continue;
            x=ipt[j].first-ipt[i].first;
            y=ipt[j].second-ipt[i].second;
            k=abs(x)>abs(y)?gcd(abs(x),abs(y)):gcd(abs(y),abs(x));
            x/=k;y/=k;
            if(v.find(p(x,y))==v.end())v.insert(p(x,y));
        }
    }
    printf("%d\n",(int)v.size());
    return 0;
}
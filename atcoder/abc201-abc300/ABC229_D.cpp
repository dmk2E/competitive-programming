/*アルゴリズムと工夫点(Longest X/CPU: 16 ms Memory: 5592 KB  Length: 563 B)
「.」の数の累積和sumOを前処理で求めて置く．
S[l]を始点とした連続成分の個数の最大値がいくつあるかを全探索することを考える．
これはsumO[l,r)の個数が，k個以下になる最大のrを求めればよく，二分探索で高速に求められる．
最悪計算量はO(|S|*log2(|S|))≒10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;
int k;

int main(){
    int i,j,ans=0;
    vector<ll> sumO;
    cin>>s>>k;
    sumO.push_back(0);
    rep(i,s.length()){
        sumO.push_back((s[i]=='.')+sumO[sumO.size()-1]);
    }
    rep(i,s.length()){
        if((j=(upper_bound(sumO.begin(),sumO.end(),k+sumO[i])-sumO.begin())-1-i)>ans)
            ans=j;
    }
    printf("%d\n",ans);
    return 0;
}
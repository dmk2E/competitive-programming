/*アルゴリズムと工夫点(Palindromic Number/CPU: 1 ms Memory: 3844 KB  Length: 740 B)
「0」を含めると実装しずらくなるから，「0」の場合だけ別で処理させる．つまり，「0」ではなく「1」が1番目として，処理する．
回文がもつ性質として，前半部分が決まると，後半部分が自動的に決まるため，前半部分に着目して特徴を見るとよい．
今回は，回文数の大小関係は，その前半部分の整数値の大小関係と変わらないため，「求める値の桁数」と「その桁において何番目に大きいか」が分かれば，解を求めることができる．
最悪計算量はO(log10(N))程度で，十分高速．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef long long ull;

ll n;
vector<ll> cnt;
string ans="";

int main(){
    int i,j,keta;
    ull sum=0,tmp=1;
    //cnt.push_back(10);cnt.push_back(9);
    scanf("%lld",&n);
    if(n==1){
        printf("0\n");
        return 0;
    }
    n--;
    for(keta=1;;keta++){
        tmp=9;
        rep(j,(keta-1)/2)tmp*=10;
        if(n>tmp)n-=tmp;
        else break;
    }
    //printf("%lld %d\n",n,keta);
    n+=tmp/9-1;
    ans+=to_string(n);
    string r=ans;
    if(keta%2==1)r.pop_back();
    reverse(r.begin(),r.end());
    cout<<ans+r<<endl;
    return 0;
}
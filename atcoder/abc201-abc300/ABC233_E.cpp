/*アルゴリズムと工夫点(Σ[k=0..10^100]floor(X／10^k)/CPU: 32 ms Memory: 7628 KB  Length: 754 B)
桁数が大きすぎるので，整数を文字列と捉えて入力を貰い，整数の可変長配列xxで表す．
求めたい値は，「X+X/10+X/100...」であり，それは「Xの先頭からi桁目の値を，i桁目から末尾の桁に加算する」という処理をxx上でN回繰り返せばよい．
ただ愚直に加算してしまうと，O(|xx|^2)かかってしまうため，imos法を用いる．
※初見5完!嬉しい!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string x;

int main(){
    int i,j;
    cin>>x;
    vector<int> xx(x.size(),0);
    //rep(i,x.size()){j=x.size()-1-i;while(j>=0){xx[x.size()-1-i-j]+=x[j]-'0';j--;}}
    i=0;
    xx[0]+=x[i]-'0';
    for(i++;i<x.size();i++){
        xx[0]+=x[i]-'0';
        xx[x.size()-i]-=x[i]-'0';
    }
    rep(i,x.size()-1)xx[i+1]+=xx[i];
    rep(i,xx.size()-1){
        xx[i+1]+=xx[i]/10;
        xx[i]%=10;
    }
    while(xx[i]/10>0){
        xx.push_back(xx[i]/10);
        xx[i]%=10;
        i++;
    }
    rep(i,xx.size())printf("%d",xx[xx.size()-1-i]);puts("");
    return 0;
}
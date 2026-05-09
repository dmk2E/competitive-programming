/*アルゴリズムと工夫点(Doubles/CPU: 509 ms Memory: 6684 KB  Length: 1213 B)
さいころ2個の選び方を全通り試し，連想配列を使いながら，同じ目の出方を全探索する．
最悪計算量は O(N^(2)+log2(N)*Σk)<10^7 となり高速．
※ループ内部の和はオーバーフローする可能性があるかをきちんと確かめること．
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    ll a,b;

    Data(ll aa=0,ll bb=0):a(aa),b(bb){};

    bool operator<(const Data& k)const{
        return a*k.b<k.a*b;
    }
};

int n;

int main(){
    int i,j,k;
    ll tmp;
    long double ans=0;
    scanf("%d",&n);
    vector<vector<int> > a(n);
    vector<Data> temp;
    rep(i,n){
        scanf("%d",&j);
        a[i]=vector<int>(j);
        rep(j,a[i].size())scanf("%d",&a[i][j]);
    }
    rep(i,n){
        map<int,int> dic;
        rep(j,a[i].size())dic[a[i][j]]++;
        rep(j,i){
            tmp=0;
            rep(k,a[j].size()){
                if(dic.find(a[j][k])!=dic.end())tmp+=dic[a[j][k]];
            }
            //printf("%.15Lf\n",(long double)tmp/((long double)a[i].size()*(long double)a[j].size()));
            temp.push_back(Data(tmp,((ll)a[i].size())*a[j].size()));
        }
    }
    sort(temp.begin(),temp.end());
    printf("%.15Lf\n",(long double)temp.back().a/(long double)temp.back().b);
    return 0;
}
/*アルゴリズムと工夫点(Happy New Year!/CPU: 1 ms Memory: 3848 KB  Length: 727 B)
2:1
20,22:2
200,202,220,222:4
2000,:8
x桁ある数は，前から0-indexで [2^(x-1)-1,2^(x)-1) 番目だから，これで桁数を決定できる．
先頭の桁から2or0を決めていけばよい．
最悪計算量は，O(log2(K)) <10^2 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll k;

int main(){
    int i,j;
    ll left=1,right=2;
    scanf("%lld",&k);
    k--;
    j=1;
    vector<ll> powTwo(1,1);
    rep(i,60)powTwo.push_back(powTwo.back()*2);
    while(!(left-1<=k&&k<right-1)){
        left*=2;
        right*=2;
        j++;
    }
    k-=(left-1);
    string ans(j,'0');
    ans[0]='2';
    j=1;
    while(k>0){//ans.length()-1-j
        if(k>=powTwo[(int)ans.length()-1-j]){
            k-=powTwo[(int)ans.length()-1-j];
            ans[j]='2';
        }
        j++;
    }
    cout<<ans<<'\n';
    return 0;
}
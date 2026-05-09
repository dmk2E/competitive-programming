/*アルゴリズムと工夫点(There are two types of characters（★3）/CPU: 65 ms Memory: 11448 KB  Length: 1015 B)
ある区間[l,r)における，oとxの個数の数え上げを高速に行うため，それぞれで累積和sumO,sumXを取っておく．
次に，左端lを固定した時，「oとxの個数それぞれが1個以上になる」という条件Pの満たしやすさは，rの増加に対して増加するため，単調性が存在する．
従って，二分探索が可能となるから，最悪計算量はO(N*log2(N))≒10^7 となり，十分高速．
ただ，ある左端lを固定した時，条件Pを満たす最小のrをrMinとすると，lの増加に対し，rMinも単調増加するため，尺取り法が使え，その場合の最悪計算量はO(N)となり，より高速．
※ランレングス圧縮して，余事象から求めることもできる．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    ll ans=0;
    scanf("%d",&n);
    vector<int> sumO,sumX;
    sumO.push_back(0);
    sumX.push_back(0);
    getchar();
    rep(i,n){
        if(getchar()=='o'){
            sumO.push_back(1);
            sumX.push_back(0);
        }else{
            sumO.push_back(0);
            sumX.push_back(1);
        }
        sumO[sumO.size()-1]+=sumO[sumO.size()-2];
        sumX[sumX.size()-1]+=sumX[sumX.size()-2];
    }
    auto search=[&](int l)->int{
        int left=l,right=n+1,mid;
        while(left<right){
            mid=(left+right)/2;
            if(sumO[mid]-sumO[l]==0||sumX[mid]-sumX[l]==0)
                left=mid+1;
            else
                right=mid;
        }
        return n+1-left;
    };
    rep(i,n)ans+=search(i);
    printf("%lld\n",ans);
    return 0;
}
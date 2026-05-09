/*アルゴリズムと工夫点(Select Mul/CPU: 8 ms Memory: 3892 KB  Length: 1136 B)
与えられたNに含まれる0の数zeroとすると，どのような2つの数に分けたとしても，その積の結果の末尾には0がzero個並ぶ．
そこで，Nから0を除いてできる数をN'とし，N'の順列をまず考える．その中でN-1通りの分け方を考える．この時，10^nとその時の順列のN'の値を前計算で求めておけば，2つに分けた片方の数が分かればもう片方はO(1)で求められる．
よって最悪計算量はO(N*N!)<10^8 となり高速．
*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n,zero;
const int ten[]={1,10,100,1000,10000,(int)(1e5),(int)(1e6),(int)(1e7),(int)(1e8),(int)(1e9)};//(int)(1e7)を入れ忘れて1WA．悔しい
string nonZero;

int main(){
    int i,j;
    ll nn,now,mmax=0;
    scanf("%d",&n);
    j=n;zero=0;
    while(j>0){
        if(j%10>0)
            nonZero+=(char)((j%10)+'0');
        else
            zero++;
        j/=10;
    }
    //printf("zero:%d %s\n",zero,nonZero.c_str());
    sort(nonZero.begin(),nonZero.end());
    do{
        nn=0;
        rep(i,nonZero.length()){
            nn*=10;
            nn+=nonZero[i]-(int)'0';
        }
        now=0;
        rep(i,nonZero.length()-1){
            now*=10;
            now+=nonZero[i]-(int)'0';
            if(mmax<(ll)now*(nn-now*ten[nonZero.length()-1-i])){
                mmax=(ll)now*(nn-now*ten[nonZero.length()-1-i]);
            }
        }
    }while(next_permutation(nonZero.begin(),nonZero.end()));
    printf("%lld\n",mmax*ten[zero]);
    return 0;
}
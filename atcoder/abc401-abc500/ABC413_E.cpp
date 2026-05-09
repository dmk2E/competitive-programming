/*アルゴリズムと工夫点(Reverse 2^i/CPU: 43 ms Memory: 4372 KB  Length: 683 B)
Pをセグ木のように2べきの範囲に分けた二分木で考え，ボトムアップに求めていく．
逆順にreverseする作業は，二分木の左右の子のswapを繰り返すことと等しいことに着目する．
最悪計算量は，O(N*2^(N))<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t,n;

int main(){
    int i,j;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        int nn=1<<n;
        vector<int> p(nn);
        rep(i,nn)scanf("%d",&p[i]);
        for(int width=1;width<nn;width<<=1){
            for(int l=0;l<nn;l+=width*2){
                if(p[l]>p[l+width]){
                    rep(i,width)swap(p[l+i],p[l+i+width]);
                }
            }
        }
        rep(i,nn-1)printf("%d ",p[i]);printf("%d\n",p[i]);
    }
    return 0;
}
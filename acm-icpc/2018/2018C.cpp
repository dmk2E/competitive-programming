/*アルゴリズムと工夫点(超高層ビル「みなとハルカス」/CPU: 3400 ms  Memory: 3492 KB  Length: 721 B)
問題の条件より、以下の二つの単調性が見られる。
・一番下の階層を固定した時、一番上の階層が大きいほど、かかる賃貸の値は大きくなる。
・予算bとちょうど一致する、連続した多くのフロアを借りる時、一番下の階層が小さければ小さいほど、フロア数は大きくなる。
したがって、「フロア数fを固定した時、一番下の階層がが大きいほど、かかる賃貸の値は大きくなる」という単調性が成立する。ここで連続するfの最大値だが、1階から10^5階まで連続したフロアを借りる際、約10^10程度の予算が必要にな
るが、b<10^9より、0<f<10^5 の探索範囲で十分であることがわかる。
したがって、fを最大値から線型的に固定していき、fを固定した時に賃貸にかかる値が予算bと一致するか二分探索で判定し、初めてbと一致した(left,f)の組が求める解となる。
最悪計算量は、O(MAX_F*log2(b))≒10^6 となり、十分高速。
※京都産業大学の解説ではO(√b) で解けるやり方が存在する。
*/
#include<bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_F 100000
using namespace std;

int b;

long long sum(int s,int e){
    return (long long)e*(e+1)/2-(long long)s*(s-1)/2;
}

int main(){
    int f,left,right,mid;
    while(1){
        scanf("%d",&b);
        if(b==0)
            break;
        for(f=MAX_F;f>=1;f--){
            left=1;right=b;
            while(left<right){
                mid=(left+right)/2;
                if(sum(mid,mid+f-1)<(long long)b)
                    left=mid+1;
                else
                    right=mid;
            }
            if(sum(left,left+f-1)==(long long)b)
                break;
        }
        printf("%d %d\n",left,f);
    }
    return 0;
}
/*アルゴリズムと工夫点(Max/Min/CPU: 54 ms Memory: 7804 KB  Length: 586 B)
Aiを昇順にソートした状態で考えても値は変わらない．そこで，Aiを固定した時，[Aj/Ai](j>i)の値を考える．
[Aj/Ai]の値は，Aj∈[j*Ai,(j+1)*Ai)であれば，jとなることから，各Aiの出現回数を数えて，累積和sumをとっておく．Aiを固定して，sumを用いて[Aj/Ai]の総和を数え上げる．
区間[j*Ai,(j+1)*Ai)の数は全部で，max(Ai)/Ai つまり全体では，Σ(1<=i<=N) max(Ai)/Ai <= Σ(1<=i<=N) max(Ai)/i =max(Ai)log2(N) となる．各区間の数はsumを用いてO(1)で求まるから，
最悪計算量はO(M*log2(N))≒10^7 となり，高速．
※Ai==Aj の時，その数Cとすると，本来はC(C-1)/2 だけ数え上げればよいのだが，上記の解法だと，C^2回数え上げてしまう．したがって，1*(C^2-C(C-1)/2)=C*(C+1)/2 だけ数から引けばよい．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_A (int)(1e6)
using namespace std;

int n,sum[MAX_A+1]={0};

int main(){
    int i,j,d;
    long long ans=0;
    scanf("%d",&n);
    rep(i,n){
        scanf("%d",&j);
        sum[j]++;
    }
    rep(i,MAX_A+1)sum[i+1]+=sum[i];
    for(i=1;i<=MAX_A;i++){
        d=sum[i]-sum[i-1];
        for(j=1;i*j<=MAX_A;j++){
            ans+=(long long)j*d*(sum[((j+1)*i-1>=MAX_A?MAX_A:(j+1)*i-1)]-sum[j*i-1]);
        }
        ans-=(long long)d*(d+1)/2;
    }
    printf("%lld\n",ans);
    return 0;
}
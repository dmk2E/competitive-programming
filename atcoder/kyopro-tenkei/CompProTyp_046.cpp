/*アルゴリズムと工夫点(I Love 46/CPU: 33 ms Memory: 3936 KB  Length: 764 B)
a+b+cがkの倍数となることは，a%k+b%k+c%kがkの倍数となることに等しい．したがって，ある配列yについて，kで割った時の余りがjになる数をy[j]として保持して置き，余りの組み合わせについて全探索すればよい．
最悪計算量はO(k^3)<10^6 となり，十分高速．
※キーワード:同じ意味のものをまとめて考える．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_MOD 46
using namespace std;

int n,a[MAX_MOD]={0},b[MAX_MOD]={0},c[MAX_MOD]={0};

int main(){
    int i,j,k;
    long long ans=0;
    scanf("%d",&n);
    rep(i,n){
        scanf("%d",&j);
        a[j%MAX_MOD]++;
    }
    rep(i,n){
        scanf("%d",&j);
        b[j%MAX_MOD]++;
    }
    rep(i,n){
        scanf("%d",&j);
        c[j%MAX_MOD]++;
    }
    rep(i,MAX_MOD){
        if(a[i]==0)
            continue;
        rep(j,MAX_MOD){
            if(b[j]==0)
                continue;
            rep(k,MAX_MOD){
                ans+=(i+j+k)%MAX_MOD==0?(long long)a[i]*b[j]*c[k]:0;
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
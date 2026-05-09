/*アルゴリズムと工夫点(Divide by 2 or 3/CPU: 1 ms Memory: 3880 KB  Length: 749 B)
まず，最小の操作でa1=a2=...=an の状態に出来た時のa1の値は，k=gcd(a1,a2,...,an) となる．
aiをkの値にするために割らなけらばならない数はj=ai/kとなり，jを2と3で割り切れるだけ割る．
その結果がj==1とならない場合，どのように操作を行っても目標を達成できないと判定できる．
最悪計算量はO(N*log(max(Ai)))<10^5 となり，十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

int main(){
    int i,j,gcm,ans=0;
    scanf("%d",&n);
    vector<int> a(n);
    rep(i,n)scanf("%d",&a[i]);
    gcm=a[0];
    rep(i,n-1)gcm=gcd(gcm,a[i+1]);
    //printf("(G,C,M)=%d\n",gcm);
    rep(i,n){
        j=a[i]/gcm;
        while(j>1&&(j%2==0)){
            j/=2;
            ans++;
        }
        while(j>1&&(j%3==0)){
            j/=3;
            ans++;
        }
        if(j>1){
            puts("-1");
            return 0;
        }
    }
    printf("%d\n",ans);
    return 0;
}
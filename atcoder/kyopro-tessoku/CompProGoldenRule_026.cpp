/*アルゴリズムと工夫点(Prime Check/CPU: 4 ms Memory: 3940 KB  Length: 715 B)
エラトステネスの篩を用いて高速化して求める．
最悪計算量はO(MAX_X*log2(log2(MAX_X))+Q)<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_X 300000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int q,x;

vector<bool> init(int n){
    int i,j;
    vector<bool> isPrime(n+1,true);
    isPrime[0]=isPrime[1]=false;
    for(i=2;i<=n;i++){
        if(isPrime[i]){
            j=i*2;
            while(j<=n){
                isPrime[j]=false;
                j+=i;
            }
        }
    }
    return isPrime;
}

int main(){
    int i,j;
    vector<bool> isPrime=init(MAX_X);
    scanf("%d",&q);
    while(q--){
        scanf("%d",&x);
        printf("%s\n",isPrime[x]?"Yes":"No");
    }
    return 0;
}
/*アルゴリズムと工夫点(K Factors/CPU: 242 ms Memory: 52712 KB  Length: 736 B)
計算量がO(n*log2(log2(n)))であるエラトステネスの篩と同じような処理を行うことで、素数列挙&素数に対する処理を高速に行える。
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 10000000
using namespace std;

bool isPrime[MAX_N+1];
int n,k,pF[MAX_N+1]={0};

void init(){
    int i,j;
    rep(i,MAX_N+1)
        isPrime[i]=true;
    isPrime[0]=isPrime[1]=false;
    for(i=2;i<=MAX_N;i++){
        if(isPrime[i]){
            pF[i]=1;
            j=2*i;
            for(;j<=MAX_N;j+=i){
                isPrime[j]=false;
                pF[j]++;
            }
        }
    }
}

int main(){
    int i,cnt=0;
    init();
    scanf("%d%d",&n,&k);
    for(i=2;i<=n;i++){
        //printf("%d:%d\n",i,pF[i]);
        if(pF[i]>=k)
            cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
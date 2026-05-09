/*アルゴリズムと工夫点(Prime Sum Game/CPU: 1 ms Memory: 3904 KB  Length: 856 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_B 100
#define MAX_D 100
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b,c,d;

vector<bool> erato(int MAX){
    int i,j;
    vector<bool> isPrime(MAX+1,true);
    isPrime[0]=isPrime[1]=false;
    for(i=2;i<=MAX;i++){
        if(isPrime[i]){
            j=2*i;
            while(j<=MAX){
                isPrime[j]=false;
                j+=i;
            }
        }
    }
    return isPrime;
}

int main(){
    int i,j;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    vector<bool> isPrime=erato(MAX_B+MAX_D);
    for(i=a;i<=b;i++){
        for(j=c;j<=d;j++)if(isPrime[i+j])break;
        if(j==d+1){
            puts("Takahashi");
            return 0;
        }
    }
    puts("Aoki");
    return 0;
}
/*アルゴリズムと工夫点(KEYENCE building/CPU: 2 ms Memory: 3896 KB  Length: 544 B)
前処理で「与えられたSの値は条件を満たすか」を求めておき，その後に各クエリに答えればよい．
最悪計算量はO(N+S^2)≒10^6 となり，十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_S 1000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    vector<bool> isCorrect(MAX_S+1,false);
    rep(i,MAX_S)rep(j,MAX_S){
        if(4*(i+1)*(j+1)+3*(i+j+2)<=MAX_S)
            isCorrect[4*(i+1)*(j+1)+3*(i+j+2)]=true;
    }
    scanf("%d",&n);
    j=0;
    while(n--){
        scanf("%d",&i);
        j+=isCorrect[i]?0:1;
    }
    printf("%d\n",j);
    return 0;
}
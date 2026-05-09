/*アルゴリズムと工夫点(Many Operations/CPU: 68 ms Memory: 3892 KB  Length: 890 B)
ビット演算は整数の各ビット毎に独立である．これを即座に思い浮かべれるようになろう．
各ビットのとり得る値は「0」か「1」の2通りしか存在しないため，全ての桁について，その桁の値が0, 1だった場合の，操作を終えた後の値を保持すればよい．
最悪計算量は O(N*log2(MAX_N))<10^7 となり高速．
*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX 30
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,c,a;

int main(){
    int i,j,zero=0,one=(1<<MAX)-1,tmp;
    scanf("%d%d",&n,&c);
    while(n--){
        scanf("%d%d",&i,&a);
        j=tmp=0;
        switch(i){
            case 1:
                zero&=a;
                one&=a;
                break;
            case 2:
                zero|=a;
                one|=a;
                break;
            default :
                zero^=a;
                one^=a;
                break;
        }
        // printf("zero:%d one:%d\n",zero,one);
        while(j<MAX){
            tmp+=((c>>j)&1)?(((one>>j)&1)<<j):(((zero>>j)&1)<<j);
            j++;
        }
        c=tmp;
        printf("%d\n",c);
    }
    return 0;
}
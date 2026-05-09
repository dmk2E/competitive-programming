/*アルゴリズムと工夫点(Not Acceptable/CPU: 1 ms Memory: 3900 KB  Length: 289 B)
分に変換して比較するのが楽．
*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int a,b,c,d;

int main(){
    scanf("%d%d%d%d",&a,&b,&c,&d);
    printf("%s\n",c*60+d<=a*60+b?"Yes":"No");
    return 0;
}
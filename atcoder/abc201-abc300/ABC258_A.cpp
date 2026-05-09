/*アルゴリズムと工夫点(When?/CPU: 1 ms Memory: 3912 KB  Length: 329 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int k;

int main(){
    int h,m;
    scanf("%d",&k);
    h=21+(k/60);
    m=k%60;
    cout<<to_string(h)+":"+(m>=10?"":"0")+to_string(m)<<endl;
    return 0;
}
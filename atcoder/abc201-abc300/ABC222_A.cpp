/*アルゴリズムと工夫点(Four Digits/CPU: 1 ms Memory: 3696 KB  Length: 282 B)
printf("%04d",n)で済むらしい．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string n;

int main(){
    int i;
    cin>>n;
    rep(i,4-(int)n.length())
        putchar('0');
    cout<<n<<endl;
    return 0;
}
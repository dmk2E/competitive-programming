/*アルゴリズムと工夫点(QQ solver/CPU: 1 ms Memory: 3808 KB  Length: 238 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    cin>>s;
    printf("%d\n",(s[0]-'0')*(s[2]-'0'));
    return 0;
}
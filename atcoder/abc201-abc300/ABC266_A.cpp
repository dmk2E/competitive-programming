/*アルゴリズムと工夫点(Middle Letter/CPU: 1 ms Memory: 3796 KB  Length: 232 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    cin>>s;
    printf("%c\n",s[s.size()/2]);
    return 0;
}
/*アルゴリズムと工夫点(Rightmost/CPU: 1 ms Memory: 3720 KB  Length: 291 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    int i;
    cin>>s;
    for(i=s.length()-1;i>=0;i--)if(s[i]=='a')break;
    printf("%d\n",i<0?i:i+1);
    return 0;
}
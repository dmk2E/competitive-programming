/*アルゴリズムと工夫点(camel Case/CPU: 1 ms Memory: 3824 KB  Length: 246 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

string s;

int main(){
    int i;
    cin>>s;
    rep(i,s.length())
        if(isupper(s[i]))
            break;
    printf("%d\n",i+1);
    return 0;
}
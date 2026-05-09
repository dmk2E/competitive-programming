/*アルゴリズムと工夫点(LOOKUP/CPU: 2 ms Memory: 3636 KB  Length: 391 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s,t;

int main(){
    int i,j;
    cin>>s>>t;
    if(s.length()>=t.length()){
        rep(i,s.length())if(s.substr(i,t.length())==t)break;
        printf("%s\n",i==s.length()?"No":"Yes");
    }else
        puts("No");
    return 0;
}
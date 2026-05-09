/*アルゴリズムと工夫点(Sandwich Number/CPU: 2 ms Memory: 3696 KB  Length: 719 B)

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
    rep(i,s.length())if((int)'0'<=(int)s[i]&&(int)s[i]<=(int)'9')break;
    if(i!=1){
        puts("No");
        return 0;
    }
    rep(i,s.length())if((int)'0'<=(int)s[s.length()-1-i]&&(int)s[s.length()-1-i]<=(int)'9')break;
    if(i!=1){
        puts("No");
        return 0;
    }
    for(i=1;i<s.length()-1;i++)
        if((int)'0'>(int)s[s.length()-1-i]||(int)s[s.length()-1-i]>(int)'9')break;
    if(s.length()-1==i&&s[1]!='0'){
        puts("Yes");
    }else{
        puts("No");
    }
    return 0;
}
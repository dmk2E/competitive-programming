/*アルゴリズムと工夫点(Swap Odd and Even/CPU: 1 ms Memory: 3576 KB  Length: 231 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

string s;

int main(){
    int i;
    cin>>s;
    for(i=0;i<s.length();i+=2)
        swap(s[i],s[i+1]);
    cout<<s<<endl;
    return 0;
}
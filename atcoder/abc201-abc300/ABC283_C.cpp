/*アルゴリズムと工夫点(Cash Register/CPU: 3 ms Memory: 3936 KB  Length: 364 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s;

int main(){
    int i,j=0;
    cin>>s;
    rep(i,s.length()){
        if(i+1<s.length()&&s[i]=='0'&&s[i]==s[i+1]){
            i++;
        }
        j++;
    }
    printf("%d\n",j);
    return 0;
}
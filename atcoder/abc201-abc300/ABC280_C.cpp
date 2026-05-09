/*アルゴリズムと工夫点(/CPU:  ms Memory:  KB  Length:  B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string s,t;

int main(){
    int i;
    cin>>s>>t;
    rep(i,s.length()){
        if(s[i]!=t[i]){
            printf("%d\n",i+1);
            return 0;
        }
    }
    printf("%d\n",i+1);
    return 0;
}
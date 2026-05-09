/*アルゴリズムと工夫点(Binary Representation 1/CPU: 1 ms Memory: 3916 KB  Length: 468 B)

*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i;
    const int BASE=2;
    string ans="";
    scanf("%d",&n);
    while(n>0){
        ans+=(char)((int)'0'+n%BASE);
        n/=BASE;
    }
    i=10-(int)ans.size();
    while(i--)ans+='0';
    reverse(ans.begin(),ans.end());
    cout<<ans<<endl;
    return 0;
}
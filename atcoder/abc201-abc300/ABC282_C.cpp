/*アルゴリズムと工夫点(String Delimiter/CPU: 4 ms Memory: 3904 KB  Length: 398 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;
string s;

int main(){
    int i,cnt=0;
    scanf("%d",&n);
    cin>>s;
    rep(i,n){
        if(s[i]=='"')
            cnt+=cnt>0?-1:1;
        else if(s[i]==','&&cnt==0)
            s[i]='.';
    }
    cout<<s<<endl;
    return 0;
}
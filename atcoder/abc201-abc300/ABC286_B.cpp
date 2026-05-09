/*アルゴリズムと工夫点(Cat/CPU: 1 ms Memory: 3680 KB  Length: 404 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

string s,ans="";

int main(){
    int i,j;
    scanf("%d",&i);
    cin>>s;
    rep(i,s.length()){
        if(i+1<s.length()&&s[i]=='n'&&s[i+1]=='a'){
            ans+="nya";
            i++;
        }else
            ans.push_back(s[i]);
    }
    cout<<ans<<endl;
    return 0;
}
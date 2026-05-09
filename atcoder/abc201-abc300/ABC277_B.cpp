/*アルゴリズムと工夫点(Playing Cards Validation/CPU: 1 ms Memory: 3828 KB  Length: 651 B)

*/
#include<iostream>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

bool judge(const string& s){
    int i;
    if(s[0]!='H'&&s[0]!='D'&&s[0]!='C'&&s[0]!='S')return false;
    return (('2'<=s[1]&&s[1]<='9')||s[1]=='A'||s[1]=='T'||s[1]=='J'||s[1]=='Q'||s[1]=='K');
}

int main(){
    int i,j;
    string s;
    set<string> v;
    scanf("%d",&n);
    rep(i,n){
        cin>>s;
        if(!judge(s)||v.find(s)!=v.end()){
            puts("No");
            return 0;
        }
        v.insert(s);
    }
    puts("Yes");
    return 0;
}
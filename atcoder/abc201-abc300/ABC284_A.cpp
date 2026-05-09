/*アルゴリズムと工夫点(Sequence of Strings/CPU: 1 ms Memory: 3752 KB  Length: 331 B)

*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n;
vector<string> ipt;

int main(){
    int i;
    scanf("%d",&n);
    ipt=vector<string>(n);
    rep(i,n)
        cin>>ipt[i];
    rep(i,n)
        cout<<ipt[n-1-i]<<endl;
    return 0;
}
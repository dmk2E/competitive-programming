/*アルゴリズムと工夫点(Longest Uncommon Prefix/CPU: 6 ms Memory: 3916 KB  Length: 348 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n;
string s;

int main(){
    int i,j;
    scanf("%d",&n);
    cin>>s;
    for(i=1;i<n;i++){
        for(j=1;j-1+i<n;j++){
            if(s[j-1]==s[j-1+i])break;
        }
        printf("%d\n",j-1);
    }
    return 0;
}
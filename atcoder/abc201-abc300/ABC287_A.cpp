/*アルゴリズムと工夫点(/CPU:  ms Memory:  KB  Length:  B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int n;
string s;

int main(){
    int i,j=0;
    scanf("%d",&n);
    rep(i,n){
        cin>>s;
        if(s=="For")
            j++;
    }
    printf("%s\n",2*j>n?"Yes":"No");
    return 0;
}
/*アルゴリズムと工夫点(Rotation/CPU: 80 ms Memory: 4480 KB  Length: 537 B)

*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;
string s;

int main(){
    int i,j,head=0;
    scanf("%d%d",&n,&q);
    cin>>s;
    while(q--){
        scanf("%d",&i);
        if(i==1){
            scanf("%d",&j);
            head=(head-j+(int)(s.length()))%s.length();
        }else{
            scanf("%d",&j);
            printf("%c\n",s[(head+j-1)%s.length()]);
        }
    }
    return 0;
}
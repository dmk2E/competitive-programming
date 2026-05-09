/*アルゴリズムと工夫点(Qual B/CPU: 1 ms Memory: 3904 KB  Length: 349 B)

*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

int n,k;
string s;

int main(){
    int i;
    scanf("%d%d",&n,&k);
    cin>>s;
    rep(i,s.length()){
        if(s[i]=='o'&&k>0){
            putchar('o');
            k--;
        }else
            putchar('x');
    }
    puts("");
    return 0;
}
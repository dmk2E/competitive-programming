/*アルゴリズムと工夫点(Commencement/CPU: 1 ms Memory: 3520 KB  Length: 602 B)
複雑でやることが多いだけ。
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_ALFA 26
using namespace std;

int alfa[MAX_ALFA]={0};
string s;

int main(){
    int i,max=-1,j,k;
    cin>>s;
    rep(i,(int)s.length()){
        alfa[(int)s[i]-(int)'a']++;
        if(max<alfa[(int)s[i]-(int)'a'])
            max=alfa[(int)s[i]-(int)'a'];
    }
    for(i=1;i<=max;i++){
        k=0;
        rep(j,MAX_ALFA){
            if(i==alfa[j])
                k++;
        }
        if(k!=0&&k!=2){
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}
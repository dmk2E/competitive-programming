/*アルゴリズムと工夫点(Vertical Reading/CPU: 1 ms Memory: 3656 KB  Length: 659 B)
全探索するだけだが，問題理解が難しかった...w,cをどの順番で固定するかによって実装の楽さが異なるかも．
最悪計算量はO(|s^3|)<10^7 で高速．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;

string s,t;

int main(){
    int i,j,k;
    string now,rgt;
    cin>>s>>t;
    for(i=1;i<s.length();i++){
        for(j=1;j<=i;j++){
            rgt="";
            k=0;
            while(k<s.length()){
                now=s.substr(k,i);
                k+=i;
                if(now.length()>=j){
                    rgt+=now[j-1];
                }
            }
            if(rgt==t){
                puts("Yes");
                //printf("i:%d j:%d\n",i,j);
                return 0;
            }
        }
    }
    puts("No");
    return 0;
}
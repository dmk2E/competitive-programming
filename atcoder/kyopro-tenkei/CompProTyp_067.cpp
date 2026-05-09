/*アルゴリズムと工夫点(Base 8 to 9（★2）/CPU: 1 ms Memory: 3684 KB  Length: 640 B)
N=0のコーナーケースは，do-while文を用いた進数変換を用いれば，場合分けを用いずとも対応可能．
※キーワードはN進法展開を理解しよう
*/
#include<iostream>
#include<algorithm>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

string n;
int k;

int main(){
    int i,j;
    ull ten=0;
    cin>>n>>k;
    while(k--){
        rep(i,n.length()){
            ten*=8;
            ten+=(unsigned int)n[i]-(unsigned int)'0';
        }
        n="";
        do{
            n+=(char)((int)'0'+(ten%9));
            if(n.back()=='8')
                n[n.length()-1]='5';
            ten/=9;
        }while(ten>0);
        reverse(n.begin(),n.end());
    }
    cout<<n<<endl;
    return 0;
}
/*アルゴリズムと工夫点(Rotate and Palindrome/CPU: 100 ms Memory: 3912 KB  Length: 699 B)
Aの操作は最大N回行えるが，Aの操作を行える回数が固定すると，回文にするのに必要な最小の「Bの操作を行う回数」はO(N)で求まる．
従って，Aの操作を行う回数を固定して，Sを回文にするための最低金額を全探索する．
この時，Aの操作によって，Sが変化した文字列S'における各文字が，元のSで先頭から何番目の文字なのかを別で保持して置くことで，わざわざ新しいS'を作らず処理を行える．
最悪計算量はO(N^2)<10^8 となり，間に合う．
*/
#include<iostream>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 5000
using namespace std;
typedef long long ll;

int n,a,b,t2S[MAX_N];
string s,t;

int main(){
    int i,j;
    ll ans=(ll)(1e13),sum;
    scanf("%d%d%d",&n,&a,&b);
    cin>>t;
    rep(i,n){
        sum=(ll)a*i;
        s=t;
        rep(j,n)
            t2S[(j+n-i)%n]=j;
        rep(j,n){
            if(s[j]!=s[t2S[n-1-((j+n-i)%n)]]){
                sum+=b;
                s[j]=s[t2S[n-1-((j+n-i)%n)]];
            }
        }
        //printf("a:%d,b:%lld,sum:%lld\n",i,(sum-i)/b,sum);cout<<s<<endl;
        if(sum<ans)
            ans=sum;
    }
    printf("%lld\n",ans);
    return 0;
}
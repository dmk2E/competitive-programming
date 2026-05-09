/*アルゴリズムと工夫点(Keys/CPU: 36 ms Memory: 3940 KB  Length: 1272 B)
鍵が正しいかどうかは2^N通りしか存在しないから，このパターンを全探索する．
そのパターンが矛盾が無いかどうかは，与えられたM行のデータを元に判定できる．最悪計算量はO((2^N)*M*N)≒10^7<10^8 より，高速．
p.s.
問題では，組み合わせの数を聞いているのに，正しい鍵の本数を答えると勘違いしていたため，ACまで20分ほど時間が余分にかかってしまった．悔しすぎる泣
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_N 15
#define MAX_M 100
#define NIL -1
using namespace std;

int n,m,k,c,ans;
bool r[MAX_M];
vector<int> a[MAX_M];

int judge(int s){
    int i,j,crt;
    rep(i,m){
        crt=0;
        rep(j,a[i].size()){
            if(s&(1<<(n-1-a[i][j]))){
                crt++;
            }
        }
        //printf("%d %d\n",i,crt);
        if((crt>=k&&r[i]==false)||(crt<k&&r[i]==true))
            return NIL;
    }
    crt=0;
    //printf("%d\n",s);
    rep(i,n)
        if(s&(1<<i))
            crt++;
    return crt;
}

int main(){
    int i,j,min,cnt=0;
    char rr;
    bool flag=false;
    scanf("%d%d%d",&n,&m,&k);
    rep(i,m){
        scanf("%d",&c);
        while(c--){
            scanf("%d",&j);
            j--;
            a[i].push_back(j);
        }
        getchar();
        scanf("%c",&rr);
        r[i]=rr=='o';
    }
    min=n+1;
    //rep(i,m){rep(j,a[i].size())printf("%d ",a[i][j]);printf("%d\n",r[i]?1:0);}return 0;
    for(i=0;i<(1<<n);i++){
        //printf("i:%d\n",i);
        if((j=judge(i))!=NIL){
            cnt++;
        }
    }
    //printf("i:%d\n",i);
    printf("%d\n",cnt);
    return 0;
}
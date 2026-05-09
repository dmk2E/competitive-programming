/*アルゴリズムと工夫点(Connect 6/CPU: 43 ms Memory: 4076 KB  Length: 798 B)
連続した6マスを全列挙し，その6マスが条件を満たすことはあるかを調べればよい．
最悪計算量は O(6*4*N^(2))<10^8 となり高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define C 6
#define ADD 2
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j,k,ii,cnt;
    scanf("%d",&n);
    vector<vector<bool> > mmap(n,vector<bool>(n,false));
    rep(i,n){
        getchar();
        rep(j,n)mmap[i][j]=(getchar()=='#');
    }
    const int dy[]={0,1,1,1},dx[]={1,1,0,-1},MAX_D=4;
    rep(i,n)rep(j,n)rep(k,MAX_D){
        cnt=0;
        rep(ii,C){
            if(0>i+ii*dy[k]||i+ii*dy[k]>=n||0>j+ii*dx[k]||j+ii*dx[k]>=n)break;
            cnt+=mmap[i+ii*dy[k]][j+ii*dx[k]];
        }
        if(ii==C&&cnt>=C-ADD){
            puts("Yes");
            return 0;
        }
    }
    puts("No");
    return 0;
}
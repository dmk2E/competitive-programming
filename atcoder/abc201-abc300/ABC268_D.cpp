/*アルゴリズムと工夫点(Unique Username/CPU: 77 ms Memory: 14328 KB  Length: 1352 B)
順列全列挙を用いて，条件を満たす文字列を全探索する．
条件を満たす文字列の総数は多いので，全てを列挙する余裕はないが，列挙後その文字列が条件を満たさないと判定される回数は最大でもM回であり，一つでも条件を満たせばその時点で探索が終了できる．
そのため，最悪計算量は O(N*M*log2(M))≒10^7 (文字列の長さは定数とした) となる．
※文字列の長さを考えると，最悪計算量が怪しかったので，再帰による枝刈りを用いて高速化を行った．
*/
#include<iostream>
#include<vector>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MIN_S 3
#define MAX_S 16
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,m;

int main(){
    int i,j,sumS=0;
    string tmp;
    scanf("%d%d",&n,&m);
    vector<string> ipt(n);
    rep(i,n){
        cin>>ipt[i];
        sumS+=ipt[i].length();
    }
    set<string> t;
    rep(i,m){
        cin>>tmp;
        t.insert(tmp);
    }
    tmp="................";
    const int NIL=-1;
    auto rec=[&](auto& f,int now,int l,int cntUS,int state)->int{
        int i,j,k,ii;
        if(now==n-1){
            rep(i,n)if(((state>>i)&1)==false)break;
            rep(j,ipt[i].size())tmp[l++]=ipt[i][j];
            if(MIN_S<=l&&l<=MAX_S&&t.find(tmp.substr(0,l))==t.end())return l;
            return NIL;
        }
        rep(i,n)if(((state>>i)&1)==false){
            k=l;
            rep(j,ipt[i].length())tmp[k++]=ipt[i][j];
            for(j=1;j<=MAX_S;j++){
                if(sumS+j+cntUS>MAX_S)break;
                tmp[k++]='_';
                if((ii=f(f,now+1,k,cntUS+j,state|(1<<i)))!=NIL)return ii;
            }
        }
        return NIL;
    };
    if((j=rec(rec,0,0,0,0))!=NIL)
        cout<<tmp.substr(0,j)<<'\n';
    else
        puts("-1");
    return 0;
}
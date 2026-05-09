/*アルゴリズムと工夫点(LRUD Instructions/CPU: 460 ms Memory: 62304 KB  Length: 2164 B)
グリッドを，壁がある行，列のみに圧縮して扱う．
それぞれの行ではsetで，壁がある列番号を保持して置く．そうすることで，ある行での移動(L,R)の際，「今現在挟まれている壁の列座標」を取得することができ，それを元に移動後の座標を求めることができる．
列についても同様になる．
よって最悪計算量は O(N*log2(N)+Q*log2(N))<10^7 となり，高速．
※バーチャルコンテスト内で初見4完!
*/
#include<iostream>
#include<vector>
#include<set>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<int,int> P;

int n,q,l;
ll h,w,r,c;
char d;

int main(){
    int i,j;
    scanf("%lld%lld%lld%lld%d",&h,&w,&r,&c,&n);
    vector<P> ipt(n);
    rep(i,n)scanf("%d%d",&ipt[i].first,&ipt[i].second);
    map<int,set<int> > rs,cs;
    rep(i,n){
        rs[ipt[i].first].insert(ipt[i].second);
        cs[ipt[i].second].insert(ipt[i].first);
    }
    const int dy[]={0,-1,0,1},dx[]={-1,0,1,0};
    auto d2Id=[](char c)->int{
        switch(c){
            case 'L':
                return 0;
            case 'R':
                return 2;
            case 'U':
                return 1;
            default :
                break;
        }
        return 3;
    };
    scanf("%d",&q);
    set<int>::iterator it;
    int mmin=1,mmax=h;
    while(q--){
        getchar();
        scanf("%c %d",&d,&l);
        i=d2Id(d);
        if(i==0||i==2){
            if(rs.find(r)==rs.end()){
                c=max(1LL,min(c+dx[i]*l,w));
            }else{
                it=rs[r].lower_bound(c);
                if(it==rs[r].end())mmax=w;
                else mmax=(*it)-1;
                if(it==rs[r].begin())mmin=1;
                else{
                    it--;
                    mmin=(*it)+1;
                }
                c=max((ll)mmin,min(c+dx[i]*l,(ll)mmax));
            }
        }else{
            if(cs.find(c)==cs.end()){
                r=max(1LL,min(r+dy[i]*l,h));
            }else{
                it=cs[c].lower_bound(r);
                if(it==cs[c].end())mmax=h;
                else mmax=(*it)-1;
                if(it==cs[c].begin())mmin=1;
                else{
                    it--;
                    mmin=(*it)+1;
                }
                //printf("rgt:%lld\n",r+dy[i]*l);
                r=max((ll)mmin,min(r+dy[i]*l,(ll)mmax));
            }
        }
        //printf("%d:[%d,%d]\n",i,mmin,mmax);
        printf("%lld %lld\n",r,c);
    }
    return 0;
}
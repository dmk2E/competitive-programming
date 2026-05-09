/*アルゴリズムと工夫点(Tangency of Cuboids/CPU: 176 ms Memory: 45324 KB  Length: 1422 B)
座標空間にインプットして処理．
座標の大きさが小さいため，3次元グリッド空間に直方体をインプットし，各座標に直方体番号を振る．
各々グリッドにて，x,y,z方向それぞれで隣接している，異なる番号を持つ座標が無いか判定すればよい．
最悪計算量は，O(N+MAX_X*MAX_Y*MAX_Z)<10^7 となり高速．
※ 「被りの処理->setを使う」という考えに至れるようになりたい．
*/
#include<iostream>
#include<unordered_set>
#include<random>
#include<time.h>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_X 100
#define MAX_Y 100
#define MAX_Z 100
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,coord_to_id[MAX_X+1][MAX_Y+1][MAX_Z+1];

int main(){
    int i,j,k;
    const int NIL=-1;
    scanf("%d",&n);
    rep(i,MAX_X+1)rep(j,MAX_Y+1)rep(k,MAX_Z+1)coord_to_id[i][j][k]=NIL;
    rep(i,n){
        int lx,ly,lz,rx,ry,rz;
        scanf("%d%d%d%d%d%d",&lx,&ly,&lz,&rx,&ry,&rz);
        int ii,jj,kk;
        for(ii=lx;ii<rx;ii++)for(jj=ly;jj<ry;jj++)for(kk=lz;kk<rz;kk++)coord_to_id[ii][jj][kk]=i;
    }
    vector<unordered_set<int> > id_to_cnt(n);
    // evil-case対策
    mt19937 mt_for_encode(time(NULL));
    int value_for_encode=mt_for_encode();
    vector<int> id_to_encoded(n);
    rep(i,n)id_to_encoded[i]=value_for_encode^i;
    auto add=[&](int a,int b)->void{
        if(a==b||a==NIL||b==NIL)return ;
        id_to_cnt[a].insert(id_to_encoded[b]);
        id_to_cnt[b].insert(id_to_encoded[a]);
    };
    rep(i,MAX_X)rep(j,MAX_Y)rep(k,MAX_Z){
        add(coord_to_id[i][j][k],coord_to_id[i][j][k+1]);
        add(coord_to_id[i][j][k],coord_to_id[i][j+1][k]);
        add(coord_to_id[i][j][k],coord_to_id[i+1][j][k]);
    }
    rep(i,n)printf("%ld\n",id_to_cnt[i].size());
    return 0;
}
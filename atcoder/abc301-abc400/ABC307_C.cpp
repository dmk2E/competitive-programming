/*アルゴリズムと工夫点(Ideal Sheet/CPU: 4 ms Memory: 3932 KB  Length: 3260 B)
シートXの領域を基準に，2つのシートの貼り方を全探索する．
まず，シートA,Bについては，必ず含めなければならない範囲に切り取る（全ての黒い部分を含む中で，最小の面積となるように）．
その後，各シートのシートXの範囲内への収め方を全探索する．
この時，一度黒く塗ったところを再び透明に塗りつぶさないように注意．
最悪計算量は，O(H_A*W_A+H_B*W_B+(H_X*W_X)^3)<10^7 となり高速．
※水Diffも納得の重実装系の問題．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

struct Data{
    int min_y,min_x,max_y,max_x;

    Data(int mmin_y=0,int mmin_x=0,int mmax_y=0,int mmax_x=0):min_y(mmin_y)
                                                             ,min_x(mmin_x)
                                                             ,max_y(mmax_y)
                                                             ,max_x(mmax_x)
                                                             {};
};

int h_a,w_a,h_b,w_b,h_x,w_x;

/// @brief シートsrcをシートdstに貼り付ける
/// @param src 貼り付け元のシート
/// @param y srcの有効範囲の左上を合わせるdst上のy座標
/// @param x srcの有効範囲の左上を合わせるdst上のx座標
/// @param d srcのData型データ
/// @param dst 貼り付け先のシート
void paint(const vector<vector<bool> >& src,int y,int x,const Data& d,vector<vector<bool> >& dst){
    int i,j;
    rep(i,d.max_y-d.min_y+1)rep(j,d.max_x-d.min_x+1){
        dst[y+i][x+j]=(dst[y+i][x+j]||src[d.min_y+i][d.min_x+j]);
    }
}

/// @brief 2つのシートの内容が一致しているか判定
/// @param src 1つ目のシート
/// @param dst 2つ目のシート
/// @return 2つのシートの内容は一致しているか否か
bool judge(vector<vector<bool> >& src,vector<vector<bool> >& dst){
    int i,j;
    rep(i,src.size())rep(j,src[i].size())if(src[i][j]!=dst[i][j])return false;
    return true;
}

int main(){
    int i,j,ii,jj;
    scanf("%d%d",&h_a,&w_a);
    vector<vector<bool> > a(h_a,vector<bool>(w_a,false));
    Data d_a(h_a,w_a,-1,-1);
    rep(i,h_a){
        string str;
        cin>>str;
        rep(j,str.size()){
            a[i][j]=(str[j]=='#');
            if(a[i][j]){
                d_a.min_y=min(i,d_a.min_y);
                d_a.max_y=max(i,d_a.max_y);
                d_a.min_x=min(j,d_a.min_x);
                d_a.max_x=max(j,d_a.max_x);
            }
        }
    }
    scanf("%d%d",&h_b,&w_b);
    vector<vector<bool> > b(h_b,vector<bool>(w_b,false));
    Data d_b(h_b,w_b,-1,-1);
    rep(i,h_b){
        string str;
        cin>>str;
        rep(j,str.size()){
            b[i][j]=(str[j]=='#');
            if(b[i][j]){
                d_b.min_y=min(i,d_b.min_y);
                d_b.max_y=max(i,d_b.max_y);
                d_b.min_x=min(j,d_b.min_x);
                d_b.max_x=max(j,d_b.max_x);
            }
        }
    }
    scanf("%d%d",&h_x,&w_x);
    vector<vector<bool> > x(h_x,vector<bool>(w_x,false));
    rep(i,h_x){
        string str;
        cin>>str;
        rep(j,str.size())x[i][j]=(str[j]=='#');
    }
    for(i=0;i+d_a.max_y-d_a.min_y<h_x;i++)for(j=0;j+d_a.max_x-d_a.min_x<w_x;j++)
        for(ii=0;ii+d_b.max_y-d_b.min_y<h_x;ii++)for(jj=0;jj+d_b.max_x-d_b.min_x<w_x;jj++){
            vector<vector<bool> > c(h_x,vector<bool>(w_x,false));
            paint(a,i,j,d_a,c);
            paint(b,ii,jj,d_b,c);
            if(judge(c,x)){
                puts("Yes");
                return 0;
            }
        }
    puts("No");
    return 0;
}
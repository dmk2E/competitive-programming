/*アルゴリズムと工夫点(Monochromatic Subgrid（★4）/CPU: 34 ms Memory: 4088 KB  Length: 792 B)
hの値が小さいから，どの行を選択するかを固定すると，パターン数は2^n-1通り．
どの行を選択するかが決定されていれば，その行それぞれで全ての列の値を参照し，同じ数字で構成されているかを確認し，適宜最大値を更新すれば良い．
同じ数字の列か今までいくつかあるかは，別の一次元配列で保持して置く．
最悪計算量はO((2^h)*h*w)=256*8*10^4≒10^6 となり，十分高速．
符号無し整数と符号ありの整数が混在した式では，正しく処理が行われない可能性があることに注意．
※キーワードは「変な制約に着目する/状態数が少ない変量を全探索」
※初見AC嬉しい!
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;

int h,w;

int main(){
    int i,j,k,max=-1;
    scanf("%d%d",&h,&w);
    vector<vector<int> > p(h,vector<int>(w));
    rep(i,h)
        rep(j,w)
            scanf("%d",&p[i][j]);
    rep(i,1<<h){
        vector<int> cnt(h*w+1,0),row;
        rep(j,h)if(i&(1<<j))row.push_back(j);
        rep(j,w){
            rep(k,row.size()-1)
                if(p[row[k]][j]!=p[row[k+1]][j])break;
            if(k==row.size()-1){
                cnt[p[row[0]][j]]++;
                if(max<(int)row.size()*cnt[p[row[0]][j]])
                    max=(int)row.size()*cnt[p[row[0]][j]];
            }
        }
    }
    printf("%d\n",max);
    return 0;
}
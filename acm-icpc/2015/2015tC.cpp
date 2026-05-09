/*アルゴリズムと工夫点(ブロック落とし/CPU: 2 ms Memory: 3524 KB  Length: 5153 B)
H, Nが小さいから，落とすブロックの水平移動のパターンを全て試せばよい．
落とすブロックの形によっては，それが底面まで到達する可能性があることに注意．
最悪計算量は h=w=z=2とし， O(((2H+1) * (2W+1))^(N) * h * w * z * N * (H * h * w * z * N)) = O(((2H+1) * (2W+1))^(N) * h^2 * w^2 * z^2 * N^2 * H) < 10^6 となり十分高速．

※実装が非常に重く，またその方法が多様な問題という印象
※CPUの値は，AtCoderのコードテストページで測定
※問題URL：https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2701
*/
//#include<iostream>
//#include<cassert>
#include<bits/stdc++.h>
#define rep(i,n)for(i=0;i<(int)(n);i++)
#define H 2 //ブロックの塊の縦の長さ
#define W 2 //ブロックの塊の幅の長さ
#define Z 2 //ブロックの塊の高さ
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,n;

/// @brief 平行移動させる関数
/// @param block 対象ブロック
/// @param dy yの移動量
/// @param dx xの移動量
/// @return 平行移動後ブロック
vector<vector<vector<bool> > > parallel(vector<vector<vector<bool> > >& block,int dy,int dx){
    int i,j,k;
    vector<vector<vector<bool> > > ans(Z,vector<vector<bool> >(H,vector<bool>(W,false)));
    rep(i,Z)rep(j,H)rep(k,W)if(block[i][j][k])ans[i][j+dy][k+dx]=true;
    return ans;
}

/// @brief 2つのブロックが重なるか
/// @param block1 1つ目のブロック
/// @param block2 2つ目のブロック
/// @return 判定値
bool judge(vector<vector<bool> >& block1,vector<vector<bool> >& block2){
    int i,j;
    rep(i,H)rep(j,W)if(block1[i][j] && block2[i][j])return false;
    return true;
}

/// @brief 指定した段を削除する関数
/// @param field 対象行列
/// @param id 指定した要素の添え字
void deleteLine(vector<vector<vector<bool> > >& field,int id){
    for(;id<field.size()-1;id++)field[id]=field[id+1];
    field.pop_back();
}

/// @brief 指定した段のセルが全てブロックで埋まっているか否か判定
/// @param block 2*2マスのセル
/// @return 判定値
bool isAll(vector<vector<bool> >& block){
    for(int y=0;y<H;y++)for(int x=0;x<W;x++){
        if(block[y][x]==false)return false;
    }
    return true;
}

/// @brief 指定した段のセルが全て空か判定
/// @param block 2*2マスのセル
/// @return 判定値
bool isNone(vector<vector<bool> >& block){
    for(int y=0;y<H;y++)for(int x=0;x<W;x++){
        if(block[y][x])return false;
    }
    return true;
}

int main(){
    int i,j,k,ii;
    while(1){
        scanf("%d%d",&h,&n);
        if(!(h||n))break;
        // ブロックが存在するならtrue, しないならfalse
        vector<vector<vector<bool> > > ipt(0,vector<vector<bool> >(H,vector<bool>(W,false)));
        rep(i,h){
            vector<vector<bool> > tmp(H,vector<bool>(W,false));
            rep(j,H){
                string str;
                cin>>str;
                rep(k,W)tmp[j][k]=str[k]=='#';
            }
            ipt.push_back(tmp);
        }
        vector<vector<vector<vector<bool> > > > blocks(0,vector<vector<vector<bool> > >(Z,vector<vector<bool> >(H,vector<bool>(W,false))));
        rep(i,n){
            vector<vector<vector<bool> > > tmp(Z,vector<vector<bool> >(H,vector<bool>(W,false)));
            rep(ii,Z){
                rep(j,H){
                    string str;
                    cin>>str;
                    rep(k,W)tmp[ii][j][k]=str[k]=='#';
                }
            }
            blocks.push_back(tmp);
        }
        auto calc=[&]()->int{
            vector<vector<vector<bool> > > field=ipt;
            int ans=0,now_h,now_block=0,i;        
            while(now_block<n){
                if(isNone(blocks[now_block][0])){
                    swap(blocks[now_block][0],blocks[now_block][1]);
                }
                now_h=field.size()-1;
                // 落下停止するまでの処理
                while(now_h>=0
                    && judge(field[now_h],blocks[now_block][0])
                    && (now_h+1>=field.size() || judge(field[now_h+1],blocks[now_block][1])))now_h--;
                now_h++;
                for(int i=0;i<=1;i++){
                    if(now_h+i>=field.size())field.push_back(blocks[now_block][i]);
                    else{
                        int j,k;
                        rep(j,H)rep(k,W)field[now_h+i][j][k]=(field[now_h+i][j][k]||blocks[now_block][i][j][k]);
                    }
                }
                // ブロック消去処理
                if(now_h<field.size() && isAll(field[now_h])){
                    deleteLine(field,now_h);
                    ans++;
                    now_h--;
                }
                now_h++;
                if(now_h<field.size() && isAll(field[now_h]))ans++,deleteLine(field,now_h);
                now_block++;
            }
            return ans;
        };
        auto rec=[&](auto& func,int now)->int{
            if(now==n)return calc();
            int ans=-1;
            for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++){
                int i,j,ii;
                bool flag=true;// (dy,dx)だけ平行移動を行っても，フィールドからはみ出さないか判定
                rep(ii,Z)rep(i,H)rep(j,W)if(blocks[now][ii][i][j]&&(!(0<=i+dy&&i+dy<H&&0<=j+dx&&j+dx<W)))flag=false;
                if(flag){
                    // 情報の更新
                    blocks[now]=parallel(blocks[now],dy,dx);
                    ans=max(ans,func(func,now+1));
                    // 情報の復元
                    blocks[now]=parallel(blocks[now],-dy,-dx);
                }
            }
            return ans;
        };
        printf("%d\n",rec(rec,0));
    }
    return 0;
}
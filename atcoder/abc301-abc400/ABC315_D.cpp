/*アルゴリズムと工夫点(Magical Cookies/CPU: 381 ms Memory: 20176 KB  Length: 1851 B)
シミュレーションの高速化で解く．
最悪計算量は，O(H*W + 26*(H+W)) < 10^7 となり高速．
※慣らし計算量の見積もりを正しく行う必要があった...
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define ALFA 26
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;

int main(){
    int i,j;
    scanf("%d%d",&h,&w);
    vector<vector<int> > parsed_mp(h,vector<int>(w,0));
    vector<vector<int> > row(h,vector<int>(ALFA,0)),col(w,vector<int>(ALFA,0));
    rep(i,h){
        string tmp;
        cin>>tmp;
        rep(j,w){
            parsed_mp[i][j]=tmp[j]-'a';
            row[i][parsed_mp[i][j]]++;
            col[j][parsed_mp[i][j]]++;
        }
    }
    vector<bool> is_deleted_row(h,false),is_deleted_col(w,false);
    auto toDelete=[&](vector<int> arr)->bool{
        int i,sum=0,kind=0;
        rep(i,arr.size()){
            sum+=arr[i];
            if(arr[i])kind++;
        }
        return sum>=2&&kind==1;
    };
    auto del=[&](int y,int x)->void{
        if(is_deleted_row[y] || is_deleted_col[x])return ;
        row[y][parsed_mp[y][x]]--;
        col[x][parsed_mp[y][x]]--;
    };
    while(1){
        bool is_continued=false;
        vector<int> del_row,del_col;
        rep(i,h){
            if(!is_deleted_row[i] && toDelete(row[i]))del_row.push_back(i);
        }
        rep(j,w){
            if(!is_deleted_col[j] && toDelete(col[j]))del_col.push_back(j);
        }
        for(int row_id : del_row){
            rep(j,w)del(row_id,j);
            is_deleted_row[row_id]=true;
            is_continued=true;
        }
        for(int col_id : del_col){
            rep(i,h)del(i,col_id);
            is_deleted_col[col_id]=true;
            is_continued=true;
        }
        if(!is_continued)break;
    }
    int ans=0;
    rep(i,h)rep(j,w)ans+=!(is_deleted_row[i] || is_deleted_col[j]);
    printf("%d\n",ans);
    return 0;
}
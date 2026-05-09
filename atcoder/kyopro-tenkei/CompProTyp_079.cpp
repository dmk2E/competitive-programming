/*アルゴリズムと工夫点(Two by Two（★3）/CPU: 2 ms Memory: 3988 KB  Length: 1161 B)
操作を行う位置(x,y)の選び方は(h-1)*(w-1)通り存在する．条件を満たす選び方が存在するとすると，操作の順番に関係なく解は変わらず，(x,y)で行う操作はまとめて行っても良い．
そこで，その位置(x,y)で操作を行うか，左上から右下の順で決めていくことにする．そうすると，位置(x,y)を選ぶとき，それ以前の操作はもう行わないから，a[y][x]の値は一致するように操作をしなければならない．
そのように操作を行った時，最終的にaとbが一致していれば，「Yes」となる．最悪計算量はO(H*W)≒10^4 となる．
※操作順序によらない
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;
vector<vector<int> > a,b;
vector<vector<bool> > isEqual;

int operate(int y,int x,int& cnt){
    int i,j,tmp=b[y][x]-a[y][x];
    rep(i,2)rep(j,2){
        a[y+i][x+j]+=tmp;
        if(isEqual[y+i][x+j]==false&&a[y+i][x+j]==b[y+i][x+j]){
            isEqual[y+i][x+j]=true;
            cnt++;
        }else if(isEqual[y+i][x+j]&&a[y+i][x+j]!=b[y+i][x+j]){
            isEqual[y+i][x+j]=false;
            cnt--;
        }
    }
    return abs(tmp);
}

int main(){
    int i,j,cnt=0;
    ll ans=0;
    scanf("%d%d",&h,&w);
    a=vector<vector<int> >(h,vector<int>(w)),b=vector<vector<int> >(h,vector<int>(w));
    isEqual=vector<vector<bool> >(h,vector<bool>(w,false));
    rep(i,h)rep(j,w)scanf("%d",&a[i][j]);
    rep(i,h)rep(j,w)scanf("%d",&b[i][j]);
    rep(i,h-1){
        rep(j,w-1){
            ans+=operate(i,j,cnt);
        }
    }
    if(cnt==h*w){
        puts("Yes");
        printf("%lld\n",ans);
    }else
        puts("No");
    return 0;
}
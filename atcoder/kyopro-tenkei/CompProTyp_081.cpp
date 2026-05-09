/*アルゴリズムと工夫点(Friendly Group（★5）/CPU: 140 ms Memory: 101268 KB  Length: 757 B)
平面走査+BITだと思ったが，問題文の理解が足りず，解けなかった．
二次元にプロットするのはいいが，必ずしも平面走査ではないことに気を付けたい．
また，(集合内のどの2つもある絶対値の差がK以下である):(ある集合内の最小値と最大値の絶対値の差がKとなる範囲)の全探索をする必要があることに注意．
※データを二次元にプロット/二次元累積和
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_K 5000
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,k,a,b;

int main(){
    int i,j,mmax;
    scanf("%d%d",&n,&k);
    vector<vector<int> > sumAB(MAX_K+2,vector<int>(MAX_K+2,0));
    rep(i,n){
        scanf("%d%d",&a,&b);
        sumAB[a+1][b+1]++;
    }
    rep(i,MAX_K+1)rep(j,MAX_K+1)sumAB[i+1][j+1]+=sumAB[i+1][j]+sumAB[i][j+1]-sumAB[i][j];
    mmax=-1;
    rep(i,MAX_K+1-k)rep(j,MAX_K+1-k){
        if(mmax<sumAB[i+k+1][j+k+1]-sumAB[i+k+1][j]-sumAB[i][j+k+1]+sumAB[i][j])
            mmax=sumAB[i+k+1][j+k+1]-sumAB[i+k+1][j]-sumAB[i][j+k+1]+sumAB[i][j];
    }
    printf("%d\n",mmax);
    return 0;
}
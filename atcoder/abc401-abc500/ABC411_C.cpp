/*アルゴリズムと工夫点(Black Intervals/CPU: 81 ms Memory: 3908 KB  Length: 832 B)
各マスの色状態を保持しておき，色を反転させたマスの両隣のマスを見て，黒マス連続区間の数を数え上げる．
最悪計算量は O(N+Q)<10^7 となり高速．
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,q;

int main(){
    int i,j,cnt=0;
    scanf("%d%d",&n,&q);
    vector<bool> a(n,false);//true:黒 false:白
    while(q--){
        scanf("%d",&i);
        i--;
        //rep(j,n)printf("%d",a[j]?1:0);puts("");
        if(a[i]){// 黒->白
            a[i]=false;
            if((i-1>=0&&a[i-1])&&(i+1<n&&a[i+1]))cnt++;
            if((i-1<0||a[i-1]==false)&&(i+1>=n||a[i+1]==false))cnt--;
        }else{// 白->黒
            a[i]=true;
            if((i-1>=0&&a[i-1])&&(i+1<n&&a[i+1]))cnt--;
            if((i-1<0||a[i-1]==false)&&(i+1>=n||a[i+1]==false))cnt++;
        }
        printf("%d\n",cnt);
    }
    return 0;
}
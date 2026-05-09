/*アルゴリズムと工夫点(String Rotation/CPU: 23 ms Memory: 4020 KB  Length: 635 B)
辞書順最小は貪欲法が適用できる．
辞書順最小であるためには，できるだけ先頭文字のアルファベットが'a'に近い必要がある．
そのため，以下の[l,r)について1回左巡回シフトを行えばよい．
l=(S_{i)>S_(i+1) を満たす最小のi)
r=(S_(i)<S_(j) (j>=i)を満たす最小のj)
1テストケース当たりの最悪計算量は，O(N) となり十分高速．
*/
#include<iostream>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int t,n;

/// @brief [l,r)の範囲で1回左に巡回シフトさせる
/// @param str 対象文字列
/// @param l 範囲の左端
/// @param r 範囲の右端
void leftShift(string& str,int l,int r){
    int i;
    char tmp=str[l];
    while(l<r-1){
        str[l]=str[l+1];
        l++;
    }
    str[l]=tmp;
}

int main(){
    int i,j;
    string str;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        cin>>str;
        rep(i,n-1)if(str[i]>str[i+1])break;
        for(j=i;j<n;j++)if(str[i]<str[j])break;
        leftShift(str,i,j);
        cout<<str<<'\n';
    }
    return 0;
}
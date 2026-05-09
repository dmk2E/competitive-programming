/*アルゴリズムと工夫点(Tournament Result/CPU: 19 ms Memory: 5736 KB  Length: 796 B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n;

int main(){
    int i,j;
    scanf("%d",&n);
    vector<string> a(n);
    rep(i,n)cin>>a[i];
    rep(i,n)rep(j,n){
        if(i==j)continue;
        if(a[i][j]=='W'){
            if(a[j][i]!='L'){
                puts("incorrect");
                return 0;
            }
        }else if(a[i][j]=='L'){
            if(a[j][i]!='W'){
                puts("incorrect");
                return 0;
            }
        }else{
            if(a[j][i]!='D'){
                puts("incorrect");
                return 0;
            }
        }
    }
    puts("correct");
    return 0;
}
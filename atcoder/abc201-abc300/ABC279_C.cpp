/*アルゴリズムと工夫点(RANDOM/CPU: 68 ms Memory: 17636 KB  Length: 701 B)

*/
#include<iostream>
#include<vector>
#include<map>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int h,w;

int main(){
    int i,j;
    string col;
    scanf("%d%d",&h,&w);
    map<string,int> v;
    vector<string> tmp(h);
    rep(i,h)cin>>tmp[i];
    rep(j,w){
        col="";
        rep(i,h)col+=tmp[i][j];
        v[col]+=1;
    }
    rep(i,h)cin>>tmp[i];
    rep(j,w){
        col="";
        rep(i,h)col+=tmp[i][j];
        v[col]-=1;
    }
    for(pair<string,int> p:v){
        if(p.second!=0){
            puts("No");
            return 0;
        }
    }
    puts("Yes");
    return 0;
}
/*アルゴリズムと工夫点(One More aab aba baa/CPU: 11 ms Memory: 7072 KB  Length: 687 B)
文字列Sの長さが8と大したことないから，階乗全探索とsetを用いる．
最悪計算量は，O(K+|S|!*log2(|S|!))<10^7 より，十分高速．
*/
#include<iostream>
#include<set>
#define rep(i,n) for(i=0;i<(int)n;i++)
#define MAX_S 8
using namespace std;

int k;
string s;
set<string> v;

void res(int num,string ss,bool used[MAX_S]){
    int i,j;
    if(num==s.length()){
        v.insert(ss);
        return ;
    }
    rep(i,s.length()){
        if(used[i]==false){
            used[i]=true;
            res(num+1,ss+s[i],used);
            used[i]=false;
        }
    }
}

int main(){
    bool used[MAX_S]={0};
    cin>>s;scanf("%d",&k);
    res(0,"",used);
    for(string str:v){
        k--;
        if(k==0){
            cout<<str<<endl;
            break;
        }
    }
    return 0;
}
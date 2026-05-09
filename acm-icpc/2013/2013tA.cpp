/*アルゴリズムと工夫点(王様の視察/CPU: 1 ms Memory: 3420 KB  Length: 737 B)
"アルファベット->'a'から数えて何番目か"，"'a'から数えて何番目か->アルファベット"と参照できる配列を用意しておくと楽．
最悪計算量は，1テストケースあたり，O(|S|)
*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_ALFA (1<<8)
#define STATION 52
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int n,alfa_to_id[MAX_ALFA]={0},id_to_alfa[STATION];
string s;

int main(){
    int i,j;
    rep(i,STATION/2)id_to_alfa[i]=(char)('a'+i);
    rep(i,STATION/2)id_to_alfa[STATION/2+i]=(char)('A'+i);
    rep(i,STATION)alfa_to_id[(int)id_to_alfa[i]]=i;
    while(1){
        scanf("%d",&n);
        if(!n)break;
        vector<int> k(n);
        rep(i,n)scanf("%d",&k[i]);
        cin>>s;
        rep(i,s.length())s[i]=id_to_alfa[(alfa_to_id[s[i]]-k[i%n]+STATION)%STATION];
        printf("%s\n",s.c_str());
    }
    return 0;
}
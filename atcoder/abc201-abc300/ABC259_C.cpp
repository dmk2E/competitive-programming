/*アルゴリズムと工夫点(XX to XXX/CPU: 9 ms Memory: 8080 KB  Length: 1216 B)

*/
#include<iostream>
#include<vector>
#include<cassert>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<char,int> P;

string s,t;

int main(){
    int i,j;
    cin>>s>>t;
    vector<P> rle_s,rle_t;
    i=0;
    while(i<s.length()){
        rle_s.push_back(P(s[i],1));
        i++;
        while(i<s.length()&&s[i]==rle_s.back().first){
            rle_s[rle_s.size()-1].second++;
            i++;
        }
    }
    i=0;
    while(i<t.length()){
        rle_t.push_back(P(t[i],1));
        i++;
        while(i<t.length()&&t[i]==rle_t.back().first){
            rle_t[rle_t.size()-1].second++;
            i++;
        }
    }
    if(rle_s.size()==rle_t.size()){
        rep(i,rle_s.size()){
            if(rle_s[i].first==rle_t[i].first){
                if(rle_s[i].second==rle_t[i].second)continue;
                if(rle_s[i].second>=2&&rle_s[i].second<rle_t[i].second)continue;
                break;
            }else
                break;
        }
        if(i==(int)rle_s.size()){
            puts("Yes");
            return 0;
        }
    }
    puts("No");
    return 0;
}
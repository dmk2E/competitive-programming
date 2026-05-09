/*アルゴリズムと工夫点(11/22 Substring/CPU: 6 ms Memory: 5692 KB  Length: 847 B)
c={'1','/','2'}それぞれを(c,連続数)の形にランレングス圧縮すると，c='/'の部分だけに着目して，それが中心となる11/22文字列を考えた時の長さの最大値をそれぞれ求め，その中の最大値を出力すればよい．
最悪計算量は O(N)<10^6 となり十分高速．
*/
#include<iostream>
#include<vector>
#define rep(i,n) for(i=0;i<(int)n;i++)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

typedef pair<char,int> P;

int n;
string s;

int main(){
    int i,j;
    P tmp;
    scanf("%d",&n);
    cin>>s;
    vector<P> rle;
    i=0;
    while(i<s.length()){
        tmp.first=s[i];
        j=0;
        while(tmp.first==s[i]){
            i++;
            j++;
        }
        tmp.second=j;
        rle.push_back(tmp);
    }
    //rep(i,rle.size())printf("(%c,%d)",rle[i].first,rle[i].second);puts("");
    j=1;
    rep(i,rle.size()){
        if(rle[i].first=='/'&&i-1>=0&&i+1<rle.size()&&rle[i-1].first=='1'&&rle[i+1].first=='2'){
            j=max(j,1+2*min(rle[i-1].second,rle[i+1].second));
        }
    }
    printf("%d\n",j);
    return 0;
}
/*アルゴリズムと工夫点(ぶりしゃぶしゃぶり部/CPU: 0 ms Memory: 3428 KB  Length: 1084 B)
回文となるため，文字列前半が決まっていれば，後半部分は勝手に決まる．そこで，文字列真ん中から回文となっているかor反転させて回文にできるか判定すればよい．反転させる区間はできるだけ小さくする貪欲法となる．
その時点での各アルファベットの出現回数を保持して置くことで，文字列比較の回数を減らし，最悪計算量はO(|S|)<10^6 となり，十分高速．
*/
#include<bits/stdc++.h>
#define rep(i,n)for(i=0;i<n;i++)
using namespace std;

string s;

pair<long long,int> cnt(int x,int y){
    vector<int> a1(26,0),a2(26,0);
    int i,j=y,k;
    for(i=x;i<s.size()&&j>=0;i++,j--){
        a1[s[i]-'a']++;
        a2[s[j]-'a']++;
        if(s[i]==s[y]&&s[j]==s[x]){
            rep(k,26){
                if(a1[k]!=a2[k])break;
            }
            if(k!=26)continue;
            if(s.substr(x,i-x+1)==s.substr(j,y-j+1))
                return {1LL*(i-x+1)*(i-x+1),i};
        }
    }
    return {-1,-1};
}

int main(){
    int i,j,h;
    while(cin>>s,s[0]!='#'){
        long long ans=0;
        h=(s.size()+1)/2;
        if(s.size()%2==0)j=h-1;
        else j=h-2;
        for(i=h;i<s.size()&&j>=0;i++,j--){
            if(s[i]!=s[j]){
                pair<int,int> temp=cnt(i,j);
                if(temp.first==-1)break;
                ans+=temp.first;
                j-=temp.second-i;
                i=temp.second;
            }
        }
        if(i==s.size()&&j==-1)cout<<ans<<endl;
        else cout<<-1<<endl;
    }
    return 0;
}
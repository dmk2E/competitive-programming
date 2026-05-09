/*アルゴリズムと工夫点(Many Replacement/CPU: 18 ms  Memory: 4576 KB  Length: 635 B)
'a'~'z'それぞれに0~25の番号を割り当てる。文字cに対するこの番号をnum(c)とする。alfa[i]:文字iが存在する文字列s上の添え字 aalfa[i]:番号iの文字が置き換わる文字の番号 とし、クエリで文字c、を文字dに置き換
える度にaalfa[i]=num(c)となるすべてのaalfa[i]の値をnum(d)に書き換える。最後にalfaとaalfaの情報を元に最終的な文字列sを作成し、出力する。最悪計算量はO(n+MAX_ALFA*q)<10^7となり高速。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_ALFA 26
using namespace std;

int n,q,aalfa[MAX_ALFA];
char c,d;
vector<int> alfa[MAX_ALFA];
string s;

int main() {
	int i,j;
	scanf("%d",&n);
	cin>>s;
	rep(i,MAX_ALFA)
		aalfa[i]=i;
	rep(i,s.length())
		alfa[(int)s[i]-(int)'a'].push_back(i);
	scanf("%d",&q);
	while(q--){
		getchar();
		scanf("%c %c",&c,&d);
		rep(i,MAX_ALFA){
			if(aalfa[i]==(int)c-(int)'a')
				aalfa[i]=(int)d-(int)'a';
		}
	}
	rep(i,MAX_ALFA){
		rep(j,alfa[i].size()){
			s[alfa[i][j]]=(char)((int)'a'+aalfa[i]);
		}
	}
	cout <<s<<endl;
	return 0;
}
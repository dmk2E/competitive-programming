/*アルゴリズムと工夫点(Smallest Subsequence/CPU: 13 ms  Memory: 14232 KB  Length: 585 B)
辞書順最小は貪欲法なのは気づいていたが、前処理の仕方が思いつかなかった。
*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_ALFA 26
using namespace std;

int n,k;
string s;

int main() {
	int i,j,now;
	scanf("%d%d",&n,&k);
	cin>>s;
	vector<vector<int> > c(MAX_ALFA,vector<int>(n,n));
	rep(i,n){
		for(j=i;j>=0;j--){
			if(i<c[(int)s[i]-(int)'a'][j])
				c[(int)s[i]-(int)'a'][j]=i;
			else
				break;
		}
	}
	now=-1;
	rep(i,k){
		rep(j,MAX_ALFA){
			if(now+1<=c[j][now+1]&&c[j][now+1]<=n-k+i){
				printf("%c",(char)(j+(int)'a'));
				now=c[j][now+1];
				break;
			}
		}
	}
	puts("");
	return 0;
}
/*TLEver
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
#define MAX_N 100000
using namespace std;

typedef struct data{
	int id;
	string alfa;

	data(int iid=0,string aalfa="a"):id(iid),alfa(aalfa){}

	bool operator<(const data& k) const {
		return alfa<k.alfa||(alfa==k.alfa&&id<k.id);
	}

}Data;

int n,k;
string s;

int main() {
	int i,j,now=0;
	Data pri[MAX_N];
	scanf("%d%d",&n,&k);
	cin>>s;
	rep(i,n)
		pri[i]=Data(i,s.substr(i,1));
	sort(pri,pri+n);
	now=0;
	rep(i,k){
		rep(j,n){
			if(now<=pri[j].id&&pri[j].id<=n-k+i)
				break;
		}
		cout<<pri[j].alfa<<flush;
		now=pri[j].id+1;
	}
	cout<<endl;
	return 0;
}
*/
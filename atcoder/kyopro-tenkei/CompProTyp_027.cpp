/*アルゴリズムと工夫点(Sign Up Requests/CPU: 188 ms  Memory: 11224 KB  Length: 313 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n;
set<string> v;

int main() {
	int i;
	string s;
	scanf("%d",&n);
	rep(i,n){
		cin>>s;
		if(v.find(s)==v.end()){//既に登録済みか判定
			v.insert(s);
			printf("%d\n",i+1);
		}
	}
	return 0;
}
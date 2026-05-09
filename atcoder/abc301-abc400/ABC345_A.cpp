/*アルゴリズムと工夫点(Leftrightarrow/CPU: 1 ms  Memory: 3648 KB  Length: 324 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

string s;

int main() {
	int i;
	cin>>s;
	if(s[0]=='<'&&s[s.length()-1]=='>'){
		rep(i,s.length()-2){
			if(s[i+1]!='=')
				break;
		}
		printf("%s\n",i==s.length()-2?"Yes":"No");
	}else
		printf("No\n");
	return 0;
}
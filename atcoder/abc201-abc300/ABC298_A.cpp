/*アルゴリズムと工夫点(Job Interview/CPU: 100 ms  Memory: 3676 KB  Length: 302 B)

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<(int)(n);i++)
using namespace std;

int n;
string s;

int main() {
	int i;
	bool f1=false,f2=true;
	cin>>n>>s;
	rep(i,n){
		if(s[i]=='o')
			f1=true;
		if(s[i]=='x')
			f2=false;
	}
	printf("%s\n",(f1&&f2)?"Yes":"No");
	return 0;
}
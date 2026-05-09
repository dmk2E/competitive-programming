/*アルゴリズムと工夫点(Alice&Brown/CPU: 1 ms  Memory: 3904 KB  Length: 319 B

*/
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

typedef long long ll;

ll x, y;

ll toAbs(ll x) {
	return x > 0 ? x : -x;
}

int main() {
	int i;
	ll sum, tmp;
	bool flag;
	scanf("%lld%lld", &x, &y);
	printf("%s\n", toAbs(x - y) > 1 ? "Alice" : "Brown");
	return 0;
}

/*全探索で法則を見つけるために用いた関数。
#include <bits/stdc++.h>
#define rep(i,n) for(i=0;i<n;i++)
using namespace std;

typedef long long ll;

ll x, y;

void search(vector<pair<ll, ll> >&sta) {
	int i, j;
	ll x = sta[sta.size() - 1].first, y = sta[sta.size() - 1].second;
	if (x < 2 && y < 2) {
		rep(i, sta.size())
			printf("%lld %lld\n", sta[i].first, sta[i].second);
		printf("%s wins!\n", sta.size() % 2 == 0 ? "Alice" : "Brown");
		return;
	}
	for (i = 1; x - 2 * i >= 0; i++) {
		sta.push_back(make_pair(x - (2 * i), y + i));
		search(sta);
		sta.pop_back();
	}
	for (i = 1; y - 2 * i >= 0; i++) {
		sta.push_back(make_pair(x + i, y - (2 * i)));
		search(sta);
		sta.pop_back();
	}
}

int main() {
	int i;
	ll sum, tmp;
	bool flag;
	scanf("%lld%lld", &x, &y);
	for (i = 0, sum = x + y, flag = sum % 2 != 1; x >= 2 || y >= 2; i++) {
		tmp = max(x, y);
		printf("%lld %lld\n", x, y);
		if (i % 2 == 0) {   //Alice:flag==trueであってほしい
			if (flag) {
				if (sum % 2 == 0) {
					tmp /= 2;
					if (tmp % 2 == 1)
						tmp--;
				}
				else {
					tmp /= 2;
					if (tmp % 2 == 0)
						tmp--;
				}
			}
			else {
				if (sum % 2 == 0) {
					tmp /= 2;
					if (tmp % 2 == 0)
						tmp--;
				}
				else {
					tmp /= 2;
					if (tmp % 2 == 1)
						tmp--;
				}
			}
		}
		else {
			if (flag) {
				if (sum % 2 == 0) {
					tmp /= 2;
					if (tmp % 2 == 0)
						tmp--;
				}
				else {
					tmp /= 2;
					if (tmp % 2 == 1)
						tmp--;
				}
			}
			else {
				if (sum % 2 == 0) {
					tmp /= 2;
					if (tmp % 2 == 1)
						tmp--;
				}
				else {
					tmp /= 2;
					if (tmp % 2 == 0)
						tmp--;
				}
			}
		}
		if (tmp <= 0)
			tmp = 1;
		if (x > y) {
			x -= 2 * tmp;
			y += tmp;
		}
		else {
			y -= 2 * tmp;
			x += tmp;
		}
		if ((sum = x + y) % 2 == 1)
			flag = !flag;
	}
	printf("%s\n", i % 2 == 0 ? "Alice" : "Brown");
	return 0;
}
*/
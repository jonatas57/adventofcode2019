#include <bits/stdc++.h>

using namespace std;

typedef long long          ll;
typedef unsigned long long ull;
typedef vector<int>	       vi;
typedef vector<bool>       vb;
typedef map<int, int>      mii;
typedef pair<int, int>     ii;

#define INF                0x3f3f3f3f
#define MAX                100000
#define N                  4 * MAX + 10
#define MOD                1000000007
#define each(x, s)         for(auto& x : s)
#define ceach(x, s)        for(auto const& x : s)
#define rep(x, y, z)       for(int i = x;i < y;i+=z)
#define loop(x)	           for(int i = 0;i < x;i++)
#define vloop(v, x)        for(int v = 0;v < x;v++)
#define avg(l, r)          l + (r - l) / 2
#define iter(a)            a.begin(), a.end()

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	int l, r;
	char c;
	cin >> l >> c >> r;
	int ans = 0;
	for (int i = l;i <= r;i++) {
		string s = to_string(i);
		bool p = false, q = true;
		int pp = 1;
		loop(5) {
			if (s[i] == s[i + 1]) pp++;
			else {
				if (s[i] > s[i + 1]) q = false;
				if (pp == 2) p = true;
				pp = 1;
			}
		}
		if (pp == 2) p = true;
		if (p and q) ans++;
	}
	cout << ans << endl;
	return 0;
}


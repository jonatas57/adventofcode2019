#include <bits/stdc++.h>

using namespace std;

typedef long long          ll;
typedef unsigned long long ull;
typedef vector<int>	       vi;
typedef vector<bool>       vb;
typedef map<int, int>      mii;
typedef pair<int, int>     ii;

#define INF                0x3f3f3f3f
#define INFLL              0x3f3f3f3f3f3f3f3f
#define MOD                1000000007
#define each(x, s)         for(auto& x : s)
#define loop(x)	           for(int i = 0;i < x;i++)
#define vloop(v, x)        for(int v = 0;v < x;v++)
#define avg(l, r)          l + (r - l) / 2
#define iter(a)            a.begin(), a.end()
#define riter(a)           a.rbegin(), a.rend()
#define endl               "\n"

auto reachable(int x, int y) {
	vector<ii> ans;
	if (x > 0) ans.emplace_back(x - 1, y);
	if (y < 4) ans.emplace_back(x, y + 1);
	if (x < 4) ans.emplace_back(x + 1, y);
	if (y > 0) ans.emplace_back(x, y - 1);
	return ans;
}

int step(vector<string>* area, bool act) {
	int bio = 0, mask = 1;
	loop(5) {
		vloop(j, 5) {
			int cnt = 0;
			for (auto& [x, y] : reachable(i, j)) {
				if (area[act][x][y] == '#') cnt++;
			}
			if (area[act][i][j] == '#') {
				area[!act][i][j] = (cnt == 1 ? '#' : '.');
			}
			else {
				area[!act][i][j] = (cnt == 1 or cnt == 2 ? '#' : '.');
			}
			if (area[!act][i][j] == '#') bio |= mask;
			mask <<= 1;
		}
	}
	return bio;
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	vector<string> area[2];
	string s;
	while (cin >> s) {
		area[0].push_back(s);
		area[1].push_back(s);
	}
	int bio = 0;
	map<int, bool> bios;
	for (bool p = false;;p = !p) {
		bio = step(area, p);
		if (bios[bio]) break;
		bios[bio] = true;
	}
	cout << bio << endl;
	return 0;
}


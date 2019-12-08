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

struct layer {
	vi cnt;
	layer(string s) : cnt(3, 0) {
		each(c, s) {
			cnt[c - '0']++;
		}
	}
};

const int w = 25, h = 6;

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	string s;
	cin >> s;
	int l = s.length();
	vector<layer> ls;
	for (int i = 0;i < l;i += w * h) {
		ls.emplace_back(s.substr(i, w * h));
	}
	sort(iter(ls), [](layer& a, layer& b) {
		return a.cnt[0] < b.cnt[0];
	});
	cout << ls[0].cnt[1] * ls[0].cnt[2] << endl;
	return 0;
}


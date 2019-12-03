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

ll add(ll a, ll b) {
	return a + b;
}

ll mult(ll a, ll b) {
	return a * b;
}

typedef ll (*fn)(ll, ll);

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	
	fn fs[] = {add, mult};
	string s;
	cin >> s;
	stringstream ss;
	ss << s;
	int x;
	char c;
	vi prog;
	while (ss >> x >> c) prog.push_back(x);
	prog[1] = 82, prog[2] = 26;
	int l = prog.size();
	for (int i = 0;i < l and prog[i] != 99;i += 4) {
		prog[prog[i + 3]] = fs[prog[i] - 1](prog[prog[i + 1]], prog[prog[i + 2]]);
	}
	cout << prog[0] << endl;
	return 0;
}


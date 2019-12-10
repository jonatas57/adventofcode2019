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

const double EPS = 1e-7;

struct point {
	int x, y;
	point(int x = 0, int y = 0) : x(x), y(y) {}

	double norm() {
		return sqrt(x * x + y * y);
	}
	point operator-(point& p) {
		return {x - p.x, y - p.y};
	}
	int operator*(point& p) {
		return x * p.x + y * p.y;
	}
};

double angle(point p, point q) {
	int dot = p * q;
	double x = dot / (p.norm() * q.norm());
	return acos(x) * (q.y < 0 ? -1 : 1);
}

class cmp {
	public:
	bool operator()(const double a, const double b) {
		if (abs(a - b) < EPS) return false;
		return a < b;
	}
};

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	string s;
	vector<point> ps;
	for (int i = 0;cin >> s;i++) {
		vloop(j, s.length()) {
			if (s[j] == '#') ps.emplace_back(i, j);
		}
	}
	int ans = 0;
	loop(ps.size()) {
		set<double, cmp> as;
		vloop(j, ps.size()) {
			if (i == j) continue;
			point del = ps[j] - ps[i];
			as.insert(angle({1, 0}, del));
		}
		ans = max(ans, (int)as.size());
	}
	cout << ans << endl;
	return 0;
}


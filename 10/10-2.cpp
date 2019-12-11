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
#define loop(x)	           for(int i = 0;i < (int)x;i++)
#define vloop(v, x)        for(int v = 0;v < (int)x;v++)
#define avg(l, r)          l + (r - l) / 2
#define iter(a)            a.begin(), a.end()

const double EPS = 1e-7;
const double PI  = acos(-1);
const double DPI = 2 * PI;

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
	double ang = (q.y < 0 ? 2 * PI - acos(x) : acos(x)) + PI / 2;
	if (ang > DPI || abs(ang - DPI) < EPS) ang -= DPI;
	return ang;
}

class cmp {
	public:
	bool operator()(const pair<double, point>& a, const pair<double, point>& b) {
		if (abs(a.first - b.first) < EPS) return false;
		return a.first < b.first;
	}
};

double dist(point p, point q) {
	point del = p - q;
	return del.norm();
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	string s;
	vector<point> ps;
	for (int i = 0;cin >> s;i++) {
		vloop(j, s.length()) {
			if (s[j] == '#') ps.emplace_back(j, i);
		}
	}
	int ans = 0;
	set<pair<double, point>, cmp> ansSet;
	loop(ps.size()) {
		set<pair<double, point>, cmp> as;
		vloop(j, ps.size()) {
			if (i == j) continue;
			point del = ps[j] - ps[i];
			auto aux = make_pair(angle({1, 0}, del), ps[j]);
			auto it = as.insert(aux);
			if (!it.second and dist(ps[j], ps[i]) < dist(ps[i], it.first->second)) {
				as.erase(it.first);
				as.insert(aux);
			}
		}
		if (ans < (int)as.size()) {
			ans = as.size();
			ansSet = as;
		}
	}
	auto it = ansSet.begin();
	for (ans = 1;ans < 200 and it != ansSet.end();ans++, it++);
	cout << it->second.x * 100 + it->second.y << endl;
	return 0;
}


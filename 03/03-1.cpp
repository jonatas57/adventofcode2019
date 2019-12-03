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

typedef tuple<int, int, int, int> tpl;

struct point {
	int x, y;

	point(int x = 0, int y = 0) : x(x), y(y) {}

	point operator-(point p) {
		return point(x - p.x, y - p.y);
	}
	point operator+(point p) {
		return point(x + p.x, y + p.y);
	}
};

struct line {
	int a, b, c;
	int st, end;
	line(point p, point q) {
		point del = p - q;
		if (del.x) {
			a = 0;
			b = 1;
			c = -p.y;
			st = p.x;
			end = q.x;
		}
		else {
			a = 1;
			b = 0;
			c = -p.x;
			st = p.y;
			end = q.y;
		}
	}
};

struct wire {
	vector<tpl> lines;
	point last;

	void addLine(string d, int w) {
		bool h = d[0] == 'R' or d[0] == 'L';
		int del = stoi(d.substr(1), nullptr, 10);
		point next = (h ? point(last.x + del, 0) : point(0, last.y + del));
		if (h) {
			lines.emplace_back(last.x, -INF, h, w);
			lines.emplace_back(last.x + del, INF, (int)h, w);
		}
		else lines.emplace_back(next.x, next.y, h, w);
		last = last + next;
	}
};

void conswire(string s, wire& w, int t) {
	string x = "";
	each(c, s) {
		if (c == ',') {
			w.addLine(x, t);
			x = "";
		}
		else x += c;
	}
};


int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	wire w1, w2;
	string s, t;
	getline(cin, s);
	getline(cin, t);
	conswire(s, w1, 1);
	conswire(t, w2, 2);

	vector<tpl> sl;
	sl.insert(sl.end(), iter(w1.lines));
	sl.insert(sl.end(), iter(w2.lines));
	sort(iter(sl));
	set<ii> hs;
	int ans = 
	for (auto [x, y, h, w] : sl) {
		if (h) {
			if (y == -INF) hs.emplace(x, w);
			else {
				auto it = hs.find(ii(x, w));
				hs.erase(it);
			}
		}
		else {
			auto l = lower_bound(iter(hs), ii(x, -1));
			auto u = upper_bound(iter(hs), ii(y, 10));
			for (auto it = l;it != u;it++) {
				if (it->second != w) {
					ans = min(ans, dist(point(0, 0), point(x, it->first)));
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}


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

typedef tuple<int, int, int, int, int, int> tpl;
typedef tuple<int, int, int> line;

struct point {
	int x, y, dist;

	point(int x = 0, int y = 0) : x(x), y(y) , dist(0) {}

	point operator-(point p) {
		return point(x - p.x, y - p.y);
	}
	point operator+(point p) {
		return point(x + p.x, y + p.y);
	}
};

int id = 0;
vector<point> getPoint;

struct wire {
	vector<tpl> lines;
	point last;

	void addLine(string d, int w) {
		bool h = d[0] == 'R' or d[0] == 'L';
		int del = stoi(d.substr(1), nullptr, 10) * (d[0] == 'L' or d[0] == 'D' ? -1 : 1);
		point next = last + (h ? point(del, 0) : point(0, del));
		next.dist = last.dist + abs(del);
		if (h) {
			lines.emplace_back(min(last.x, next.x), last.y, -INF, h, id, w);
			lines.emplace_back(max(last.x, next.x), last.y,  INF, h, id, w);
		}
		else lines.emplace_back(last.x, min(last.y, next.y), max(last.y, next.y), h, id, w);
		id++;
		getPoint.push_back(last);
		last = next;
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
	w.addLine(x, t);
};

int dist(point a, point b) {
	point del = a - b;
	return abs(del.x) + abs(del.y);
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	wire w1, w2;
	string s, t;
	getline(cin, s);
	getline(cin, t);
	conswire(s, w1, 0);
	conswire(t, w2, 1);

	vector<tpl> sl;
	sl.insert(sl.end(), iter(w1.lines));
	sl.insert(sl.end(), iter(w2.lines));
	sort(iter(sl));
	set<line> hs;
	int ans = INF;
	for (auto [x, y1, y2, h, id, w] : sl) {
		if (h) {
			if (y2 == -INF) hs.emplace(y1, w, id);
			else {
				auto it = hs.find(line(y1, w, id));
				hs.erase(it);
			}
		}
		else {
			point p = getPoint[id];
			auto l = lower_bound(iter(hs), line(y1, -1, 0));
			auto u = upper_bound(iter(hs), line(y2, 10, 0));
			for (auto it = l;it != u;it++) {
				int hy, hid, hw;
				tie(hy, hw, hid) = *it;
				point hp = getPoint[hid];
				if (hw != w) {
					point cross(x, hy);
					int dis = p.dist + dist(p, cross) + hp.dist + dist(hp, cross);
					if (dis) ans = min(ans, dis);
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}


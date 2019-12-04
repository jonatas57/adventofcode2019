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

struct point {
	int x, y;

	point(int x = 0, int y = 0) : x(x), y(y) {}

	point operator-(point p) {
		return point(x - p.x, y - p.y);
	}
	point operator+(point p) {
		return point(x + p.x, y + p.y);
	}
	bool operator<(const point& p) const {
		return x == p.x ? y < p.y : x < p.x;
	}
	bool operator!=(const point& p) const {
		return x != p.x or y != p.y;
	}
};

int dist(point a, point b) {
	point del = a - b;
	return abs(del.x) + abs(del.y);
}

struct graph {
	int size;
	map<int, mii> adj[2];
	map<point, int> conv;

	graph() : size(1) {}
	void addEdge(point a, point b, int w) {
		addNode(a, w);
		addNode(b, w);
		if (conv[a] == conv[b]) return;
			adj[w][conv[a]][conv[b]] = dist(a, b);
	}
	void addNode(point a, int w) {
		if (conv[a] or !(a.x | a.y)) return;
		conv[a] = size++;
	}
	void remEdge(point a, point b, int w) {
		adj[w][conv[a]].erase(conv[b]);
	}
} g;

typedef tuple<int, int, int, int, int, int> tpl; // x, y1, y2, hor, wire, id
typedef tuple<int, int, int> line; // y, wire, id

vector<pair<point, point>> getPoints;
int id = 0;

struct wire {
	vector<tpl> lines;
	point last;

	void addLine(string d, int w) {
		bool h = d[0] == 'R' or d[0] == 'L';
		int del = stoi(d.substr(1), nullptr, 10) * (d[0] == 'L' or d[0] == 'D' ? -1 : 1);
		point next = last + (h ? point(del, 0) : point(0, del));
		getPoints.emplace_back(last, next);
		g.addEdge(last, next, w);
		if (h) {
			lines.emplace_back(min(last.x, next.x), last.y, -INF, h, w, id);
			lines.emplace_back(max(last.x, next.x), last.y,  INF, h, w, id);
		}
		else lines.emplace_back(last.x, min(last.y, next.y), max(last.y, next.y), h, w, id);
		id++;
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

vi dijkstra(int w) {
	vb visit(g.size, false);
	vi dist(g.size, INF);
	queue<int> q;
	visit[0] = true;
	dist[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (auto& [y, v] : g.adj[w][x]) {
			if (!visit[y]) {
				visit[y] = true;
				q.push(y);
			}
			dist[y] = min(dist[y], dist[x] + v);
		}
	}
	return dist;
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
	vector<line> hs;
	vi crosses;
	int ans = INF;
	for (auto [x, y1, y2, h, w, id] : sl) {
		if (h) {
			if (y2 == -INF) hs.emplace_back(y1, w, id);
			else {
				int i;
				for (i = 0;i < hs.size();i++) {
					if (get<2>(hs[i]) == id) break;
				}
				hs.erase(hs.begin() + i);
			}
		}
		else {
			auto l = lower_bound(iter(hs), line(y1, -1, 0));
			auto u = upper_bound(iter(hs), line(y2, 10, 0));
			point p, q, cross;
			tie(p, q) = getPoints[id];
			point p2 = p, q2 = q, hp, hq;
			for (auto it = l;it != u;it++) {
				int hy, hw, hid;
				tie(hy, hw, hid) = *it;
				tie(hp, hq) = getPoints[hid];
				if (abs(hid - id) == 1 or (!x and !hy)) continue;
				cross = {x, hy};
				(p < q ? g.addEdge(p, cross, w) : g.addEdge(cross, q, w));
				(p < q ? p = cross : q = cross);
				g.addEdge(hp, cross, hw);
				g.addEdge(cross, hq, hw);
				if (hp != cross and cross != hq) g.remEdge(hp, hq, hw);
				(hp < hq ? getPoints[hid].first : getPoints[hid].second) = cross;
				if (w != hw) crosses.push_back(g.conv[cross]);
			}
			if (p != p2 or q != q2) {
				(p < q ? g.addEdge(cross, q, w) : g.addEdge(p, cross, w));
				g.remEdge(p2, q2, w);
			}
		}
		sort(iter(hs));
	}
	auto d0 = dijkstra(0), d1 = dijkstra(1);
	each(c, crosses) {
		ans = min(ans, d0[c] + d1[c]);
	}
	cout << ans << endl;
	return 0;
}


#include <bits/stdc++.h>
#include "../intcode.hpp"

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

map<int, mii> mapa;
map<int, map<int, bool>> vis;

struct droid {
	prog p;
	int x, y;

	droid(char* file) : p(file, INPUT_BUFFER | OUTPUT_BUFFER, 1), x(0), y(0) {
		mapa[x][y] = 1;
		vis[x][y] = true;
	}

	void search() {
		vloop(dir, 4) {
			int nx = x + (dir == 3) - (dir == 2);
			int ny = y + (dir == 0) - (dir == 1);
			if (vis[nx][ny]) continue;
			vis[nx][ny] = true;
			int out = move(dir + 1);
			mapa[nx][ny] = out;
			if (out) {
				swap(x, nx), swap(y, ny);
				search();
				move((dir ^ 1) + 1);
				swap(x, nx), swap(y, ny);
			}
		}
	}

	int move(int dir) {
		p << dir;
		p.exec();
		ll ans;
		p >> ans;
		return ans;
	}
};

struct graph {
	int size;
	map<int, mii> conv;
	vector<list<int>> adj;

	graph() : size(1), adj(1) {
		conv[0][0];
	}

	int addNode(int x, int y) {
		if (!(x | y) or conv[x][y]) return conv[x][y];
		adj.emplace_back();
		return conv[x][y] = size++;
	}

	void addEdge(int x, int y, int a, int b) {
		int p = addNode(x, y);
		int q = addNode(a, b);
		adj[p].push_back(q);
		adj[q].push_back(p);
	}
};

vi dist;

void bfs(graph& g, int st) {
	vb visit(g.size, false);
	dist.assign(g.size, INF);
	queue<int> q;
	visit[st] = true;
	dist[st] = 0;
	q.push(st);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		each(v, g.adj[u]) {
			if (!visit[v]) {
				visit[v] = true;
				q.push(v);
				dist[v] = dist[u] + 1;
			}
		}
	}
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);cerr.tie(NULL);

	if (argc == 1) cerr << "input file needed" << endl, exit(0);

	droid d(argv[1]);
	d.search();
	mapa[0][0] = 4;
	int goal;
	graph g;
	for (auto& [x, m] : mapa) {
		for (auto& [y, t] : m) {
			if (!t) continue;
			if (mapa[x - 1][y]) g.addEdge(x, y, x - 1, y);
			if (mapa[x][y - 1]) g.addEdge(x, y, x, y - 1);
			if (t == 2) goal = g.conv[x][y];
		}
	}
	bfs(g, goal);
	int ans = 0;
	each(x, dist) {
		if (x != INF) ans = max(ans, x);
	}
	cout << ans << endl;
	return 0;
}

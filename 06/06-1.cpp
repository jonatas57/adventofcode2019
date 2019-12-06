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

struct graph {
	int size;
	map<int, list<int>> adj;
	map<string, int> conv;

	graph() : size(1) {
		addNode("COM");
	}
	void addNode(string s) {
		if (s == "COM" or conv[s]) return;
		conv[s] = size++;
	}
	void addEdge(string a, string b) {
		addNode(a);
		addNode(b);
		adj[conv[a]].push_back(conv[b]);
	}
};

vi dist;

void bfs(graph& g) {
	dist.resize(g.size, INF);
	vb visit(g.size, false);
	queue<int> q;
	dist[0] = 0;
	visit[0] = true;
	q.push(0);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		each(y, g.adj[x]) {
			if (!visit[y]) {
				visit[y] = true;
				q.push(y);
			}
			dist[y] = dist[x] + 1;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	string s;
	graph g;
	while (cin >> s) {
		int f = s.find(')');
		g.addEdge(s.substr(0, f), s.substr(f + 1));
	}
	bfs(g);
	int ans = 0;
	each(d, dist) {
		if (d != INF) ans += d;
	}
	cout << ans << endl;
	return 0;
}


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

vector<string> mapa;
map<string, ii> lastPort;
map<ii, ii> portals;
ii start, finish;
int w, h;

void setPortal(int x, int y, int dir) {
	ii here(x, y);
	x += (dir == 2) - (dir == 0);
	y += (dir == 1) - (dir == 3);
	string s = "";
	s += mapa[x][y];
	x += (dir == 2) - (dir == 0);
	y += (dir == 1) - (dir == 3);
	if (dir == 0 or dir == 3) {
		s += s[0];
		s[0] = mapa[x][y];
	}
	else s += mapa[x][y];
	ii p = lastPort[s];
	if (p.first | p.second) {
		portals[p] = here;
		portals[here] = p;
	}
	else if (s == "AA") start = here;
	else if (s == "ZZ") finish = here, portals[here] = {INF, INF};
	else lastPort[s] = here;
}

bool isouter(ii a) {
	int x, y;
	tie(x, y) = a;
	return x == 2 or y == 2 or x == h - 3 or y == w - 3;
}

tuple<int, int, int> getPortal(int x, int y, int depth) {
	int a, b;
	ii p(x, y);
	tie(a, b) = portals[p];
	if ((p == start or p == finish) and depth) return {x, y, depth};
	if (isouter(p) and !depth) return {x, y, depth};
	depth += isouter(p) ? -1 : 1;
	return {a, b, depth};
}

#define MAXDEPTH 200

int bfs() {
	int x, y;
	tie(x, y) = start;
	vector<vector<bitset<MAXDEPTH>>> visit(h, vector<bitset<MAXDEPTH>>(w, 0));
	map<int, map<int, mii>> dist;
	queue<tuple<int, int, int>> q;
	visit[x][y][0] = 1;
	dist[x][y][0] = 0;
	q.emplace(start.first, start.second, 0);
	int depth;
	while (!q.empty()) {
		tie(x, y, depth) = q.front();/*@*/
		if (depth > MAXDEPTH) {
			cerr << "ERRO" << endl;
			exit(0);
		}/*@*/
		q.pop();
		if (make_pair(x, y) == finish and !depth) break;
		vloop(dir, 4) {
			int nx = x + (dir == 2) - (dir == 0), ny = y + (dir == 1) - (dir == 3), d = depth;
			if (mapa[nx][ny] == '#') continue;
			if (isupper(mapa[nx][ny])) tie(nx, ny, d) = getPortal(x, y, depth);
			if (!visit[nx][ny][d]) {
				visit[nx][ny][d] = 1;
				dist[nx][ny][d] = dist[x][y][depth] + 1;
				q.emplace(nx, ny, d);
			}
		}
	}
	tie(x, y) = finish;
	return dist[x][y][0];
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	string s;
	while (getline(cin, s)) mapa.push_back(s);
	h = mapa.size(), w = mapa[0].length();
	for (int i = 0;i < h;i++) {
		char c;
		for (int j = 0;(c = mapa[i][j]);j++) {
			if (c != '.') continue;
			vloop(dir, 4) {
				int x = i + (dir == 2) - (dir == 0), y = j + (dir == 1) - (dir == 3);
				if (isupper(mapa[x][y])) {
					setPortal(i, j, dir);
				}
			}
		}
	}
	cout << bfs() << endl;
	return 0;
}

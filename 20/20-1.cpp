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
	else if (s == "ZZ") finish = here;
	else lastPort[s] = here;
}

int bfs() {
	int x, y;
	tie(x, y) = start;
	vector<vb> visit(h, vb(w, false));
	vector<vi> dist (h, vi(w, INF));
	queue<ii> q;
	visit[x][y] = true;
	dist[x][y] = 0;
	q.push(start);
	while (!q.empty()) {
		tie(x, y) = q.front();
		q.pop();
		vloop(dir, 4) {
			int nx = x + (dir == 2) - (dir == 0), ny = y + (dir == 1) - (dir == 3);
			if (mapa[nx][ny] == '#') continue; 
			if (isupper(mapa[nx][ny])) tie(nx, ny) = portals[make_pair(x, y)];
			if (!(nx | ny)) continue;
			if (!visit[nx][ny]) {
				visit[nx][ny] = true;
				dist[nx][ny] = dist[x][y] + 1;
				q.emplace(nx, ny);
			}
		}
	}
	tie(x, y) = finish;
	return dist[x][y];
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


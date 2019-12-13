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

wstring screenFont = L".█▄█o";
int score = 0;

void printScreen(auto& screen) {
	//loop(13) cout << endl;
	loop(23) {
		wcout << endl;
		vloop(j, 45) {
			wcout << screenFont[screen[j][i]];
		}
	}
	wcout << "     score: " << score << endl;
}

void setScreen(auto& screen, vi& out) {
	screen[out[0]][out[1]] = out[2];
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "pt_BR.UTF-8");
	prog p(argv[1], true, 3);
	map<int, mii> screen;
	int x = 0, y = 0;
	while (true) {
		p.exec();
		auto out = p.getOutput();
		x = out[0], y = out[1];
		if (x == -1 and y == 0) {
			score = out[2];
			break;
		}
		screen[x][y] = out[2];
	}
	printScreen(screen);
	p.unpause();
	while (!p.stopped()) {
		if (p.isPaused()) {
			int x;
			cin >> x;
			p.setInput(x);
		}
		else {
			p.exec();
			auto out = p.getOutput();
			if (out[0] == -1) score = out[2], wcout << "score " << score << endl;
			else setScreen(screen, out);
		}
		printScreen(screen);
	}
	return 0;
}


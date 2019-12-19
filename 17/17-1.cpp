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

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	prog p(argv[1], OUTPUT_BUFFER, 1);

	vector<string> mapa;
	string s = "";
	while (p.canRun()) {
		p.exec();
		char c;
		p >> c;
		if (c == '\n') {
			mapa.push_back(s);
			s = "";
		}
		else s += c;
	}
	int sum = 0;
	for (size_t i = 1;i < mapa.size() - 1;i++) {
		for (size_t j = 1;j < mapa[0].length() - 1;j++) {
			if (mapa[i][j] == '.') continue;
			int cnt = 0;
			vloop(dir, 4) {
				int x = i + (dir == 2) - (dir == 0);
				int y = j + (dir == 1) - (dir == 3);
				if (mapa[x][y] == '#') cnt++;
			}
			if (cnt == 4) {
				sum += i * j;
			}
		}
	}
	cout << sum << endl;
	return 0;
}


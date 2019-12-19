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

	prog p(argv[1], INPUT_BUFFER | OUTPUT_BUFFER, 1);

	string s = "";
	while (!p.stopped()) {
		if (p.hasOutput()) {
			char c;
			p >> c;
			if (c == '\n') {
				s += c;
				cout << s;
				s = "";
			}
			else s += c;
		}
		if (p.isPaused()) {
			char c = getchar();
			p.setInput(c);
		}
		p.exec();
	}
	ll ans;
	p >> ans;
	cout << ans << endl;
	return 0;
}


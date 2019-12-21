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

char* file;

bool test(int x, int y) {
	prog p(file, INPUT_BUFFER | OUTPUT_BUFFER);
	p << x;
	p << y;
	p.exec();
	ll ans;
	p >> ans;
	return ans;
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	file = argv[1];
	bool found = false;
	int x, y, size = 100;
	for (int i = 0, j = 0;not found;) {
		if (test(i + size - 1, j)) {
			if (test(i, j + size - 1)) {
				x = i;
				y = j;
				found = true;
			}
			else i++;
		}
		else j++;
	}
	cout << 10000 * x + y << endl;
	return 0;
}


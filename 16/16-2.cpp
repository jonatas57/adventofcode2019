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

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	char c;
	vi inout[2];
	int input = 0, output = 1; 
	while (cin >> c) {
		inout[input].push_back(c - '0');
	}
	int size = inout[input].size();
	int pos = 0;
	loop(7) pos = 10 * pos + inout[input][i];
	int x = (size * 10000 - pos) / size;
	loop(x) inout[input].insert(inout[input].end(), inout[input].begin(), inout[input].begin() + size);
	inout[output].assign(inout[input].size(), 0);
	pos %= size;
	size = inout[input].size();
	loop(100) {
		inout[output][size - 1] = inout[input][size - 1];
		for (int i = size - 2;i >= 0;i--) {
			inout[output][i] = abs(inout[output][i + 1] + inout[input][i]) % 10;
		}
		swap(input, output);
	}
	loop(8) {
		cout << inout[input][pos + i];
	}
	cout << endl;
	return 0;
}


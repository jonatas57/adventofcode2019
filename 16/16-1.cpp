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

vi basePattern = {0, 1, 0, -1};

auto genPattern(int n) {
	vector<vi> pat;
	for (int i = 1;i <= n;i++) {
		int id = 0;
		pat.emplace_back();
		for (int j = 1;j <= n;j++) {
			if (j % i == 0) {
				id++;
				if (id == 4) id = 0;
			}
			pat[i - 1].push_back(basePattern[id]);
		}
	}
	return pat;
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	char c;
	vi inout[2];
	int input = 0, output = 1; 
	while (cin >> c) {
		inout[input].push_back(c - '0');
		inout[output].push_back(0);
	}
	int size = inout[input].size();
	auto pat = genPattern(size);
	loop(100) {
		loop(size) {
			int sum = 0;
			vloop(j, size) {
				sum += inout[input][j] * pat[i][j];
			}
			inout[output][i] = abs(sum) % 10;
		}
		swap(input, output);
	}
	loop(8) {
		cout << inout[input][i];
	}
	cout << endl;
	return 0;
}


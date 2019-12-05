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

vi args(3);

int add() {
	return args[0] + args[1];
}

int mult() {
	return args[0] * args[1];
}

int input() {
	int x;
	cin >> x;
	return x;
}

int output() {
	cout << args[0] << endl;
	return args[0];
}

typedef int (*fn)();

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	
	vi par = {0, 4, 4, 2, 2};

	fn fs[] = {add, add, mult, input, output};
	ifstream ss(argv[1]);
	int x;
	char c;
	vi prog;
	while (ss >> x >> c) prog.push_back(x);
	int del, l = prog.size();
	for (int i = 0;i < l and prog[i] != 99;i += del) {
		int op = prog[i] % 100, mode = prog[i] / 100;
		del = par[op];
		vloop(j, del - 1) {
			int m = mode % 10;
			args[j] = (m ? prog[i + j + 1] : prog[prog[i + j + 1]]);
			mode /= 10;
		}
		prog[prog[i + del - 1]] = fs[op]();
	}
	return 0;
}


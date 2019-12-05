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
vi prog;
int ptr, del;

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

int jumpif() {
	if (args[0]) {
		ptr = args[1];
		del = 0;
	}
	return 0;
}

int jumpnotif() {
	if (!args[0]) {
		ptr = args[1];
		del = 0;
	}
	return 0;
}

int lessthan() {
	return args[0] < args[1];
}

int equals() {
	return args[0] == args[1];
}

typedef int (*fn)();

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	
	vi par = {0, 4, 4, 2, 2, 3, 3, 4, 4};

	fn fs[] = {add, add, mult, input, output, jumpif, jumpnotif, lessthan, equals};
	ifstream ss(argv[1]);
	int x;
	char c;
	while (ss >> x){
		prog.push_back(x);
		ss >> c/*@*/, cerr << x << " "/*@*/;
	}
	int l = prog.size();
	for (ptr = 0;ptr < l and prog[ptr] != 99;ptr += del) {
		int op = prog[ptr] % 100, mode = prog[ptr] / 100;
		del = par[op];/*@*/cerr << op << " ";/*@*/
		vloop(j, del - 1) {
			int m = mode % 10;
			args[j] = (m ? prog[ptr + j + 1] : prog[prog[ptr + j + 1]]);
			mode /= 10;/*@*/cerr << args[j] << " ";
		}/*@*/cerr<<endl;/*@*/
		int pos = ptr + del - 1;
		if (op == 5 or op == 6) fs[op]();
		else prog[prog[pos]] = fs[op]();
	}
	return 0;
}


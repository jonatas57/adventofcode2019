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

vector<ll> prog;
ll ptr, del;
bool useBuffer = false;
ll buffer[2] = {0, 0}, pos = 0, relBase = 0, memsize;
map<int, ll> extMem;

ll get(ll pos, int mode = 0) {
	switch (mode) {
		case 0:
		pos = prog[pos];
		break;
		case 2:
		pos = prog[pos] + relBase;
		break;
		default:
		break;
	}
	return pos < memsize ? prog[pos] : extMem[pos];
}

void Set(ll pos, ll val) {
	(pos < memsize ? prog[pos] : extMem[pos]) = val;
}

void add(vector<ll>& args) {
	Set(args[2], args[0] + args[1]);
}

void mult(vector<ll>& args) {
	Set(args[2], args[0] * args[1]);
}

void input(vector<ll>& args) {
	ll x;
	if (useBuffer) x = buffer[pos], pos = 1; 
	else cin >> x;
	Set(args[0], x);
}

void output(vector<ll>& args) {
	if (useBuffer) buffer[1] = get(args[0]);
	else cout << args[0] << endl;
}

void jumpif(vector<ll>& args) {
	if (args[0]) {
		ptr = args[1];
		del = 0;
	}
}

void jumpnotif(vector<ll>& args) {
	if (!args[0]) {
		ptr = args[1];
		del = 0;
	}
}

void lessthan(vector<ll>& args) {
	Set(args[2], args[0] < args[1]);
}

void equals(vector<ll>& args) {
	Set(args[2], args[0] == args[1]);
}

void offset(vector<ll>& args) {
	relBase += args[0];
}

typedef void (*fn)(vector<ll>&);
fn fs[] = {add, add, mult, input, output, jumpif, jumpnotif, lessthan, equals, offset};
vi dels = {0, 4, 4, 2, 2, 3, 3, 4, 4, 2};

void exec() {
	for (;ptr < memsize and prog[ptr] != 99;ptr += del) {
		int op = prog[ptr] % 100, mode = prog[ptr] / 100;
		del = dels[op];
		vector<ll> args;
		int m = 0;
		vloop(j, del - 1) {
			m = mode % 10;
			args.push_back(get(ptr + j + 1, m));
			mode /= 10;
		}
		if ((op > 6 or op < 4) and op != 9) args[del - 2] = prog[ptr + del - 1] + (m == 2 ? relBase : 0);
		fs[op](args);
	}
}

void readProg(char* file) {
	ifstream ss(file);
	ll x;
	char c;
	while (ss >> x){
		prog.push_back(x);
		ss >> c;
	}
	memsize = prog.size();
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	
	readProg(argv[1]);
	exec();
	return 0;
}


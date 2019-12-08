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

vi prog;
int ptr, del;
bool useBuffer = true;
int buffer[2] = {0, 0}, pos = 0;

void add(vi& args) {
	prog[args[2]] = args[0] + args[1];
}

void mult(vi& args) {
	prog[args[2]] = args[0] * args[1];
}

void input(vi& args) {
	int x;
	if (useBuffer) x = buffer[pos], pos ^= 1; 
	else cin >> x;
	prog[args[0]] = x;
}

void output(vi& args) {
	if (useBuffer) buffer[1] = prog[args[0]];
	else cout << prog[args[0]] << endl;
}

void jumpif(vi& args) {
	if (args[0]) {
		ptr = args[1];
		del = 0;
	}
}

void jumpnotif(vi& args) {
	if (!args[0]) {
		ptr = args[1];
		del = 0;
	}
}

void lessthan(vi& args) {
	prog[args[2]] = args[0] < args[1];
}

void equals(vi& args) {
	prog[args[2]] = args[0] == args[1];
}

typedef void (*fn)(vi&);
fn fs[] = {add, add, mult, input, output, jumpif, jumpnotif, lessthan, equals};
vi dels = {0, 4, 4, 2, 2, 3, 3, 4, 4};

vector<vi> getPerm() {
	vector<vi> ans;
	vloop(a, 5) vloop(b, 5) vloop(c, 5) vloop(d, 5) vloop(e, 5) {
		set<int> aux({a, b, c, d, e});
		if (aux.size() == 5) {
			ans.push_back({a, b, c, d, e});
		}
	}
	return ans;
}

void exec() {
	int l = prog.size();
	for (ptr = 0;ptr < l and prog[ptr] != 99;ptr += del) {
		int op = prog[ptr] % 100, mode = prog[ptr] / 100;
		del = dels[op];
		vi args;
		vloop(j, del - 1) {
			int m = mode % 10;
			args.push_back(m ? prog[ptr + j + 1] : prog[prog[ptr + j + 1]]);
			mode /= 10;
		}
		if (op > 6 or op < 5) args[del - 2] = prog[ptr + del - 1];
		fs[op](args);
	}
}

int run(vi& v) {
	buffer[1] = 0;
	each(x, v) {
		buffer[0] = x;
		exec();
	}
	return buffer[1];
}

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	
	ifstream ss(argv[1]);
	int x;
	char c;
	while (ss >> x){
		prog.push_back(x);
		ss >> c;
	}
	int ans = 0;
	each(v, getPerm()) {
		ans = max(ans, run(v));
	}
	cout << ans << endl;
	return 0;
}


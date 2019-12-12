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

class prog {
	vector<ll> mem;
	map<ll, ll> extMem;
	bool useBuffer;
	int stopAfterOutput, memSize;
	int buffer[3] = {0, 0, 0}, dels[10] = {0, 4, 4, 2, 2, 3, 3, 4, 4, 2};
	int ptr, relativeBase, bufferPos, step;
	bool eop;

	ll access(ll pos) {
		return pos < memSize ? mem[pos] : extMem[pos];
	}

	public:
	prog(char* file, bool ub = false, int sao = 0) : useBuffer(ub), stopAfterOutput(sao), ptr(0), relativeBase(0), bufferPos(0), step(0), eop(false) {
		ifstream fin(file);
		ll x;
		char c;
		while (fin >> x) {
			mem.push_back(x);
			fin >> c;
		}
		memSize = mem.size();
	}

	ii parse(int op) {
		return make_pair(op % 100, op / 100);
	}

	void set(ll x, ll y) {
		(x < memSize ? mem[x] : extMem[x]) = y;
	}

	ll get(ll pos, int mode = 0) {
		switch (mode) {
			case 0:
			pos = access(pos);
			break;
			case 2:
			pos = access(pos) + relativeBase;
			break;
			default:
			break;
		}
		return access(pos);
	}

	void add(vector<ll>& args) {
		set(args[2], args[0] + args[1]);
	}

	void mult(vector<ll>& args) {
		set(args[2], args[1] * args[0]);
	}

	void input(vector<ll>& args) {
		ll x;
		if (useBuffer) x = buffer[2];
		else cin >> x;
		set(args[0], x);
	}

	void output(vector<ll>& args) {
		if (useBuffer) buffer[bufferPos] = args[0], bufferPos ^= 1;
		else cout << args[0] << endl;
	}

	void jumpif(vector<ll>& args) {
		if (args[0]) {
			step = 0;
			ptr = args[1];
		}
	}

	void jumpifnot(vector<ll>& args) {
		if (!args[0]) {
			step = 0;
			ptr = args[1];
		}
	}

	void lessthan(vector<ll>& args) {
		set(args[2], args[0] < args[1]);
	}

	void equals(vector<ll>& args) {
		set(args[2], args[0] == args[1]);
	}

	void offset(vector<ll>& args) {
		relativeBase += args[0];
	}

	void call(size_t i, vector<ll>& args);

	void exec() {
		int op, mode, cnt = 0;
		for (;access(ptr) != 99 and (!stopAfterOutput or stopAfterOutput != cnt);ptr += step) {
			tie(op, mode) = parse(mem[ptr]);
			step = dels[op];
			vector<ll> args;
			int m = 0;
			for (int i = 1;i < step;i++) {
				m = mode % 10;
				mode /= 10;
				args.push_back(get(ptr + i, m));
			}
			if ((op < 4 or op > 6) and op != 9) args[step - 2] = access(ptr + step - 1) + (m == 2 ? relativeBase : 0);
			call(op, args);
			if (stopAfterOutput and op == 4) cnt++;
		}
		if (access(ptr) == 99) eop = true; 
	}

	void bufset(int pos, ll val) {
		buffer[pos] = val;
	}

	ll bufget(int pos) {
		return buffer[pos];
	}

	bool canRun() {
		return !eop;
	}
};

typedef void (prog::*fn)(vector<ll>& args);
vector<fn> fs = {&prog::add, &prog::mult, &prog::input, &prog::output, &prog::jumpif, &prog::jumpifnot, &prog::lessthan, &prog::equals, &prog::offset};

void prog::call(size_t i, vector<ll>& args) {
	if (i > fs.size()) cout << "function not found" << endl, exit(0);
	(this->*fs[i - 1])(args);
}

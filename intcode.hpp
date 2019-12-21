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

#define INPUT_BUFFER  1
#define OUTPUT_BUFFER 2

#define INT_MODE   0
#define ASCII_MODE 1

class prog {
	vector<ll> mem;
	map<ll, ll> extMem;
	int useBuffer, stopAfterOutput, memSize;
	queue<ll> inBuffer, outBuffer;
	vi dels = {0, 4, 4, 2, 2, 3, 3, 4, 4, 2};
	int ptr, relativeBase, step;
	bool eop, waitInput, paused, outputReady, asciiMode;
	int outputCnt;

	ll access(ll pos) {
		return pos < memSize ? mem[pos] : extMem[pos];
	}

	public:
	prog(char* file, int ub = 0, int sao = 0, int mode = INT_MODE) : 
	useBuffer(ub),
	stopAfterOutput(sao), 
	ptr(0), 
	relativeBase(0), 
	step(0), 
	eop(false),
	waitInput(true),
	paused(false),
	outputReady(false),
	asciiMode(mode),
	outputCnt(0) {
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
		if (useBuffer & INPUT_BUFFER) {
			if (waitInput) {
				paused = true;
			}
			else {
				x = inBuffer.front();
				inBuffer.pop();
				waitInput = inBuffer.empty();
			}
		}
		else {
			if (asciiMode) x = getchar();
			else cin >> x;
		}
		set(args[0], x);
	}

	void output(vector<ll>& args) {
		if (useBuffer & OUTPUT_BUFFER) {
			outBuffer.push(args[0]);
			outputReady = true;
		}
		else {
			if (asciiMode) cout << (char)args[0];
			else cout << args[0] << endl;
		}
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
		paused = false;
		int op, mode;
		if (stopAfterOutput == outputCnt) outputCnt = 0;
		for (;access(ptr) != 99 and (!stopAfterOutput or stopAfterOutput != outputCnt);ptr += step) {
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
			if (op == 3 and paused) break;
			else if (stopAfterOutput and op == 4) outputCnt++;
		}
		if (access(ptr) == 99) eop = true; 
	}

	bool canRun() {
		return !eop and !paused;
	}

	bool isPaused() {
		return paused;
	}

	bool stopped() {
		return eop;
	}

	void unpause() {
		paused = false;
	}

	vector<ll> getOutput() {
		vector<ll> out;
		while (!outBuffer.empty()) {
			out.push_back(outBuffer.front());
			outBuffer.pop();
		}
		outputReady = false;
		return out;
	}

	void setInput(ll val) {
		inBuffer.push(val);
		waitInput = false;
		paused = false;
	}

	bool hasOutput() {
		return outputReady;
	}

	prog& operator<<(ll x) {
		setInput(x);
		return *this;
	}

	prog& operator>>(ll& x) {
		x = outBuffer.front();
		outBuffer.pop();
		outputReady = !outBuffer.empty();
		return *this;
	}

	prog& operator>>(char& x) {
		x = (char)outBuffer.front();
		outBuffer.pop();
		outputReady = !outBuffer.empty();
		return *this;
	}
};

typedef void (prog::*fn)(vector<ll>& args);
vector<fn> fs = {&prog::add, &prog::mult, &prog::input, &prog::output, &prog::jumpif, &prog::jumpifnot, &prog::lessthan, &prog::equals, &prog::offset};

void prog::call(size_t i, vector<ll>& args) {
	if (i > fs.size()) cout << "function not found" << endl, exit(0);
	(this->*fs[i - 1])(args);
}


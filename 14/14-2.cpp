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

struct subs {
	int qtd;
	string name;
	subs() {};
	subs(string s) {
		int x = s.find(' ');
		qtd = stoi(s.substr(0, x), nullptr, 10);
		name = s.substr(x + 1);
	}
};

vector<string> split(string s, string p) {
	int last = -1;
	bool stop = false;
	vector<string> ans;
	while (!stop) {
		size_t x = s.find(p, last + 1);
		if (x == string::npos) {
			ans.push_back(s.substr(last + 1));
			break;
		}
		else {
			ans.push_back(s.substr(last + 1, x - last - 1));
		}
		last = x + 1;
	}
	return ans;
}

struct reac {
	subs prod;
	vector<subs> reags;
	reac() {}
	reac(string s) {
		int x = s.find(" => ");
		prod = subs(s.substr(x + 4));
		each(r, split(s.substr(0, x), ", ")) {
			reags.emplace_back(r);
		}
	}
};

map<string, ll> disp;
map<string, reac> reacs;

vector<string> execReac(reac& r, ll qtd) {
	vector<string> neg;
	disp[r.prod.name] += qtd * r.prod.qtd;
	each(p, r.reags) {
		disp[p.name] -= qtd * p.qtd;
		if (disp[p.name] < 0) neg.push_back(p.name);
	}
	return neg;
}

#define MAXORE 1000000000000

void reset() {
	disp.clear();
	disp["ORE"] = MAXORE;
}

bool check(ll x) {
	reset();
	queue<string> q;
	q.push("FUEL");
	disp["FUEL"] = -x;
	while (!q.empty()) {
		string p = q.front();
		q.pop();
		if (p == "ORE" or disp[p] > 0) continue;

		reac r = reacs[p];
		ll qtd = (-disp[p] + r.prod.qtd - 1) / r.prod.qtd;
		auto aux = execReac(r, qtd);
		each(a, aux) q.push(a);
	}
	return disp["ORE"] > 0;
}

ll bb(ll l, ll r) {
	if (l == r) return l;
	ll mid = avg(l, r);
	if (check(mid)) return bb(mid + 1, r);
	else return bb(l, mid);
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	string s;
	while (getline(cin, s)) {
		reac r(s);
		reacs[r.prod.name] = r;
	}
	cout << bb(0, MAXORE) - 1 << endl;
	return 0;
}

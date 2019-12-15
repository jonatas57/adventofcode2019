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

map<string, int> disp;
map<string, reac> reacs;

vector<string> execReac(reac& r, int qtd) {
	vector<string> neg;
	disp[r.prod.name] += qtd * r.prod.qtd;
	each(p, r.reags) {
		disp[p.name] -= qtd * p.qtd;
		if (disp[p.name] < 0) neg.push_back(p.name);
	}
	return neg;
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	string s;
	while (getline(cin, s)) {
		reac r(s);
		reacs[r.prod.name] = r;
	}
	queue<string> q;
	q.push("FUEL");
	disp["FUEL"] = -1;
	while (!q.empty()) {
		string p = q.front();
		q.pop();
		if (p == "ORE" or disp[p] > 0) continue;

		reac r = reacs[p];
		int qtd = (-disp[p] + r.prod.qtd - 1) / r.prod.qtd;
		auto aux = execReac(r, qtd);
		each(a, aux) q.push(a);
	}
	cout << -disp["ORE"] << endl;
	return 0;
}

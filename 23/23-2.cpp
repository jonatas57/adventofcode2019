#include <bits/stdc++.h>
#include "../intcode.hpp"

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

bool flag = true;
int ans;

bitset<50> idleness;

struct computer {
	ll address;
	prog nic;
	queue<ll> received;

	computer(ll add, char* file) : address(add), nic(file, INPUT_BUFFER | OUTPUT_BUFFER) {
		nic << add;
	}
	auto exec() {
		if (received.empty()) {
			received.push(-1);
			idleness.set(address);
		}
		while(!received.empty()) {
			nic << received.front();
			received.pop();
		}
		nic.exec();
		vector<tuple<ll, ll, ll>> packets;
		while (nic.hasOutput()) {
			ll c, x, y;
			nic >> c >> x >> y;
			packets.emplace_back(c, x, y);
		}
		return packets;
	}

	void receive(ll x, ll y) {
		idleness.reset(address);
		received.push(x);
		received.push(y);
	}
};

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	if (argc < 2) {
		cerr << "input file needed" << endl;
		exit(0);
	}

	vector<computer> comps;
	loop(50) comps.emplace_back(i, argv[1]);
	pair<ll, ll> nat;
	map<ll, bool> sent;
	while (flag) {
		for (int i = 0;i < 50 and flag;i++) {
			auto ps = comps[i].exec();
			if (ps.empty()) continue;
			for (auto& [c, x, y] : ps) {
				if (c == 255) {
					nat = {x, y};
					continue;
				}
				comps[c].receive(x, y);
			}
		}
		if (idleness.all()) {
			comps[0].receive(nat.first, nat.second);
			if (sent[nat.second]) flag = false, ans = nat.second;
			sent[nat.second] = true;
		}
	}
	cout << ans << endl;
	return 0;
}


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

const int mod = 10007;

void cut(ll& card, ll x) {
	card -= x;
	if (card < 0) card += mod;
	else if (card > mod) card -= mod;
}

void increment(ll& card, ll x) {
	card *= x;
	card %= mod;
}

void newStack(ll& card) {
	card = mod - card - 1;
}

int main() {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	ll card = 2019;
	string s;
	while (getline(cin, s)) {
		if (s[0] == 'c') {
			ll x = stoi(s.substr(4), nullptr, 10);
			cut(card, x);
		}
		else if (s[5] == 'i') {
			newStack(card);
		}
		else {
			ll x = stoi(s.substr(20), nullptr, 10);
			increment(card, x);
		}
	}
	cout << card << endl;
	return 0;
}


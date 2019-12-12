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

int cmp(int a, int b) {
	return a == b ? 0 : (a < b ? 1 : -1);
}

struct vec {
	int x, y, z;
	vec(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}

	void operator+=(vec v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}
	vec diff(vec v) {
		return {cmp(x, v.x), cmp(y, v.y), cmp(z, v.z)};
	}
	int sum() {
		return abs(x) + abs(y) + abs(z);
	}
};

struct moon {
	vec pos, vel;
	moon(vec p) : pos(p), vel() {}
	int energy() {
		return pos.sum() * vel.sum();
	}
	void updateVel(vec npos) {
		vel += pos.diff(npos);
	}
	void updatePos() {
		pos += vel;
	}
};

int main() {
	vector<moon> ms;
	loop(4) {
		vec p;
		scanf("<x=%d, y=%d, z=%d>\n", &(p.x), &(p.y), &(p.z));
		ms.emplace_back(p);
	}
	loop(1000) {
		each(m, ms) {
			each(n, ms) {
				m.updateVel(n.pos);
			}
		}
		each(m, ms) m.updatePos();
	}
	int en = 0;
	each(m, ms) en += m.energy();
	cout << en << endl;
	return 0;
}


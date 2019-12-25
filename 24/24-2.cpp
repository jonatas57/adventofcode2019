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

struct level {
	vector<string> area;
	vector<vi> cnt;
	vi outerBorder;

	level(vector<string>& a) : area(a), cnt(5, vi(5, 0)) {}
	level() : area({".....", ".....", ".....", ".....", "....."}), cnt(5, vi(5, 0)) {}
	
	vi count(vi& fromOut) {
		vi aux(4, 0);
		outerBorder.assign(4, 0);
		loop(5) vloop(j, 5) {
			if (i == 2 and j == 2) continue;
			cnt[i][j] = 0;
			vloop(dir, 4) {
				int x = i + (dir == 2) - (dir == 0), y = j + (dir == 1) - (dir == 3);
				if (x < 0 or x > 4 or y < 0 or y > 4) {
					cnt[i][j] += fromOut[dir];
					if (area[i][j] == '#') outerBorder[dir]++;
				}
				else if (x == 2 and y == 2) {
					if (area[i][j] == '#') aux[dir ^ 2] = 1;
				}
				else if (area[x][y] == '#') cnt[i][j]++;
			}
		}
		return aux;
	}

	void update() {
		loop(5) vloop(j, 5) {
			if (area[i][j] == '#' and cnt[i][j] != 1) area[i][j] = '.';
			else if (area[i][j] == '.' and (cnt[i][j] == 1 or cnt[i][j] == 2)) area[i][j] = '#';
		}
	}

	void add(vi& border) {
		vloop(dir, 4) {
			int x = 2 + (dir == 2) - (dir == 0), y = 2 + (dir == 1) - (dir == 3);
			cnt[x][y] += border[dir];
		}
	}

	int countBugs() {
		int ans = 0;
		loop(5) vloop(j, 5) {
			ans += area[i][j] == '#';
		}
		return ans;
	}

	vi getBorder() { return outerBorder; }
};

struct mapa {
	deque<level> ls;
	int start, left, right;

	mapa(vector<string>& a) : start(1), left(0), right(0) {
		ls.emplace_back();
		ls.emplace_back(a);
		ls.emplace_back();
	}

	void update() {
		vi fromOut(4, 0);
		for (int i = left;i <= right;i++) {
			fromOut = (*this)[i].count(fromOut);
			if (i == right) each(x, fromOut) if (x) {
				newLevel(true);
				break;
			}
			auto border = (*this)[i].getBorder();
			if (i == 0) each(x, border) if (x) {
				newLevel(false);
				break;
			}
			(*this)[i - 1].add(border);
		}
		for (int i = left;i <= right;i++) {
			(*this)[i].update();
		}
	}

	void newLevel(bool r) {
		if (r) ls.emplace_back(), right++;
		else ls.emplace_front(), left--, start++;
	}
	
	int countBugs() {
		int ans = 0;
		for (int i = left;i <= right;i++) {
			ans += (*this)[i].countBugs();
		}
		return ans;
	}

	level& operator[](int x) {
		return ls[start + x];
	}
};

int main() {
	vector<string> input;
	string s;
	while (cin >> s) input.push_back(s);
	mapa l(input);
	loop(200) {
		l.update();
	}
	cout << l.countBugs() << endl;
	return 0;
}

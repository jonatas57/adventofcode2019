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

int w = 25, h = 6;

struct layer {
	vector<string> img;
	layer(string s) : img(h, string(w, '2')) {
		loop(h) {
			vloop(j, w) {
				img[i][j] = s[i * w + j];
			}
		}
	}
	void print(ostream& os = cout) {
		each(s, img) {
			each(c, s) os << (c == '0' ? ' ' : c);
			os << endl;
		}
	}
	void operator+=(layer& l) {
		loop(h) vloop(j, w) {
			if (img[i][j] == '2') img[i][j] = l.img[i][j];
		}
	}
};

int main(int argc, char** argv) {
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

	if (argc > 1) {
		w = stoi(argv[1], nullptr, 10);
		h = stoi(argv[2], nullptr, 10);
	}

	string s;
	cin >> s;
	int l = s.length();
	vector<layer> ls;
	for (int i = 0;i < l;i += w * h) {
		ls.emplace_back(s.substr(i, w * h));
	}
	layer img(string(w * h, '2'));
	for (auto l : ls) {
		img += l;
	}
	img.print();
	return 0;
}


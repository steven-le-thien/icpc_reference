#include<cstdio>
#include<iostream>
#include<math.h>
#include<cstring>
#include<vector>
#include<algorithm>
#include<functional>

#define FORI(n) for(int i = 0; i < n; i++)
#define FORJ(n) for(int j = 0; j < n; j++)
#define FORK(n) for(int k = 0; k < n; k++)
#define	FOR2I(a, b) for(int i = 0; i < a; i++) for(int j = 0; j < b; j++)
#define	FOR2J(a, b) for(int j = 0; j < a; j++) for(int k = 0; k < b; k++)

#define FORIT(S) for(auto it = S.cbegin(); it != S.cend(); it++)
#define clear(S) memset(S, 0, sizeof(S))
#define neg(S) memset(S, -1, sizeof(S))

#define DEBUG 0
#define MOD_NUM ((long long) (1E9 + 7))
#define MOD(a) ((long long)(((a % MOD_NUM) + MOD_NUM) % MOD_NUM))

using namespace std;

struct point{
	int x;
	int y;
	point() = default;
	point(int a, int b): x(a), y(b) {}
};

int p, q, c, m;
vector<point> avoid;
const int maxm = 4000010;
long long fac[maxm];
long long inverse[maxm];
long long facinverse[maxm];
long long ecul[maxm];

long long memoize[3050];

long long gcdExtended(long long a, long long b, long long *x, long long *y){
    if (a == 0){
        *x = 0, *y = 1;
        return 1ll * b;
    }
 
    long long x1, y1;
    long long gcd = gcdExtended(1ll * b%a, a, &x1, &y1);

    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}

long long mod_inverse(long long a){
    long long x, y;
    long long g = gcdExtended(a, MOD_NUM, &x, &y);
    if (g != 1) return -1;
    else return MOD(x);
}

long long binom(long long n, long long k){
	if(k == n || k == 0) return 1;
	if(k > n || k < 0 || n < 0) return 0;
	if(k == 1 || n == k + 1) return n;

	return MOD(1ll * MOD(1ll * MOD(1ll * fac[n]) * facinverse[k]) * facinverse[n - k]);
}

long long count_path(int idx_a, int idx_b){
	long long a = 1ll * avoid[idx_a].x;
	long long b = 1ll * avoid[idx_a].y;
	long long c1 = 1ll * avoid[idx_b].x;
	long long d = 1ll * avoid[idx_b].y;
	if((c1 + d - a - b) % 2 != 0) return 0;

	long long res = MOD((binom(c1 - a, (c1 + d - b - a)/2) - binom(c1 - a, (c1 + d - a + b)/2)));
	return res;
}

void preproc(){
	clear(fac); clear(ecul); clear(inverse); clear(facinverse); neg(memoize);

	fac[1] = 1;
	FORI(maxm) if(i >= 2) fac[i] = MOD(fac[i - 1] * i);
 	for(int i = 2; i < maxm; i++)
 		if(ecul[i] == 0)
 			for(int s = 2 * i; s < maxm; s+=i)
 				ecul[s] = 1ll * i;

 	FORI(maxm) if(i > 1) inverse[i] = (i < 4 || ecul[i] == 0) ? MOD(mod_inverse(1ll * i)) : MOD(1ll * inverse[ecul[i]] * inverse[(i) / ecul[i]]);

 	facinverse[2] = inverse[2];
	FORI(maxm) if(i >= 3) facinverse[i] = MOD(1ll * facinverse[i - 1] * inverse[i]);
}

bool compu(point a, point b) {return a.x < b.x;}

int main(){
	preproc();
	cin >> p >> q >> c >> m;
	c--;
	FORI(m) {
		int g, b; 
		cin >> g;
		cin >> b;
		if(b == 0 && g <= c + 1) {cout << 0 << endl; return 0;}
		int x = g + b - c;
		int y = g - b - c;
		if(x == p + q - c && y == p - q - c) {cout << 0 << endl; return 0;}
		if(y <= 0) continue;
		if(y > x || x >= p + q - c || x <= 1) continue;
		bool accepted = true;
		FORJ(avoid.size()) if(avoid[j].x == x && avoid[j].y == y) accepted = false;
		if(accepted) avoid.push_back(point(x, y)); 
	}
	if(p - q - c < 1) {cout << 0 << endl; return 0;}
	avoid.push_back(point(1, 1));
	avoid.push_back(point(p + q - c, p - q - c));

	sort(avoid.begin(), avoid.end(), compu);

	memoize[0] = 1;
	memoize[1] = count_path(0, 1);
	FORI(avoid.size()){
		if(i < 2) continue;
		long long res = count_path(0, i);
		FORJ(i){
			if(j == 0) continue;
			if(avoid[j].x == avoid[i].x) continue;
			res = MOD(res - MOD(memoize[j] * count_path(j, i)));
		}
		memoize[i] = res;
	}
	cout << memoize[avoid.size() - 1] << endl;
	return 0;
}
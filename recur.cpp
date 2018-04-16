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

int fac[10000000];
int inverse[10000000];

int prefsum[10000000];
long long catalan[10000000];

long long gcdExtended(long long a, long long b, long long *x, long long *y){
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return 1ll * b;
    }
 
    long long x1, y1;
    long long gcd = gcdExtended(1ll * b%a, a, &x1, &y1);

    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}

long long modInverse(long long a){
    long long x, y;
    long long g = gcdExtended(a, MOD_NUM, &x, &y);
    if (g != 1) return -1;
    else return MOD(x);
}

long long binom(int m, int b, int k1){
	long long res = 1;
	long long n = 2 * m - 2;
	long long k = m - 1; 
	FORI(k){
		res = MOD(res * (n - i));
		res = MOD(res * modInverse(i + 1));
		res = MOD(res * b); 
		res = MOD(res * k1);
	}
	res = MOD(MOD(res * k1) * 2);
	return res;
}

int main(){
	clear(fac);
	clear(inverse);
	long long n, k, a, b;
	cin >> n >> k >> a >> b;

	for(int i = 2; i <= n + 4; i++) if(fac[i] == 0) for(int j = 2 * i; j <= n + 4; j += i) fac[j] = i;
	FORI(n + 4) if(i!=0) inverse[i] = (i < 4 || fac[i] == 0) ? MOD(modInverse(1ll * i)) : MOD(1ll * inverse[fac[i]] * inverse[(i) / fac[i]]);
	
	if(a == 0){
		clear(catalan);
		catalan[0] = MOD(1ll * k);
		FORI(n + 4) if(i > 0) catalan[i] = MOD(2ll * b * MOD(1ll * k * MOD(1ll * (2ll * i - 1) * MOD(1ll * catalan[i - 1] * MOD(inverse[i + 1])))));

		clear(prefsum);
		prefsum[0] = 0;
		prefsum[1] = MOD(1ll * k * k);
		FORI(n + 4) if(i >= 2) prefsum[i] = MOD(1ll * prefsum[i - 1] + MOD(1ll * catalan[i - 2] * catalan[i - 2]));
		
		int q;
		cin >> q;
		FORI(q){
			int l, r;
			cin >> l >> r;
			cout << MOD(1ll * prefsum[r + 1] - prefsum[l]) << endl;
		}
		return 0;
	}

	if(n == 1){
		int q; cin >> q;
		FORI(q) cout << MOD(1ll * k * k) << endl;
		return 0;
	}

	vector<long long> rec;
	rec.push_back(MOD(MOD(MOD(b * k) * k) + MOD(k * a)));
	rec.push_back(MOD(MOD(MOD(rec[0] * k) * 2ll * b) + MOD(rec[0] * a)));

	long long c = MOD(a + MOD(2ll * b * k));
	FORI(n) rec.push_back(MOD(MOD(MOD(MOD(MOD(rec[i] * (- 1ll - i)) * a) * a) + MOD(MOD(c + 2ll * MOD(c * (i + 2ll))) * rec[i + 1])) * inverse[4 + i]));

	clear(prefsum);
	prefsum[0] = 0;
	prefsum[1] = MOD(1ll * k * k);
	FORI(n + 4) if(i >= 2) prefsum[i] = MOD(1ll * prefsum[i - 1] + MOD(1ll * rec[i - 2] * rec[i - 2]));
		
	int q;
	cin >> q;
	FORI(q){
		int l, r;
		cin >> l >> r;
		cout << MOD(1ll * prefsum[r] - prefsum[l - 1]) << endl;
	}
	return 0;
}
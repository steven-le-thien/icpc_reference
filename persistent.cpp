#include<cstdio>
#include<math.h>
#include<cstring>
#include<vector>
#include<algorithm>

#define DEBUG 0
#define UPDATE_DEBUG 0
#define GET_DEBUG 0

#define FORI(n) for(int i = 0; i < n; i++)
#define FORJ(n) for(int j = 0; j < n; j++)
#define FORK(n) for(int k = 0; k < n; k++)
#define	FOR2I(a, b) for(int i = 0; i < a; i++) for(int j = 0; j < b; j++)
#define	FOR2J(a, b) for(int j = 0; j < a; j++) for(int k = 0; k < b; k++)

#define FORIT(S) for(auto it = S.cbegin(); it != S.cend(); it++)
#define clear(S) memset(S, 0, sizeof(S))
#define neg(S) memset(S, -1, sizeof(S))

#define pb push_back

using namespace std;

const int maxN = 100050;
const int maxSeg = 4 * maxN;

int n, m, logN;

int arr[maxN];
int sorted[maxN];
vector<int> st[maxSeg];

vector<int> * construct(int ss, int se, int si){
	if(se - ss == 1){if(ss < n) st[si].pb(arr[ss]); return &st[si];}

	int mid = ss + ((se - ss) >> 1);
	vector<int> * left = construct(ss, mid, (si << 1) + 1);
	vector<int> * right = construct(mid, se, (si << 1) + 2);

	st[si].resize(se - ss);
	merge(left->begin(), left->end(), right->begin(), right->end(), st[si].begin());
	return &st[si];
}

int query(int qs, int qe, int val, int ss, int se, int si) {
    if (ss >= qe || se <= qs) return 0;
    if (qs <= ss && se <= qe) return upper_bound(st[si].begin(), st[si].end(), val) - st[si].begin();

    int mid = ss + ((se - ss) >> 1);
    return query(qs, qe, val, ss, mid, (si << 1) + 1) + query(qs, qe, val, mid, se, (si << 1) + 2);
}

int main(){
	clear(arr); clear(sorted);
	scanf("%d %d", &n, &m);

	FORI(n) scanf("%d", &sorted[i]);
	FORI(n) arr[i] = sorted[i];

	sort(sorted, sorted + n);
	logN = n;
	logN |= logN >> 1;
	logN |= logN >> 2;
	logN |= logN >> 4;
	logN |= logN >> 8;
	logN |= logN >> 16;
	logN += 1;
	logN >>= (logN == n << 1);
	construct(0, logN, 0);

	while(m--){
		int a, b, k; scanf("%d %d %d", &a, &b, &k);

		int lo = 0, hi = n - 1;
		if(query(a - 1, b, sorted[lo], 0, logN, 0) >= k) {
			printf("%d\n", sorted[lo]);
			continue;
		}

		while(hi - lo > 1){
			if(query(a - 1, b, sorted[lo + ((hi - lo) >> 1)], 0, logN, 0) >= k) hi = lo + ((hi - lo) >> 1);
			else lo = lo + ((hi - lo) >> 1);
		}
		printf("%d\n", sorted[hi]);
	}
	return 0;
}





#include<iostream>
#include<cstdio>
#include<cmath>
#include<unordered_map>
#include<set>
#include<vector>
#include<list>
#include<queue>
#include<bitset>
#include<cstring>
#include<algorithm>
#define BIG_NUM 1E9


#define FORI(n) for(int i = 0; i < n; i++)
#define FORJ(n) for(int j = 0; j < n; j++)
#define FORK(n) for(int k = 0; k < n; k++)
#define	FOR2I(a, b) for(int i = 0; i < a; i++) for(int j = 0; j < b; j++)
#define	FOR2J(a, b) for(int j = 0; j < a; j++) for(int k = 0; k < b; k++)
#define FORIT(S) for(auto it = S.cbegin(); it != S.cend(); it++)

#define CLEAR(S) memset(S, 0, sizeof(S))

using namespace std; 

long long a[200000]; 
long long st[1000000];
long long flag[1000000];

long long construct(int ss, int se, int si){
	if(ss == se) {
		st[si] = a[ss];
		return a[ss];
	}

	int mid = ss + (se - ss)/2;
	st[si] = construct(ss, mid, 2 * si + 1) + construct(mid + 1, se, 2 * si + 2);
	return st[si];  
}

void propagato(int ss, int se, int si){
	if(flag[si]){
		st[si] += flag[si] * (long long)(se - ss + 1);
		if(ss != se){
			flag[(si << 1) + 1] += flag[si];
			flag[(si << 1) + 2] += flag[si];
		}
		flag[si] = 0;
	}
}

void update(int qs, int qe, int ss, int se, int si, long long diff){	
	propagato(ss, se, si);

	if(qe < ss || qs > se) return;

	if(qs <= ss && qe >= se){
		st[si] += diff * (long long)(se - ss + 1);
		if(ss != se){
			flag[(si << 1) + 1] += diff;
			flag[(si << 1) + 2] += diff;
		}
		return;
	}

	int mid = (ss + se) >> 1;
	update(qs, qe, ss, mid, (si << 1) + 1, diff);
	update(qs, qe, mid + 1, se, (si << 1) + 2, diff);
	st[si] = st[(si << 1) + 1] +  st[(si << 1) + 2];
}

long long get(int qs, int qe, int ss, int se, int si){
	propagato(ss, se, si);

	if(qe < ss || qs > se) return 0;

	if(qs <= ss && se <= qe) return st[si];

	int mid = (ss + se) >> 1;
	return get(qs, qe, ss, mid, (si << 1) + 1) + get(qs, qe, mid + 1, se, (si << 1) + 2);
}

int main(){
	int t;
	scanf("%d", &t);
	FORK(t){
		int n, c;
		memset(a, 0, sizeof(a));
		memset(st, 0, sizeof(st));
		memset(flag, 0, sizeof(flag));

		scanf("%d %d", &n, &c);
		construct(0, n - 1, 0);

		FORI(c){
			int control;
			scanf("%d", &control);
			if(control == 0){
				int p, q;
				long long v;
				scanf("%d %d %lld", &p, &q, &v);
				update(p - 1, q - 1, 0, n - 1, 0, v);
			} else {
				int p, q;
				scanf("%d %d", &p, &q);
				printf("%lld\n", get(p - 1, q - 1, 0, n - 1, 0));
			}
		}
	}
}
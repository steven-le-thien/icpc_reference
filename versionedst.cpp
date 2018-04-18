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

using namespace std;

struct node{
	node * left;
	node * right; 
	int val;
 	node():left(NULL), right(NULL), val(0) {}
	node(int a): left(NULL), right(NULL), val(a) {}
	node(node * l, node * r): left(l), right(r), val(l->val + r->val){}	
};

vector<int> a, arr, logu;
node st[400050];
node version[100050][22];
node * newest[400050];

int n, m, l, r, k; 

node * construct(int ss, int se, int si){
	if(ss != se){
		int mid = (ss + se) >> 1;
		st[si] = node(construct(ss, mid, 2 * si + 1), construct(mid + 1, se, 2 * si + 2));
	}
	return &st[si];
}

node * update(int ss, int se, int i, int si, int pos){
	if (i < ss || i > se) return newest[si];
 
    if (se != ss) {
        int mid = ss + (se - ss)/2; 
        version[pos][logu[si]] = node(update(ss, mid, i, 2 * si + 1, pos), update(mid + 1, se, i, 2 * si + 2, pos));
    } else version[pos][logu[si]] = node(newest[si]->val + 1);
    return newest[si] = &version[pos][logu[si]];
}

int get_sum(node * stl, node * str, int ss, int se, int qs, int qe, int si){
	if (qs <= ss && qe >= se) return str->val - stl->val;

	if (se < qs || ss > qe) return 0; 
	int mid = ss + (se - ss)/2;
 	return get_sum(stl->left, str->left, ss, mid, qs, qe, 2 * si +1) + get_sum(stl->right, str->right, mid + 1, se, qs, qe, 2 * si +2);
}

int find_left_close(int key){
	int u = a.size();
	int l = 0;
	while(l != u){
		int mid = (l + u) >> 1;
		if(a[mid] > key) u = mid - 1;
		else if(a[mid] < key) l = mid + 1;
		else return mid;
	}
	return l;
}

int serach_cand(int l, int r, int k){
	int hi = a.size() + 1;
	int lo = 0;
	while(lo != hi){
		int mid = lo + ((hi - lo) >> 1);
		int cand = get_sum(l >= 0 ? &version[l][0] : &st[0], &version[r][0], 0, n - 1, 0, mid, 0);
		if(cand < k) lo = mid + 1;
		else hi = mid;
	}
	return lo;
}


int main(){
	double l2 = 0.30102999566398119521373889472449;
	clear(st);
	clear(version);
	clear(newest);

	scanf("%d %d", &n, &m);
	a.assign(n, 0);
	logu.assign(4 * n, 0);
	arr.assign(n, 0);
	FORI(4 * n) logu[i + 1] = (int)(log(1.0 + i) / l2) + 1;
	logu[0] = 0;
	FORI(4 * n) newest[i] = &st[i];
	construct(0, n - 1, 0);

	FORI(n) scanf("%d", &a[i]);
	FORI(n) arr[i] = a[i];

	sort(a.begin(), a.end());
	a.resize(unique(a.begin(), a.end()) - a.begin());

	FORI(n) update(0, n - 1, find_left_close(arr[i]), 0, i);

	FORI(m){
		scanf("%d %d %d", &l, &r, &k);
		printf("%d\n", a[serach_cand(l - 2, r - 1, k)]);
	}
	return 0; 
}

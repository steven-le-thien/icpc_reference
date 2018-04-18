#include <cstdio> 
#include <vector> 
#include <cmath>
#include <iostream>
#include <cstring>

using namespace std;

#define FORI(n) for(int i = 0; i < n; i++)
#define FORJ(n) for(int j = 0; j < n; j++)
#define FORK(n) for(int k = 0; k < n; k++)
#define F first 
#define S second
#define mp make_pair
#define DEBUG 0
#define DEBUG_STACK 0

typedef pair<int, pair<int, int> > iii;
typedef vector<iii> viii;

const int N = 10050;
const int seg_size = 60050;
const int logN = 15;

int n;

viii adj[N];

int num_chain, edge_counter;
int chain_head[N], chain_id[N];
int sst[N], level[N];
int node_pos[N], old_edge[N], edge[N];
int st[seg_size];
int ances[N][logN];

void init(){
	num_chain = 0;
	edge_counter = -1;
	FORI(seg_size) st[i] = 0;
	FORI(N) chain_head[i] = chain_id[i] = old_edge[i] = edge[i] = level[i] = node_pos[i] = -1;
	FORI(N) FORJ(logN) ances[i][j] = -1;
	FORI(N) adj[i].resize(0);
	FORI(N) sst[i] = 1;
}

void init_ss(int cur_node, int parento, int levelo){
	level[cur_node] = levelo;
	ances[cur_node][0] = parento;
	FORI(adj[cur_node].size()) if(adj[cur_node][i].F != parento){
		init_ss(adj[cur_node][i].F, cur_node, levelo + 1);
		sst[cur_node] += sst[adj[cur_node][i].F];
	}
}

void dfs_hld(int cur_node, int parento, int ind){
	if(chain_head[num_chain] < 0) chain_head[num_chain] = cur_node;
	chain_id[cur_node] = num_chain;
	if(edge_counter >= 0){
		edge[edge_counter] = adj[parento][ind].S.F;
		old_edge[adj[parento][ind].S.S] = edge_counter;
		node_pos[cur_node] = edge_counter;
	}
	edge_counter++;

	int mai = -1, idx = -1;
	FORI(adj[cur_node].size()) if(adj[cur_node][i].F != parento) if(sst[adj[cur_node][i].F] > mai) {
		mai = sst[adj[cur_node][i].F];
		idx = i;
	}
	if(idx >= 0) dfs_hld(adj[cur_node][idx].F, cur_node, idx);
	

	FORI(adj[cur_node].size()) if(adj[cur_node][i].F != parento) if(i != idx) {
		num_chain++;
		dfs_hld(adj[cur_node][i].F, cur_node, i);
	}
}
int construct(int ss, int se, int si){
	if(ss == se) return st[si] = edge[ss];

	int mid = ss + ((se - ss) >>  1);
	return st[si] = max(construct(ss, mid, (si << 1) + 1), construct(mid + 1, se, (si << 1) + 2)); 
}

int query(int qs, int qe, int ss, int se, int si){
	if(qe < ss || se < qs) return 0;
	if(qs <= ss && se <= qe) return st[si];

	int mid = ss + ((se - ss) >> 1);
	return max(query(qs, qe, ss, mid, (si << 1) + 1), query(qs, qe, mid + 1, se, (si << 1) + 2));
}

void update(int ss, int se, int si, int i, int change){
	if(i < ss || se < i) return;
	if(ss == se) st[si] = edge[ss] = change;
	else{
		int mid = ss + ((se - ss) >> 1);
		update(ss, mid, (si << 1) + 1, i, change);
		update(mid + 1, se, (si << 1) + 2, i, change);
		st[si] = max(st[(si << 1) + 1], st[(si << 1) + 2]);
	}
}

int lca(int v1, int v2){
	if(level[v1] < level[v2]) swap(v1, v2); 
	int main_log = (int) log2(level[v1]);
	for(int i = main_log; i + 1; i--) 
		if(level[v1] - (1 << i) >= level[v2]) 
			v1 = ances[v1][i];

	if(v1 == v2) return v1;
	for(int i = main_log; i + 1; i--) {
		if(ances[v1][i] != -1 && ances[v2][i] != ances[v1][i]) {
			v1 = ances[v1][i], v2 = ances[v2][i];
		}
	}
	return ances[v1][0];
}

int find_dist(int v1, int v2){
	if(level[v1] < level[v2]) swap(v1, v2);
	int lc = lca(v1, v2);

	int cur_max = -1;
	while(chain_id[v1] != chain_id[lc]){
		int tmp = query(node_pos[chain_head[chain_id[v1]]], node_pos[v1], 0, n - 1, 0);
		if(tmp > cur_max) cur_max = tmp;
		if(edge[node_pos[v1]] > cur_max) cur_max = edge[node_pos[v1]];
		v1 = ances[chain_head[chain_id[v1]]][0];
	}

	while(chain_id[v2] != chain_id[lc]){
		int tmp = query(node_pos[chain_head[chain_id[v2]]], node_pos[v2], 0, n - 1, 0);
		if(tmp > cur_max) cur_max = tmp;
		if(edge[node_pos[v2]] > cur_max) cur_max = edge[node_pos[v2]];
		v2 = ances[chain_head[chain_id[v2]]][0];
	}
	if(v1 == v2) return cur_max > 0 ? cur_max : 0;
	else if(level[v1] > level[v2]){
		int tmp = query(node_pos[v2] + 1, node_pos[v1], 0, n - 1, 0);
		if(tmp > cur_max) return tmp;
		else return cur_max;
	}
	else{
		int tmp = query(node_pos[v1] + 1, node_pos[v2], 0, n - 1, 0);
		if(tmp > cur_max) return tmp;
		else return cur_max;
	} 
}

int main(){
	int t; scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		init();
		FORI(n - 1){
			int a, b, c; scanf("%d %d %d", &a, &b, &c);
			a--; b--;
			adj[a].push_back(mp(b, mp(c, i)));
			adj[b].push_back(mp(a, mp(c, i)));
		}
		init_ss(0, -1, 0);
		dfs_hld(0, -1, -1);
		construct(0, n - 1, 0);

		FORI((int)log2(n) - 1) 
			FORJ(n) 
				if(ances[j][i] != -1) 
					ances[j][i + 1] = ances[ances[j][i]][i];
			
		char s[500];
		scanf("%s", s);
		while(s[0] != 'D'){
			int a, b; 
			scanf("%d %d", &a, &b);
			if(s[0] == 'C') update(0, n - 1, 0, old_edge[a - 1], b);
			else printf("%d\n", find_dist(a - 1, b - 1)); 
			scanf("%s", s);
		}
	}
	return 0; 
}



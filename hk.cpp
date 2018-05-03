#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>

#define FORI(n) for(int i = 0; i < n; i++)
#define FORJ(n) for(int j = 0; j < n; j++)
#define FORK(n) for(int k = 0; k < n; k++)

#define INF (int) (1 << 28)
#define neg(S) memset(S, -1, sizeof(S))
#define clear(S) memset(S, 0, sizeof(S))

#define pb push_back
#define sz size

using namespace std;

const int maxN = 100010;
const int maxE = 150050;

int n, m, p, a, b;
int qs, qe;

vector<int> adj[maxN];
int l[maxN], d[maxN];
int q[5 * maxN];

bool bfs(){
	clear(q);
	qs = qe = 0;
	FORI(n + 1){
		if(i == 0) {d[i] = INF; continue;}
		if(!l[i]){
			d[i] = 0; 
			q[qe++] = i;
		} else d[i] = INF;
	} 
	while(qs < qe){
		int v = q[qs++];
		if(v) FORI(adj[v].sz()) if(d[l[adj[v][i]]] == INF) {d[l[adj[v][i]]] = d[v] + 1; q[qe++] = l[adj[v][i]];}
	}
	return (d[0] != INF);
}

bool dfs(int v){
	if(v){
		FORI(adj[v].sz()) if(d[l[adj[v][i]]] == d[v] + 1) if(dfs(l[adj[v][i]])) {l[v] = adj[v][i]; l[adj[v][i]] = v; return true;}
		d[v] = INF;
		return false;
	}
	return true;
}

int main(){
	clear(l);
	scanf("%d %d %d", &n, &m, &p);
	FORI(p){
		scanf("%d %d", &a, &b); 
		b += n;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	int res = 0;
	while(bfs()) FORI(n) if((!l[i + 1]) && dfs(i + 1)) res++;


	printf("%d\n", res);
	return 0;
}
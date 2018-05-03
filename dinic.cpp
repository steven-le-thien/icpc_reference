#include <cstdio>
#include <algorithm>
#include <cstring> 
#include <vector>

#define FORI(n) for(int i = 0; i < n; i++)
#define FORJ(n) for(int j = 0; j < n; j++)
#define FORK(n) for(int k = 0; k < n; k++)

#define clear(S) memset(S, 0, sizeof(S))
#define neg(S) memset(S, -1, sizeof(S))

#define pb push_back
#define sz size

#define DEBUG 1

using namespace std;

const int maxN = 5010;
const int maxM = 30010 * 5;
const int maxC = 1000000000;

int n, m, a, b, c;
int l[maxN];
int adj[maxN];
int pro[maxN];
int q[maxN];
int qs, qe;
int counter;

int point[maxM];
int to[maxM];
int flow[maxM];
int cap[maxM];



bool bfs(){
	neg(l);
	l[1] = qe = qs = 0;
	q[qe++] = 1;
	while(qs < qe){
		int v = q[qs++];
		for(int e = adj[v]; e >= 0; e = point[e]){
			if(l[to[e]] < 0 && cap[e] > flow[e]){
				l[to[e]] = l[v] + 1; 
				q[qe++] = to[e];
			}
		}
	}

	return l[n] != -1;
}

long long dfs(int v, int f){
	if(v == n) return f; 

	for(int &e = pro[v]; e >= 0; e = point[e]){
		if(l[to[e]] == l[v] + 1 && cap[e] - flow[e] > 0){
			if(long long tmp = dfs(to[e], min(cap[e]-flow[e], f))){
				flow[e] += tmp;
				flow[e^1] -= tmp;
				return tmp;
			}
		}
	}
	return 0;
}

int main(){
	counter = 0;
	clear(to); clear(flow); clear(cap); clear(point); neg(adj); clear(pro);
	scanf("%d %d", &n, &m);
	FORI(m){
		scanf("%d %d %d", &a, &b, &c);
		if(a == b) continue;
		to[counter] = b;
		flow[counter] = 0;
		cap[counter] = c;
		point[counter] = adj[a];
		adj[a] = counter;
		counter++;
		to[counter] = a;
		flow[counter] = 0;
		cap[counter] = c;
		point[counter] = adj[b];
		adj[b] = counter;
		counter++;
	}

	long long res = 0;
	bool flag = false;
	while(bfs()){
		FORI(n) pro[i + 1] = adj[i + 1]; 

		while(1){
			if(long long tmp = dfs(1, (int) 1e9)) res += tmp;
			else break;
		}
	}
	printf("%lld\n", res);

	return 0;
}

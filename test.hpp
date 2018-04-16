#ifndef TEST_H
#define TEST_H

#define BIG_NUM 1000000000

#define DEBUG 0


#define FOR(i, a, b) for(int i = a; i < b; i++)
#define FORI(n) for(int i = 0; i < n; i++)
#define FORJ(n) for(int j = 0; j < n; j++)
#define FORK(n) for(int k = 0; k < n; k++)
#define	FOR2I(a, b) for(int i = 0; i < a; i++) for(int j = 0; j < b; j++)
#define	FOR2J(a, b) for(int j = 0; j < a; j++) for(int k = 0; k < b; k++)
#define FORIT(S) for(auto it = S.cbegin(); it != S.cend(); it++)

#define CLEAR(S) memset(S, 0, sizeof(S))
#define SANITY(i) printf("sanity checkpoint %d\n", i)
#define OMG(i) printf("OMG NO!!!! at %d", i)

typedef pair<int, int> ii; 
typedef vector<ii> vii;
typedef vector<int> vi;

// Testing guidlines: ./a.out < input > myoutput >> diff myoutput output. trick cases,
	// large cases, 

// Bitwise op. To find the least sig set bit, do S & -S 

// Clear
	//memset(arr, 0, size);

// Comp
	//bool compareInterval(Interval i1, Interval i2) return (i1.start < i2.start);

// Find max
	//std::cout << *std::max_element(std::begin(list), std::end(list), comp);

// Find max index
	//std::distance(A, std::max_element(A, A + N))

// Sort decreasing order
	//std::sort(arr, arr+n, greater<int>());

// Print with precision for double
	//printf("%.9lf\n", result); double operation takes the type of the first operand

// hypot(p1.x - p2.x, p1.y - p2.y), pi = 2 * acos(0.0), A = sqrt(s × (s − a) ×
// (s − b) × (s − c)), r = A/s, R = a × b × c/(4 × A). sine law = 2, shoelace

// Check convexity with ccw

// BFS
// adj	:	list of indices
// s 	:	starting
// V 	:	num vertices
void BFS(int s, list<int> *adj, int V){
	bool * visited[V];
	FORI(V) visited[i] = false;
	int meta[V];

	list<int> queue; 

	visited[s] = true;
	queue.push_back(s);
	meta[s] = -1; 

	while(!queue.empty()){
		s = queue.front();

		//do something with s

		queue.pop_front();
		FORIT(adj[s]){
			if(!visited[*it]) {
				visited[*it] = true;
				meta[*it] = s;
				queue.push_back(*it); 
			}
		}
	}
}


// DFS
// adj	:	list of indices
// v 	:	starting
// V	:	num vertices
void DFSre(int v, bool visited[], list<int> *adj){
	visited[v] = true;

	// Do something with v

	list<int>::iterator i;
	FORIT(adj[v]) if(!visited[*it]) DFSre(*it, visited)
}

void DFS(int v, int V, list<int> *adj) {
	bool *visited;
	FORI(V) visited[i] = false;
	DFSre(v, visited, list<int> *adj);
}

// Dịkstra using priority queue
vi dist(V, BIG_NUM); dist[s] = 0;
priority_queue< ii, vector<ii>, greater<ii> > pq; pq.push(ii(0, s));
while (!pq.empty()) {
	ii front = pq.top();
	pq.pop();
	int d = front.first, u = front.second;
	if (d > dist[u]) continue;
	for (int j = 0; j < (int)AdjList[u].size(); j++){
		ii v = AdjList[u][j];
		if (dist[u] + v.second < dist[v.first]) {
			dist[v.first] = dist[u] + v.second;
			pq.push(ii(dist[v.first], v.first));
		}
	}
}

// Prim's
// a 	:	adjacency matrix
// n 	: 	num vertices
void primMST(int a[][], int n){
	int result[n], key[n], pathSet[n];
	FORI(n) key[i] = BIG_NUM, pathSet[i] = false;

	key[0] = 0;
	result[0] = -1;

	FORI(n - 1) {
		int min = BIG_NUM, min_idx;
		FORJ(n) if(!pathSet[j] && key[j] < min) min_idx = j;

		pathSet[min_idx] = true;

		FORJ(n) if(a[min_idx][j] 
			&& !pathSet[j]
			&& a[min_idx][j] < key[j]) 
				result[j] = min_idx, key[j] = a[min_idx][j];
	}
}

// Floyd-Warshall
void floydWarshall(int graph[][], int n){
	FOR2I(n, n) FORK(n) graph[j][k] = min(dist[j][i] + dist[i][k], dist[j][k]);
}


// LIS
int lis(int a[], int n){
	int lis[n];
	int max = 0;

	FORI(n) lis[i] = 1; 
	FOR2I(n, n) if(a[i] > a[j] && lis[i] < lis[j] + 1 && i!=0) lis[i] = lis[j] + 1;
	FORI(n) if(max < lis[i]) max = lis[i]; 

	return max; 
}

int fast_lis(int n, int * w){
	FORI(n){
		m[i] = 0;
		p[i] = 0; 
		lis
	}
	m[n] = 0;

	int l = 0;
	FORI(n){
		int lo = 1;
		int hi = l;

		while(lo <= hi){
			int mid = ceil((lo + hi)/2);
			if(w[m[mid]] < w[i]) lo = mid + 1; 
			else hi = mid - 1;
		}

		int newL = lo;
		p[i] = m[newL-1];
		m[newL] = i; 
		if(newL > l){
			l = newL;
		}
	}
	int k = m[l];
	FORI(l){
		lis[l - 1 - i] = w[k];
		idx[l - 1 - i] = k;
		k = p[k];
	}
	return l;
}

int x = (int)(ceil(log2(n))); 
int max_size = 2*(int)pow(2, x) - 1; 
int *st = new int[max_size];
construct(arr, 0, n-1, st, 0);
// Segment tree 
int construct(int ss, int se, int si){
	if(ss == se) {
		st[si] = a[ss];
		return a[ss];
	}

	int mid = ss + ((se - ss) >> 1);
	st[si] = construct(ss, mid, (si << 1) + 1) + construct(mid + 1, se, (si << 1) + 2);
	return st[si];  
}

void updateValueUtil(int *st, int ss, int se, int i, int diff, int si)
{
    if (i < ss || i > se) return;
 
    st[si] = st[si] + diff;
    if (se != ss) {
        int mid = ss + ((ss - se) >> 1); 
        updateValueUtil(st, ss, mid, i, diff, (si << 1) + 1);
        updateValueUtil(st, mid + 1, se, i, diff, (si << 1) + 2);
    }
}

int get_sum(int * st, int ss, int se, int qs, int qe, int si){
	if (qs <= ss && qe >= se) return st[si];
	if (se < qs || ss > qe) return 0; 
	int mid = ss + ((se - ss) >> 1);
	return get_sum(st, ss, mid, qs, qe, (si << 1) + 1) + get_sum(st, mid + 1, se, qs, qe, (si << 1) + 2);
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

	int mid = ss + (se - ss) >> 1;
	update(qs, qe, ss, mid, (si << 1) + 1, diff);
	update(qs, qe, mid + 1, se, (si << 1) + 2, diff);
	st[si] = st[(si << 1) + 1] +  st[(si << 1) + 2];
}

long long get(int qs, int qe, int ss, int se, int si){
	propagato(ss, se, si);

	if(qe < ss || qs > se) return 0;

	if(qs <= ss && se <= qe) return st[si];

	int mid = ss + (se + ss) >> 1;
	return get(qs, qe, ss, mid, (si << 1) + 1) + get(qs, qe, mid + 1, se, (si << 1) + 2);
}

// Union set
UnionFind(int n) {
	rank.assign(n, 0);
	p.assign(n, 0);
	FORI(n) p[i] = i; 
}

int find_set(int i) {return p[i] == i ? i : p[i] = find_set(p[i]);}

bool is_same_set(int i, int j) {return find_set(i) == find_set(j);}

int unionSet(int i, int j){
	int x = find_set(i);
	int y = find_set(j);
	if(x != y){
		if(rank[x] > rank[y]) p[y] = x; 
		else {
			p[x] = y; 
			if(rank[x] == rank[y]) rank[y]++;
		}
	}
}

// Fenwick
Fenwick(int n) {ft.assign(n + 1, 0)}

int rsq(int b){
	int sum = 0;
	for(; b; b -= (b & -b)) sum += ft[b];
	return sum;
}

int rsq(int a, int b){
	return rsq(b) - (a == 0 ? 1 : rsq(a - 1)); 
}

void adjust(int v, int k){
	for(; k < (int) ft.size(); k += (k & -k)) ft[k] += v;
}

// Euler cycle
list<int> cyc; // we need list for fast insertion in the middle
void EulerTour(list<int>::iterator i, int u) {
	for (int j = 0; j < (int)AdjList[u].size(); j++) {
		ii v = AdjList[u][j];
		if (v.second) { // if this edge can still be used/not removed
			v.second = 0; // make the weight of this edge to be 0 (‘removed’) for (int k = 0; k < (int)AdjList[v.first].size(); k++) {
			for (int k = 0; k < (int)AdjList[v.first].size(); k++) {
				ii uu = AdjList[v.first][k];
				if (uu.first == u && uu.second) {
					uu.second = 0;
					break; 
				}
			}
			EulerTour(cyc.insert(i, u), v.first); 
		}
	}
}
// remove bi-directional edge
// inside int main()
cyc.clear();
EulerTour(cyc.begin(), A); // cyc contains an Euler tour starting at A for (list<int>::iterator it = cyc.begin(); it != cyc.end(); it++)
for (list<int>::iterator it = cyc.begin(); it != cyc.end(); it++) printf("%d\n", *it);

// GCD
int gcd(int a, int b) {return b == 0 ? a : gcd(b, a % b);}

// Diophantine
void extendedEuclid(int a, int b) {
	if (b == 0) { x = 1; y = 0; d = a; return; }
	extendedEuclid(b, a % b);
	int x1 = y;
	int y1 = x - (a / b) * y;
	x = x1;
	y = y1;
}

// Sieve 
bitset<10000010> bs; 
bs.set();
b[0] = b[1] = 0;
for (ll i = 2; i <= _sieve_size; i++) if (bs[i]){
	for (ll j = i * i; j <= _sieve_size; j += i) bs[j] = 0;
	primes.push_back((int)i);
}


// Factor 
bs.set();
bs[0] = bs[1] = 0;
for (int i = 2; i <= 10001; i++) if (bs[i]){
	for (int j = i * i; j <= 10001; j += i){ bs[j] = 0;
		factor[j] = i;
	}
	factor[i] = -1;
}

// Golden
int main(){
	double qr = 3;
	double a = 0.0; 
	double b = 50000.0;

	FORI(100){
		double c = b - (b - a) / qr;
		double d = a + (b - a) / qr;
		// printf("a is %f, b is %f, c is %f, d is %f, fc is %f fd is %f\n", a, b, c, d, loss(c), loss(d));
		if(loss(c) > loss(d)) b = c;
		else a = d;
	}

	printf("%.9lf\n", a);
}

// KMP
void kmpPreprocess() {
	int i = 0, j = -1; b[0] = -1; 
	while (i < m) {
		while(j >= 0 && p[i] != p[j]) j = b[j];
		i++, j++;
		b[i] = j;
	}
}

void kmpSearch() {
	int i = 0, j = 0;
	while(i < n) {
		while(j >= && p[i] != p[j]) j = b[j];
		i++, j++;
		if(j == m){
			// found
			j = b[j];
		}
	}
}

// Kosaraju 
int kosaraju(int u, int pass){
	dfs_num[u] = 1;
	vii neighbor;
	if (pass == 1) neighbor = AdjList[u]; 
	else neighbor = AdjListT[u];
	for (int j = 0; j < (int)neighbor.size(); j++) {
		ii v = neighbor[j];
		if (dfs_num[v.first] == DFS_WHITE) kosaraju(v.first, pass);
	}
	S.push_back(u);
} 

S.clear();
dfs_num.assign(N, DFS_WHITE); 
for (i = 0; i < N; i++) if (dfs_num[i] == DFS_WHITE) kosaraju(i, 1);
numSCC = 0;
dfs_num.assign(N, DFS_WHITE);
for (i = N - 1; i >= 0; i--)if (dfs_num[S[i]] == DFS_WHITE) {
	numSCC++;
	kosaraju(S[i], 2);
}

// Splay
Node * r_rota(Node * parent){
	Node * child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}

Node * l_rota(Node * parent){
	Node * child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child; 
}

Node * splay(int val, Node * root){
	if(!root || root->val == val) return root;

	if(root->val > val){
		if(!root->left) return root;
		else if(root->left->val > val){
			root->left->left = splay(val, root->left->left);
			root = r_rota(root); 
		} else if(root->left->val < val){
			root->left->right = splay(val, root->left->right);
			if(root->left->right) root->left = l_rota(root->left);
		}
		return root->left == NULL ? root : r_rota(root);
	} else {
		if(!root->right) return root;
		else if(root->right->val > val){
			root->right->left = splay(val, root->right->left);
			if(root->right->left) root->right = r_rota(root->right);
		} else if(root->right->val < val){
			root->right->right = splay(val, root->right->right);
			root = l_rota(root);
		}
		return root->right == NULL ? root : l_rota(root);
	}
}

// Top down
Node head;

Node * splay(int val, Node * root){
	if(!root || root->val == val) return root;

	head.right = head.left = NULL;

	Node * left_max = &head;
	Node * right_min = &head;

	while(1){
		if(root->val > val){
			if(!root->left) break;
			if(root->left->val > val){
				root = r_rota(root);
				if(!root->left) break;
			}
			right_min->left = root;
			right_min = right_min->left;
			root = root->left;
			right_min->left = NULL;
		} else if(root->val < val){
			if(!root->right)  break;
			if(root->right->val < val){
				root = l_rota(root);
				if(!root->right) break;
			}
			left_max->right = root;
			left_max = left_max->right;
			root = root->right;
			left_max->right = NULL;
		} else break;
	}
	left_max->right = root->left;
	right_min->left = root->right;
	root->left = head.right;
	root->right = head.left;

	return root;
}

Node * insert(int val, Node * root){
	Node * nn = new Node;
	nn->val = val; 
	nn->right = nn->left = NULL;

	if(!root){
		root = nn;
		nn = NULL;
		return root;
	}
	root = splay(val, root);
	if(root->val > val){
		nn->left = root->left;
		nn->right = root;
		root->left = NULL;
		root = nn;
	} else if(root->val < val){
		nn->right = root->right;
		nn->left = root;
		root->right = NULL;
		root = nn;
	} else return root;
	nn = NULL;
	free(nn);
	return root;
}

Node * del(int val, Node * root){
	Node * temp;
	if(!root) return NULL;
	root = Splay(key, root);
	if(key != root->key) return root;
	else {
		if(!root->lchild){
			temp = root;
			root = root->rchild;
		}
		else{
			temp = root;
			root = Splay(key, root->lchild);
			root->rchild = temp->rchild;
		}
		free(temp);
		return root;
	}
}

#endif //TEST_H 
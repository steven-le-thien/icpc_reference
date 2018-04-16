#include<cstring>
#include<vector>
#include<cstdio>

#define FORI(n) for(int i = 0; i < n; i++)
#define FORJ(n) for(int j = 0; j < n; j++)
#define FORK(n) for(int k = 0; k < n; k++)
#define blue(cond, n) do{while(cond && n->parent) n = n->blue;}while(0)

using namespace std;

char REF; 
int COUNT;

struct node{
	int c;
	int end;
	node * parent;
	node * child[57];
	node * blue;
	node * green;
	node() = default;
	node(char c, node * n): c(c - REF), parent(n), end(-1) {FORI(COUNT) child[i] = NULL; blue = green = NULL;}
};

node * root;
vector<node *> queue;
vector<pair<int, int>> res;
bool summ[1000];
int q_begin, q_end;
char S[100050];
char T[1000];
vector<int> rep[1000];

int t, q;

void add_word(char * s, node * n, int i){
	char cur = *s;
	while(cur){
		if(!n->child[cur - REF]) n->child[cur - REF] = new node(cur, n);
		n = n->child[cur - REF];
		cur = *(++s);
	}
	if(n->end < 0) n->end = i;
	else rep[n->end].push_back(i);
}

void find_blue(node * n){
	if(!n->parent || !n->parent->parent) {
		n->blue = root;
		return;
	}
	node * cand = n->parent->blue;
	blue(!cand->child[n->c], cand);
	n->blue = cand->child[n->c] ? cand->child[n->c] : root;
}

void find_green(node * n){
	if(!n->parent) return;
	node * cand = n;
	blue(cand->blue->end < 0, cand);
	if(cand->blue->end >= 0) n->green = cand->blue;
}

void bfs_all(){
	q_begin = 0;
	q_end = 1;
	queue.resize(0);
	queue.push_back(root);
	while(q_begin != q_end){
		node * s = queue[q_begin];
		q_begin++;
		find_blue(s);
		find_green(s);
		FORI(COUNT) if(s->child[i] && !s->child[i]->blue) queue.push_back(s->child[i]), q_end++;
	}
}

void green(node * n, int counter){
	node * copy = n;
	while(copy->green){
		copy = copy->green;
		res.push_back(make_pair(copy->end, counter));
	}
}

void search(char * s){
	node * n = root;
	int counter = 0;
	char c = *s;
	while(c){
		blue(!n->child[c - REF], n);
		if(n->child[c - REF] || n->parent) n = n->child[c - REF];
		if(n->end >= 0) res.push_back(make_pair(n->end, counter));
		green(n, counter);
		c = *(++s);
		counter++;
	}
}

int main(){
	REF = 'A';
	COUNT = 'z' - 'A';
	scanf("%d", &t);
	FORK(t){
		res.resize(0);
		scanf("%s", S);
		scanf("%d", &q);
		root = new node(-1, NULL);
		FORI(q) rep[i].resize(0);
		FORI(q) summ[i] = false;
		FORI(q){
			scanf("%s", T);
			add_word(T, root, i);
		}
		bfs_all();
		search(S);
		FORI(res.size()){
			summ[res[i].first] = 1;
			FORJ(rep[res[i].first].size()) summ[rep[res[i].first][j]] = 1;
		}
		FORI(q) printf("%c\n", summ[i] ? 'y' : 'n');
		delete root;
	}
	return 0; 
}



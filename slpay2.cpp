#include<iostream>
#include<cstdio>
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

#define clear(S) memset(S, 0, sizeof(S))
using namespace std; 

typedef struct Node{
	int order;
	int val;
	bool flip;
	Node * left;
	Node * right;
	Node * parent;
	Node():order(100), val(100), flip(0), left(NULL), right(NULL){}
} Node;

Node a[100000];
Node * master;
int maxi;

int get_order(Node * node) {return node ? node->order : 0;}

void prop(Node * node){
	if(!node) return;
	if(node->flip){
		Node * tmp = node->left;
		node->left = node->right;
		node->right = tmp;
		if(node->left) node->left->flip ^= 1;
		if(node->right) node->right->flip ^= 1;
		node->flip = 0;
	}
}

Node * find_pos(int order, Node * tmp2){
	Node * tmp = tmp2; 
	while(1){
		prop(tmp);
		if(get_order(tmp->left) == order - 1) return tmp;
		if(get_order(tmp->left) < order - 1){
			if(!tmp->right) return NULL;
			order -= get_order(tmp->left) + 1;
			tmp = tmp->right;
			continue;
		}
		tmp = tmp->left;
	}
}

Node * r_rota(Node * parent){
	if(parent->parent) prop(parent->parent);
	prop(parent);
	Node * child = parent->left;
	prop(child);

	if(parent->parent) {if(parent->parent->left == parent){
		parent->parent->left = child;
	} else parent->parent->right = child;}
	child->order = get_order(parent);
	parent->order = get_order(parent->right) + 1 + get_order(child->right);

	parent->left = child->right;
	if(child->right) child->right->parent = parent;
	child->right = parent;

	child->parent = parent->parent;
	parent->parent = child;
	
	return child;
}

Node * l_rota(Node * parent){
	if(parent->parent) prop(parent->parent);
	prop(parent);
	Node * child = parent->right;
	prop(child);

	if(parent->parent) {if(parent->parent->left == parent){
		parent->parent->left = child;
	} else parent->parent->right = child;}
	child->order = get_order(parent);
	parent->order = get_order(parent->left) + 1 + get_order(child->left);

	parent->right = child->left;
	if(child->left) child->left->parent = parent;
	child->left = parent;
	child->parent = parent->parent;
	parent->parent = child;
	return child; 
}

Node * single_splay(Node * p, Node * n){
	if(n == p->left) return r_rota(p);
	else return l_rota(p);
}

Node * double_splay(Node * g, Node * p, Node * n){
	if(p == g->left){
		if(n == p->left) return r_rota(r_rota(p)->parent);
		else return r_rota(l_rota(p)->parent);
	} else {
		if(n == p->left) return l_rota(r_rota(p)->parent);
		else return l_rota(l_rota(p)->parent);
	}
}

void inorder(Node * n){
	if(!n) return; 
	prop(n);
	inorder(n->left);
 				maxi--;
 				if(maxi == 0) printf("%d", n->val); 
 				else printf("%d\n", n->val);
	inorder(n->right);
}

Node * splay_ptr(Node * n){
	while(1){
		Node * p = n->parent;
		if(!p) return n;
		Node * g = p->parent;
		if(!g){
			n = single_splay(p, n);
			return n;
		}
		n = double_splay(g, p, n);
	}
}

Node * find_lr(Node * n, bool left){
	if(!n) return n;
	Node * tmp = n;

	if(left){
		while(tmp->left) {
			prop(tmp);
			tmp = tmp->left;
		}
	} else {
		while(tmp->right) {
			prop(tmp);
			tmp = tmp->right;
		}
	}
	return tmp;
}

int build(int size, int start, int parent){
	if(size == 2){
		a[start + 1].left = &a[start];
		a[start + 1].right = NULL;
		a[start].parent = &a[start + 1];
		a[start + 1].parent = &a[parent];
		a[start].order = 1;
		a[start + 1].order = 2;
		return start + 1;
	} else if(size == 1) {
		a[start].parent = &a[parent];
		a[start].order = 1;
		return start;
	}

	int root_idx = start + size/2;
	a[root_idx].left = &a[build(size/2, start, root_idx)];
	a[root_idx].right = &a[build(size - size/2 - 1, root_idx + 1, root_idx)];
	a[root_idx].parent = &a[parent];
	a[root_idx].order = a[root_idx].left->order + 1 + a[root_idx].right->order;
	return root_idx;
}

void update(Node * n){n->order = get_order(n->left) + 1 + get_order(n->right);}

Node * join(Node * l, Node * r){
	if(!l) return r;
	if(!r) return l;
	l = splay_ptr(find_pos(l->order, l));
	l->right = r;
	update(l);
	r->parent = l;
	return l;
}

int main(){
	scanf("%d", &maxi);
	int m;
	scanf("%d", &m);

	master = &a[build(maxi, 0, 0)];
	master->parent = NULL;
	FORI(maxi) a[i].val = i + 1;

	FORI(m){
		int a1, b;
		scanf("%d %d", &a1, &b);
		if(a1 == b && b == maxi) continue;
		if(a1 == 1 && b == maxi){
			master->flip ^= 1;
			continue;
		}

		Node * alo = find_pos(a1, master);
		master = splay_ptr(alo);
		Node * blo = find_pos(b, master);
		master = splay_ptr(blo);
		Node * tmp;
		if(alo == blo->right){
			prop(alo);
			prop(blo);
			Node * lb = blo->left;
			Node * ra = alo->right;

			if(alo)alo->right = NULL;
			update(alo);
			if(ra)ra->parent = NULL;

			if(blo)blo->left = NULL;
			update(blo);
			if(lb)lb->parent = NULL;

			lb = join(lb, ra);
			master->flip ^= 1;
			master = join(lb, master);
		} else {


			prop(alo);
			prop(blo);
			Node * lb = blo->right;
			Node * ra = alo->left;

			if(alo)alo->left = NULL;
			update(alo);
			if(ra)ra->parent = NULL;

			if(blo)blo->right = NULL;
			update(blo);
			if(lb)lb->parent = NULL;

			ra = join(ra, lb);
			master->flip ^= 1;
			master = join(ra, master);
		}
	}
	inorder(master); 
	printf("\n");
	return 0;
}


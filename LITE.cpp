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

#define clear(S) memset(S, 0, sizeof(S))

using namespace std; 

int a[100000];
int b[100000]; 

typedef struct Node{
	int order;
	int val;
	bool flip;
	bool newflip;
	int prop;
	int sub;
	Node * left;
	Node * right;
	Node():order(100), val(100), flip(0), newflip(0), prop(0), sub(0), left(NULL), right(NULL){}
	Node(int val):order(val), val(val), flip(0), newflip(0), prop(0), sub(0), left(NULL), right(NULL){} 
} Node;

Node arr[100000];
Node * master;
int maxi;

void find_pos(int order, Node * tmp){
	if(master->order == order){
		tmp = master; 
		return;
	}
	// Node * traverse = master;
	while(1){
		if(tmp->order == order) return ;
		if(!tmp->left){
			tmp = NULL;
			return;
		}
	}
}

void propa(Node * node, int control){
	if(node->prop){
		node->order += node->prop;
		if(node->left) node->left->prop += node->prop;
		if(node->right) node->right->prop += node->prop;
		node->prop = 0;
	}
	if(node->sub){
		node->order = node->sub - node->order;
		if(node->left) {
			if(node->left->sub){
				node->left->sub = 0;
				node->left->prop += node->sub - node->left->sub;
			} else node->left->sub = node->sub;
		}
		if(node->right) {
			if(node->right->sub){
				node->right->sub = 0;
				node->right->prop += node->sub - node->right->sub;
			} else node->right->sub = node->sub;
		}
		node->sub = 0;
	}
	if(node->newflip){
		Node * tmp = node->left;
		node->left = node->right;
		node->right = tmp;
		if(node->left) {
			node->left->flip = ~node->left->flip;
			if(node->left->flip) node->left->newflip = 1;
		}
		if(node->right) {
			node->right->flip = ~node->right->flip;
			if(node->right->flip) node->right->newflip = 1;
		}
		node->newflip = 0;
	}
}

Node * r_rota(Node * parent){
	Node * child = parent->left;
	propa(child, 0);
	if(parent->flip ^ child->flip){
		parent->left = child->left; 
		child->left = parent;
	} else {
		parent->left = child->right;
		child->right = parent;
	}
	return child;
}

Node * l_rota(Node * parent){
	Node * child = parent->right;
	propa(child, 0);
	if(parent->flip ^ child->flip){
		parent->right = child->right; 
		child->right = parent;
	} else {
		parent->right = child->left;
		child->left = parent;
	}
	return child; 
}

void InOrder(Node* root)
{
	if(root)
	{
		InOrder(root->left);
		std::cout<< "key: " <<root->order ;
		if(root->left)
			std::cout<< " | left child: "<< root->left->order;
		if(root->right)
			std::cout << " | right child: " << root->right->order;
		std::cout<< "\n";
		InOrder(root->right);
	}
}

Node * splay(int val, Node * root){
	printf("from splay root is %d\n", root->val);
	propa(root, 1);
	if(!root || root->order == val) return root;
	Node head;

	head.right = head.left = NULL;

	Node * left_max = &head;
	Node * right_min = &head;

	while(1){
		printf("in while, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);
		// InOrder(&head);
		if(!root->flip){
			if(root->order > val){
											printf("in lèt3333, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);
				if(!root->left) break;
				propa(root->left, 1);
				bool f = false;
											printf("in lèt33332, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);

				if(root->left->order > val){
					root = r_rota(root);
					f = true;

					if(root->flip){
						if(!root->right) break;
																								printf("in lèt3333 thre, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);

						propa(root->right, 1); 
					} else {
						if(!root->left) break;
																								printf("in lèt3333 fur, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);

						propa(root->left, 1); 
					}	
																							printf("in lèt3333 fai, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);

				}
																						printf("in lèt333 si, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);
					printf("my righmin is %d\n", right_min->order);		
				if(right_min->flip){
					right_min->right = root;
					right_min = right_min->right;
				} else {
					right_min->left = root;
					right_min = right_min->left;
				}
				
				if(f){
					if(root->flip){
						root = root->right;
						right_min->right = NULL;
					} else {
						root = root->left;
						right_min->left = NULL;
					}
				} else {
					root = root->left;
					right_min->left = NULL;
				}
			} else if(root->order < val){
			printf("in right111, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);

				if(!root->right){
					cout << "OMG" << endl;  
					break;
				}
				propa(root->right, 1);
				bool f = false;
				if(root->right->order < val){
																			printf("in 2, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);
					f = true;
					root = l_rota(root);
					if(!root->right) break;
																			printf("in right222, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);

					propa(root->right, 1);
				}
																			printf("in right33, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);

				if(left_max->flip){
					left_max->left = root;
					left_max = left_max->left;
				} else {
																								printf("in another ss, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);
					left_max->right = root;
					left_max = left_max->right;
				}
				
				if(f){
					if(root->flip){
						root = root->left;
						left_max->left = NULL;
					} else {
						root = root->right;
						left_max->right = NULL;
					}
				} else {
																								printf("in ssss, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);
					root = root->right;
					left_max->right = NULL;
				}
			} else break;
		} else {
			if(root->order > val){

				if(!root->right) break;
										printf("in left1, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->right->order, val);

				propa(root->right, 1);
				bool f = false; 
				if((root->right->flip && root->right->order > val) ||(
					!root->right->flip && root->right->order > val)){
					root = l_rota(root);
					f = true;


					if(!root->flip){
						if(!root->left) break;
												printf("in left2, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->right->order, val);

						propa(root->left, 1);
					} else {
						if(!root->right) break;
												printf("in left3, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->right->order, val);

						propa(root->right, 1);
					}
											printf("in left4, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->right->order, val);

				}
										printf("in left5, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->right->order, val);
				
				if(f){ //zigzig
						printf("right min is %d left max is %d\n", right_min->order, left_max->order);

					if(right_min->flip){
						right_min->right = root;
						right_min = right_min->right;
					} else {
						right_min->left = root;
						right_min = right_min->left;
					}
					if(root->flip){
						root = root->right;
						right_min->right = NULL;
					} else {
						root = root->left;
						right_min->left = NULL;
					}
				} else {//zig
					// cout << "zig" << endl;
					if(right_min->flip){
						right_min->right = root;
						right_min = right_min->right;
					} else {
						right_min->left = root;
						right_min = right_min->left;
					}
					root = root->right;
					right_min->right = NULL;
				}
				
			} else if(root->order < val){
										printf("in right1, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);

				if(!root->left)  break;

				propa(root->left, 1);
				bool f = false;
				if((root->right->flip && root->right->order < val) ||(
					!root->right->flip && root->right->order < val)){
					f = true;
					root = r_rota(root);
					if(!root->flip){
												printf("in right2, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);

						if(!root->right) break;
						propa(root->right, 1);
					} else {
						if(!root->left) break;
												printf("in right3, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);
						propa(root->left, 1);
					}
											printf("in right4, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);
				}
										printf("in right5, val is %d order is %d, root prop is %d, actual val is %d\n", root->val, root->order, root->flip, val);
				if(f){ //zigzig
					if(left_max->flip){
						left_max->left = root;
						left_max = left_max->left;
					} else {
						left_max->right = root;
						left_max = left_max->right;
					}
					if(root->flip){
						root = root->left;
						left_max->left = NULL;
					} else {
						root = root->right;
						left_max->right = NULL;
					}
				} else {//zig
					if(left_max->flip){
						left_max->left = root;
						left_max = left_max->left;
					} else {
						left_max->right = root;
						left_max = left_max->right;
					}
					root = root->left;
					left_max->left = NULL;
				}
			} else break;
		}
	}
	if(left_max->flip){
		left_max->left = root-> flip ? root->right : root->left;
	} else {
		left_max->right = root-> flip ? root->right : root->left;
	}
	if(right_min->flip){
		right_min->right = root-> flip ? root->left : root->right;
	} else {
		right_min->left = root-> flip ? root->left : root->right;
	}
	if(root->flip){
		root->right = head.right;
		root->left = head.left;
	} else {
		root->left = head.right;
		root->right = head.left;
	}

	return root;
}

int build(int size, int start){
	printf("my start is %d, my size is %d\n", start, size);
	if(size == 2){
		arr[start + 1].left = &arr[start];
		return start + 1;
	} else if(size == 1) {
		// return -1;
		return start;
	}

	int root_idx = start + size/2;
	arr[root_idx].left = &arr[build(size/2, start)];
	arr[root_idx].right = &arr[build(size - size/2 - 1, root_idx + 1)];
	return root_idx;
	// if(size == 0) return;
	// arr[start].val = start + 1;
	// arr[start].order = start;
	// arr[start].left = start > 0 ? arr[start - 1] : NULL;
	// arr[start].right = NULL;
	// arr[start].flip = 0;
	// build(size - 1, start + 1);
}

void inorder(Node * root, bool flip){
	if(!root) {
		// cout << endl; 
		return;
	}
		propa(root, 0);


	bool cop = flip;

	// if(root->flip){
	// 	inorder(root->right, cop);
	// 	// cout << root->val << " <- with bit " << cop << " ";
	// 	// cout << root->val << " ";
	// 	printf("(val is %d, prop is %d, order is %d)\n", root->val, root->order, root->flip);

	// 	// cout << root->order << " ";
	// 	inorder(root->left, cop);
	// } else {
		inorder(root->left, cop);
		// cout << root->val << " <- with bit " << cop << " ";
		// cout << root->val << " ";
		printf("(val is %d, prop is %d, order is %d)\n", root->val, root->order, root->flip);

		// cout << root->order << " ";
		inorder(root->right, cop);	
	// }	
}

int main(){
	int n, m;
	clear(a);
	clear(b);
	clear(arr);
	scanf("%d %d", &n, &m);

	FORI(n) arr[i] = Node(i + 1);

	Node * master = &arr[build(n, 0)];

	FORI(m){
		int c, d;
		scanf("%d %d", &c, &d);
	}
	master = splay(8, master);
	master->left = splay(4, master->left);

	InOrder(master);
	inorder(master, 0);
	if(master->left->left) master->left->left->prop += 5;
	if(master->right) master->right->prop -= 5;
	if(master->left->right) master->left->right->sub = 28;
	master->order = n - 4;
	master->left->order = n;
	
	Node * tmp = master->right;
	if(!tmp) master->right = master->left->left, master->left->left = NULL;
	else{
		while(tmp->left){
			tmp = tmp->left;
		}
		tmp->left = master->left->left, master->left->left = NULL;
	}

	master->flip = 0;
	master->newflip = 0; 
	master->left->flip = 1;
	master->left->newflip = 1;

	tmp = master->left;
	master->left = master->right;
	master->right = tmp;
	cout <<endl;
			// master = splay(20, master);

	inorder(master, 0);
	InOrder(master);

	// master = splay(20, master);
	// master->left = splay(17, master->left);
	// inorder(master, 0);
	// InOrder(master);

	// if(master->left->left) master->left->left->prop += 4;
	// if(master->right) master->right->prop -= 4;
	// if(master->left->right) master->left->right->sub = 0;
	// // master->order = n - 3;
	// // master->left->order = n;
	
	// tmp = master->right;
	// if(!tmp) master->right = master->left->left, master->left->left = NULL;
	// else{
	// 	while(tmp->left){
	// 		tmp = tmp->left;
	// 	}
	// 	tmp->left = master->left->left, master->left->left = NULL;
	// }
	// cout << tmp->order << endl;
	// master->flip = 0;
	// master->newflip = 0; 
	// master->left->flip ^= 1;
	// master->right->flip ^= 1;
	// master->left->newflip = 1;
	// tmp = master->left;
	// master->left = master->right;
	// master->right = tmp;

	// cout << endl;
	// inorder(master, 0);
	// InOrder(master);
}



#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>


#define FORI(n) for(int i = 0; i < n; i++)
#define FORJ(n) for(int j = 0; j < n; j++)
#define FORK(n) for(int k = 0; k < n; k++)
#define	FOR2I(a, b) for(int i = 0; i < a; i++) for(int j = 0; j < b; j++)
#define	FOR2J(a, b) for(int j = 0; j < a; j++) for(int k = 0; k < b; k++)

#define FORIT(S) for(auto it = S.cbegin(); it != S.cend(); it++)
#define clear(S) memset(S, 0, sizeof(S))
#define neg(S) memset(S, -1, sizeof(S))

#define EPS 0.00000001

const int N = 16;
const int state_num = 1034;
const int aug_size = 2068;
const int death = 1033;
const int pipe_num = 'z' - 'a';

char a[N][N];
int n, m, start, master_size, state_size;
int locator[pipe_num], num_active[state_num], is_coin[state_num], coin_map[state_num];
long double trans[state_num][state_num], master[state_num][aug_size];
bool visited[state_num], visited2[state_num], is_rec[state_num];

int find_state(int a, int b, int l) {return l > 0 ? l * N * N + a * N + b : death;}

int delocator(char a, int l) {return locator[a - 'a'] + l * N * N;}

void logic_unit(int init_x, int init_y, int end_x, int end_y){
	char cur = a[init_x][init_y];
	int state[4];
	FORI(4) state[i] = find_state(end_x, end_y, i);
	if(cur == '#') return;
	else if (cur == '!') FORI(3) trans[state[i + 1]][find_state(init_x, init_y, i)] += 1;
	else if (cur >= 'a' && cur <= 'z') FORI(3) trans[state[i + 1]][delocator(cur, i + 1)] += 1;
	else FORI(3) trans[state[i + 1]][find_state(init_x, init_y, i + 1)] += 1;
	FORI(3) num_active[state[i + 1]]++;
}

bool dfs(int state){
	is_rec[state] = false;
	bool tmp = false;
	FORI(state_num) if(is_rec[i] && trans[state][i] > EPS) {tmp |= (is_coin[i] > 0); tmp |= dfs(i);}
	return tmp;
}

bool dfs2(int state){
	visited2[state] = true;
	bool tmp = is_coin[state] > 0;
	FORI(state_num) if(!visited2[i] && trans[state][i] > EPS) {tmp |= (is_coin[i] > 0); tmp |= dfs2(i);}
	return tmp;
}


int elim(){
	for (int i = 0; i < master_size; i++) {
        long double maxEl = abs(master[i][i]);
        int maxRow = i;
        for (int k =i + 1; k < master_size; k++) {
            if (abs(master[k][i]) > maxEl) {
                maxEl = abs(master[k][i]);
                maxRow = k;
            }
        }

        if(!master[maxRow][i]) return i;

        for (int k = i; k < 2 * master_size; k++) {
            long double tmp = master[maxRow][k];
            master[maxRow][k] = master[i][k];
            master[i][k] = tmp;
        }

        for (int k = i + 1; k < master_size; k++) {
            long double c = -master[k][i]/master[i][i];
            for (int j = i; j < 2 * master_size; j++) {
                if (i == j) {
                    master[k][j] = 0;
                } else {
                    master[k][j] += c * master[i][j];
                }
            }
        }
    }
	return -1;
}

void back_sub(){
	for(int i = master_size - 1; i >= 0; i--){
		for(int j = i + 1; j < master_size; j++){
			long double f = master[i][j] / master[j][j];
			for(int k = i + 1; k < 2 * master_size; k++) master[i][k] -= master[j][k] * f;
		}
	}

	FORI(master_size){
		for(int j = i + 1; j < 2 * master_size; j++){
			master[i][j] /= master[i][i];
		}
	}
}

int main(){
	clear(a); clear(trans); neg(locator); clear(num_active); clear(is_coin); clear(visited); neg(coin_map); clear(visited2); clear(is_rec);
	scanf("%d %d", &m, &n);
	FOR2I(m, n){
		scanf("%c", &a[i][j]);
		if(j == 0)scanf("%c", &a[i][j]);
		if(a[i][j] <= 'Z' && a[i][j] >= 'A') locator[a[i][j] - 'A'] = i * N + j; 
		if(a[i][j] == '$') start = find_state(i, j, 3);
	}

	trans[death][death] = 1;
	num_active[death] = 1;
	FORI(m){
		FORJ(n){
			if(i > 0) logic_unit(i, j, i - 1, j);
			if(i < m - 1) logic_unit(i, j, i + 1, j);
			if(j > 0) logic_unit(i, j, i, j - 1);
			if(j < n - 1) logic_unit(i, j, i, j + 1);
			if(a[i][j] > '0' && a[i][j] <= '9') FORK(3) is_coin[find_state(i, j, k + 1)] = a[i][j] - '0';
		}
	}
	FORI(state_num) FORJ(state_num) trans[i][j] /= 1.0 * num_active[i];

	FORI(state_num) is_rec[i] = true;
	dfs(start); 					

	FORI(state_num){
		if(!is_rec[i]){
			clear(visited2);
			if(!dfs2(i)) {is_rec[i] = true;}
		}
	}

	int master_size_y = 0;																							
	master_size = 0;
	FORI(state_num){
		if(i == death || is_rec[i]) continue;

		master_size_y = 0;
		FORJ(state_num){
			if(j != death && !is_rec[j]){
				master[master_size][master_size_y] = -trans[i][j];
				if(master_size == master_size_y) master[master_size][master_size_y] += 1.0;
				master_size_y++;
				
			}
 		}
 		if(i == start) start = master_size;
 		FORK(3) if(is_coin[i] > 0) coin_map[i] = master_size;
 		master_size++;
	}
	FORI(master_size) master[i][master_size + i] = 1.0;

	if(elim() >= 0) {printf("-1\n"); return 0;}
	back_sub();

	long double res = 0;
	FORI(state_num) if(is_coin[i] > 0 && coin_map[i] >= 0){res += 1.0 * is_coin[i] * master[start][master_size + coin_map[i]];}

	printf("%.9Lf\n", res);
	return 0;
}
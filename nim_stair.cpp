#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

#define FORI(n) for(int i = 0; i < n; i++)
#define FORJ(n) for(int j = 0; j < n; j++)
#define FORK(n) for(int k = 0; k < n; k++)

#define neg(S) memset(S, -1, sizeof(S))

#define pb push_back
#define sz size

using namespace std;

const int maxN = 1010;

int a[maxN];
int t, n; 

int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		FORI(n) scanf("%d", &a[i]);
		if(n % 2) {a[n] = 0; n++;}
		sort(a, a + n);
		int res = 0;
		FORI(n / 2) res^= a[(i << 1) + 1] - a[i << 1] - 1;
		if(res) printf("Georgia will win\n");
		else printf("Bob will win\n");
	}
	
	return 0;
}

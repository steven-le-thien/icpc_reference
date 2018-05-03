#include <cstdio>
#include <vector>
#include <iostream>
#include <cstring>
#include <unordered_set>

#define FORI(n) for(int i = 0; i < n; i++)
#define FORJ(n) for(int j = 0; j < n; j++)
#define FORK(n) for(int k = 0; k < n; k++)

#define neg(S) memset(S, -1, sizeof(S))

#define pb push_back
#define sz size

using namespace std;

const int maxN = 100010;

unordered_set<string> us;

int main(){
	while(1){
		int n; cin >> n;
		if(cin.fail()) return 0;
		FORI(n){
			string s; cin >> s;
			unordered_set<string>::iterator it = us.find(s);
			if(it == us.end()) us.insert(s);
			else us.erase(it);
		}
		if(us.empty()) cout << "second player" << endl;
		else cout << "first player" << endl;
		us.clear();
	}
	
	return 0;
}

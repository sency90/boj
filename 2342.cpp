#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;
stringstream ss;
string s;
int v[100001];

int dp[100001][5][5];
const int inf = 0x3f3f3f3f;
const int NA = -1;

int adj[5][5] = {{0,1,2,3,4}, {1,2,0,4,NA}, {2,1,0,3,NA}, {3,2,0,4,NA}, {4,1,0,3,NA}};
int cost[5][5];

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> s;
	ss.str(""); ss.clear();
	ss.str(s);

	int n=1;
	while(true) {
		ss >> v[n];
		if(v[n]==0) break;
		n++;
	}

	memset(dp, 0x3f, sizeof(dp));
	dp[0][0][0] = 0;

	memset(cost, 0x3f, sizeof(cost));
	for(int i=1; i<5; i++) {
		for(int j=0; j<5; j++) { 
			if(adj[i][j] == NA) cost[adj[i][j]][i] = 3; //adj[i][j]->i
			else if(adj[i][j] == i) cost[i][i] = 1; //i->i
			else cost[adj[i][j]][i] = 4; //adj[i][j]->i
		}
	}
	for(int i=1; i<5; i++) cost[0][i] = 2; //0->i
	for(int i=1; i<5; i++) cost[i][i] = 1; //i->i

	for(int l=0; l<5; l++) { //current left-foot
		for(int r=0; r<5; r++) { //current right-foot
			if(l==r) continue;
			for(int i=1; i<=n; i++) {
				if(l!=v[i] && r!=v[i]) continue;
				for(int a=0; a<5; a++) {
					if(a!=l) dp[i][l][r] = min(dp[i][l][r], dp[i-1][a][r] + cost[a][l]); //a->l
					if(a!=r) dp[i][l][r] = min(dp[i][l][r], dp[i-1][l][a] + cost[a][r]); //a->r
				}
			}
		}
	}
	int ans = inf;
	for(int l=0; l<5; l++) {
		for(int r=0; r<5; r++) {
			ans = min(ans, dp[n][l][r]);
		}
	}
	printf("%d\n", ans);
	return 0;
}

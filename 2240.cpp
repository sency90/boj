#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int v[1001];
int dp[1001][31][2];
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int n, w; cin >> n >> w;

	for(int i=1; i<=n; i++) {
		cin >> v[i];
		v[i]--;
	}

	//dp[i][0][1] = 0;
	//dp[i][0][0] = dp[i-1][0][0]+1;
	for(int i=1; i<=n; i++) {
		if(v[i]==0) {
			dp[i][0][0] = dp[i-1][0][0]+1;
		}
	}
	for(int j=1; j<=w; j++) {
		for(int i=j; i<=n; i++) {
			dp[i][j][0] = max(dp[i-1][j-1][1]+(v[i]==0), dp[i-1][j][0]+(v[i]==0));
			dp[i][j][1] = max(dp[i-1][j-1][0]+(v[i]==1), dp[i-1][j][1]+(v[i]==1));
		}
	}

	int ans=0;
	for(int j=1; j<=w; j++) {
		ans = max({ans, dp[n][j][0], dp[n][j][1]});
	}
	printf("%d\n", ans);
	return 0;
}

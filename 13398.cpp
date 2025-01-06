#include <cstdio>
#include <algorithm>
using namespace std;
int v[100010];
int dp[100010][2];
int main() {
	int n; scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		scanf("%d", &v[i]);
	}
	dp[1][0] = v[1];
	dp[1][1] = 0;
	int mx = v[1];
	for(int i=2; i<=n; i++) {
		dp[i][0] = max(dp[i-1][0] + v[i], v[i]);
		dp[i][1] = max(dp[i-1][1] + v[i], dp[i-1][0]);
		mx = max({mx, dp[i][0], dp[i][1]});
	}
	printf("%d\n", mx);
	return 0;
}

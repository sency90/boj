#include <stdio.h>
int v[20][20];
int dp[20][20][3];
bool DiagCheck(int x, int y) {
	return v[x][y]==0 && v[x-1][y-1]==0 && v[x-1][y]==0 && v[x][y-1]==0;
}
int main() {
	int n; scanf("%d", &n);
	dp[1][2][0] = 1;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			scanf("%d", &v[i][j]);
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=2; j<=n; j++) {
			for(int k=0; k<3; k++) {
				if(k==0 && v[i][j+1]==0) {
					dp[i][j+1][k] += dp[i][j][k];
					if(DiagCheck(i+1,j+1)) {
						dp[i+1][j+1][k+1] += dp[i][j][k];
					}
				}
				else if(k==1) {
					if(v[i][j+1]==0) dp[i][j+1][0] += dp[i][j][k];
					if(DiagCheck(i+1,j+1)) dp[i+1][j+1][k] += dp[i][j][k]; //diagonal
					if(v[i+1][j]==0) dp[i+1][j][2] += dp[i][j][k];
				}
				else if(k==2) {
					if(DiagCheck(i+1,j+1)) dp[i+1][j+1][1] += dp[i][j][k];
					if(v[i+1][j]==0) dp[i+1][j][2] += dp[i][j][k];
				}
			}
		}
	}
	int ans=0;
	for(int k=0; k<3; k++) {
		ans += dp[n][n][k];
	}
	printf("%d\n", ans);
	return 0;
}

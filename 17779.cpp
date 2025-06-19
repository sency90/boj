#include <cstdio>
#include <algorithm>
using namespace std;
int N;
bool chk[22][22];
int sum[4][22][22], v[22][22];
int regn_sum[5];
int dx[] = {1,1,-1,-1};
int dy[] = {-1,1,1,-1};
int sdx[] = {-1,0,1,0};
int sdy[] = {0,-1,0,1};
const int INF = 0x3f3f3f3f;
int main() {
	scanf("%d",&N);
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			scanf("%d", &v[i][j]);
			sum[0][i][j] = sum[0][i-1][j]+sum[0][i][j-1]-sum[0][i-1][j-1]+v[i][j];
		}
	}

	for(int i=N; i>=1; i--) {
		for(int j=1; j<=N; j++) {
			sum[1][i][j] = sum[1][i+1][j]+sum[1][i][j-1]-sum[1][i+1][j-1]+v[i][j];
		}
	}

	for(int i=N; i>=1; i--) {
		for(int j=N; j>=1; j--) {
			sum[2][i][j] = sum[2][i+1][j]+sum[2][i][j+1]-sum[2][i+1][j+1]+v[i][j];
		}
	}

	for(int i=1; i<=N; i++) {
		for(int j=N; j>=1; j--) {
			sum[3][i][j] = sum[3][i-1][j]+sum[3][i][j+1]-sum[3][i-1][j+1]+v[i][j];
		}
	}

	chk[1][1]=chk[1][N]=chk[N][1]=chk[N][N]=true;
	int ans = INF;
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			if(chk[i][j]) continue;
			for(int d1=1; d1<=N-1; d1++) {
				for(int d2=1; d2<=N-1; d2++) {
					if(!(i+d1+d2<=N && 1<=j-d1 && j+d2<=N)) break;

					int x=i,y=j,regn_total_sum=0;
					for(int z=0; z<4; z++) {
						regn_sum[z] = sum[z][x+sdx[z]][y+sdy[z]];
						int lim = (z%2==0)?d1:d2;
						for(int k=0; k<lim; k++,x+=dx[z],y+=dy[z]) {
							regn_sum[z] += sum[z][x][y]-sum[z][x+sdx[z]][y+sdy[z]]-v[x][y];
						}
						regn_total_sum += regn_sum[z];
					}
					regn_sum[4] = sum[0][N][N]-regn_total_sum;

					int mn=INF, mx=0;
					for(int k=0; k<5; k++) {
						mn = min(mn, regn_sum[k]);
						mx = max(mx, regn_sum[k]);
					}
					ans = min(ans, mx-mn);
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}

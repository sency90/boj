#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char a[4010], b[4010];
int dp[4010][4010];
int main() {
	scanf("%s%s", a+1, b+1);
	int an = strlen(a+1);
	int bn = strlen(b+1);
	int mx = 0;
	for(int i=1; i<=an; i++) {
		for(int j=1; j<=bn; j++) {
			if(a[i] == b[j]) {
				dp[i][j] = dp[i-1][j-1]+1;
				mx = max(dp[i][j], mx);
			}
		}
	}
	printf("%d\n", mx);
	return 0;
}

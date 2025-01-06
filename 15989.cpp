#include <cstdio>
#include <algorithm>
using namespace std;
int chk[10001][4];
int d[10001][4];
int f(int x, int y) {
	if(x==y) return 1;
	else if(x<y) return 0;
	if(chk[x][y]) return d[x][y];

	chk[x][y] = true;
	int & ret = d[x][y];
	for(int i=1; i<=y; i++) {
		ret += f(x-y, i);
	}
	return ret;
}
int main() {
	int tc; scanf("%d", &tc);
	while(tc--) {
		int n, ans=0;
		scanf("%d", &n);
		for(int i=1; i<=3; i++) {
			ans += f(n,i);
		}
		printf("%d\n", ans);
	}
	return 0;
}

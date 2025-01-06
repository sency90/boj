#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
using namespace std;
const int inf = 0x3f3f3f3f;
int n;
int d[16][16][1<<16];
int v[16][16];
int f(int x, int bit, int fx) {
	int & ret = d[x][fx][bit];
	if(bit == (1<<x)) {
		if(v[fx][x]==0) return ret=inf;
		else return ret = v[fx][x];
	}
	if(ret>=0) return ret;

	ret = inf;
	for(int i=0; i<n; i++) {
		if(v[i][x] == 0) continue;
		if(bit & (1<<i)) {
			ret = min(ret, f(i, (bit^(1<<x)), fx) + v[i][x]);
		}
	}
	if(ret>inf) ret=inf;
	return ret;
}
int main() {
	scanf("%d", &n);
	memset(d, -1, sizeof(d));
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			scanf("%d", &v[i][j]);
		}
	}

	int mn = inf, allBit = (1<<n)-1;
	for(int i=0; i<n; i++) {
		mn = min(mn, f(i, allBit, i));
	}
	printf("%d\n", mn);
	return 0;
}

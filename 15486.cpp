#include <cstdio>
#include <algorithm>
using namespace std;
int d[1500001];
int main() {
	int n; scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		int t,p; scanf("%d%d", &t, &p);
		d[i] = max(d[i], d[i-1]);
		if(i+t-1>n) continue;
		d[i+t-1] = max(d[i+t-1], d[i-1] + p);
	}
	printf("%d\n", d[n]);
	return 0;
}

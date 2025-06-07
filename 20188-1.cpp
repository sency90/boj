//O(N) Solution:
//간선 1개가 정답에 포함되는 개수를 센다.
//Edge(x,y)가 정답에 포함되는 개수는
//전체 정점 N개중 2개를 택하는 것에서
//해당 edge를 지나지 않는 tree내 정점들 중 2개를 택하는 걸 뺀 것과 같다.
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
vector<vector<int>> v;
vector<bool> chk;
vector<ll> d;
int n;
ll ans;
ll combi(int x) {
	if(x<=1) return 0;
	else if(d[x]) return d[x];
	return d[x] = (ll)x*(x-1)/2;
}
int dfs(int x) {
	int ret = 1;
	chk[x] = true;
	for(int y: v[x]) {
		if(chk[y]) continue;
		ret += dfs(y);
	}

	if(x!=1) {
		ans += combi(n)-combi(n-ret);
	}

	return ret;
}
int main() {
#ifdef _WIN32
	freopen("C:\\Users\\User\\Documents\\boj\\in", "r", stdin);
#endif
	scanf("%d", &n);
	v.resize(n+1, vector<int>());
	chk.resize(n+1, false);
	d.resize(n+1, 0);
	for(int i=0; i<n-1; i++) {
		int x,y; scanf("%d%d",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}

	dfs(1);
	printf("%lld\n", ans);
	return 0;
}
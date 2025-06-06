#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
vector<int> v[300001];
bool chk[300001];
ll tree_cnt[300001];
ll tree_hsum[300001];
ll g[300001];
int g_N;

int n;
ll sum;
void dfs(int x, ll hh) {
	chk[x] = true;
	tree_cnt[x] = 1;
	tree_hsum[x] += hh;
	ll cnt = 0;
	vector<int> g;
	for(int i=0; i<v[x].size(); i++) {
		int y = v[x][i];
		if(chk[y]) continue;
		dfs(y, hh+1);
		tree_cnt[x] += tree_cnt[y];
		tree_hsum[x] += tree_hsum[y];
		g.push_back(y);
	}
	//printf("[%d] cnt:%lld, husm:%lld\n", x, tree_cnt[x], tree_hsum[x]);

	for(int i=0; i<g.size(); i++) {
		sum += tree_hsum[g[i]];
		for(int j=i+1; j<g.size(); j++) {
			sum += tree_cnt[g[j]]*tree_hsum[g[i]];
			sum += tree_cnt[g[i]]*tree_hsum[g[j]];
			sum -= hh*tree_cnt[g[i]]*tree_cnt[g[j]];
		}
	}
	g.clear();
}
int main() {
	scanf("%d", &n);
	for(int i=0; i<n-1; i++) {
		int x,y;
		scanf("%d%d", &x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}

	dfs(1,0);
	printf("%lld\n", sum);
	return 0;
}

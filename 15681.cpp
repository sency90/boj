#include <cstdio>
#include <vector>
using namespace std;
vector<vector<int>> v;
vector<int> ans;
int dfs(int x) {
	ans[x] = 1;
	for(int i=0; i<v[x].size(); i++) {
		int y = v[x][i];
		if(ans[y]>0) continue;
		ans[x] += dfs(y);
	}
	return ans[x];
}
int main() {
	int n,r,q; scanf("%d%d%d",&n,&r,&q);
	v.resize(n+1, vector<int>());
	ans.resize(n+1, 0);
	for(int i=0; i<n-1; i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(r);

	for(int i=0; i<q; i++) {
		int u;
		scanf("%d", &u);
		printf("%d\n", ans[u]);
	}
	return 0;
}

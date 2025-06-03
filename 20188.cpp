#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
vector<int> v[300001];
bool chk[300001];

int n;
ll sum;
ll dfs(int x, int hh) {
	chk[x] = true;
	//ll sub[2] = {0,0};
	vector<int> sub;
	int k=0;
	for(int i=0; i<v[x].size(); i++) {
		int y = v[x][i];
		if(chk[y]) continue;
		sub.push_back(dfs(y, hh+1));
	}
	sum += (ll)hh*(n-1);
	int ret = 0;
	for(int i=0; i<sub.size(); i++) ret += sub[i];

	if(sub.size()>=2) {
		for(int i=0; i<sub.size(); i++) {
			for(int j=i+1; j<sub.size(); j++) {
				sum -= hh*((ll)(sub[i]+1)*(sub[j]+1)-1);
			}
		}
	}
	else if(sub.size()==1) sum -= (ll)hh*sub[0];
	//sum -= (ll)hh*((ll)(sub[0]+1)*(sub[1]+1)-1);
	return ret+1;
	//return sub[0] + sub[1] + 1;
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

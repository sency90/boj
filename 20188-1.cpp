#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
vector<int> v[300001];
bool chk[300001];

int n;
ll sum;
ll dd;
int dfs(int x, ll hh) {
	chk[x] = true;
	vector<int> sub;
	int sub_total = 1; //self
	for(int i=0; i<v[x].size(); i++) {
		int y = v[x][i];
		if(chk[y]) continue;
		sub.push_back(dfs(y, hh+1));
		sub_total += sub.back();
	}
	sum += hh*(n-1);
	dd += hh*(n-1);

	for(int i=0; i<sub.size(); i++) {
		sum -= hh;
		for(int j=i+1; j<sub.size(); j++) {
			sum -= hh*sub[i]*sub[j];
		}
	}
	return sub_total;
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
	printf("dd: %lld\n", dd);
	return 0;
}

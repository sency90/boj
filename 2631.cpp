#include <cstdio>
#include <vector>
using namespace std;
vector<int> v;
int main() {
	int n; scanf("%d", &n);
	for(int i=0; i<n; i++) {
		int x; scanf("%d", &x);
		auto it = lower_bound(v.begin(), v.end(), x);
		if(it == v.end()) v.push_back(x);
		else *it = x;
	}
	printf("%d", n-(int)v.size());
	return 0;
}

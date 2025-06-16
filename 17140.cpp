#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int,int> pii;
int r,c,k;
int v[101][101];
int cnt[101];
vector<pii> tmp;
int R=3,C=3;
void operateR() {
	for(int i=0; i<R; i++) {
		memset(cnt, 0, sizeof(cnt));
		for(int j=0; j<C; j++) {
			//if(v[i][j]==0) break;
			cnt[v[i][j]]++;
		}
		tmp.clear();
		for(int j=1; j<=100; j++) {
			if(cnt[j]>0) {
				tmp.push_back(pii(cnt[j], j));
			}
		}
		sort(tmp.begin(), tmp.end());
		int lim = min((int)tmp.size(), 50);

		int k=0;
		for(int j=0; j<lim; j++) {
			v[i][k++] = tmp[j].second;
			v[i][k++] = tmp[j].first;
		}
		C = max(C, k);
		for(; k<100; k++) v[i][k] = 0;
	}
}
vector<int> g;
void operateC() {
	for(int j=0; j<C; j++) {
		g.clear();
		for(int i=0; i<R; i++) {
			//if(v[i][j]==0) break;
			g.push_back(v[i][j]);
		}
		memset(cnt, 0, sizeof(cnt));
		for(int i=0; i<g.size(); i++) {
			cnt[g[i]]++;
		}
		tmp.clear();
		for(int i=1; i<=100; i++) {
			if(cnt[i]>0) {
				tmp.push_back(pii(cnt[i], i));
			}
		}
		sort(tmp.begin(), tmp.end());
		int lim = min((int)tmp.size(), 50);

		int k=0; 
		for(int i=0; i<lim; i++) {
			v[k++][j] = tmp[i].second;
			v[k++][j] = tmp[i].first;
		}
		R = max(R, k);
		for(; k<100; k++) v[k][j] = 0;
	}
}
int main() {
	scanf("%d%d%d",&r,&c,&k);
	r--; c--;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			scanf("%d", &v[i][j]);
		}
	}

	for(int t=0; t<=100; t++) {
		if(v[r][c] == k) {
			printf("%d\n", t);
			return 0;
		}

		if(R>=C) operateR();
		else operateC();
	}
	puts("-1");
	return 0;
}

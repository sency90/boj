#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int t;
int R,C,M;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,1,-1};
struct Info{
	int pos, dir;
	Info(){}
	Info(int pos, int dir):pos(pos),dir(dir) {}
	int next_x() {
		if(dir==0) pos--; //up
		else pos++; //down

		if(pos<=0) { pos=2; dir^=1; }
		else if(pos>R) { pos=R-1; dir^=1; }
		return dir;
	}
	int next_y() {
		if(dir==2) pos++; //right
		else pos--; //left

		if(pos<=0) { pos=2; dir^=1; }
		else if(pos>C) { pos=C-1; dir^=1; }
		return dir;
	}
};
Info dp[101][4][1001];
struct Shark{
	int r,c,s,d,z;
	void move() {
		if(d<=1) {
			int nr = dp[r][d][s].pos;
			int nd = dp[r][d][s].dir;
			r = nr;
			d = nd;
		}
		else {
			int nc = dp[c][d][s].pos;
			int nd = dp[c][d][s].dir;
			c = nc;
			d = nd;
		}
	}
};
Shark v[10001][2];
constexpr int INF = 0x3f3f3f3f;
constexpr int NA = -1;
int get_shark(int c, int t) {
	int mnr=INF, mni=NA;
	for(int i=0; i<M; i++) {
		if(v[i][t].c == c) {
			if(mnr > v[i][t].r) {
				mnr = v[i][t].r;
				mni = i;
			}
		}
	}
	if(mni==NA) return 0;
	else {
		int sz = v[mni][t].z;
		v[mni][t] = v[--M][t]; //reduce a shark
		return sz;
	}
}
int idx[101][101];
void move_shark(int & t) {
	memset(idx,-1,sizeof(idx));
	for(int i=0; i<M; i++) {
		v[i][t].move();
		int & mxidx = idx[v[i][t].r][v[i][t].c];
		if(mxidx<0) mxidx=i;
		else if(v[mxidx][t].z < v[i][t].z) mxidx=i;
	}

	int cnt=0;
	for(int i=1; i<=R; i++) {
		for(int j=1; j<=C; j++) {
			if(idx[i][j]<0) continue;
			v[cnt++][t^1] = v[idx[i][j]][t];
		}
	}
	M=cnt;
	t^=1;
}
typedef pair<int,int> pii;
typedef pair<pii,int> piipi;
piipi regn[4];
int main() {
	scanf("%d%d%d",&R,&C,&M);
	for(int i=0; i<M; i++) {
		int r,c,s,d,z;
		scanf("%d%d%d%d%d",&r,&c,&s,&d,&z);
		v[i][t] = {r,c,s,d-1,z};
	}

	regn[0] = piipi(pii(R,0),-1);
	regn[1] = piipi(pii(1,R+1),1);
	regn[2] = piipi(pii(1,C+1),1);
	regn[3] = piipi(pii(C,0),-1);

	for(int dir=0; dir<4; dir++) {
		for(int p=regn[dir].first.first; p!=regn[dir].first.second; p+=regn[dir].second) {
			Info info(p,dir);
			for(int s=0; s<=1000; s++) {
				dp[p][dir][s] = info;
				if(dir<=1) info.next_x();
				else info.next_y();
			}
		}
	}

	int ans=0;
	for(int i=1; i<=C; i++) {
		ans += get_shark(i,t);
		move_shark(t);
	}
	printf("%d\n", ans);
	return 0;
}

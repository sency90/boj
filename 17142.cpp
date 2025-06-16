#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;
int N,M;
int v[51][51];
struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
};

bool sel[11];
Coord vco_list[11];
int chk[51][51], CHKVAL;
int vco_N;
queue<Coord> q, init_q;
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
constexpr int INF = 0x3f3f3f3f;
int mn = INF;
int e; //empty
int bfs() {
	CHKVAL++;
	q = init_q;
	for(int i=0; i<vco_N; i++) {
		if(!sel[i]) continue;
		chk[vco_list[i].x][vco_list[i].y] = CHKVAL;
		q.push(vco_list[i]);
	}

	int lv=-1,cnt=0,ans=0;
	while(!q.empty()) {
		int sz = q.size();
		lv++;
		for(int z=0; z<sz; z++) {
			Coord co = q.front(); q.pop();
			if(v[co.x][co.y]!=2) ans = lv;
			cnt++;
			for(int i=0; i<4; i++) {
				int nx=co.x+dx[i];
				int ny=co.y+dy[i];
				if(nx<0||ny<0||nx>=N||ny>=N) continue;
				if(v[nx][ny]==1) continue;
				if(chk[nx][ny] == CHKVAL) continue;
				chk[nx][ny] = CHKVAL;
				q.push(Coord(nx,ny));
			}
		}
	}
	for(int i=0; i<vco_N; i++) {
		if(sel[i]) continue;
		if(chk[vco_list[i].x][vco_list[i].y] != CHKVAL) cnt++;
	}
	if(cnt == e+vco_N) return ans;
	else return INF;
}
void dfs(int x, int co_N) {
	if(co_N == M) {
		for(int i=x; i<vco_N; i++) sel[i] = false;
		mn = min(mn, bfs());
		return;
	}
	if(x==vco_N) return;

	sel[x] = true;
	dfs(x+1, co_N+1);
	sel[x] = false;
	dfs(x+1, co_N);
}
int main() {
	scanf("%d%d",&N,&M);
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			scanf("%d", &v[i][j]);
			if(v[i][j]==2) vco_list[vco_N++] = Coord(i,j);
			else if(v[i][j]==0) e++;
		}
	}

	dfs(0,0);
	if(mn == INF) puts("-1");
	else printf("%d\n", mn);
	return 0;
}

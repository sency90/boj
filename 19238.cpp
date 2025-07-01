#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
int N,M,G;
struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
	bool operator<(const Coord & rhs) const {
		if(x==rhs.x) return y<rhs.y;
		else return x<rhs.x;
	}
	bool operator==(const Coord & rhs) const {
		return x==rhs.x && y==rhs.y;
	}
	void sub1() { x--; y--; }
};
struct Passenger{
	Coord src, dst;
};
Passenger p[401];
Coord taxi;
int v[21][21];
int chk[21][21];
int CHKVAL;
queue<Coord> q, init_q;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
vector<Coord> hubo_list;
bool bfs(int & pi, int & dist, Coord dst = Coord(-1,-1)) {
	chk[taxi.x][taxi.y] = ++CHKVAL;
	q = init_q;
	q.push(taxi);
	dist=0;
	hubo_list.clear();
	while(!q.empty()) {
		int sz = q.size();
		for(int z=0; z<sz; z++) {
			Coord co = q.front(); q.pop();
			if(dst.x<0) {
				if(v[co.x][co.y]>0) {
					hubo_list.push_back(co);
				}
			}
			else if(dst == co) return true;
			for(int i=0; i<4; i++) {
				int nx = co.x+dx[i];
				int ny = co.y+dy[i];
				if(nx<0||ny<0||nx>=N||ny>=N) continue;
				if(v[nx][ny]<0) continue;
				if(chk[nx][ny] == CHKVAL) continue;
				chk[nx][ny] = CHKVAL;
				q.push(Coord(nx,ny));
			}
		}
		if(!hubo_list.empty()) break;
		dist++;
	}

	if(hubo_list.empty()) return false;
	sort(hubo_list.begin(), hubo_list.end());
	Coord & co = hubo_list[0];
	pi = v[co.x][co.y];
	v[co.x][co.y] = 0;
	return true;
}
int main() {
	scanf("%d%d%d",&N,&M,&G);
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			scanf("%d", &v[i][j]);
			if(v[i][j]) v[i][j]=-1;
		}
	}
	scanf("%d%d",&taxi.x,&taxi.y);
	taxi.sub1();

	for(int i=1; i<=M; i++) {
		scanf("%d%d%d%d",&p[i].src.x,&p[i].src.y,&p[i].dst.x,&p[i].dst.y);
		p[i].src.sub1();
		p[i].dst.sub1();
		v[p[i].src.x][p[i].src.y] = i;
	}

	int pi, dist;
	while(M>0) {
		pi=0;
		bool ret = bfs(pi, dist);

		if(G<dist || !ret) {
			puts("-1");
			return 0;
		}

		G-=dist;
		taxi = p[pi].src;

		int dummy=-1;
		ret = bfs(dummy, dist, p[pi].dst);
		if(G<dist || !ret) {
			puts("-1");
			return 0;
		}
		G+=dist;
		taxi = p[pi].dst;

		p[pi] = p[M--];
	}
	printf("%d\n", G);

	return 0;
}

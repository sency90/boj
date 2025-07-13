#include <cstdio>
#include <cstring>
using namespace std;
int N,M;
int a[51][51],d[101],s[101];
struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
	bool operator<(const Coord & rhs) const {
		if(x == rhs.x) return y<rhs.y;
		else return x<rhs.x;
	}
};
int dx[] = {0,-1,-1,-1,0,1,1,1};
int dy[] = {-1,-1,0,1,1,1,0,-1};
int crs_dir[] = {1,3,5,7};
int CV;
struct Cloud{
	int co_N; 
	Coord co_list[2501];
	int chk[51][51];

	Cloud():co_N(0) {}
	void init() {
		co_N=0;
		CV=1;
		memset(chk,0,sizeof(chk));
		co_list[co_N++] = Coord(N,1);
		co_list[co_N++] = Coord(N,2);
		co_list[co_N++] = Coord(N-1,1);
		co_list[co_N++] = Coord(N-1,2);
	}

	void move(int d, int s) {
		for(int i=0; i<co_N; i++) {
			Coord & co = co_list[i];
			co.x += s*dx[d];
			co.y += s*dy[d];
			if(co.x<=0) co.x+=(int)((N-co.x)/N)*N;
			else if(co.x>N) co.x-=(int)((co.x-1)/N)*N;
			if(co.y<=0) co.y+=(int)((N-co.y)/N)*N;
			else if(co.y>N) co.y-=(int)((co.y-1)/N)*N;
			chk[co.x][co.y] = CV;
		}
	}
	void rain() {
		for(int i=0; i<co_N; i++) {
			Coord & co = co_list[i];
			a[co.x][co.y]++;
		}
	}
	void copy_magic() {
		//1,3,5,7
		for(int i=0; i<co_N; i++) {
			int cnt=0;
			for(int j=0; j<4; j++) {
				int nx = co_list[i].x + dx[crs_dir[j]];
				int ny = co_list[i].y + dy[crs_dir[j]];
				if(nx<=0||ny<=0||nx>N||ny>N) continue;
				if(a[nx][ny]==0) continue;
				cnt++;
			}
			a[co_list[i].x][co_list[i].y]+=cnt;
		}
	}
	void reinit() {
		co_N=0;
		for(int i=1; i<=N; i++) {
			for(int j=1; j<=N; j++) {
				if(chk[i][j]==CV) continue;
				if(a[i][j]>=2) {
					co_list[co_N++] = Coord(i,j);
					a[i][j]-=2;
				}
			}
		}
		CV++;
	}
};
Cloud cloud;
int main() {
	scanf("%d%d",&N,&M);
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	cloud.init();
	for(int i=0; i<M; i++) {
		int d,s;
		scanf("%d%d", &d,&s);
		d--;
		cloud.move(d,s);
		cloud.rain();
		cloud.copy_magic();
		cloud.reinit();
	}

	int ans=0;
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			ans += a[i][j];
		}
	}
	printf("%d\n", ans);
	return 0;
}

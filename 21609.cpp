#include <cstdio>
using namespace std;
int N,M;
int tmp[22][22];
constexpr int E = -2;
constexpr int NA = -3;
void rotate(int (*arr)[22]) {
	for(int i=1,v=N; i<=N; i++,v--) {
		for(int j=1,u=1; j<=N; j++,u++) {
			tmp[i][j] = arr[u][v];
		}
	}
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			arr[i][j] = tmp[i][j];
		}
	}
}
void do_something(int b, int e, int j, int (*v)[22]) {
	int k=b;
	for(int i=b; i>e; i--) {
		if(v[i][j]!=E) {
			v[k--][j] = v[i][j];
		}
	}
	for(int i=k; i>e; i--) {
		v[i][j] = E;
	}
}
int col[22];
void gravity(int (*v)[22]) {
	for(int j=1; j<=N; j++) {
		int b=NA,e=NA;
		for(int i=N+1; i>=0; i--) {
			if(v[i][j] == -1) {
				if(b==NA) b=i-1;
				else e=i;

				if(e>=0) {
					do_something(b,e,j,v);
					b=e-1;
					e=NA;
				}
			}
		}
	}
}
struct MxInfo{
	int sum, rainbow_cnt, x, y, color;
	MxInfo():sum(1),rainbow_cnt(0),x(0),y(0),color(0) {}
	MxInfo(int sum, int rainbow_cnt, int x, int y, int color):sum(sum),rainbow_cnt(rainbow_cnt),x(x),y(y),color(color) {}
	bool operator>(const MxInfo & rhs) const {
		if(sum == rhs.sum) {
			if(rainbow_cnt == rhs.rainbow_cnt) {
				if(x == rhs.x) return y>rhs.y;
				else return x>rhs.x;
			}
			else return rainbow_cnt > rhs.rainbow_cnt;
		}
		else return sum > rhs.sum;
	}
	MxInfo & operator+=(MxInfo && rhs) {
		this->sum += rhs.sum;
		this->rainbow_cnt += rhs.rainbow_cnt;
		return *this;
	}
};
int v[22][22];
int chk[22][22][6];
int CV;
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int rainbow_cnt;
struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
	bool operator<(const Coord & rhs) const {
		if(x==rhs.x) return y<rhs.y;
		else return x<rhs.x;
	}
};
int co_N, mx_co_N;
Coord co_list[441], mx_co_list[441];
MxInfo dfs(int x, int y, int c) {
	co_list[co_N++] = Coord(x,y);
	chk[x][y][c] = CV;
	MxInfo ret;
	if(v[x][y]==0) ret.rainbow_cnt++;
	for(int i=0; i<4; i++) {
		int nx = x+dx[i];
		int ny = y+dy[i];
		if(nx<=0||ny<=0||nx>N||ny>N) continue;
		if(chk[nx][ny][c] == CV) continue;
		if(v[nx][ny]==c || v[nx][ny]==0) {
			ret += dfs(nx,ny,c);
		}
	}
	return ret;
}

int main() {
	scanf("%d%d",&N,&M);
	for(int i=0; i<=N+1; i++) {
		for(int j=0; j<=N+1; j++) {
			v[i][j] = -1;
		}
	}

	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			scanf("%d", &v[i][j]);
		}
	}

	int score=0;
	while(true) {
		CV++;
		MxInfo mxinfo(0,0,0,0,0), info(0,0,0,0,0);
		mx_co_N=0;
		for(int i=1; i<=N; i++) {
			for(int j=1; j<=N; j++) {
				if(v[i][j]<=0) continue;
				if(chk[i][j][v[i][j]] == CV) continue;

				co_N=0;
				info = dfs(i,j,v[i][j]);
				info.x = i;
				info.y = j;
				info.color = v[i][j];
				if(info > mxinfo) {
					mxinfo = info;
					mx_co_N = co_N;
					for(int k=0; k<co_N; k++) {
						mx_co_list[k] = co_list[k];
					}
				}
			}
		}

		if(mxinfo.x==0 || mx_co_N<=1) break;
		for(int i=0; i<mx_co_N; i++) {
			v[mx_co_list[i].x][mx_co_list[i].y] = E;
		}

		score += mxinfo.sum*mxinfo.sum;

		gravity(v);
		rotate(v);
		gravity(v);
	}
	printf("%d\n", score);
	return 0;
}

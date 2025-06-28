#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
constexpr int N = 4;
struct Fish{
	int fno,x,y,dir;
	bool dead;
	Fish(){}
	Fish(int fno, int x, int y, int dir, bool dead):fno(fno), x(x), y(y), dir(dir), dead(dead) {}
};

struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
};

Coord co_by_fno[17];

void save_map(Fish (*dst)[N][N], Fish (*src)[N][N]) {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			(*dst)[i][j] = (*src)[i][j];
		}
	}
}

void save_co(Coord (*dst)[17], Coord (*src)[17]) {
	for(int i=1; i<17; i++) {
		(*dst)[i] = (*src)[i];
	}
}

Fish m[N][N];
int dx[] = {-1,-1,0,1,1,1,0,-1};
int dy[] = {0,-1,-1,-1,0,1,1,1};

inline void rotate(int & dir) { dir = (dir+1)%8; }

void swap_fish(int fno, int nfno) {
	Coord co = co_by_fno[fno];
	Coord nco = co_by_fno[nfno];
	Fish fish(fno, nco.x, nco.y, m[co.x][co.y].dir, m[co.x][co.y].dead);
	Fish nfish(nfno, co.x, co.y, m[nco.x][nco.y].dir, m[nco.x][nco.y].dead);

	m[nco.x][nco.y] = fish;
	m[co.x][co.y] = nfish;
	co_by_fno[fno] = nco;
	co_by_fno[nfno] = co;
}

void mv_fishes(const Fish & s) {
	for(int fno=1; fno<=16; fno++) {
		const Coord co = co_by_fno[fno];
		if(m[co.x][co.y].dead) continue;
		for(int z=0; z<8; z++) {
			int & dir = m[co.x][co.y].dir;
			int nx = co.x + dx[dir];
			int ny = co.y + dy[dir];
			if(nx<0||ny<0||nx>=N||ny>=N || (s.x==nx && s.y==ny)) {
				rotate(dir);
				continue;
			}
			swap_fish(m[co.x][co.y].fno, m[nx][ny].fno);
			break;
		}
	}
}

int ans;
void dfs(Fish & s, int sum, int depth) {
	//save current state
	Fish prv_m[N][N];
	Coord prv_co_by_fno[17];
	save_map(&prv_m, &m);
	save_co(&prv_co_by_fno, &co_by_fno);

	//eat a fish
	int nsum = sum + m[s.x][s.y].fno;
	m[s.x][s.y].dead = true;
	s.dir = m[s.x][s.y].dir;
	Fish prv_shark = s;
	ans = max(ans, nsum);

	mv_fishes(s);
	for(int i=1; i<=3; i++) {
		int nx = s.x + i*dx[s.dir];
		int ny = s.y + i*dy[s.dir];
		if(nx<0||ny<0||nx>=N||ny>=N) break;
		if(m[nx][ny].dead) continue;

		s.x=nx; s.y=ny;
		dfs(s, nsum, depth+1);
		s = prv_shark;
		//s.x=prv_shark.x, s.y=prv_shark.y;
	}

	//restore map state
	save_map(&m, &prv_m);
	save_co(&co_by_fno, &prv_co_by_fno);
	s = prv_shark;
	m[s.x][s.y].dead = false;
}
int main() {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			int fno, dir;
			scanf("%d%d", &fno, &dir);
			m[i][j] = Fish(fno,i,j,--dir,false);
			co_by_fno[fno] = Coord(i,j);
		}
	}

	Fish shark(0,0,0,0,false);
	dfs(shark, 0, 0);
	printf("%d\n", ans);
	return 0;
}

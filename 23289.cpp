#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <queue>
using namespace std;
int RR,CC,KK,WW;
int vno[22][22];
struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
	bool operator<(const Coord & rhs) const {
		if(x==rhs.x) return y<rhs.y;
		else return x<rhs.x;
	}
};
Coord co_by_vno[22*22];
struct Wind{
	Coord co;
	int dir,pwr,id;
	Wind() {}
	Wind(const Coord & co, int dir, int pwr, int id):co(co),dir(dir),pwr(pwr),id(id) {}

	void print() const {
		printf("wid:%d -> co:(%d,%d), dir:%d, pwr:%d\n", id, co.x, co.y, dir, pwr);
	}
};

vector<Wind> wind_list;
vector<Coord> chkco_list;
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};

vector<vector<int>> w;
vector<vector<vector<int>>> v;

bool HasWall(int from, int to) {
	for(int i=0; i<w[from].size(); i++) {
		if(w[from][i] == to) return true;
	}
	return false;
}

int temp[22*22], delta[22*22];
queue<Wind> q;

constexpr int R=0,D=1,L=2,U=3;
int dirset[4][2][2] = {
	{{U,R},{D,R}}, //R
	{{R,D},{L,D}}, //D
	{{U,L},{D,L}}, //L
	{{L,U},{R,U}}  //U
};
int chgdir(int fake_dir) {
	if(fake_dir == 1) return R;
	if(fake_dir == 2) return L;
	if(fake_dir == 3) return U;
	if(fake_dir == 4) return D;
	assert(false);
	return -1;
}

inline void debug() {
	for(int i=1; i<=RR; i++) {
		for(int j=1; j<=CC; j++) {
			printf("%2d ", temp[vno[i][j]]);
		}
		puts("");
	}
	puts("");
}

inline bool IsOutOfBound(int x, int y) {
	return x<=0||y<=0||x>RR||y>CC;
}
int main() {
	int no=0,wid=0;
	scanf("%d%d%d",&RR,&CC,&KK);
	for(int i=1; i<=RR; i++) {
		for(int j=1; j<=CC; j++) {
			vno[i][j] = no;
			co_by_vno[no++] = Coord(i,j);
			int x; scanf("%d", &x);
			if(1<=x && x<=4) {
				int dir = chgdir(x);
				int nx = i+dx[dir];
				int ny = j+dy[dir];
				if(nx<=0||ny<=0||nx>RR||ny>CC) continue;
				wind_list.push_back(Wind(Coord(nx,ny),dir,5,wid++));
			}
			else if(x==5) {
				chkco_list.push_back(Coord(i,j));
			}
		}
	}
	w.resize(no, vector<int>());
	v.resize(no, vector<vector<int>>(4, vector<int>()));
	scanf("%d",&WW);
	for(int i=0; i<WW; i++) {
		int x,y,t;
		scanf("%d%d%d",&x,&y,&t);
		if(t==0) {
			w[vno[x][y]].push_back(vno[x-1][y]);
			w[vno[x-1][y]].push_back(vno[x][y]);
		}
		else {
			w[vno[x][y]].push_back(vno[x][y+1]);
			w[vno[x][y+1]].push_back(vno[x][y]);
		}
	}

	int nx[2],ny[2];
	for(int x=1; x<=RR; x++) {
		for(int y=1; y<=CC; y++) {
			for(int d=0; d<4; d++) {
				int xx = x+dx[d];
				int yy = y+dy[d];
				if(xx<=0||yy<=0||xx>RR||yy>CC) continue;
				if(HasWall(vno[x][y], vno[xx][yy])) continue;
				v[vno[x][y]][d].push_back(vno[xx][yy]);
			}
			for(int d=0; d<4; d++) {
				for(int i=0; i<2; i++) {
					nx[0] = x+dx[dirset[d][i][0]];
					ny[0] = y+dy[dirset[d][i][0]];
					nx[1] = nx[0]+dx[dirset[d][i][1]];
					ny[1] = ny[0]+dy[dirset[d][i][1]];
					if(IsOutOfBound(nx[0], ny[0])) continue;
					if(IsOutOfBound(nx[1], ny[1])) continue;

					if(HasWall(vno[x][y], vno[nx[0]][ny[0]]) || HasWall(vno[nx[0]][ny[0]], vno[nx[1]][ny[1]])) continue;
					v[vno[x][y]][d].push_back(vno[nx[1]][ny[1]]);
				}
			}
		}
	}

	static int chk[22*22][22*22];
	int choco=0, CV=0;
	while(true) {
#if 1 //Heater Wind
		CV++;
		for(const Wind & wind : wind_list) {
			//wind.print();
			chk[wind.id][vno[wind.co.x][wind.co.y]] = CV;
			q.push(wind);
		}

		while(!q.empty()) {
			int sz = q.size();
			for(int z=0; z<sz; z++) {
				Wind wind = q.front(); q.pop();
				temp[vno[wind.co.x][wind.co.y]] += wind.pwr;
				if(wind.pwr==1) continue;
				for(int to : v[vno[wind.co.x][wind.co.y]][wind.dir]) {
					if(chk[wind.id][to] == CV) continue;
					chk[wind.id][to] = CV;
					q.push(Wind(co_by_vno[to], wind.dir, wind.pwr-1, wind.id));
				}
			}
		}
#endif
		//debug();

#if 1 //Adjust Temperature
		for(int x=1; x<=RR; x++) {
			for(int y=1; y<=CC; y++) {
				for(int d=0; d<4; d++) {
					int xx = x+dx[d];
					int yy = y+dy[d];
					if(xx<=0||yy<=0||xx>RR||yy>CC) continue;
					if(HasWall(vno[x][y], vno[xx][yy])) continue;
					if(temp[vno[x][y]] < temp[vno[xx][yy]]) continue;

					int dt = (temp[vno[x][y]] - temp[vno[xx][yy]])/4;
					delta[vno[x][y]] -= dt;
					delta[vno[xx][yy]] += dt;
				}
			}
		}

		for(int i=0; i<no; i++) {
			temp[i] += delta[i];
			delta[i] = 0;
		}

		//debug();

		for(int x=1; x<=RR; x++) {
			for(int y=1; y<=CC; y++) {
				if(x==1 || x==RR || y==1 || y==CC) {
					if(temp[vno[x][y]]>0) temp[vno[x][y]]--;
				}
			}
		}
#endif

		choco++;

		bool pass = true;
		for(const Coord & co : chkco_list) {
			if(temp[vno[co.x][co.y]]<KK) {
				pass = false;
				break;
			}
		}

		//debug();
		//puts("==============================================================");

		if(pass) break;
		if(choco>100) break;
	}
	printf("%d\n", choco);
	return 0;
}

#include <cstdio>
#include <queue>
#include <map>
#include <vector>
using namespace std;
int N,M,K;

struct Info{
	int x,y,m,s,d;
	Info() {}
	Info(int x, int y, int m, int s, int d):x(x),y(y),m(m),s(s),d(d) {}
};

queue<Info> q;

int dx[] = {-1,-1,0,1,1,1,0,-1};
int dy[] = {0,1,1,1,0,-1,-1,-1};

map<int, vector<Info>> dic;
int t;

void correct(int & x, int & y) {
	while(x>N) x-=N;
	while(y>N) y-=N;
	while(x<=0) x+=N;
	while(y<=0) y+=N;
}

struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
};

constexpr int o=1, e=2, mask=3;

int dir[2][4] = {{0,2,4,6}, {1,3,5,7}};

int main() {
	scanf("%d%d%d",&N,&M,&K);
	for(int i=0; i<M; i++) {
		int x,y,m,s,d;
		scanf("%d%d%d%d%d",&x,&y,&m,&s,&d);
		q.push(Info(x,y,m,s,d));
		//v[x][y] = Info(x,y,m,s,d);
	}

	int lv=0;
	while(!q.empty()) {
		int sz = q.size();
		for(int z=0; z<sz; z++) {
			Info info = q.front(); q.pop();
			int nx = info.x + info.s*dx[info.d];
			int ny = info.y + info.s*dy[info.d];
			correct(nx,ny);
			dic[nx*N+ny].push_back(Info(nx, ny, info.m, info.s, info.d));
		}

		for(auto & it : dic) {
			if(it.second.size()==1) {
				q.push(it.second[0]);
				continue;
			}

			int x = (it.first)/N;
			int y = (it.first)%N;

			int M=0, S=0, eo=0;
			for(int i=0; i<it.second.size(); i++) {
				M += it.second[i].m;
				S += it.second[i].s;
				if(it.second[i].d&1) eo|=o;
				else eo|=e;
			}
			M/=5;
			if(M==0) continue;
			S/=(int)it.second.size();

			int di = (eo==mask)?1:0;
			for(int i=0; i<4; i++) {
				q.push(Info(x,y,M,S,dir[di][i]));
			}
			it.second.clear();
		}
		dic.clear();
		if(++lv == K) break;
	}

	int ans=0;
	while(!q.empty()) {
		ans += q.front().m; q.pop();
	}
	printf("%d\n", ans);
	return 0;
}

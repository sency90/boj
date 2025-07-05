#include <cstdio>
using namespace std;
int N,M,K;

struct Info{
	int x,y,m,s,d;
	Info() {}
	Info(int x, int y, int m, int s, int d):x(x),y(y),m(m),s(s),d(d) {}
	bool operator<(const Info & rhs) const {
		if(x==rhs.x) return y<rhs.y;
		else return x<rhs.x;
	}
};

int dx[] = {-1,-1,0,1,1,1,0,-1};
int dy[] = {0,1,1,1,0,-1,-1,-1};

void correct(int & x, int & y) {
	x%=N, y%=N;
	if(x<0) x+=N;
	if(y<0) y+=N;
}

struct Coord{
	int x,y;
	Coord() {}
	Coord(int x, int y):x(x),y(y) {}
};

constexpr int o=1, e=2, mask=3;

int dir[2][4] = {{0,2,4,6}, {1,3,5,7}};

Info info_list[2][2500*4];
int info_N[2];
int gno[50][50], gcnt, gsz[2500];
void init() {
	int k=0;
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			gno[i][j] = -1;
			gsz[k++] = 0;
		}
	}
	info_N[1]=gcnt=0;
}

template <typename T>
struct Msort{
	T tmp[10000];
	void go(T *arr, int s, int e) {
		if(s+1>=e) return;
		int m = (s+e)>>1;
		go(arr, s, m);
		go(arr, m, e);

		int i=s, j=m, k=s;
		while(i<m && j<e) {
			if(arr[i] < arr[j]) tmp[k++] = arr[i++];
			else tmp[k++] = arr[j++];
		}
		while(i<m) tmp[k++] = arr[i++];
		while(j<e) tmp[k++] = arr[j++];
		for(i=s; i<e; i++) arr[i] = tmp[i];
	}
};

Msort<Info> msort;


int main() {
	scanf("%d%d%d",&N,&M,&K);
	for(int i=0; i<M; i++) {
		int x,y,m,s,d;
		scanf("%d%d%d%d%d",&x,&y,&m,&s,&d);
		info_list[0][info_N[0]++] = Info(--x,--y,m,s,d);
	}

	int lv=0;
	while(info_N[0]>0) {
		init();
		for(int z=0; z<info_N[0]; z++) {
			Info & info = info_list[0][z];
			int nx = info.x + info.s*dx[info.d];
			int ny = info.y + info.s*dy[info.d];
			correct(nx,ny);
			if(gno[nx][ny]<0) gno[nx][ny]=gcnt++;
			info_list[1][info_N[1]++] = Info(nx, ny, info.m, info.s, info.d);
			gsz[gno[nx][ny]]++;
		}

		msort.go(info_list[1], 0, info_N[1]);

		info_N[0] = 0;
		for(int z=0; z<info_N[1]; z++) {
			Info & info = info_list[1][z];
			int sz = gsz[gno[info.x][info.y]];
			if(sz==1) {
				info_list[0][info_N[0]++] = info;
				continue;
			}

			int M=0, S=0, eo=0;
			for(int i=z; i<z+sz; i++) {
				M += info_list[1][i].m;
				S += info_list[1][i].s;
				if(info_list[1][i].d&1) eo|=o;
				else eo|=e;
			}
			M/=5;
			if(M==0) {
				z+=sz-1;
				continue;
			}
			S/=sz;

			int di = (eo==mask)?1:0;
			for(int i=0; i<4; i++) {
				info_list[0][info_N[0]++] = Info(info.x, info.y, M, S, dir[di][i]);
			}
			z += sz-1;
		}
		if(++lv == K) break;
	}

	int ans=0;
	for(int i=0; i<info_N[0]; i++) {
		ans += info_list[0][i].m;
	}
	printf("%d\n", ans);
	return 0;
}

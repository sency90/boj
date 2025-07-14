#include <cstdio>
using namespace std;
constexpr int U=0, D=1, F=2, B=3, L=4, R=5;
constexpr int dx[] = {0,1,0,-1};
constexpr int dy[] = {1,0,-1,0};
constexpr int roll[4][5] = {
	{U,R,D,L,U}, //East
	{U,F,D,B,U}, //South
	{U,L,D,R,U}, //West
	{U,B,D,F,U}  //North
};

int N,M,K;
int v[21][21];
struct Dice{
	int state[6];
	Dice() {
		state[U] = 1;
		state[D] = 6;
		state[F] = 5;
		state[B] = 2;
		state[L] = 4;
		state[R] = 3;
	}

	void rotate(int dir) {
		int tmp = state[roll[dir][4]];
		for(int i=3; i>=1; i--) {
			state[roll[dir][i+1]] = state[roll[dir][i]];
		}
		state[roll[dir][1]] = tmp;
	}
};

struct Coord{
	int x,y;
};

inline void rot180(int & dir) {
	dir = (dir+2)%4;
}

inline void crot90(int & dir) {
	dir = (dir+1)%4;
}

inline void ccrot90(int & dir) {
	dir = (dir-1+4)%4;
}

void GoNext(Coord & co, int & dir) {
	int nx = co.x + dx[dir];
	int ny = co.y + dy[dir];
	if(nx<0||ny<0||nx>=N||ny>=M) {
		rot180(dir);
		GoNext(co, dir);
		return;
	}
	co = Coord{nx,ny};
}

int CV;
int chk[21][21];
int dfs(int x, int y) {
	chk[x][y] = CV;
	int ret = 1;
	for(int i=0; i<4; i++) {
		int nx = x+dx[i];
		int ny = y+dy[i];
		if(nx<0||ny<0||nx>=N||ny>=M) continue;
		if(chk[nx][ny] == CV) continue;
		if(v[nx][ny] != v[x][y]) continue;
		ret += dfs(nx, ny);
	}
	return ret;
}

int main() {
	scanf("%d%d%d",&N,&M,&K);
	for(int i=0; i<N; i++) {
		for(int j=0; j<M; j++) {
			scanf("%d", &v[i][j]);
		}
	}

	Dice dice;
	Coord co{0,0};
	int dir=0, score=0;

	while(K--) {
		GoNext(co, dir);
		dice.rotate(dir);

		CV++;
		int cnt = dfs(co.x, co.y);

		score += cnt * v[co.x][co.y];
		//printf("cnt:%d, v[%d][%d]:%d, dice.state[D]:%d\n", cnt, co.x, co.y, v[co.x][co.y], dice.state[D]);

		if(dice.state[D] > v[co.x][co.y]) crot90(dir);
		else if(dice.state[D] < v[co.x][co.y]) ccrot90(dir);
	}
	printf("%d\n", score);
	return 0;
}

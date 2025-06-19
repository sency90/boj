#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
constexpr int NA = -1;
int N, K;
struct Horse{
	int x,y,dir;
	Horse(){}
	Horse(int x, int y, int dir):x(x),y(y),dir(dir) {}
};
Horse h[11];
int v[15][15];
struct Cell{
	vector<int> hidx_list;
	int color;
	Cell():color(2) {}
};
Cell board[15][15];
int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};
bool move(int x, int y, int hidx, int tno) {
	int tx=h[hidx].x+dx[h[hidx].dir];
	int ty=h[hidx].y+dy[h[hidx].dir];

	Cell & b = board[x][y];
	int list_idx=NA;
	for(int i=0; i<b.hidx_list.size(); i++) {
		if(b.hidx_list[i] == hidx) {
			list_idx = i;
			break;
		}
	}

	Cell & tb = board[tx][ty];
	if(tb.color == 2) {//blue
		if(tno==1) {
			h[hidx].dir^=1;
			return move(x,y,hidx,tno+1);
		}
	}
	else { //white & red
		if(tb.color == 1) { //red
			reverse(b.hidx_list.begin()+list_idx, b.hidx_list.end());
		}
		for(int i=list_idx; i<b.hidx_list.size(); i++) {
			h[b.hidx_list[i]].x = tx;
			h[b.hidx_list[i]].y = ty;
		}
		tb.hidx_list.insert(tb.hidx_list.end(), b.hidx_list.begin()+list_idx, b.hidx_list.end());
		b.hidx_list.erase(b.hidx_list.begin()+list_idx, b.hidx_list.end());
		return (int)tb.hidx_list.size()>=4;
	}
	return false;

}
int main() {
	scanf("%d%d",&N,&K);
	int color;
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			scanf("%d",&board[i][j].color);
		}
	}

	for(int i=0; i<K; i++) {
		int x,y,dir;
		scanf("%d%d%d",&x,&y,&dir);
		h[i] = {x,y,dir-1};
		board[x][y].hidx_list.push_back(i);
	}

	for(int t=1; t<=1000; t++) {
		for(int i=0; i<K; i++) {
			if(move(h[i].x, h[i].y, i, 1)) {
				printf("%d\n", t);
				return 0;
			}
		}
	}
	puts("-1");
	return 0;
}

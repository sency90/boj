#include <cstdio>
using namespace std;
int n,m,k;
int a[11][11];
struct Tree{
	int age;
	bool operator<(const Tree & rhs) const {
		return age < rhs.age;
	}
	Tree():age(0){}
};
struct Ground{
	int nut, tree_N, prv_tree_N, nxt_tree_N;
	Tree tree_list[10001];
	Ground():nut(5),tree_N(0),prv_tree_N(0) {}
};
Ground ground[11][11];

Tree tmp[10001];
void msort(Tree *list, int s, int e) {
	if(s+1>=e) return;
	int m = ((s+e)>>1);
	msort(list, s, m); msort(list, m, e);
	int i=s, j=m, k=s;
	while(i<m && j<e) {
		if(list[i].age < list[j].age) tmp[k++] = list[i++];
		else tmp[k++] = list[j++];
	}
	while(i<m) tmp[k++] = list[i++];
	while(j<e) tmp[k++] = list[j++];
	for(i=s; i<e; i++) list[i]=tmp[i];
}

int dx[] = {-1,-1,-1,0,1,1,1,0};
int dy[] = {-1,0,1,1,1,0,-1,-1};
void spring(int x, int y) {
	Ground & g = ground[x][y];
	msort(g.tree_list, 0, g.tree_N);
	bool is_in = false;
	for(int i=0; i<g.tree_N; i++) {
		g.nut -= g.tree_list[i].age;
		if(g.nut < 0) {
			is_in = true;
			g.nut += g.tree_list[i].age; //restore
			g.prv_tree_N = g.tree_N;
			g.tree_N = i;
			break;
		}
		g.tree_list[i].age++;
		if(!is_in) g.prv_tree_N = g.tree_N;
	}
}
void summer(int x, int y) {
	Ground & g = ground[x][y];
	for(int i=g.tree_N; i<g.prv_tree_N; i++) {
		g.nut += g.tree_list[i].age/2;
		g.tree_list[i].age = 0;
	}
	g.prv_tree_N = g.tree_N;
}
void pre_fall(int x, int y) {
	Ground & g = ground[x][y];
	g.nxt_tree_N = g.tree_N;
}
void fall(int x, int y) {
	Ground & g = ground[x][y];
	for(int i=0; i<g.tree_N; i++) {
		if(g.tree_list[i].age%5 == 0) {
			for(int j=0; j<8; j++) {
				int nx = x+dx[j];
				int ny = y+dy[j];
				if(nx<0||ny<0||nx>=n||ny>=n) continue;
				Ground & ng = ground[nx][ny];
				ng.tree_list[ng.nxt_tree_N++].age = 1;
			}
		}
	}
}
void post_fall(int x, int y) {
	Ground & g = ground[x][y];
	g.tree_N = g.nxt_tree_N;
}
void winter(int x, int y) {
	ground[x][y].nut += a[x][y];
}

void (*f[6])(int, int) = {spring, summer, pre_fall, fall, post_fall, winter};

int main() {
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			scanf("%d", &a[i][j]);
		}
	}

	int x,y,z;
	for(int i=0; i<m; i++) {
		scanf("%d%d%d",&x,&y,&z);
		Ground & g = ground[x-1][y-1];
		g.tree_list[g.tree_N++].age = z;
	}

	for(int a=0; a<k; a++) {
		for(int b=0; b<6; b++) {
			for(int i=0; i<n; i++) {
				for(int j=0; j<n; j++) {
					f[b](i,j);
				}
			}
		}
	}
	int ans = 0;
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			ans += ground[i][j].tree_N;
		}
	}
	printf("%d\n", ans);
	return 0;
}

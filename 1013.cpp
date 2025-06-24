#include <cstdio>
#include <cstring>
using namespace std;
int T,N;
char s[202];
constexpr int NA = -1;

int z(const char *s, int idx, int th) {
	if(s[idx] == '0') return z(s, idx+1, th+1);
	else if(th==0) return NA;
	else return idx;
}
int o(const char *s, int idx, int th) {
	if(s[idx] == '1') return o(s, idx+1, th+1);
	else if(th==0) return NA;
	else return idx;
}
int b(const char *s, int idx) { //10
	if(strncmp(s+idx, "10", 2)==0) {
		return idx+2;
	}
	else return NA;
}
int c(const char *s, int idx) { //01
	if(strncmp(s+idx, "01", 2)==0) {
		return idx+2;
	}
	else return NA;
}

int a(const char *s, int idx) { //(100+1+ | 01)+	
	if(s[idx]==0) return idx;

	int nidx = b(s, idx); //idx+=nidx;
	if(nidx == NA) {
		nidx = c(s, idx);
		if(nidx == NA) return NA;
	}
	else {
		idx = nidx;
		nidx = z(s, idx, 0);
		if(nidx == NA) return NA;

		idx = nidx;
		nidx = o(s, idx, 0);
		if(nidx == NA) return NA;
		for(int i=idx; i<nidx; i++) {
			nidx = a(s,i+1);
			if(nidx != NA) {
				return nidx;
			}

		}
	}
	return NA;
	//return a(s, res);
}

int main() {
	scanf("%d", &T);
	for(int i=0; i<T; i++) {
		memset(s,0,sizeof(s));
		scanf("%s", s);
		N = strlen(s);
		int idx=0;
		if(a(s,idx)==N) puts("YES");
		else puts("NO");
	}
	return 0;
}

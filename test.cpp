#include <cstdio>
#include <cstring>
using namespace std;
int main() {
	int cnt=0;

	int lim=200;
	while(true) {
		for(int i=0; i<lim; i++) {
			cnt++;
			printf("A");
			if(cnt==4000) break;
		}
		if(cnt==4000) break;
		cnt++;
		printf("C");
		if(cnt==4000) break;
		lim++;
	}
	puts("");

	cnt=0;
	lim = 100;
	while(true) {
		for(int i=0; i<lim; i++) {
			cnt++;
			printf("A");
			if(cnt==4000) break;
		}
		if(cnt==4000) break;
		cnt++;
		printf("C");
		if(cnt==4000) break;
		lim+=20;
	}

	return 0;
}

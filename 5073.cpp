#include <cstdio>
using namespace std;
int a[3];
void judge() {
		if(a[0]==a[1] && a[1]==a[2]) {
			puts("Equilateral");
			return;
		}
		else {
			int sum = a[0]+a[1]+a[2];
			for(int i=0; i<3; i++) {
				if(sum-a[i] <= a[i]) {
					puts("Invalid");
					return;
				}
			}
		}

		if(a[0]==a[1] || a[1]==a[2] || a[2]==a[0]) {
			puts("Isosceles");
			return;
		}
		else if(a[0]!=a[1] && a[1]!=a[2] && a[2]!=a[0]) {
			puts("Scalene");
			return;
		}
		puts("Invalid");
}
int main() {
	while(true) {
		scanf("%d%d%d",&a[0],&a[1],&a[2]);
		if(a[0]==0 && a[1]==0 && a[2]==0) return 0;

		judge();
	}
	return 0;
}

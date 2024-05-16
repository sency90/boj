#include <stdio.h>
int main() {
    int i,n,t;
    while((t=getchar()) < 48); //숫자를 하나 받는다. 숫자를 받을때까지 반복문을 돈다.
    printf("%d\n", t&15); //1111이라는 mask를 씌운다.
    //즉, 숫자를 getchar()를 통해 문자형태로 받았기 때문에 이를 숫자형태로 변환하는 것이다.
    //일의자리 숫자는 0~9이므로 이는 0000~1001 라는 이진수로 표현할 수 있으므로 4bit짜리 마스크(1111)를 씌운 것이다.

    //48을 이진수로 나타내면 110000이고 &연산자를 썼으므로 이를 마스크로 활용하겠다는 얘기인데,
    //이것을 for의 반복을 계속하는 조건쪽에 썼으므로 48(숫자 0의 아스키값)이하로 읽힌 문자들(\n, EOF, \r 등등...)을 전부 숫자 0로 취급해버리겠다는 뜻이다.
    //즉, 숫자가 아닌 값이 찍히는 순간 반복문을 종료하겠다는 뜻.

    for(n=t&15; (t=getchar())&48; n = n*10 + (t&15));
    //아! 그러니까 바로 위의 반복문은 숫자가 아닌 다른 문자가 나올때까지 입력을 받으면서
    //초기값(t&15)은 위의 while((t=getchar()) < 48)에서 구한 첫번째 숫자값(예를들어 사용자가 처음에 452를 입력했다면 4라는 숫자 하나만 의미)
    //처음 적히는 숫자를 일의 자리 단위로만 하나씩 받으므로 위와 같이 n = n*10 + (t&15)와 같은 구문이 필요함.


}
#include <stdio.h>

#define MAXLINE 1000
char s[MAXLINE];
void itoa(int n);

int main()
{
  itoa(-157);
  printf("%s", s);

  return 0;
}

void  itoa(int n) {

static int i = 0;

  if (n < 0) {

    s[i] = '-';
    ++i;
    n = -n;
  }

  if (n / 10) {
    itoa(n / 10);
  }

  s[i] = n % 10 + '0';
  s[++i] = '\0';
}


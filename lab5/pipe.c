#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main() {
  int potok_fd[2], licznik, status;
  char bufor[BUFSIZ], filename[50], sign;
  FILE *f;

  if (pipe(potok_fd) == -1) {
    perror("pipe");
    exit(1);
  }

  if (fork() == 0) {
    close(0);
    dup(potok_fd[0]);
    close(potok_fd[0]);
    close(potok_fd[1]);
    execlp("display", "display", NULL);
  }
  else {
    printf("Podaj nazwe pliku \n");
    scanf("%s", filename);
    close(1);
    f = fopen(filename, "r");
    while (feof(f) == 0) {
      sign = getc(f);
      write(potok_fd[1], &sign, 1);
    }
    fclose(f);
    close(potok_fd[1]);
    close(0);
  }
  return (0);
}

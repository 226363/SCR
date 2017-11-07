#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  int potok_fd[2], i, sign;
  char *fifo = "ff";
  FILE *f;

  if (mkfifo(fifo, 0666) < 0) {
    perror("fifo");
    exit(1);
  }
  for (i = 1; i < argc; i++) {
    potok_fd[0] = open(fifo, O_WRONLY);
    /*  readFile(fd[0], argv[i]);  */
    f = fopen(argv[i], "r");
    while (feof(f) == 0) {
      sign = getc(f);
      write(potok_fd[0], &sign, 1);
    }
    fclose(f);
    close(potok_fd[0]);
  }

  unlink(fifo);
  return (0);
}

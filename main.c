#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    perror("Wrong number of arguments!");
    exit(-1);
  }

  FILE *file = fopen(argv[1], "r");

  if (!file) { perror("Incorrect input file!\n"); }

  char comand_name[FILENAME_MAX];
  char arg[FILENAME_MAX];
  int t, i = 0;

  while ((fscanf(file, "%d %s %s", &t, comand_name, arg)) == 3) {
    printf("%s is executed with delay %d\n", comand_name, t);
    pid_t p_id = fork();
    if (p_id < 0) {
      perror("couldn't make process\n");
    } else if (p_id == 0) {
      printf("%s %s is executed in child\n", comand_name, arg);
      sleep(t);
      execlp(comand_name, comand_name, arg, (char *) NULL);
    }
  }

  while (wait(NULL) != -1) {}

  if (feof(file))
    puts("end of the file reached successfully");

  fclose(file);
  return EXIT_SUCCESS;
}
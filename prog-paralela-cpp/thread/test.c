#include <stdio.h>
int main(int argc, char *argv[]) {

  char read = recv(buf);
  if (read != -1) {
    char send = send(buf);
    if (send!=-1) {
      printf("Done");
    } else {
      printf("Done");
    }
  }

  char read = recv(buf);
  if (read == -1) {
    printf("Error");
    return -1;
  }

  char send = send(buf);
  if (send==-1) {
    printf("Error");
    return -1;
  }

  printf("Done");

  return 0; 
}

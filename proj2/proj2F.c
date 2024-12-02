#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int my_strlen(char *str) {
  // TODO #1:
  int size = 1;
  while (str[size] != '\0'){
      size++;
  }
  return size;

}

void str_reverse(char *str) {
  // TODO #2:
  int right = 0;
  int left = my_strlen(str) - 1;
  while (right < left){
    char temp = str[left];
    str[left] = str[right];
    str[right] = temp;
    right++;
    left--;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <string>\n", argv[0]);
    exit(EXIT_FAILURE);
  } else {
    // Attempt to reverse the string using your str_reverse function
    char *str = malloc(strlen(argv[1]) + 1);
    strcpy(str, argv[1]);
    str_reverse(str);
    printf("Original string: %s, reversed string: %s\n", argv[1], str);
    exit(EXIT_SUCCESS);
 }
}

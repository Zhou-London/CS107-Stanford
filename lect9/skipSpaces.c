#include <stdio.h>
#include <string.h>

void skipSpaces(char** strPtr)
{
  int offset = strspn(*strPtr, " ");
  *strPtr += offset;
}

int main(int argc, char* argv[])
{
  if(argc == 1){
    printf("Usage: skipSpaces <String>\n");
    return 0;
  }
  skipSpaces(&argv[1]);
  printf("%s\n", argv[1]);
  return 0;
}

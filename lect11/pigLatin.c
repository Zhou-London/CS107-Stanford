#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOWERCASE_ALPHA "abcdefghijklmnopqrstuvwxyz"
#define LOWERCASE_VOWEL "aeiou"

void pig_vowel(char* str, char* res);
void pig_regular(char* str, char* res);

char* pig_latin(char* str){
  //Check if it starts with English Letter
  if(strcspn(str, LOWERCASE_ALPHA) > 0){
    return NULL;
  }

  char* res = NULL;

  if(strchr(LOWERCASE_VOWEL, str[0]) != NULL){
    int n = strlen(str) + strlen("way");
    res = malloc(sizeof(char) * (n + 1));
    pig_vowel(str, res);
  }else if(strchr(LOWERCASE_ALPHA, str[0]) != NULL){
    int n = strlen(str) + strlen("ay");
    res = malloc(sizeof(char) * (n + 1));
    pig_regular(str, res);
  }

  return res;
}

void pig_vowel(char* str, char* res){
  strcpy(res,str);
  strcat(res, "way");
}

void pig_regular(char* str, char* res){
  int offset = strcspn(str, LOWERCASE_VOWEL);
  strcpy(res, str + offset);
  strncat(res, str, offset);
  strcat(res, "ay");
}

void pig_list(char** strs){
  char* item = pig_latin(strs[0]);
  if(item == NULL){
    item = strdup(strs[0]);
  }
  

int main(){
  char* test = pig_latin("banana");
  printf("%s\n", test);
  free(test);
  return 0;
}

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <string>

#define MAX 1024
char buf[MAX];

int do_face(){
    memset(buf, 0, MAX);
    printf("[shell@localhost]$ ");
    fflush(stdout);
    if((scanf("%[^\n]%*c",buf) == 0)){
      getchar();
      return -1;
    }
    printf("%s\n", buf);
    return 1;
}

char** do_parse(char* buf){
  char* ptr = buf;
  int argc = 0;
  static char* argv[32];
  while(*ptr != '\0'){
    if(!isspace(*ptr)){
      argv[argc++] = ptr;
      while((!isspace(*ptr)) && (*ptr)!= '\0'){
        ptr++;
      }
    }else{
      while(!(isspace(*ptr))){
        *ptr = '\0';
        ptr++;
      }
    }
  }
  printf("argc = %d\n", argc);
  for(int i = 0; i < argc; ++i){
    printf("argv[%d] : %s\n", i, argv[i]);
  }
  argv[argc] = NULL;
  return argv;
}

int do_exec(char* buf){
  char** argv = {NULL};

  argv = do_parse(buf);
  pid_t pid = fork();
  if(pid == 0){
    //child
    argv = do_parse(buf);
    if(argv[0] == NULL){
      exit(-1);
    }
    execvp(argv[0],argv); 
  }else{
    waitpid(pid, NULL, 0);
  }

  return 0;
}

int main() {
  
  while(1){
    if(do_face() < 0){
      continue;
    }

    do_exec(buf);

  }
   
  return 0;
}


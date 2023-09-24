#include <error.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

#define __USE_GNU
#include <dlfcn.h>

static struct dirent *(*orig_readdir) (DIR *) = NULL;

struct dirent *readdir (DIR * dirp){
   if (orig_readdir == NULL){
      orig_readdir = dlsym (RTLD_NEXT, "readdir");
      if (orig_readdir == NULL)
         error (1, errno, "dlsym");
      fprintf(stderr, "Catched\n");
   }
   return (orig_readdir (dirp));
}

int main(){
   printf("running\n");
   
   return 0;
}

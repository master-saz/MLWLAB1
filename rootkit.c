#include <error.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

#define __USE_GNU
#include <dlfcn.h>

static struc dirent *(*old_readdir) (DIR *) = NULL;

struct dirent *
readdir (DIR * dirp){
   if (old_readdir == NULL){
      old_readdir = dlsym (RTLD_NEXT, "readdir");
      if (old_readdir == NULL)
         error (1, errno, "dlsym");
      fprintf(stderr, "Catched\n");
   }
   return (old_readdir (dirp));
}

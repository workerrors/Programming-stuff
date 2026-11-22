#include <stddef.h>
#include <stdio.h>

// argc counts whole chunks separated by space. System fills argv with the strings
// on command line, indexed. 
int main(int argc, char *argv[]) {

//  If the chunk count is below 2, did not specify filename
//  then it throws an error
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    } else {

//      Checks to see if 3 arguments are given
//      if 3 arguments, passes this loop to rename file 
        if (argc == 3) {

            if (rename(argv[1], argv[2]) == 0) {
                printf("Success. \n");
                return 0;
            } else {
                perror("Could not change file name. \n");
                return 1;

                
            }
        
        }
    
    }


//  Searches for the listed argv data, in a read mode
    FILE *fptr = fopen(argv[1], "r");

//  If file opens and nothing to read, succeeds. If file can not open, file directory error
    if (!fptr) {

// errno is global variable for errors, errors grabbed via fopen
// perror grabs the error from errno
        perror(argv[1]);
        return 1;
    }

// Specify basket for grabbing byte amount
    char buffer[4096];

// TOol to check how much is grabbed
    size_t bytes_read;

// Grab bytes, tries to get max char buffer each grab, counts how many is grabbed, goes on 
// as long as there is at least 1 byte left
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), fptr)) > 0) {

//  bytes_read is included so only new data in the array is printed
// sizeof(buffer) would print left over bytes and new ones at the same time 
        fwrite(buffer, 1, bytes_read, stdout);
    }


    putchar('\n');

    fclose(fptr);
    return 0;


}

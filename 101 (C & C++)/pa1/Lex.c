/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa1
 */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "List.h"
#define MAX_LINE_LENGTH 1000

int main(int argc, char* argv[]){
    FILE *in, *out;
    char *fileerr = "There was a problem opening the file.\n";
    char line[MAX_LINE_LENGTH];
    int lines = 0;

    if (argc != 3) { //checking number of args
        fprintf(stderr, "Lex needs exactly two arguments: ./Lex <input file> <output file>\n");
        exit(EXIT_FAILURE);
    }

    char *in_name = argv[1];
    char *out_name = argv[2]; //copying file names

    //opening the files
    if (access(in_name, F_OK) != 0) {
        fprintf(stderr, "%s\n", fileerr); //printing file error if cant open
        return 1;
    }
    in = fopen(in_name, "r");
    out = fopen(out_name, "w+");
    if(in == NULL || out == NULL) {
        fprintf(stderr, "error opening files\n");
        exit(EXIT_FAILURE);
    }

    //first parse to get line number
    while(fgets(line, MAX_LINE_LENGTH, in) != NULL) lines++;

    //mallocing string array
    char **lines_arr = malloc(lines * sizeof (char *));
    for (int j = 0; j < lines; j++) {
        lines_arr[j] = NULL;
    }

    rewind(in);
    //second parse to read in lines
    int i = 0;
    while(fgets(line, MAX_LINE_LENGTH, in) != NULL && i < lines){
        char *newline = strchr(line, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        lines_arr[i] = malloc(strlen(line) + 1);
        if (lines_arr[i] == NULL) {
            fprintf(stderr, "Error allocating memory\n");
            exit(EXIT_FAILURE);
        }
        strcpy(lines_arr[i], line);

        i++;
    }

    //create Lists
    List l = newList();
    bool inserted = 0;
    for (int j = 0; j < lines; ++j) { //for each data point to be added
        inserted = 0;
        if(l->length == 0) { //appends 0 as first element
            append(l, 0);
            continue;
        }
        moveFront(l);
        for (int k = 0; k < l->length; ++k) { //indexes through and checks if new val should go left of cursor val
            if(strcmp(lines_arr[j], lines_arr[get(l)]) <= 0) {
                insertBefore(l, j);
                inserted = 1;
                break;
            }
            moveNext(l);
        }
        if (inserted) continue;
        append(l, j);//if value has to go to end of list
    }

    //write to outfile
    moveFront(l);
    for (int j = 0; j < lines; ++j) {
        fprintf(out, "%s\n", lines_arr[get(l)]);
        moveNext(l);
    }

    for (int j = 0; j < lines; j++) { //freeing and closing files
        free(lines_arr[j]);
    }
    freeList(&l);
    free(lines_arr);
    fclose(in);
    fclose(out);
    return 0;
}

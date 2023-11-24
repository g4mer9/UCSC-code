#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ncurses.h>
#include "universe.h"
#define OPTIONS "htsn:i:o:"

int main(int argc, char **argv) {
    int opt = 0;
    bool t = 0;
    bool s = 0;
    int generations = 100;
    FILE *in = stdin;
    FILE *out = stdout;
    char h[] = ("SYNOPSIS\n"
                   "    Conway's Game of Life\n"
                   "\n"
                   "USAGE\n"
                   "    ./life_amd64 tsn:i:o:h\n"
                   "\n"
                   "OPTIONS\n"
                   "    -t             Create your universe as a toroidal\n"
                   "    -s             Silent - do not use animate the evolution\n"
                   "    -n {number}    Number of generations [default: 100]\n"
                   "    -i {file}      Input file [default: stdin]\n"
                   "    -o {file}      Output file [default: stdout]");

    while ((opt = (getopt(argc, argv, OPTIONS))) != -1) { //command line args
        switch (opt) {
        case 't':
            //toroidal
            t = 1;
            break;
        case 's':
            //silence ncurses
            s = 1;
            break;
        case 'n':
            //stores generations
            generations = (int) strtol(optarg, (char **) NULL, 10);
            break;
        case 'i':
            //stores input file
            in = fopen(optarg, "r");
            break;
        case 'o':
            //stores output file
            out = fopen(optarg, "w");
            break;
        case 'h':
            //prints h
            printf("%s\n", h);
            return 1;
        default: printf("%s\n", h); return 1;
        }
    }

    uint32_t x, y;
    do{
        fscanf(in, "%u %u\n", &x, &y); //scans first line, sets bounds of grid
    }while(0);

    Universe *uni_a = NULL; // creating universes
    Universe *uni_b = NULL;
    Universe *temp = NULL;
    uni_a = uv_create(x, y, t);
    uni_b = uv_create(x, y, t);
    if(!uv_populate(uni_a, in)) return 1;

    if(!s){ //inits ncurses
        initscr();
        curs_set(FALSE);
    }

    //generation loop
    for(int gen = 0; gen < generations; gen++) {
        if (!s){
            clear(); //clears screen

            for(uint32_t r = 0; r < uv_rows(uni_a); r++) {
                for(uint32_t c = 0; c < uv_cols(uni_a); c++) {
                    if(uv_get_cell(uni_a, r, c)) mvprintw(r, c, "o");
                    else mvprintw(r, c, ".");
                }
            }
            refresh();
            usleep(50000);
        }

        //update to next generation
        for(uint32_t r = 0; r < uv_rows(uni_a); r++) {
            for(uint32_t c = 0; c < uv_cols(uni_a); c++) { //for each cell
                bool current = uv_get_cell(uni_a, r, c);
                uint32_t neighbors = uv_census(uni_a, r, c); //set current cell and how many neighbors it has

                if( ((current) && ((neighbors == 2) || (neighbors == 3))) || ((!current) && (neighbors == 3)) ) { //alive cell with 2 or 3 neighbors stays alive, dead cell with 3 neighbors becomes alive
                    uv_live_cell(uni_b, r, c);
                    continue;
                }

                uv_dead_cell(b, r, c); //otherwise, kill cell
            }
        }

        temp = uni_b;//swapping universe pointers
        uni_b = uni_a;
        uni_a = temp;
        if(!s) refresh();
    }

    //ends ncurses and frees mem
    edwin();
    uv_print(uni_a, out);
    uv_delete(uni_a);
    uv_delete(uni_b);
    temp = NULL;
    fclose(in);
    fclose(out);
}
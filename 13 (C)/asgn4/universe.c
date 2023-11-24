#include "universe.h"
#include <inttypes.h>
#include <stdlib.h>

struct Universe{
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal){ //creates and allocates memory for universe
    Universe *uni = (Universe *)malloc(sizeof(Universe));
    uni->toroidal = toroidal;
    uni->rows = rows;
    uni->cols = cols;
    uni->grid = (bool **) calloc(rows, sizeof(bool *));
    for (uint32_t r = 0; r < rows; r++)
        uni->grid[r]  = (bool *) calloc(cols, sizeof(bool)); //mallocing for each row
    return uni;
}

void uv_delete(Universe *u) { //deletes and frees memory for universe
    for (uint32_t r = 0; r < u->rows; r++) {
        free(u->grid[r]);
    }
    free(u->grid);
    free(u);
    u = NULL;
}

uint32_t uv_rows(Universe *u){ // returns rows
    return u->rows;
}

uint32_t uv_cols(Universe *u) {// returns cols
    return u->cols;
}

void uv_live_cell(Universe *u, uint32_t r, uint32_t c)
{
    if(r < u->rows && c < u->cols) { //if coordinate is within bounds, set cell to live
        u->grid[r][c] = 1;
    }
}

void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    if(r < u->rows && c < u->cols) { //if coordinate is within bounds, set cell to dead
        u->grid[r][c] = 0;
    }
}

bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    if(r < u->rows && c < u->cols && u->grid[r][c]) { //if coordinate is within bounds, get cell
        return true;
    }
    return false;
}

bool uv_populate(Universe *u, FILE *infile) {
    unsigned int x, y;

    for (uint32_t r = 0; r < u->rows; r++) { //inits whole grid to dead cells
        for(uint32_t c = 0; c < u->cols; c++) {
            uv_dead_cell(u, r, c);
        }
    }

    while(fscanf(infile, "%" SCNu32 " %" SCNu32 "\n", &x, &y) != EOF) { //parsing in the live cells
        if(x < u->rows && y < u->cols) { //if coordinate is within bounds, live
            uv_live_cell(u, x, y);
        }
        else {
            fprintf(stderr, "Malformed input.\n");
            return false;
        }
    }
    return true;
}

uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    uint32_t neighbors = 0;
    long rows = r;
    long cols = c;

    for (long nr = rows - 1; nr <= rows + 1; nr++) {
        if(u->toroidal) {//setting toroidal neighbor in rows
            if (nr < 0)
                nr += u->rows;
            else
                nr = nr % u->rows;
        }
        for(long nc = cols - 1; nc <= cols + 1; nc++) {
            if(u->toroidal) {//setting toroidal neighbor in cols
                if (nc < 0)
                    nc += u->cols;
                else
                    nc = nc % u->cols;
            }

            if(uv_get_cell(u, nr, nc) && (nr != rows || nc != cols))
                neighbors++;
        }
    }
    return neighbors;
}

void uv_print(Universe *u, FILE *outfile) {
    for(uint32_t r = 0; r < u->rows; r++) {
        for(uint32_t c = 0; c < u->cols; c++) {
            if(uv_get_cell(u, r, c))
                fprintf(outfile, "o");
            else
                fprintf(outfile, ".");
        }
        fprintf(outfile, "\n");
    }
}
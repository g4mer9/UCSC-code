#include "word.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>

Word *word_create(uint8_t *syms, uint32_t len){ //constructor for word, sets syms to given syms and len to given len
    Word *word = (Word*) malloc(sizeof(Word));
    word->syms = (uint8_t*) calloc(len, sizeof(uint8_t));
    for (int i = 0; i < len; ++i) {
        word->syms[i] = syms[i];
    }
    word->len = len;
    return word;
}

Word *word_append_sym(Word *w, uint8_t sym) { //appends sym to word
    uint8_t *new_sym = (uint8_t*) calloc((w->len + 1), sizeof(uint8_t));
    for (int i = 0; i < w->len; ++i) { // copies over old syms if any
        new_sym[i] = w->syms[i];
    }
    new_sym[w->len] = sym; // appending
    Word *word = word_create(new_sym, (w->len + 1)); //creating new word
    word_delete(w); //frees memory of old word
    return word;
}

void word_delete(Word *w) {//deconstructor for word
    free(w->syms);
    free(w);
}

WordTable *wt_create(void) { //constructor for word table, sets index empty code to an empty word
    WordTable *table = (WordTable*) calloc(MAX_CODE, sizeof(Word*));
    table[EMPTY_CODE] = word_create(NULL, 0);
    return table;
}

void wt_reset(WordTable *wt) { //sets all non null words to null, skipping the empty word
    for (int i = 0; i < MAX_CODE; ++i) {
        if (i == EMPTY_CODE) //skipping empty code
            continue;
        if(wt[i] != NULL)
            word_delete(wt[i]);
    }
}

void wt_delete(WordTable *wt) {
    for (int i = 0; i < MAX_CODE; ++i) {
        word_delete(wt[i]);
    }
    free(wt);
}
#include "trie.h"
#include "code.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

TrieNode * trie_node_create(uint16_t code) { //constructor for trie, sets all children to null
    TrieNode *node = (TrieNode*) malloc(sizeof(TrieNode));
    node->code = code;
    for (int i = 0; i < ALPHABET; ++i) {
        node->children[i] = NULL;
    }
    return node;
}

void trie_node_delete(TrieNode *n) { //deconstructor for trie
    free(n);
}

TrieNode *trie_create(void) {
    TrieNode *node = trie_node_create(EMPTY_CODE);
    if(node != NULL) return node;
    else return NULL;
}

void trie_reset(TrieNode *root) { // resets trie by setting each child to null
    for (int i = 0; i < ALPHABET; ++i) {
        root->children[i] = NULL;
    }
}

void trie_delete(TrieNode *n) {
    for (int i = 0; i < ALPHABET; ++i) {
        n->children[i] = NULL;
    }
    free(n);
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    for (int i = 0; i < ALPHABET; ++i) {
        if(n->children[i]->code == sym) return n->children[i];
    }
    return NULL;
}
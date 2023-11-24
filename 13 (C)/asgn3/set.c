//my code from last quarter from when I failed CSE13S, with certain things changed to reflect the new assignments. Don't mark me for plagiarism when it's my own code please.

#include "set.h"

#include <stdint.h>

Set set_empty(void) {
    return 0;
}

bool set_member(Set s, uint8_t x) {
    return s & (1 << (x % 32));
}

Set set_insert(Set s, uint8_t x) {
    return s | (1 << (x % 32));
}

Set set_remove(Set s, uint8_t x) {
    return s & ~(1 << (x % 32));
}

Set set_union(Set s, Set t) {
    return s | t;
}

Set set_intersect(Set s, Set t) {
    return s & t;
}

Set set_difference(Set s, Set t) {
    return s & ~t;
}

Set set_complement(Set s) {
    return ~s;
}

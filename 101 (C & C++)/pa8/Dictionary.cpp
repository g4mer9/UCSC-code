/**
 * name: Riley Fink
 * cruzID: rcfink
 * assignment: pa8
 */
#include <iostream>
#include "Dictionary.h"
#define RED 1
#define BLACK 2

using namespace std;

//CONST/DEST------------------------------------------------------------------------------------------------------------

//private node constructor
Dictionary::Node::Node(keyType k, valType v) {
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
}

//dictionary constructor
Dictionary::Dictionary() {
    nil = new Node("",0);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

//copy constructor
Dictionary::Dictionary(const Dictionary &D) {
    //standard constructor
    nil = new Node("", 0);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = BLACK
    root = nil;
    current = nil;
    num_pairs = 0;

    //copy
    preOrderCopy(D.root, D.nil);
    num_pairs = D.num_pairs;

    //set current key
    if (D.current == D.nil) current = nil;
    else current = search(root, D.currentKey());
}

//destructor
Dictionary::~Dictionary() {
    postOrderDelete(root);
    delete nil;
}

//HELPER FUNCTIONS------------------------------------------------------------------------------------------------------

//appends in order string representation of tree rooted at R to s
//"key : value \n"
void Dictionary::inOrderString(std::string &s, Dictionary::Node *R) const {
    if(R->key != "") {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

//appends pre order string representation of tree rooted at R to s
//keys only, with "\n"
void Dictionary::preOrderString(std::string &s, Dictionary::Node *R) const {
    if(R != nil) {
        if (R->color == RED)
            s += R->key + " (RED)\n";
        else
            s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

//inserts deep copy of subtree rooted at R into this.
//recursion terminates at N.
void Dictionary::preOrderCopy(Dictionary::Node *R, Dictionary::Node *N) {
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

//deletes all nodes in subtree rooted at R
void Dictionary::postOrderDelete(Dictionary::Node *R) {
    if(R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

//searches subtree rooted at R for Node with key==k.
//returns address of Node if exists, nil otherwise
Dictionary::Node* Dictionary::search(Dictionary::Node *R, keyType k) const {
    if (R == nil || R->key == k) return R; //if R is nil or the correct key, return it
    if (k < R->key) return search(R->left, k); //if k is to the left of root, return search on left
    return search(R->right, k); //otherwise return search on right
}

//if subtree rooted at R is empty return nil
//otherwise returns pointer to leftmost Node in subtree
Dictionary::Node* Dictionary::findMin(Dictionary::Node *R) {
    if (R == nil || R->left == nil) return R; //if R is nil or the leftmost key, return it
    return findMin(R->left); //otherwise, return findmin on left
}

//if subtree rooted at R is empty return nil
//otherwise returns pointer to rightmost Node in subtree
Dictionary::Node* Dictionary::findMax(Dictionary::Node *R) {
    if (R == nil || R->right == nil) return R; //if R is nil or the rightmost key, return it
    return findMax(R->right); //otherwise, return findmax on right
}

//if N points to rightmost Node or is nil, return nil
//otherwise, returns pointer to node after N with in order walk
Dictionary::Node* Dictionary::findNext(Dictionary::Node *N) {
    if (N == nil) return nil; //if N is nil, return nil

    if (N->right != nil) return findMin(N->right); //return leftmost object in subtree rooted at the right of N

    Node* P = N->parent;
    while (P != nil && N == P->right) { //go up to either find an upper right path or the top of the tree
        N = P;
        P = P->parent;
    }

    return P; //return either the parent > N, or nil if N is max
}

//if N points to leftmost Node or is nil, return nil
//otherwise, returns pointer to node before N with in order walk
Dictionary::Node* Dictionary::findPrev(Dictionary::Node *N) {
    if (N == nil) return nil;   //if N is nil, return nil

    if (N->left != nil) return findMax(N->left); //return rightmost object in subtree rooted at left of N

    Node* P = N->parent;
    while (P != nil && N == P->left) { //go up to either find an upper left path or the top of the tree
        N = P;
        P = P->parent;
    }

    return P; //return either the parent < N, or nil if N is min
}

//ROTATION--------------------------------------------------------------------------------------------------------------

void Dictionary::LeftRotate(Dictionary::Node *N) {
    Node* x = N->right;
    N->right = x->left;
}

void Dictionary::RightRotate(Dictionary::Node *N) {

}

void Dictionary::RB_InsertFixUp(Dictionary::Node* N) {

}

void Dictionary::RB_Transplant(Dictionary::Node *u, Dictionary::Node *v) {

}

void Dictionary::RB_DeleteFixUp(Dictionary::Node *N) {

}

void Dictionary::RB_Delete(Dictionary::Node *N) {

}

//ACCESS FUNCTIONS------------------------------------------------------------------------------------------------------

//returns size
int Dictionary::size() const {
    return num_pairs;
}

//returns true if there is a node where key==k, false otherwise
bool Dictionary::contains(keyType k) const {
    return search(root, k) != nil;
}

//returns reference to val for key k
//pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    Node* node = search(root, k);
    return node->val;
}

//returns true if current iterator is defined, false otherwise
bool Dictionary::hasCurrent() const {
    if(current == nil) return false;
    else return true;
}

//returns current key
//pre: hascurrent()
keyType Dictionary::currentKey() const {
    if(!hasCurrent()) throw std::invalid_argument("currentKey() hasCurrent() returned false");

    return current->key;
}

//returns reference to current val
//pre: hascurrent()
valType& Dictionary::currentVal() const {
    if(!hasCurrent()) throw std::invalid_argument("currentVal() hasCurrent() returned false");

    return current->val;
}

//MANIPULATION FUNCTIONS------------------------------------------------------------------------------------------------

//resets to empty state
void Dictionary::clear() {
    if (root != nil) postOrderDelete(root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

//if a Node with key==k exists, overwrites corresponding value with v.
//otherwise inserts (k, v) as new pair
void Dictionary::setValue(keyType k, valType v) {

    Node* node = search(root, k); //search if k exists
    if (node != nil) node->val = v; //simple replace
    else { //adding new pair
        Node* pair = new Node(k, v); //create new pair
        pair->parent = nil;
        pair->left = nil;
        pair->right = nil;
        num_pairs++;

        Node* p = nil;
        Node* r = root;
        while (r != nil) { //moving to insertion location depending on the value of k
            p = r;
            if (k < r->key) r = r->left;
            else r = r->right;
        }
        pair->parent = p; //set parent

        if (p == nil) {
            root = pair; //setting as root if parent is nil
        }
        else if (k < p->key) {
            p->left = pair; //set as left child of p
        }
        else {
            p->right = pair; //set as right child of p
        }
    }
}

//deletes pair for key==k
//if that pair is current, current becomes undef
//pre: contains(k)
void Dictionary::remove(keyType k) {
    if(!contains(k)) throw std::invalid_argument("remove(k) contains(k) returned false");

    //search for k
    Node* node = search(root, k);
    if (node == current) current = nil; //current becomes undef if deleted

    //4 DELETION CASES:

    if (node->left == nil and node->right == nil) { //case: node has no child
        if (node == root) root = nil; //clear root if being deleted
        else {
            if (node == node->parent->left)
                node->parent->left = nil; //if node is a left child, nil p->left
            else
                node->parent->right = nil; //if node is a right child, nil p->right
        }
        delete node;
    }

    else if (node->right == nil) { //case: node has only a left child
        if (node == root) root = node->left; //if node is root, promote n->left to root
        else {
            if (node == node->parent->left) {
                node->parent->left = node->left; //if node is a left child, promote n->left to p->left
                node->left->parent = node->parent;
            }
            else {
                node->parent->right = node->left; //if node is a right child, promote n->left to p->right
                node->left->parent = node->parent;
            }
        }
        delete node;
    }

    else if (node->left == nil) { //case: node has only a right child
        if (node == root) root = node->right; //if node is root, promote n->right to root
        else {
            if (node == node->parent->left) {
                node->parent->left = node->right; //if node is a left child, promote n->right to p->left
                node->right->parent = node->parent;
            }
            else {
                node->parent->right = node->right; //if node is a right child, promote n->right to p->right
                node->right->parent = node->parent;
            }
        }
        delete node;
    }

    else { //case: node has two children, overwrite node with key and value from in order successor
        Node* next = findMin(node->right); //next node in subtree rooted at right of node
        //overwrite node with in order successor
        node->key = next->key;
        node->val = next->val;
        if (next == next->parent->left)
            next->parent->left = next->right; //if next is a left child, replace with n->right
        else
            next->parent->right = next->right; //if next is a right child, replace with n->right
        if (next->right != nil) next->right->parent = next->parent;
        delete next;
    }

    num_pairs--;
}

//if non empty, places current at first node, otherwise does nothing
void Dictionary::begin() {
    current = findMin(root);
}

//if non empty, places current at last node, otherwise does nothing
void Dictionary::end() {
    current = findMax(root);
}

//if current not at last, advances. otherwise, makes current undefined
//pre: hascurrent()
void Dictionary::next() {
    if(!hasCurrent()) throw std::invalid_argument("next() hasCurrent() returned false");
    current = findNext(current);
}

//if current not at first, goes back. otherwise, makes current undefined
//pre: hascurrent()
void Dictionary::prev() {
    if(!hasCurrent()) throw std::invalid_argument("prev() hasCurrent() returned false");
    current = findPrev(current);
}

//OTHER FUNCTIONS-------------------------------------------------------------------------------------------------------

//to_string, format: "key: value\n" in order
std::string Dictionary::to_string() const {
    std::string s;
    inOrderString(s, root);
    return s;
}

//returns string of: "key\n" in order
std::string Dictionary::pre_string() const {
    std::string s;
    preOrderString(s, root);
    return s;
}

//returns true iff this == D
bool Dictionary::equals(const Dictionary &D) const {
    if (num_pairs != D.num_pairs) return false; //size mismatch

    bool eq = to_string() == D.to_string();

    return eq;
}

//OVERRIDES-------------------------------------------------------------------------------------------------------------

std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    stream << D.to_string();
    return stream;
}

bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ) {
    if (this == &D) return *this; //if self, return

    clear();
    //copy
    preOrderCopy(D.root, D.nil);
    num_pairs = D.num_pairs;
    //throw std::invalid_argument("clears copy");
    //set current key
    if (D.current == D.nil) current = nil;
    else current = search(root, D.currentKey());

    return *this;
}
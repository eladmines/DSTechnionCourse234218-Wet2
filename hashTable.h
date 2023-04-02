#include <iostream>
#include "pair.h"

class HashTable {
 public:
  static constexpr int kTableSize = 11;  
  LinkedList<Pair> table[kTableSize];  

 public:
  
  void Insert(shared_ptr<Player> player,int key) {
    int hash = key % kTableSize; 
    Pair  *newPair = new Pair   (player,1); 
    Pair co= *newPair;
    table[hash].insert(co);
    Pair* p=table[hash].find(*newPair);
    p->rank=1;

  
     
  }

     Pair* Lookup(int key) {
    int hash = key % kTableSize;
    permutation_t *perm = new permutation_t();
    const permutation_t &spirit = *(perm);
    shared_ptr<Player> pl = make_shared<Player>(key,1,1,0,spirit,spirit,1,1);
    Pair  * p = new Pair (pl,1);
    return table[hash].find(*p);
    }
};
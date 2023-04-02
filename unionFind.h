
#include "genericList.h"
#include <iostream>
#include "player.h"
#include "pair.h"
using namespace std;
#include <memory> 

#ifndef UNION_FIND_H
#define UNION_FIND_H

class UnionFind {
public:
  HashTable parent; 
  HashTable rank;  

 public:
  UnionFind() {}

  void makeSet(shared_ptr<Player> p){
      parent.Insert(p,p->playerID);
      rank.Insert(p,p->playerID);
  }

    Pair* Find(int x) {
    Pair* parent_x = parent.Lookup(x);
    if (parent_x->playerParent->playerID != x) {
      parent_x= Find(parent_x->playerParent->playerID);
    }
    return parent_x;
  }

    Pair* FindWhile(int x, shared_ptr<TeamKeyId> add,int totalBU) {
    Pair* xPlayer = findThePlayer(x);
    Pair* curr;
    curr=xPlayer;
    while (curr->player->playerID != curr->playerParent->playerID) {
      curr = findThePlayer(curr->playerParent->playerID);
    }
    
    xPlayer->playerParent = curr->player;    
    return xPlayer;
  }
    


  Pair* findThePlayer(int x) {
    Pair* reqPair= parent.Lookup(x);
    return reqPair;
  }

  void Union(shared_ptr<Player> x, shared_ptr<Player> y) {
    Pair*   yRoot = Find(y->playerID);
    Pair*  xRoot = Find(x->playerID);
    if (xRoot->player->playerID == yRoot->player->playerID) {
     
      return;
    }

    
    Pair*   rank_x = parent.Lookup(xRoot->player->playerID);
    Pair*  rank_y = parent.Lookup(yRoot->player->playerID);
    if (rank_x->rank < rank_y->rank) {
      xRoot->playerParent = yRoot->playerParent;
      rank_y->rank = rank_y->rank + rank_x->rank;      
      
    } else if (rank_y->rank < rank_x->rank) {
      yRoot->playerParent = xRoot->playerParent;
      rank_x->rank = rank_y->rank + rank_x->rank;     
     
    } else if(rank_x->rank == rank_y->rank){
       yRoot->playerParent = xRoot->playerParent;
      rank_x->rank = rank_y->rank + rank_x->rank;
        
    }
    
  }
};


#endif // UNION_FIND_H
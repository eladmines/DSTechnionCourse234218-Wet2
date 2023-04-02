#include <iostream>
#include "genericList.h"
#include "player.h"
class Pair {
 public:
  
  shared_ptr<Player> player;
  shared_ptr<Player> playerParent;
  int rank;
  

  Pair(const shared_ptr<Player>& player,int rank) : player(player),playerParent(player),rank(rank){}

  Pair& operator=(const Pair& other) {
    player = other.player;
    playerParent= other.playerParent;
    return *this;
  }

  bool operator==(int id){
    if(id==player->playerID)
        return true;
    return false;
  }

  bool operator==(Pair other){
    if(other.player->playerID==player->playerID)
        return true;
    return false;
  }

  bool operator!=(int id){
    if(id!=player->playerID)
        return true;
    return false;
  }


  Pair() = default;

  ~Pair() = default;

};
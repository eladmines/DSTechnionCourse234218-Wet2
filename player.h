#include <iostream>
#include "wet2util.h"
#include "genericList.h"
#include "avl.h"
#ifndef PLAYER_H
#define PLAYER_H
#include <memory> 
class Player;
class Team;
class TeamKeyId;

class Team{
    public:
    int teamID;
    int abilitySum;
    int points;
    int gamePlayed;
    int numOfPlayers;
    bool goalKeeper;
    int beforeUnion;
   shared_ptr<Player> teamPlayer;
    permutation_t allSpirit;
    bool valid;
    shared_ptr<TeamKeyId> teamOwner;
    permutation_t BUSpirit;
    

    
    Team(int teamID, int abilitySum, int points, int gamePlayed, int numberOfPlayers, bool goalKeeper, int beforeUnion, shared_ptr<Player> teamPlayer,permutation_t allSpirit, bool valid,shared_ptr<TeamKeyId> teamOwner, permutation_t BUSpirit):teamID(teamID), abilitySum(abilitySum), points(points),gamePlayed(gamePlayed), numOfPlayers(numberOfPlayers), goalKeeper(goalKeeper), beforeUnion(beforeUnion),teamPlayer(teamPlayer),allSpirit(allSpirit), valid(valid),teamOwner(teamOwner),BUSpirit(BUSpirit)
    {

    }

    Team& operator=(Team& other){
        teamID=other.teamID;
        abilitySum=other.abilitySum;
        points=other.points;
        gamePlayed=other.gamePlayed;
        numOfPlayers=other.numOfPlayers;
        goalKeeper=other.goalKeeper;
        beforeUnion=other.beforeUnion;
        teamPlayer=other.teamPlayer;
        allSpirit=other.allSpirit;
        valid=other.valid;
        teamOwner=other.teamOwner;
        BUSpirit=other.BUSpirit;
        return *this;

    }

    Team(Team& other){
        teamID=other.teamID;
        abilitySum=other.abilitySum;
        points=other.points;
        gamePlayed=other.gamePlayed;
        numOfPlayers=other.numOfPlayers;
        goalKeeper=other.goalKeeper;
        beforeUnion=other.beforeUnion;
        teamPlayer=other.teamPlayer;
        valid=other.valid;
        allSpirit=other.allSpirit;
        teamOwner=other.teamOwner;
        BUSpirit=other.BUSpirit;



    }

    Team(int teamID):teamID(teamID){
      abilitySum = 0;
      points = 0;
      gamePlayed = 0;
      numOfPlayers = 0;
      beforeUnion = 0;
      goalKeeper = false;
      valid = true;
      teamPlayer = nullptr;
      teamOwner = nullptr;
      allSpirit = permutation_t::neutral();
      BUSpirit = permutation_t::neutral();
    }

    bool operator<(Team teamKeyId){
        if(abilitySum<teamKeyId.abilitySum){
          return true;
        }
        else if (abilitySum == teamKeyId.abilitySum){
                if(teamID<teamKeyId.teamID)
                  return true;
                else return false;
        }
          return false;
    }

    bool operator>(Team teamKeyId){
        if(abilitySum>teamKeyId.abilitySum){
          return true;
        }
        else if (abilitySum == teamKeyId.abilitySum){
                if(teamID>teamKeyId.teamID)
                  return true;
                else return false;
                }
          return false;
    }

    bool operator==(Team teamKeyId){
        if(teamID==teamKeyId.teamID)
          return true;
        return false;
    }

};


class TeamKeyId:public Team{
    public:

     using Team::Team;

    bool operator<(TeamKeyId TeamKeyId){
        if(teamID<TeamKeyId.teamID)
          return true;
        return false;
    }

    bool operator>(TeamKeyId TeamKeyId){
        if(teamID>TeamKeyId.teamID)
          return true;
        return false;
    }

    bool operator==(TeamKeyId TeamKeyId){
        if(teamID==TeamKeyId.teamID)
          return true;
        return false;
    }

};





class Player{
    public:
    int playerID;
    int cards;
    int playerGamesPlayed;
    bool goalkeeper;
    permutation_t spirit;
    permutation_t multSpirit;
    int teamPlayerID;
    int ability;
    shared_ptr<TeamKeyId> teamOfPlayer;
    
    int gamePlayedTeamofPlayer;
    bool changed;

    public:
    Player(int playerID,int cards,int playerGamesPlayed,bool goalkeeper, permutation_t spirit, permutation_t multSpirit,int teamID,int ability):playerID(playerID),cards(cards),playerGamesPlayed(playerGamesPlayed),goalkeeper(goalkeeper),spirit(spirit),multSpirit(multSpirit),teamPlayerID(teamID),ability(ability),changed(false){
      teamOfPlayer = NULL;
     }

     Player() = default;
     



  Player& operator=(const Player& other) {
    playerID = other.playerID;
    teamPlayerID = other.teamPlayerID;
    playerGamesPlayed = other.playerGamesPlayed;
    ability = other.ability;
    cards = other.cards;
    goalkeeper = other.goalkeeper;
    spirit = other.spirit;
    multSpirit = other.multSpirit;
    teamOfPlayer = other.teamOfPlayer;
    gamePlayedTeamofPlayer = other.gamePlayedTeamofPlayer;
    return *this;
  }



    bool operator<(Player TeamKeyId){
        if(playerID<TeamKeyId.playerID)
          return true;
        return false;
    }

    bool operator>(Player TeamKeyId){
        if(playerID>TeamKeyId.playerID)
          return true;
        return false;
    }

    bool operator==(Player TeamKeyId){
        if(playerID==TeamKeyId.playerID)
          return true;
        return false;
    }

};

#endif // PLAYER_H


#include "worldcup23a2.h"
#include<iostream>


world_cup_t::world_cup_t()
{
	numOfTeams =0;
	allTeams = new  AVLTree<shared_ptr<Team>>();
	allKeyByIdTeams= new  AVLTree<shared_ptr<TeamKeyId>>();
	allPlayersUF = new UnionFind();
}

world_cup_t::~world_cup_t()
{
	delete allTeams;
    delete allKeyByIdTeams;
	delete allPlayersUF;

}

StatusType world_cup_t::add_team(int teamId)
{
	shared_ptr<TeamKeyId> addedTeam = make_shared<TeamKeyId>(teamId);
	if(addedTeam==NULL)
		return StatusType::ALLOCATION_ERROR;
	if(teamId<=0)
	{
		addedTeam=nullptr;
		return StatusType::INVALID_INPUT;
	}
	if(allKeyByIdTeams->findNode(allKeyByIdTeams->root,addedTeam)!=NULL)
	{	
		addedTeam=nullptr;
		return StatusType::FAILURE;
	}
	addedTeam->valid=true;
    allTeams->root = allTeams->insert(allTeams->root,shared_ptr<Team>(addedTeam),NULL);
	allKeyByIdTeams->root = allKeyByIdTeams->insert(allKeyByIdTeams->root,addedTeam,NULL);
	numOfTeams = numOfTeams + 1;
	addedTeam=nullptr;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	if(teamId<=0)
	{
		return StatusType::INVALID_INPUT;
	}

	shared_ptr<TeamKeyId> removedTeam = make_shared<TeamKeyId>(teamId);
	if(removedTeam==NULL)
		return StatusType::ALLOCATION_ERROR;
	
	if( allKeyByIdTeams->findNode(allKeyByIdTeams->root,removedTeam)==NULL || allKeyByIdTeams->findNode(allKeyByIdTeams->root,removedTeam)->data->teamOwner != NULL)
	{	
		removedTeam=nullptr;
		return StatusType::FAILURE;
	}

	shared_ptr<TeamKeyId> foundTeam = allKeyByIdTeams->findNode(allKeyByIdTeams->root,removedTeam)->data;

     allTeams->root = allTeams->remove(allTeams->root,shared_ptr<Team>(foundTeam));
	 allKeyByIdTeams->root =  allKeyByIdTeams->remove(allKeyByIdTeams->root,foundTeam);
	foundTeam->valid=false;
	numOfTeams = numOfTeams - 1;
	removedTeam=nullptr;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	if(teamId<=0 || playerId<=0 || gamesPlayed<0 ||  cards<0 || !(spirit.isvalid()))
	{
		return StatusType::INVALID_INPUT;
	}
	shared_ptr<TeamKeyId> demoTeam = make_shared<TeamKeyId>(teamId);

	shared_ptr<Player> addedPlayer = make_shared<Player>(playerId,cards,gamesPlayed,goalKeeper,spirit,spirit,teamId,ability);
	

	if(allPlayersUF->findThePlayer(playerId) != NULL){
		demoTeam=nullptr;
		addedPlayer=nullptr;
		return StatusType::FAILURE;
	};



	if(demoTeam == NULL || addedPlayer == NULL){
		demoTeam=nullptr;
		addedPlayer=nullptr;
		return StatusType::ALLOCATION_ERROR;
	}


	if( allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam)==NULL)
	{	
		demoTeam=nullptr;
		addedPlayer=nullptr;
		return StatusType::FAILURE;
	}
	addedPlayer->playerGamesPlayed = addedPlayer->playerGamesPlayed-allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam)->data->gamePlayed;
	if(allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam)!=NULL)
	{	
		shared_ptr<TeamKeyId> findTeam =allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam)->data;	
		addedPlayer->teamOfPlayer = findTeam;
		allPlayersUF->makeSet(addedPlayer);
		if((allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam)->data->teamPlayer) != nullptr){
			
			allPlayersUF->Union(addedPlayer,allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam)->data->teamPlayer);
			
		}
		else{
			allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam)->data->teamPlayer = addedPlayer;
		}
		
		
		if(goalKeeper == true)
		{
			allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam)->data->goalKeeper = true;
		}
		
		
		if(!(findTeam->allSpirit.isvalid())){
			findTeam->allSpirit = spirit;
		}
		else{
			findTeam->allSpirit = findTeam->allSpirit*spirit;
		}
		
	    
		allTeams->root = allTeams->remove(allTeams->root,shared_ptr<Team>(findTeam));
		allKeyByIdTeams->root = allKeyByIdTeams->remove(allKeyByIdTeams->root,findTeam);

		findTeam->abilitySum += addedPlayer->ability;
		addedPlayer->multSpirit = findTeam->allSpirit;
		findTeam->numOfPlayers = findTeam->numOfPlayers +1;

		allTeams->root = allTeams->insert(allTeams->root,shared_ptr<Team>(findTeam),NULL);
		allKeyByIdTeams->root = allKeyByIdTeams->insert(allKeyByIdTeams->root,findTeam,NULL);

		
		findTeam=nullptr;
		demoTeam=nullptr;
		addedPlayer=nullptr;

	}
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	shared_ptr<TeamKeyId> demoTeam1 = make_shared<TeamKeyId>(teamId1);
	shared_ptr<TeamKeyId> demoTeam2 = make_shared<TeamKeyId>(teamId2);
	if(demoTeam1==NULL || demoTeam2 == NULL){
		demoTeam1=nullptr;
		demoTeam2=nullptr;
		return StatusType::ALLOCATION_ERROR;
	}
	
	if(teamId1<=0 ||teamId2<=0 || teamId1==teamId2)
	{
		demoTeam1=nullptr;
		demoTeam2=nullptr;
		return StatusType::INVALID_INPUT;
	}

	if( allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam1)==NULL || allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam2)==NULL)
	{	
		demoTeam1=nullptr;
		demoTeam2=nullptr;
		return StatusType::FAILURE;
	}

	if( allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam1)->data->goalKeeper == false || allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam2)->data->goalKeeper == false)
	{	
		demoTeam1=nullptr;
		demoTeam2=nullptr;
		return StatusType::FAILURE;
	}

	shared_ptr<TeamKeyId> findTeam1 = allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam1)->data;
	shared_ptr<TeamKeyId> findTeam2 = allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam2)->data;
	findTeam1->gamePlayed++;
	findTeam2->gamePlayed++;
	int sum1 = findTeam1->abilitySum + findTeam1->points;
	int sum2 = findTeam2->abilitySum + findTeam2->points;
	if(sum1 > sum2){
		findTeam1->points+=3;
		return 1;
	}

	else if(sum1 < sum2){
		findTeam2->points+=3;
		return 3;
	}

	else{
		if(findTeam1->allSpirit.strength() > findTeam2->allSpirit.strength() ){
			findTeam1->points+=3;
			return 2;
		}

		else if(findTeam1->allSpirit.strength() < findTeam2->allSpirit.strength() ){
			findTeam2->points+=3;
			return 4;
		}
		else{
			findTeam1->points+=1;
			findTeam2->points+=1;
			return 0;
		}
	}
	demoTeam1=nullptr;
	demoTeam2=nullptr;
	findTeam1=nullptr;
	findTeam2=nullptr;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	if(playerId<=0)
	{
		return StatusType::INVALID_INPUT;
	}

	if(allPlayersUF->findThePlayer(playerId) == NULL){
		return StatusType::FAILURE;
	}
	shared_ptr<TeamKeyId> teamOwner = allPlayersUF->findThePlayer(playerId)->player->teamOfPlayer;
	int totalBU = 0;
		while (teamOwner->teamOwner != NULL) {
				totalBU += teamOwner->beforeUnion;
				teamOwner = teamOwner->teamOwner;	
			}
			
	int pGames = allPlayersUF->FindWhile(playerId,teamOwner,totalBU)->player->playerGamesPlayed;
	int tGames = teamOwner->gamePlayed;
	teamOwner = nullptr;
	return totalBU + tGames + pGames;
	
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	
	if(playerId<=0 || cards<0)
	{
		return StatusType::INVALID_INPUT;
	}
	if(allPlayersUF->findThePlayer(playerId) == NULL || allPlayersUF->findThePlayer(playerId)->player->teamOfPlayer->valid==false){
		return StatusType::FAILURE;
	}

	shared_ptr<Player> findPlayer = allPlayersUF->findThePlayer(playerId)->player;
	shared_ptr<TeamKeyId> teamOwner = allPlayersUF->findThePlayer(playerId)->player->teamOfPlayer;
	bool valid = findPlayer->teamOfPlayer->valid;
		while (teamOwner != NULL) {
				valid = teamOwner->valid;
				teamOwner = teamOwner->teamOwner;	
			}
	if(valid == false){
		findPlayer=nullptr;
		teamOwner = nullptr;
		return StatusType::FAILURE;
		
	}
	findPlayer->cards+=cards;
	findPlayer=nullptr;
	teamOwner = nullptr;
	return StatusType::SUCCESS;

	
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	
	if(playerId<=0)
	{
		return StatusType::INVALID_INPUT;
	}

	if(allPlayersUF->findThePlayer(playerId) == NULL){
		return StatusType::FAILURE;
	}

	shared_ptr<TeamKeyId> teamOwner = allPlayersUF->findThePlayer(playerId)->player->teamOfPlayer;
	bool valid = teamOwner->valid;
		while (teamOwner != NULL) {
				valid = teamOwner->valid;
				teamOwner = teamOwner->teamOwner;
        }	
	
	if(valid == false){
		teamOwner = nullptr;
		return StatusType::FAILURE;
	}

	shared_ptr<Player> findPlayer = allPlayersUF->findThePlayer(playerId)->player;
	int res = findPlayer->cards;
	findPlayer = nullptr;
	teamOwner = nullptr;
	return res;

}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	shared_ptr<TeamKeyId> demoTeam = make_shared<TeamKeyId>(teamId);
	if(demoTeam==NULL)
		return StatusType::ALLOCATION_ERROR;

	if(teamId<=0)
	{
		demoTeam=nullptr;
		return StatusType::INVALID_INPUT;
	}
	
	if(allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam) == NULL)
	{	
		demoTeam=nullptr;
		return StatusType::FAILURE;
	}

	shared_ptr<TeamKeyId> findTeam = allKeyByIdTeams->findNode(allKeyByIdTeams->root,demoTeam)->data;
	int res = findTeam->points;
	findTeam = nullptr;
    return res;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	if(i<0 || numOfTeams==0 || i >= numOfTeams)
    {
		return StatusType::FAILURE;
	}
	return allTeams->ithSmallest(allTeams->root,i)->data->teamID;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	
	if(playerId<=0)
	{
		return StatusType::INVALID_INPUT;
	}
	
	if(allPlayersUF->findThePlayer(playerId) == NULL || allPlayersUF->findThePlayer(playerId)->player->teamOfPlayer->valid == false){
		return StatusType::FAILURE;
	}
	shared_ptr<TeamKeyId> teamOwner1 = allPlayersUF->findThePlayer(playerId)->player->teamOfPlayer;
	bool valid = teamOwner1->valid;
		while (teamOwner1 != NULL) {
				valid = teamOwner1->valid;
				teamOwner1 = teamOwner1->teamOwner;
        }	
	
	if(valid == false){
		teamOwner1 = nullptr;
		return StatusType::FAILURE;
	}
	shared_ptr<TeamKeyId> teamOwner = allPlayersUF->findThePlayer(playerId)->player->teamOfPlayer;
	shared_ptr<Player> demoPlayer = allPlayersUF->findThePlayer(playerId)->player;
	
	permutation_t totalper =demoPlayer->multSpirit;
		while (teamOwner != NULL) {
				totalper = teamOwner->BUSpirit*totalper;
				teamOwner = teamOwner->teamOwner;	
			}
	teamOwner1 = nullptr;
	teamOwner = nullptr;
	demoPlayer = nullptr;
	return totalper;
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2) // notice the difference between buy_team and buy_team 
{
	shared_ptr<TeamKeyId> buyTeam1 = make_shared<TeamKeyId>(teamId1);
	shared_ptr<TeamKeyId> buyTeam2 = make_shared<TeamKeyId>(teamId2);
	if(buyTeam1==NULL || buyTeam2 == NULL)
	{
		buyTeam1 = NULL;
		buyTeam2 = NULL;
		return StatusType::ALLOCATION_ERROR;
	}
		
	if(teamId1<=0 || teamId2<=0 || teamId1==teamId2)
	{
		buyTeam1=nullptr;
		buyTeam2=nullptr;
		return StatusType::INVALID_INPUT;
	}

	
	if(allKeyByIdTeams->findNode(allKeyByIdTeams->root,buyTeam1) == NULL || allKeyByIdTeams->findNode(allKeyByIdTeams->root,buyTeam2) == NULL)
	{	
		buyTeam1=nullptr;
		buyTeam2=nullptr;
		return StatusType::FAILURE;
	}

	shared_ptr<TeamKeyId> team1 = allKeyByIdTeams->findNode(allKeyByIdTeams->root,buyTeam1)->data;
	shared_ptr<TeamKeyId> team2 = allKeyByIdTeams->findNode(allKeyByIdTeams->root,buyTeam2)->data;

	allTeams->root = allTeams->remove(allTeams->root,shared_ptr<Team>(team1));

	if(team1->numOfPlayers !=0 && team2->numOfPlayers !=0)
		allPlayersUF->Union(team1->teamPlayer,team2->teamPlayer);
	team2->teamOwner=team1;
	team2->BUSpirit = team1->allSpirit;
	team1->allSpirit = team1->allSpirit*team2->allSpirit;
	team2->beforeUnion = team2->gamePlayed-team1->gamePlayed;
	team1->abilitySum = team2->abilitySum+team1->abilitySum;
	team1->points = team2->points+team1->points;
	if(team2->goalKeeper == true)
		 team1->goalKeeper = true;

	allKeyByIdTeams->root = allKeyByIdTeams->remove(allKeyByIdTeams->root,team2);
	allTeams->root = allTeams->remove(allTeams->root,shared_ptr<Team>(team2));

	
	allTeams->root = allTeams->insert(allTeams->root,shared_ptr<Team>(team1),NULL);


	
	numOfTeams = numOfTeams - 1;

	buyTeam1 = nullptr;
	buyTeam2 = nullptr;
    team1 = nullptr;
	team2 = nullptr;
	return StatusType::SUCCESS;

	}

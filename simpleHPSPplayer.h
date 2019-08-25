template <class AreaType>

class HPSPplayer: public Player<AreaType>{
  public:
		HPSPplayer (){
			//THIS FUNCTION WILL NEED TO CHANGE WHEN YOU HAVE MORE PLAYER STATS
			Player<AreaType>::maxHP = 100;
			Player<AreaType>::maxSP = 100;
			resetPlayer();
		}

    void resetPlayer(){
			//THIS FUNCTION WILL NEED TO CHANGE WHEN YOU HAVE MORE PLAYER STATS
    	//reset player stats
			Player<AreaType>::hp = Player<AreaType>::maxHP;
			Player<AreaType>::sp = Player<AreaType>::maxSP;
    }
    
    void reportStats(){
			//THIS FUNCTION WILL NEED TO CHANGE WHEN YOU HAVE MORE PLAYER STATS
			cout<<"Hit Points Remaining: "<<Player<AreaType>::hp<<endl;
			cout<<"Sanity Points Remaining: "<<Player<AreaType>::sp<<endl;
		}
		
		//void setCurrent(areaNode<AreaType>* loc){
			
		//	Player<AreaType>::currentLocation = loc;
		//}

		areaNode<AreaType>* getCurrent(){
			return Player<AreaType>::currentLocation;
		}

		int isGameOver(){
			//THIS FUNCTION WILL NEED TO CHANGE WHEN YOU HAVE MORE PLAYER STATS
			//0 continue, 1 win, 2 lose
			//check to see if instaDeath or Goal
			bool id = Player<AreaType>::currentLocation->info.getID();
			bool g = Player<AreaType>::currentLocation->info.getGoal();
			bool result;
			if(id){
				return 2;
			}
			else if(Player<AreaType>::sp <= 0 || Player<AreaType>::hp <= 0) {
				return 2;
			}
			else if(g){
				return 1;
			} 
			else{
				return 0;
			}
		}

  private:
    // you can add any other stats you want to keep here
};


#include "Game.h"
#include "simpleHPSPplayer.h"


using namespace std;

int main(){
	Game<Area, HPSPplayer<Area> > game;
	game.play();
	return 0;
}

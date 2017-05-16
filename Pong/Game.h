//
// This tutorial goes over static class members and methods.  First I'll explain what a static member
// is.  It is a class member that is only created once, and all instances of that class share that one
// variable.  This means that if its value is changed for one instance it will change for all instances.
// Now onto static methods, these are methods that can be called without an instance of the class.  If
// a class method accesses a static member, that method should be static.
//

#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
using namespace std;

enum STATE
{
	STATE_MENU,
	STATE_PLAYING,
	STATE_GAMEOVER
};

class Game
{
public:
	STATE state;	
	void handleState();
	void static reset();
	static int blueScore;
	static int redScore;
};

#endif
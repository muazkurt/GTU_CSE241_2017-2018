#include <cstdlib>	//For malloc, rand and srand functions
#include <ctime>	//For time function.
#include "header/ConnectFourPlus.h"
#include "header/ConnectFourDiag.h"
#include "header/ConnectFourPlusUndo.h"
using namespace MuazKurt;
int main(void)
{
	srand(time(NULL));
	char input;
	std::cout 	<< "Please chose the game type" << std::endl
				<< "P -> Connect Four Plus"		<< std::endl
				<< "U -> Connect Four Plus Undo"<< std::endl
				<< "D -> Connect Four Diagonal"
				<< std::endl;
	std::cin >> input;
	CharLover(input);
	if(input == 'p')
	{
		ConnectFourPlus object;
		object.PlayGame();
	}
	else if(input == 'u')
	{
		ConnectFourPlusUndo object;
		object.PlayGame();		
	}
	else if (input == 'd')
	{
		ConnectFourDiag object;
		object.PlayGame();		
	}
	else
		std::cerr << "There is no such commant." << std::endl;
	return 0;
}
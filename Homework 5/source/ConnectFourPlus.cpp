#include "../header/ConnectFourPlus.h"
namespace MuazKurt
{
	ConnectFourPlus::ConnectFourPlus(int square) : ConnectFourAbstract(square)
    {/*--.--*/}

    ConnectFourPlus::ConnectFourPlus(int rectHeight, int rectWidth) : ConnectFourAbstract(rectHeight, rectWidth)
    {/*--.--*/}

    ConnectFourPlus::ConnectFourPlus(const ConnectFourPlus & other) : ConnectFourAbstract(other)
    {/*--.--*/}
	
	bool ConnectFourPlus::WinSituation()
	{
		int y = 0,
			x = 0,
			filler = 0;
		bool win = false;
		filler = currentgameCell(getCoordinateY(), getCoordinateX()).getInside() ;
		if(filler == 0);
		else
		{
			if((y = Up_Down()) >= 4)
			{
				for(y -= 1; y > 0; --y)
					currentgameCell(getCoordinateY() + y, getCoordinateX()).setCell(filler + 2);
				win = true;
			}
			else 
			{
				x = To_Right();
				y = To_Left();

				if(x + y - 1 >= 4) 
				{
					for(y -= 1; y > 0; --y)
						currentgameCell(getCoordinateY(), getCoordinateX() - y).setCell(filler + 2);
					for(x -= 1; x > 0; --x)
						currentgameCell(getCoordinateY(), getCoordinateX() + x).setCell(filler + 2);
					win = true;
				}
			}
			if(win == true)
				currentgameCell(getCoordinateY(), getCoordinateX()).setCell(filler + 2);
		}
		return win;
	}
	
	void ConnectFourPlus::PlayGame()
	{
		setALL();
		bool noplace = false;
		do
		{
			setUser(currentTurn() % 2);
			MakeMove();
			setUser(currentTurn() + 1);
			noplace = GameDraw();
		} while(WinSituation() == false && !noplace);
		if(noplace)
			std::cout << "Game finished as draw." << std::endl;
		std::cout << *this;
	}
}
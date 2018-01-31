#include "../header/ConnectFourDiag.h"
namespace MuazKurt
{
    ConnectFourDiag::ConnectFourDiag(int square) : ConnectFourAbstract(square)
    {}

    ConnectFourDiag::ConnectFourDiag(int rectHeight, int rectWidth) : ConnectFourAbstract(rectHeight, rectWidth)
    {}

    ConnectFourDiag::ConnectFourDiag(const ConnectFourDiag & other) : ConnectFourAbstract(other)
    {}

    bool ConnectFourDiag::WinSituation()
    {
        int y = 0,
            x = 0,
            filler = 0;
        bool win = false;
		filler = currentgameCell(getCoordinateY(), getCoordinateX()).getInside() ;
        if(filler == 0);
        else
        {
            x = Left_Up();
            y = Right_Down(); 
            if(x + y - 1 >= 4)
            {
                for(y -= 1; y > 0; --y)
                    currentgameCell(getCoordinateY() + y, getCoordinateX() + y).setCell(filler + 2);
                for(x -= 1; x > 0; --x)
                    currentgameCell(getCoordinateY() - x, getCoordinateX() - x).setCell(filler + 2);
                win = true;
            }
            else 
            {
                x = Left_Down();
                y = Right_Up();
                if(x + y - 1 >= 4) 
                {
                    for(y -= 1; y > 0; --y)
                        currentgameCell(getCoordinateY() - y, getCoordinateX() + y).setCell(filler + 2);
                    for(x -= 1; x > 0; --x)
                        currentgameCell(getCoordinateY() + x, getCoordinateX() - x).setCell(filler + 2);
                    win = true;
                }
            }
            if(win == true)
                currentgameCell(getCoordinateY(), getCoordinateX()).setCell(filler + 2);
        }
        return win;
    }

    void ConnectFourDiag::PlayGame()
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
#include "../header/ConnectFourPlusUndo.h"

namespace MuazKurt
{
    
    ConnectFourPlusUndo::ConnectFourPlusUndo(int square) : ConnectFourAbstract(square), _size(0), _nowUndo(false)
    {
        _capacity = currentHeight() * currentWidth();
        CreateHistory();
    }

    
    ConnectFourPlusUndo::ConnectFourPlusUndo(int rectHeight, int rectWidth) : ConnectFourAbstract(rectHeight, rectWidth), _size(0), _nowUndo(false)
    {
        _capacity = currentHeight() * currentWidth();
        CreateHistory();
    }

    
    ConnectFourPlusUndo::ConnectFourPlusUndo(const ConnectFourPlusUndo & other) : ConnectFourAbstract(other), _size(0), _nowUndo(false)
    {
        *this = other;
    }

    
    const ConnectFourPlusUndo & ConnectFourPlusUndo::operator =(const ConnectFourPlusUndo & other)
    {
        Alzheimer();
        _capacity = other._capacity;
        CreateHistory();
        for(_size = 0; _size < other._size; ++_size)
        {
            history[_size][0] = other.history[_size][0];
            history[_size][1] = other.history[_size][1];            
        }
        return *this;
    }

    
    ConnectFourPlusUndo::~ConnectFourPlusUndo()
    {
        Alzheimer();
        history = nullptr;
    }

    
    void ConnectFourPlusUndo::play(Cell IDONTNEEDIT)
    {
        setCoordinateX(-1);
        do{
            switch(currentTurn())
            {
                case 0:
                    std::cout << "User 2' s move" << std::endl;
                    break;
                case 1:
                    std::cout << "User 1' s move" << std::endl;
                    break;
                default:
                    break;
            }
            std::cout << "Please give me a character in range a - "
                << (char)('a' + (currentWidth() - 1)) 
                << " to make your move: ";
            std::string Input;
            std::cin >> Input;
            stringLover(Input);
            if(Input.size() == 1)
            {
                if(Input[0] > 'a' + (currentWidth() - 1) || Input[0] < 'a')
                    std::cerr << "This is not legal." << std::endl;
                else
                {
                    setCoordinateX(Input[0] - 'a');
                    setCoordinateY(PositionY());
                    if(getCoordinateY() == -1)
                    {
                        std::cerr << getCoordinateY() << "This is not legal." << std::endl;
                        setCoordinateX(-1);
                    }
                }
            }
            else if(SAVE == Input)
            {
                std::cin >> Input;
                Save(Input);
            }
            else if(LOAD == Input)
            {
                std::cin >> Input;
                Load(Input);
                setCoordinateX(-1);
            }
            /*
                Undo position, if user wants to undo, then 1 move deletes from board and history log.
                Sets if undo played to _nowUndo flag.
            */
            else if(UNDO == Input)
            {
                if(_size > 0)
                {
                    --_size;
                    setCoordinateY(history[_size][0]);
                    setCoordinateX(history[_size][1]);
                    currentgameCell(history[_size][0],history[_size][1]).setCell(0);
                    history[_size][0] = history[_size][1] = 0;
                    _nowUndo = true;
                }
                else
                    std::cerr << "There is nothing to undone!" << std::endl;
            }
            else
                std::cerr << "There is no such command." << std::endl;
            } while(getCoordinateX() == -1);
        if(!_nowUndo)
        {
            history[_size][0] = getCoordinateY();
            history[_size][1] = getCoordinateX();
            ++_size;
        }
        return;
    }

    
    void ConnectFourPlusUndo::play()
    {
        ConnectFourAbstract::play();
        history[_size][0] = getCoordinateY();
        history[_size][1] = getCoordinateX();
        _size++;
        return;
    }
    
    
    void ConnectFourPlusUndo::MakeMove()
    {
        std::cout << *this;
        if(currentTurn() == 1)
        {	
            play(currentgameCell(0, 0));
            if(!_nowUndo)
            {
                if(currentTurn() == 1)
                    currentgameCell(getCoordinateY(),getCoordinateX()).setCell(1);
                else
                    currentgameCell(getCoordinateY(),getCoordinateX()).setCell(2);
            }
            else
                _nowUndo = false;    
        }
        else
        {
            if(currentAI() == false)
                play();
            else
                play(currentgameCell(0, 0));
            if(!_nowUndo)
            {
                if(currentTurn() == 1)
                    currentgameCell(getCoordinateY(),getCoordinateX()).setCell(1);
                else
                    currentgameCell(getCoordinateY(),getCoordinateX()).setCell(2);
            }
            else
                _nowUndo = false;    
        }
        return;
    }

   
    void ConnectFourPlusUndo::PlayGame()
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

    
    int ConnectFourPlusUndo::parseInput(const std::string & input)
    {
        Alzheimer();
        int position = 0, temp = 0;
        position = ConnectFourAbstract::parseInput(input);
        _capacity = currentWidth() * currentHeight();
        CreateHistory();
        _size = livingCells();
        for(int i = 0; i < _size; ++i)
        {
            position += stringParser(&input[position], history[i][0], ',');
            position += stringParser(&input[position], history[i][1]);
        }
        return position;
    }

    
    void ConnectFourPlusUndo::Load(const std::string & filename)
    {
        std::string input;
        fileInput(filename, input);
        if(input[0] != 0)
            parseInput(input);
        std::cout << *this;
        return;
    }

    
    void ConnectFourPlusUndo::toString(std::string & output) const
    {
        output = std::to_string(currentHeight());
        output += '/';
        output += std::to_string(currentWidth());
        output += '/';
        output += currentAI() + '0';
        output += '/';
        output += currentTurn() + '0';
        output += '/';
        for(int i = 0; i < currentHeight(); ++i)
            for(int j = 0; j < currentWidth(); ++j)
                output += currentgameCell(i, j).getInside() + '0';
        for(int i = 0; i < _capacity; ++i)
        {
            output += '/';
            output += std::to_string(history[i][0]);
            output += ',';
            output += std::to_string(history[i][1]);
        }
        output += '/';
        return;
    }

    
    void ConnectFourPlusUndo::Save(const std::string & filename) const
    {
        std::ofstream output;
        output.open(filename);
        if(output.is_open())
        {
            std::string info;
            toString(info);
            output << info;
            output.close();
        }
        std::cout << *this;
    }

    
    void ConnectFourPlusUndo::CreateHistory()
    {
        history = new int * [_capacity];
        for(int i = 0; i < _capacity; ++i)
        {
            history[i] = new int [Y_X];
            history[i][0] = history[i][1] = 0;
        }
    }
    
    void ConnectFourPlusUndo::Alzheimer()
    {
        _size = 0;
        for(int i = 0; i < _capacity; ++i)
            delete [] history[i];
        delete [] history;
        _capacity = 0;
    }
}
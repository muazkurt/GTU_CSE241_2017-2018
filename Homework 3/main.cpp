#include <iostream> 
#include <string>	//For string operations.
#include <cstdlib>	//For malloc, rand and srand functions
#include <ctime>	//For time function.
#include <fstream>
#include <vector>
#define SAVE "save"
#define LOAD "load"
#define MEMORY "./backup/"
#define Y_X 2
using namespace std;


class ConnectFour
{
public:
	//Constructer
		ConnectFour();
		ConnectFour(int square);
		ConnectFour(int rectHeight, int rectWidth);
	//Getter
		inline int currentWidth() const { return width; }
		inline int currentHeight() const { return height; }
		inline int currentTurn() const { return turnCounter; }
		inline bool currentAI() const { return AI_open; }
	//livingcells
		/*
			Returns how many Cell have been created.
		*/
		inline static int livingCells() { return Cell::getLivingCells(); }
	//Print Map
		void printMap() const;
	//Play Game
		void PlayGame();

private:
	//Objects inside of map.
		class Cell
		{
			public:
				//Constructer
					/*
						Declares that:
							positionX = 'a'
							positionY = 0
							info = 0
					*/
					Cell();
					/*
						Declares that:
							info = 0
						and
						Calls:
							setCell(input, value);
					*/
					Cell(const int & value, const char & input);
					/*
						Calls
							setCell(input, value);
							setCell(info);
					*/
					Cell(const int & value, const char & input, const int & info);
				//Setter
					/*
						Checks info for legal or not.
						Then checks if the cell is empty or not.
						if empty fills the cell.
						if filled Then checks if update is legal or not.
					*/
					void setCell(const int & info);
				//Getter
					/*
						Returns positionX
					*/
					char getRow() const;
					/*
						Returns positionY
					*/
					int getColumn() const;
					/*
						Returns Inside
					*/
					int getInside() const;
					/*
						Returns How many LivingCells alive.
					*/
					inline static int getLivingCells() { return LivingCells; }
					
					inline void LivingCellDestroyed() { --LivingCells; }
			private:
				inline void LivingCellUpdate();
				/*
					Declaring Cell position
				*/
				void setCell(const char & input, const int & value);
				/*
					Location info
				*/
				char positionX;
				int positionY;
				/*
					Inside information.
				*/
				int Inside;
				/*
					Living Cells.
				*/
				static int LivingCells;
		};

	//Setter
		void setHeight(int input);
		
		void setWidth(int input);
		
		void setAI(bool input);
		
		void setUser(int input);

	//Getting input from user
		// All setters
			int heightFromUser() const;

			int widthFromUser() const;
		
			bool AIFromUser() const;

		void setALL();

		int choiceObject() const;

		int PositionY() const;

		void play(ConnectFour::Cell IDONTNEEDIT);
		
		void play();

		void MakeMove();

	//Char&String lover
		void CharLover(char & letter) const;

		int stringLover(string & traget) const;

	//Printmap() -> Subfunctions.
		void printHead() const;
		
		void printBody() const;

	//Create Map.
		void createCells();


	//Destroy Map.
		void destroyCells();


	//Check Map
		/*
			Takes the game board and checks how much up way stacked from last played position.
			Returns the size of stack.
		*/
		int Up_Down() const;

		/*
			Takes the game board and checks how much Right down way stacked from last played position.
			Returns the size of stack.
		*/
		int Right_Down() const;


		/*
			Takes the game board and checks how much Right up way stacked from last played position.
			Returns the size of stack.
		*/
		int Right_Up() const;

		/*
			Takes the game board and checks how much Left-down way stacked from last played position.
			Returns the size of stack.
		*/
		int Left_Down() const;
		/*
			Takes 2d array as (int **), it's size, Position of last move as array sized Y_X.
			Checks how much Left-up way stacked from last played position.
			Returns the size of stack.
		*/
		int Left_Up() const;

		/*
			Takes the game board and checks how much right way stacked from last played position.
			Returns the size of stack.
		*/
		int To_Right() const;

		/*
			Takes the game board and checks how much left way stacked from last played position.
			Returns the size of stack.
		*/
		int To_Left() const;

	// Check Game
		bool WinSituation();

	bool compare(const ConnectFour & other) const {return (getCoordinateY() > other.getCoordinateY());}

	vector< vector< Cell >> gameCell;
	int height;
	int width;
	int turnCounter;
	bool AI_open;
	int coordinate[Y_X];


	//Coordinate Getter
		inline int getCoordinateY() const { return coordinate[0]; }
		inline int getCoordinateX() const { return coordinate[1]; }
	//
	//Coordinate Setter
		inline void setCoordinateY(const int & input) { coordinate[0] = input; }
		inline void setCoordinateX(const int & input) { coordinate[1] = input; }
	//
	//GameCell Getter
		const ConnectFour::Cell & currentgameCell(const int & y, const int & x) const
		{ return gameCell[y][x];}
	//
	//GameCell Setter
		ConnectFour::Cell & currentgameCell(const int & y, const int & x)
		{ return gameCell[y][x];}
	//
	//Load & Save
		int stringParser(const string & input, int & returnValue, const char param = '/') const;
		
		int createCells(const string & input);
		
		void parseInput(const string & input);
		
		string fileInput(const string & filename, string & loaded);
		
		void vectortoString(string & output) const;
		
		void Load(const string & filename);
		
		void Save(const string & filename) const;
	//

};

int ConnectFour::Cell::LivingCells = 0;

int main(void)
{
	srand(time(NULL));
	ConnectFour ina;
	ina.PlayGame();
	return 0;
}

// ConnectFour functions.
	//Constructer
		ConnectFour::ConnectFour() : width(0), height(0), turnCounter(1), AI_open(false)
		{/*...*/}

		ConnectFour::ConnectFour(int square) : turnCounter(1), AI_open(false)
		{
			setWidth(square);
			setHeight(square);
			createCells();
		}

		ConnectFour::ConnectFour(int rectHeight, int rectWidth) : turnCounter(1), AI_open(false)
		{
			setWidth(rectWidth);
			setHeight(rectHeight);
			createCells();
		}

	//Setter
		void ConnectFour::setWidth(int input)
		{
			if(input < 4)
				cerr << "The game cant be played in this width" << endl;
			else 
				width = input;
			return;
		}

		void ConnectFour::setHeight(int input)
		{
			if(input < 4)
				cerr << "The game cant be played in this height" << endl;
			else
				height = input;
			return;
		}

		void ConnectFour::setAI(bool input)
		{
			AI_open = input;
		}

		void ConnectFour::setUser(int input)
		{
			turnCounter = input;
		}

	//From User
		int ConnectFour::heightFromUser() const
		{
			int input = 0;
			cout << "Please give height of the game: ";
			cin >> input;
			while(input < 4)
			{
				cerr << "Please give another height: ";
				cin >> input;
			}
			return input;
		}

		int ConnectFour::widthFromUser() const
		{
			int input = 0;
			cout << "Please give width of the game: ";
			cin >> input;
			while(input < 4)
			{
				cerr << "Please give another width: ";
				cin >> input;
			}
			return input;
		}

		bool ConnectFour::AIFromUser() const
		{
			cout << "   ------------" << endl
				<<  "P) User vs User" << endl
				<<  "C) User vs Coop" << endl
				<<  "Choice: ";
			int input = 0;
			while(input == 0)
			{
				char section = 0;
				cin >> section;
				CharLover(section);
				if(section == 'p')
					input = 1;
				else if(section == 'c')
					input = 2;
				else
					cout << "Please give another input" << endl
						 << "Choice: ";
			}
			if(input == 1)
				return true;
			return false;
		}

		void ConnectFour::setALL()
		{
			setWidth(widthFromUser());
			setHeight(heightFromUser());
			setAI(AIFromUser());
			createCells();
		}

		int ConnectFour::choiceObject() const
		{
			cout << "Choice an object (give 0 for compare): ";
			int input;
			cin >> input;
			if(input > 5 || input < 0)
			{
				cerr << "There is no such object." << endl;
				return -1;
			}
			return input;
		}
	
	//Lovers
		void ConnectFour::CharLover(char & letter) const
		{
			if(letter >= 'A' && letter <= 'Z')
				letter -= ('A' - 'a');
			return;
		}

		int ConnectFour::stringLover(string & traget) const
		{
			int i = 0;
			for(i; traget[i] != 0; ++i)
				CharLover(traget[i]);
			return i;
		}

	//Map printing
		void ConnectFour::printHead() const
		{
			char a = 'a';
			for(int i = 0; i < currentWidth(); ++i)
			{
				cout << a++;
				if(i != currentWidth() - 1)
					cout << '-';
			}
			cout << endl;
			return;
		}

		void ConnectFour::printBody() const
		{
			int won = 0;
			for(int i = 0; i < currentHeight(); ++i)
			{
				for(int j = 0; j < currentWidth(); ++j)
				{
					switch(currentgameCell(i, j).getInside())
					{
						case 1:
							cout << 'X';
							break;
						case 2:
							cout << 'O';
							break;
						case 3:
							won = 1;
							cout << 'x';
							break;
						case 4:
							won = 2;
							cout << 'o';
							break;
						default:
							cout << '-';
							break;
					}
					cout << ' ';
				}
				cout << endl;
			}
			if(won > 0)
				cout << "User " << won << " won!" << endl;
			return;
		}

		void ConnectFour::printMap() const
		{
			printHead();
			printBody();
			cout << "Living Cells: " << livingCells() << endl;
			return;
		}

	//Map Creaters
		void ConnectFour::createCells()
		{
			gameCell.resize(currentHeight());
			for(int i = 0; i < currentHeight(); ++i)
				for(int j = 0; j < currentWidth(); ++j)
					gameCell[i].push_back(Cell(i, j + 'a', 0));
			return;
		}

	//Map Destroyers
		void ConnectFour::destroyCells()
		{
			for(int i = 0; i < gameCell.size(); ++i)
			{	
				for(int j = 0; j < gameCell[i].size(); ++j)
				{
					if(currentgameCell(i, j).getInside() == 1 || currentgameCell(i, j).getInside() == 2)
					{
						currentgameCell(i, j).LivingCellDestroyed();
					}
				}
				gameCell[i].resize(0);
			}
			gameCell.resize(0);
			return;
		}

	// Inputs and Move
		int ConnectFour::PositionY() const
		{
			int i = currentHeight() - 1;
			if(currentgameCell(0, getCoordinateX()).getInside() == 0)
				for(i; currentgameCell(i, getCoordinateX()).getInside() > 0 && i > 0; --i);
			else
				i = -1;
			return i;
		}

		void ConnectFour::play(ConnectFour::Cell IDONTNEEDIT)
		{
			setCoordinateX(-1);
			do{
				switch(currentTurn())
				{
					case 0:
						cout << "User 2' s move" << endl;
						break;
					case 1:
						cout << "User 1' s move" << endl;
						break;
					default:
						break;
				}
				cout << "Please give me a character in range a - "
					<< (char)('a' + (currentWidth() - 1)) 
					<< " to make your move: ";
				string Input;
				cin >> Input;
				stringLover(Input);
				if(Input.size() == 1)
				{
					if(Input[0] > 'a' + (currentWidth() - 1) || Input[0] < 'a')
						cerr << "This is not legal." << endl;
					else
					{
						setCoordinateX(Input[0] - 'a');
						setCoordinateY(PositionY());
						if(getCoordinateY() == -1)
						{
							cerr << "This is not legal." << endl;
							setCoordinateX(-1);
						}
					}
				}
				else if(SAVE == Input)
				{
					cin >> Input;
					Input = MEMORY + Input;
					Save(Input);
				}
				else if(LOAD == Input)
				{
					cin >> Input;
					Input = MEMORY + Input;
					Load(Input);
					setCoordinateX(-1);
				}
				else
					cerr << "There is no such command." << endl;
			} while(getCoordinateX() == -1);
			return;
		}

		void ConnectFour::play()
		{
			cout << "Computer moving to: ";
			int i = 0;
			bool PositionFound = false;
			while(PositionFound == false)
			{
				switch(i)
				{
					//Watch out for Up to down.
					case 0:
						if(Up_Down() > 2 && getCoordinateY() > 0)
							{
								PositionFound = true;
								setCoordinateY(getCoordinateY() - 1);
							}
						break;
					//	Watch out for right down + left up and if it is possible to win for user 1,
					//		then breake it by putting right down .coordinate.
					case 1:
						if(getCoordinateY() == currentHeight() - 1 || getCoordinateX() == currentWidth() - 1);
						else
						{
							int right_temp = Right_Down();
							if(right_temp + Left_Up() - 1 > 2)
							{
								if((getCoordinateY() + right_temp < currentHeight()) && (getCoordinateX() + right_temp < currentWidth()))
								{
									setCoordinateX(getCoordinateX() + right_temp);
									if(PositionY() == (getCoordinateY() + right_temp))
									{
										setCoordinateY(getCoordinateY() + right_temp);
										PositionFound = true;
									}
									else
										setCoordinateX(getCoordinateX() - right_temp);
								}
							}
						}
						break;
					//	Watch out for right up + left down and if it is possible to win for user 1,
					//		then breake it by putting right up .coordinate.
					case 2:
						if(getCoordinateY() == 0 || getCoordinateX() == currentWidth() - 1);
						else
						{
							int right_temp = Right_Up();
							if(right_temp + Left_Down() - 1 > 2)
							{
								if((getCoordinateY() - right_temp >= 0) && getCoordinateX() + right_temp < currentWidth())
								{	
									setCoordinateX(getCoordinateX() + right_temp);
									if(PositionY() == (getCoordinateY() - right_temp))
									{
										setCoordinateY(getCoordinateY() - right_temp);
										PositionFound = true;
									}
									else
										setCoordinateX(getCoordinateX() - right_temp);
								}
							}
						}
						break;
					//	Watch out for left down + right up and if it is possible to win for user 1,
					//		then breake it by putting left down .coordinate.
					case 3:
						if(getCoordinateY() == currentHeight() - 1 || getCoordinateX() == 0);
						else
						{
							int left_temp = Left_Down();
							if(left_temp + Right_Up() - 1 > 2)
							{
								if((getCoordinateY() + left_temp < currentHeight()) && (getCoordinateX() - left_temp >= 0))
								{
									setCoordinateX(getCoordinateX() - left_temp);
									if(PositionY() == (getCoordinateY() + left_temp))
									{
										setCoordinateY(getCoordinateY() + left_temp);
										PositionFound = true;
									}
									else
										setCoordinateX(getCoordinateX() + left_temp);
								}
							}
						}
						break;
					//	Watch out for left up + right down and if it is possible to win for user 1,
					//		then breake it by putting left up .coordinate.
					case 4:
						if(getCoordinateY() == 0 || getCoordinateX() == 0);
						else
						{
							int left_temp = Left_Up();
							if(left_temp + Right_Down() - 1 > 2)
							{
								if((getCoordinateY() - left_temp >= 0) && (getCoordinateX() - left_temp >= 0))
								{
									setCoordinateX(getCoordinateX() - left_temp);
									if(PositionY() == (getCoordinateY() - left_temp))
									{
										setCoordinateY(getCoordinateY() - left_temp);
										PositionFound = true;
									}
									else
										setCoordinateX(getCoordinateX() + left_temp);
								}
							}
						}
						break;

					//	Watch out for right + left  and if it is possible to win for user 1,
					//		then breake it by putting right .coordinate.
					case 5:
						if(getCoordinateX() == currentWidth() - 1);
						else
						{
							int right_temp = To_Right();
							if(right_temp + To_Left() - 1 > 2)
							{
								if(getCoordinateX() + right_temp < currentWidth())
								{
									setCoordinateX(getCoordinateX() + right_temp);
									if(getCoordinateY() == PositionY())
									{
										PositionFound = true;			
									}
									else
										setCoordinateX(getCoordinateX() - right_temp);
								}
							}
						}
						break;

					//	Watch out for left + right and if it is possible to win for user 1,
					//		then breake it by putting left .coordinate.
					case 6:
						if(getCoordinateX() == 0);
						else
						{
							int left_temp = To_Left();
							if(left_temp + To_Right() - 1 > 2)
							{
								if(getCoordinateX() - left_temp >= 0)
								{
									setCoordinateX(getCoordinateX() - left_temp);
									if(getCoordinateY() == PositionY())
									{
										PositionFound = true;			
									}
									else
										setCoordinateX(getCoordinateX() + left_temp);
								}
							}
						}
						break;

					//	Search that if there is a possible stack .coordinate in map for User 2 (AI) side.
					case 7:
						for(setCoordinateX(0), setCoordinateY(PositionY());
							PositionFound == false && getCoordinateX() < currentWidth(); 
							setCoordinateX(getCoordinateX() + 1), setCoordinateY(PositionY()))
						{
							if(getCoordinateY() + 1 < currentHeight())
							{
								setCoordinateY(getCoordinateY() + 1);
								if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
									if(Up_Down() > 1)
										PositionFound = true;
								setCoordinateY(getCoordinateY() - 1);
								// The way like '\' if i can check right down
								if(PositionFound == false && getCoordinateX() + 1 < currentWidth())
								{
									setCoordinateY(getCoordinateY() + 1);
									setCoordinateX(getCoordinateX() + 1);
									int right_temp = 0;
									if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
										right_temp = Right_Down();
									setCoordinateX(getCoordinateX() - 1);
									setCoordinateY(getCoordinateY() - 1);
									if(getCoordinateY() - 1 >= 0 && getCoordinateX() - 1 >= 0)
									{
										setCoordinateY(getCoordinateY() - 1);
										setCoordinateX(getCoordinateX() - 1);
										if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
											right_temp += Left_Up();
										setCoordinateX(getCoordinateX() + 1);
										setCoordinateY(getCoordinateY() + 1);
									}
									if(right_temp > 1)
										PositionFound = true;
								}
								// The way like '/' if i can check left down
								if(PositionFound == false && getCoordinateX() - 1 >= 0)
								{
									setCoordinateY(getCoordinateY() + 1);
									setCoordinateX(getCoordinateX() - 1);
									int left_temp = 0;
									if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
										left_temp = Left_Down();
									setCoordinateX(getCoordinateX() + 1);
									setCoordinateY(getCoordinateY() - 1);
									if(getCoordinateY() - 1 >= 0 && getCoordinateX() + 1 < currentWidth())
									{
										setCoordinateY(getCoordinateY() - 1);
										setCoordinateX(getCoordinateX() + 1);
										if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
											left_temp += Right_Up();
										setCoordinateX(getCoordinateX() - 1);
										setCoordinateY(getCoordinateY() + 1);
									}
									if(left_temp > 1)
										PositionFound = true;
								}
							}
							if(PositionFound == false && getCoordinateY() - 1 >= 0)
							{
								if(getCoordinateX() + 1 < currentWidth())
								{
									setCoordinateY(getCoordinateY() - 1);
									setCoordinateX(getCoordinateX() + 1);
									int right_temp = 0;
									if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
										right_temp = Right_Up();
									setCoordinateX(getCoordinateX() - 1);
									setCoordinateY(getCoordinateY() + 1);
									if(getCoordinateY() + 1 < currentHeight() && getCoordinateX() - 1 >= 0)
									{
										setCoordinateY(getCoordinateY() + 1);
										setCoordinateX(getCoordinateX() - 1);
										if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
											right_temp += Left_Down();
										setCoordinateX(getCoordinateX() + 1);
										setCoordinateY(getCoordinateY() - 1);
									}
									if(right_temp > 1)
										PositionFound = true;
								}
								if(getCoordinateX() - 1 >= 0)
								{
									setCoordinateY(getCoordinateY() - 1);
									setCoordinateX(getCoordinateX() - 1);
									int left_temp = 0;
									if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
										left_temp = Left_Up();
									setCoordinateX(getCoordinateX() + 1);
									setCoordinateY(getCoordinateY() + 1);
									if(getCoordinateY() + 1 < currentHeight() && getCoordinateX() + 1 < currentWidth())
									{
										setCoordinateY(getCoordinateY() + 1);
										setCoordinateX(getCoordinateX() + 1);
										if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
											left_temp += Right_Down();
										setCoordinateX(getCoordinateX() - 1);
										setCoordinateY(getCoordinateY() - 1);
									}
									if(left_temp > 1)
										PositionFound = true;
								}
							}
							if(PositionFound == false && getCoordinateX() + 1 < currentWidth())
							{
								setCoordinateX(getCoordinateX() + 1);
								int right_temp = 0;
								if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
									right_temp = To_Right();
								setCoordinateX(getCoordinateX() - 1);
								if(getCoordinateX() - 1 >= 0)
								{
									setCoordinateX(getCoordinateX() - 1);
									if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
										right_temp += To_Left();
									setCoordinateX(getCoordinateX() + 1);
								}
								if(right_temp > 1)
									PositionFound = true;
							}
							if(PositionFound == false && getCoordinateX() - 1 >= 0)
							{
								setCoordinateX(getCoordinateX() - 1);
								int left_temp = 0;
								if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
									left_temp = To_Left();
								setCoordinateX(getCoordinateX() + 1);
								if(getCoordinateX() + 1 < currentWidth())
								{
									setCoordinateX(getCoordinateX() + 1);
									if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
										left_temp = To_Right();
									setCoordinateX(getCoordinateX() - 1);
								}
								if(left_temp > 1)
									PositionFound = true;
							}
						}
						break;
					//Playing randomise.
					case 8:
						int temp;
						temp = rand() % currentWidth();
						if(temp < 0)
							temp *= -1;
						setCoordinateX(temp);
						setCoordinateY(PositionY());
						if(getCoordinateY() < 0)
							--i;
						else
							PositionFound = true;
						break;
					default:
						break;
				}
				if(PositionFound == true)
					if(getCoordinateY() < 0 ||
						getCoordinateX() > currentWidth() ||
						getCoordinateX() < 0 ||
						getCoordinateY() > currentHeight())
						PositionFound = false;
				++i;
			}
			cout << "[" << getCoordinateY() << "," << (char)(getCoordinateX() + 'a')<< "]" << endl;
			return;
		}

		void ConnectFour::MakeMove()
		{
			printMap();
			if(currentTurn() == 1)
			{	
				play(currentgameCell(0, 0));
				if(currentTurn() == 1)
					currentgameCell(getCoordinateY(),getCoordinateX()).setCell(1);
				else
					currentgameCell(getCoordinateY(),getCoordinateX()).setCell(2);
			}
			else
			{
				if(currentAI() == false)
					play();
				else
					play(currentgameCell(0, 0));
				if(currentTurn() == 1)
					currentgameCell(getCoordinateY(),getCoordinateX()).setCell(1);
				else
					currentgameCell(getCoordinateY(),getCoordinateX()).setCell(2);
			}
			return;
		}

	// Check Mechanism
		int ConnectFour::Up_Down() const
		{
			int i = 1;
			bool Legal = true;
			while(Legal == true && getCoordinateY() + i < currentHeight())
				{
					if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY() + i, getCoordinateX()).getInside())
						Legal = false;
					else
						++i;
				}
			return i;
		}


		int ConnectFour::Right_Down() const
		{
			int i = 1;
			if(getCoordinateY() == currentHeight() - 1 || getCoordinateX() == currentWidth() - 1);
			else
			{
				bool Legal = true;
				while(Legal == true && getCoordinateY() + i < currentHeight() && getCoordinateX() + i < currentWidth())
					{
						if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY() + i, getCoordinateX() + i).getInside())
							Legal = false;
						else
							++i;
					}
			}
			return i;
		}

		int ConnectFour::Right_Up() const
		{
			int i = 1;
			if(getCoordinateY() == 0 || getCoordinateX() == currentWidth() - 1);
			else
			{
				bool Legal = true;
				while(Legal == true && getCoordinateY() - i >= 0 && getCoordinateX() + i < currentWidth())
					{
						if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY() - i, getCoordinateX() + i).getInside())
							Legal = false;
						else
							++i;
					}
			}
			return i;
		}


		int ConnectFour::Left_Down() const
		{
			int i = 1;
			if(getCoordinateY() == currentHeight() - 1 || getCoordinateX() == 0);
			else
			{
				bool Legal = true;
				while(Legal == true && getCoordinateY() + i < currentHeight() && getCoordinateX() - i >= 0)
					{
						if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY() + i, getCoordinateX() - i).getInside())
							Legal = false;
						else
							++i;
					}
			}
			return i;
		}


		int ConnectFour::Left_Up() const
		{
			int i = 1;
			if(getCoordinateY() == 0 || getCoordinateX() == 0);
			else
			{
				bool Legal = true;
				while(Legal == true && getCoordinateY() - i >= 0 && getCoordinateX() - i >= 0)
					{
						if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY() - i, getCoordinateX() - i).getInside())
							Legal = false;
						else
							++i;
					}
			}
			return i;
		}


		int ConnectFour::To_Right() const
		{
			int i = 1;
			if(getCoordinateX() == currentWidth() - 1);
			else
			{
				bool Legal = true;
				while(Legal == true && getCoordinateX() + i < currentWidth())
					{
						if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY(), getCoordinateX() + i).getInside())
							Legal = false;
						else
							++i;
					}
			}
			return i;
		}


		int ConnectFour::To_Left() const
		{
			int i = 1;
			if(getCoordinateX() == 0);
			else
			{
				bool Legal = true;
				while(Legal == true && getCoordinateX() - i >= 0)
				{
					if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY(), getCoordinateX() - i).getInside())
						Legal = false;
					else
						++i;
				}
			}
			return i;
		}

		bool ConnectFour::WinSituation()
		{
			int y = 0,
				x = 0,
				filler = currentgameCell(getCoordinateY(), getCoordinateX()).getInside() ;
			bool win = false;
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
					}
				}
				if(win == true)
					currentgameCell(getCoordinateY(), getCoordinateX()).setCell(filler + 2);
			}
			return win;
		}

	//	File operations.



		int ConnectFour::stringParser(const string & input, int & returnValue, const char param) const
		{
			int i = 0;
			returnValue = 0;
			for(i = 0; input[i] != param; ++i)
				returnValue = returnValue * 10 + (input[i] - '0');
			return i + 1;
		}


		int ConnectFour::createCells(const string & input)
		{
			createCells();
			for(int j = 0; j < currentHeight(); ++j)
				for(int k = 0; k < currentWidth(); ++k)
					currentgameCell(j, k).setCell((int)(input[k + j * currentWidth()] - '0'));
			return currentHeight() * currentWidth();
		}


		void ConnectFour::parseInput(const string & input)
		{
			destroyCells();
			int position = 0, temp = 0;
			position = stringParser(input, temp);
			setHeight(temp);
			position += stringParser(&input[position], temp);
			setWidth(temp);
			position += stringParser(&input[position], temp);
			if(temp == 0)
				setAI(false);
			else if(temp == 1)
				setAI(true);
			position += stringParser(&input[position], temp);
			setUser(temp);
			position += createCells(&input[position]);
			return;
		}


		string ConnectFour::fileInput(const string & filename, string & loaded)
		{
			loaded[0] = 0;
			ifstream input;
			input.open(filename);
			if(input.is_open())
			{
				input >> loaded;
				input.close();
			}
			else
				cerr << "Error opening file." << endl;
			return loaded;
		}


		void ConnectFour::Load(const string & filename)
		{
			string input;
			fileInput(filename, input);
			if(input[0] != 0)
				parseInput(input);
			printMap();
			return;
		}


		void ConnectFour::vectortoString(string & output) const
		{
			output = to_string(currentHeight());
			output += '/';
			output += to_string(currentWidth());
			output += '/';
			output += currentAI() + '0';
			output += '/';
			output += currentTurn() + '0';
			output += '/';
			for(int i = 0; i < currentHeight(); ++i)
				for(int j = 0; j < currentWidth(); ++j)
					output += currentgameCell(i, j).getInside() + '0';
			return;
		}

		void ConnectFour::Save(const string & filename) const
		{
			ofstream output;
			output.open(filename);
			if(output.is_open())
			{
				string info;
				vectortoString(info);
				output << info;
				output.close();
			}
			printMap();
		}

	//Play Game
		void ConnectFour::PlayGame()
		{
			cout << "Please chose game mode." << endl
				 << "S - Single game mode." << endl
				 << "M - Multi game mode." << endl;
			char input;
			cin >> input;
			CharLover(input);
			if(input == 's')
			{
				setALL();
				do
				{
					setUser(currentTurn() % 2);
					MakeMove();
					setUser(currentTurn() + 1);
				} while(WinSituation() == false);
				printMap();
				destroyCells();
			}
			else if(input == 'm')
			{
				ConnectFour obj2, obj3, obj4, obj5;
				cout << "For object 1" << endl;
				setALL();
				cout << "For object 2" << endl;
				obj2.setALL();
				cout << "For object 3" << endl;
				obj3.setALL();
				cout << "For object 4" << endl;
				obj4.setALL();
				cout << "For object 5" << endl;
				obj5.setALL();
				bool obj1F = false, obj2F = false, obj3F = false,
					  obj4F = false,  obj5F = false;
				while(	obj1F == false ||
						obj2F == false ||
						obj3F == false ||
						obj4F == false ||
						obj5F == false)
				{
					switch(choiceObject())
					{
						case 0:
							if(compare(obj2))
								cout << "Object 1 is greater than Object 2" << endl;
							else
								cout << "Object 2 is greater than Object 1" << endl;
							if(compare(obj3))
								cout << "Object 1 is greater than Object 3" << endl;
							else
								cout << "Object 3 is greater than Object 1" << endl;
							if(compare(obj4))
								cout << "Object 1 is greater than Object 4" << endl;
							else
								cout << "Object 4 is greater than Object 1" << endl;
							if(compare(obj5))
								cout << "Object 1 is greater than Object 5" << endl;
							else
								cout << "Object 5 is greater than Object 1" << endl;
							break;
						case 1:
							if(obj1F == false)
							{
								setUser(currentTurn() % 2);
								MakeMove();
								setUser(currentTurn() + 1);
								obj1F = WinSituation();
							}
							else
								cout << "Object 1 has finished." << endl;
							break;
						case 2:
							if(obj2F == false)
							{
								obj2.setUser(obj2.currentTurn() % 2);
								obj2.MakeMove();
								obj2.setUser(obj2.currentTurn() + 1);
								obj2F = obj2.WinSituation();
							}
							else
								cout << "Object 2 has finished." << endl;
							break;
						case 3:
							if(obj3F == false)
							{
								obj3.setUser(obj3.currentTurn() % 2);
								obj3.MakeMove();
								obj3.setUser(obj3.currentTurn() + 1);
								obj3F = obj3.WinSituation();
							}
							else
								cout << "Object 3 has finished." << endl;
							break;
						case 4:
							if(obj4F == false)
							{
								obj4.setUser(obj4.currentTurn() % 2);
								obj4.MakeMove();
								obj4.setUser(obj4.currentTurn() + 1);
								obj4F = obj4.WinSituation();
							}
							else
								cout << "Object 4 has finished." << endl;
							break;
						case 5:
							if(obj5F == false)
							{
								obj5.setUser(obj5.currentTurn() % 2);
								obj5.MakeMove();
								obj5.setUser(obj5.currentTurn() + 1);
								obj5F = obj5.WinSituation();
							}
							else
								cout << "Object 5 has finished." << endl;
							break;
						default:
							break;
					}
				}
			}
			else
				cerr << "Unknown input!" << endl;
		}
//

//Cell Functions

	inline void ConnectFour::Cell::LivingCellUpdate()
	{
		++LivingCells;
		return;
	}

	ConnectFour::Cell::Cell() : positionY(0), positionX('a'), Inside(0)
	{ /*...*/ }


	ConnectFour::Cell::Cell(const int & value, const char & input):  Inside(0)
	{
		setCell(input, value);
	}

	ConnectFour::Cell::Cell(const int & value, const char & input, const int & info) : Inside(0)
	{
		setCell(input, value);
		setCell(info);
	}

	void ConnectFour::Cell::setCell(const char & input, const int & value)
	{
		if(input >= 'a' && input <= 'z' && value >= 0)
		{
			positionX = input;
			positionY = value;
		}
		else
			cerr << "Error while setting Cell Row/Column" << endl;
	}

	void ConnectFour::Cell::setCell(const int & info)
	{
		if(info >= 0 && info < 5)
		{
			int tempinside = getInside();
			if(tempinside == 0)
			{
				if(info < 3 && info > 0)
					{
						Inside = info;
						LivingCellUpdate();
					}
			}
			else if(Inside == 1 && info == 3)
			{
				Inside = info;
				LivingCellDestroyed();
			}
			else if(Inside == 2 &&  info == 4)
			{
				Inside = info;
				LivingCellDestroyed();
			}
			else
				cerr << "This cell is filled." << endl;
		}
		else
			cerr << "Error while setting Cell Inside" << endl;
		return;
	}

	char ConnectFour::Cell::getRow() const
	{
		return positionX;
	}

	int ConnectFour::Cell::getColumn() const
	{
		return positionY;
	}

	int ConnectFour::Cell::getInside() const
	{
		return Inside;
	}
//
#include "../header/ConnectFourAbstract.h"
namespace MuazKurt
{
	//Lovers
		void CharLover(char & letter)
		{
			if(letter >= 'A' && letter <= 'Z')
				letter -= ('A' - 'a');
			return;
		}

		int stringLover(std::string & traget)
		{
			int i = 0;
			for(i; traget[i] != 0; ++i)
				CharLover(traget[i]);
			return i;
		}
	//~
	//ConnectFourAbstract
		// ConnectFourAbstract functions.
			//Constructer Basic
			ConnectFourAbstract::ConnectFourAbstract(int square) : turnCounter(1), AI_open(false)
			{
				setWidth(square);
				setHeight(square);
				createCells();
			}

			ConnectFourAbstract::ConnectFourAbstract(int rectHeight, int rectWidth) : turnCounter(1), AI_open(false)
			{
				setWidth(rectWidth);
				setHeight(rectHeight);
				createCells();
			}

			ConnectFourAbstract::ConnectFourAbstract(const std::string & input) : width(0), height(0), turnCounter(1), AI_open(false)
			{
				std::string parser;
				{
					std::ifstream filename;
					filename.open(input);
					if(!filename.is_open())
					{
						std::cerr << "failed to open file." << std::endl;
						exit(1);
					}
					char temp;
					int widthTop = 0;
					while(filename.get(temp))
					{
						switch(temp)
						{
							case ' ':
								++widthTop;					
								parser += '9';
								break;
							case '*':
								++widthTop;					
								parser += '0';
								break;
							case '\n':
								++height;
								if(widthTop > width)
									width = widthTop;
								widthTop = 0;
								break;
							default:
								std::cerr << "Unknown format" << std::endl;
								exit(1);
								break;
						}
					}
					filename.close();
				}
				createCells(parser);
			}
			// Cpy 
			ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract & other) : ConnectFourAbstract()
			{
				*this = other;
			}
			//Asign
			const ConnectFourAbstract & ConnectFourAbstract::operator =(const ConnectFourAbstract & other)
			{
				destroyCells();
				setHeight(other.currentHeight());
				setWidth(other.currentWidth());
				AI_open = other.AI_open;
				turnCounter = other.turnCounter;
				createCells();
				for(int i = 0; i < currentHeight(); ++i)
					for(int j = 0; j < currentWidth(); ++j)
						currentgameCell(i, j).setCell(other.currentgameCell(i, j).getInside());
				return *this;
			}
		//~
		//Dest
			//Map Destroyers
				void ConnectFourAbstract::destroyCells()
				{
					for(int i = 0; i < currentHeight(); ++i)
						delete [] gameCell[i];
					delete [] gameCell;
					return;
				}
			ConnectFourAbstract::~ConnectFourAbstract()
			{
				destroyCells();
				gameCell = nullptr;
			}
		//~
		//Operators
			//Boolian opt
				bool ConnectFourAbstract::operator ==(const ConnectFourAbstract & other) const
				{
					if(currentHeight() == other.currentHeight() && currentWidth() == other.currentWidth())
						for(int i = 0; i < currentHeight(); ++i)
							for(int j = 0; j < currentWidth(); ++j)
								if(gameCell[i][j] != other.gameCell[i][j])
									return false;
					else return false;
					return true;
				}
			
				bool ConnectFourAbstract::operator !=(const ConnectFourAbstract & other) const
				{
					return !(*this == other);
				}
			//
		//~
		//Setter
			void ConnectFourAbstract::setWidth(int input)
			{
				if(input < 4)
					std::cerr << "The game cant be played in this width" << std::endl;
				else 
					width = input;
				return;
			}

			void ConnectFourAbstract::setHeight(int input)
			{
				if(input < 4)
					std::cerr << "The game cant be played in this height" << std::endl;
				else
					height = input;
				return;
			}

			void ConnectFourAbstract::setAI(bool input)
			{
				AI_open = input;
			}

			void ConnectFourAbstract::setUser(int input)
			{
				turnCounter = input;
			}

		//~
		//From User
			int ConnectFourAbstract::heightFromUser() const
			{
				int input = 0;
				std::cout << "Please give height of the game: ";
				std::cin >> input;
				while(input < 4)
				{
					std::cerr << "Please give another height: ";
					std::cin >> input;
				}
				return input;
			}

			int ConnectFourAbstract::widthFromUser() const
			{
				int input = 0;
				std::cout << "Please give width of the game: ";
				std::cin >> input;
				while(input < 4)
				{
					std::cerr << "Please give another width: ";
					std::cin >> input;
				}
				return input;
			}

			bool ConnectFourAbstract::AIFromUser() const
			{
				std::cout << "   ------------" << std::endl
					<<  "P) User vs User" << std::endl
					<<  "C) User vs Coop" << std::endl
					<<  "Choice: ";
				int input = 0;
				while(input == 0)
				{
					char section = 0;
					std::cin >> section;
					CharLover(section);
					if(section == 'p')
						input = 1;
					else if(section == 'c')
						input = 2;
					else
						std::cout << "Please give another input" << std::endl
							<< "Choice: ";
				}
				if(input == 1)
					return true;
				return false;
			}

			void ConnectFourAbstract::setALL()
			{
				std::cout << "Please give file name or width/height." << std::endl;
				std::string input;
				std::cin >> input;
				if(input.size() < 3)
				{
					if(input[0] <= '9' && input[0] >= '0')
					{
						setWidth(stoi(input));
						setHeight(heightFromUser());
						setAI(AIFromUser());
						createCells();
					}
					else
					{
						std::cerr << "There is no such input!" << std::endl;
						exit(1);
					}
				}
				else
				{
					input = BOARD + input;
					*this = ConnectFourAbstract(input);
					setAI(AIFromUser());				
				}
				return;
			}
		//~
		//Map printing
			void ConnectFourAbstract::printHead(std::ostream & file) const
			{
				char a = 'a';
				for(int i = 0; i < currentWidth(); ++i)
				{
					file << a++;
					if(i != currentWidth() - 1)
						file << '-';
				}
				file << std::endl;
				return;
			}

			void ConnectFourAbstract::printBody(std::ostream & file) const
			{
				int won = 0;
				for(int i = 0; i < currentHeight(); ++i)
				{
					for(int j = 0; j < currentWidth(); ++j)
					{
						file << currentgameCell(i, j);
						if(currentgameCell(i, j) == 3)
							won = 1;
						else if(currentgameCell(i, j) == 4)
							won = 2;
						file << ' ';
					}
					file << std::endl;
				}
				if(won > 0)
					file << "User " << won << " won!" << std::endl;
				return;
			}

			std::ostream & operator <<(std::ostream & file, const ConnectFourAbstract & object)
			{
				object.printHead(file);
				object.printBody(file);
				file << "Living Cells: " << object.livingCells() << std::endl;
				return file;
			}
		//~
		//Map Creaters
			void ConnectFourAbstract::createCells()
			{
				gameCell = new Cell * [currentHeight()];
				for(int i = 0; i < currentHeight(); ++i)
				{
					gameCell[i] = new Cell [currentWidth()];
					for(int j = 0; j < currentWidth(); ++j)
						gameCell[i][j] = Cell(i, 'a' + j, 0);
				}
				return;
			}
		//~
		// Inputs and Move
			int ConnectFourAbstract::PositionY() const
			{
				if(currentgameCell(0, getCoordinateX()).getInside() < 1)
				{
					int i = currentHeight() - 1;
					for(i; currentgameCell(i, getCoordinateX()).getInside() > 0 && i > 0; --i);
					if(currentgameCell(i, getCoordinateX()) == 0)
						return i;
				}
				return -1;
			}

			void ConnectFourAbstract::play(Cell IDONTNEEDIT)
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
						Input = MEMORY + Input;
						Save(Input);
					}
					else if(LOAD == Input)
					{
						std::cin >> Input;
						Input = MEMORY + Input;
						Load(Input);
						setCoordinateX(-1);
					}
					else
						std::cerr << "There is no such command." << std::endl;
				} while(getCoordinateX() == -1);
				return;
			}


			void ConnectFourAbstract::play()
			{
				std::cout << "Computer moving to: ";
				int i = 0;
				bool PositionFound = false;
				while(PositionFound == false)
				{
					switch(i)
					{
						//Watch out for Up to down.
						case 0:						
							if(Up_Down() > 2 && getCoordinateY() > 0 && 
								currentgameCell(getCoordinateX(), getCoordinateY() - 1) == 0)
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
								PositionFound == false && getCoordinateX() < currentWidth() - 1
								&& getCoordinateY() >= 0; 
								setCoordinateX(getCoordinateX() + 1), setCoordinateY(PositionY()))
							{
								if(getCoordinateY() + 1 < currentHeight())
								{
									setCoordinateY(getCoordinateY() + 1);
									if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
										if(Up_Down() > 1)
											PositionFound = true;
									setCoordinateY(getCoordinateY() - 1);
									// The way like '\' if i can check right down
									if(PositionFound == false && getCoordinateX() + 1 < currentWidth())
									{
										setCoordinateY(getCoordinateY() + 1);
										setCoordinateX(getCoordinateX() + 1);
										int right_temp = 0;
										if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
											right_temp = Right_Down();
										setCoordinateX(getCoordinateX() - 1);
										setCoordinateY(getCoordinateY() - 1);
										if(getCoordinateY() - 1 >= 0 && getCoordinateX() - 1 >= 0)
										{
											setCoordinateY(getCoordinateY() - 1);
											setCoordinateX(getCoordinateX() - 1);
											if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
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
										if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
											left_temp = Left_Down();
										setCoordinateX(getCoordinateX() + 1);
										setCoordinateY(getCoordinateY() - 1);
										if(getCoordinateY() - 1 >= 0 && getCoordinateX() + 1 < currentWidth())
										{
											setCoordinateY(getCoordinateY() - 1);
											setCoordinateX(getCoordinateX() + 1);
											if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
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
										if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
											right_temp = Right_Up();
										setCoordinateX(getCoordinateX() - 1);
										setCoordinateY(getCoordinateY() + 1);
										if(getCoordinateY() + 1 < currentHeight() && getCoordinateX() - 1 >= 0)
										{
											setCoordinateY(getCoordinateY() + 1);
											setCoordinateX(getCoordinateX() - 1);
											if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
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
										if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
											left_temp = Left_Up();
										setCoordinateX(getCoordinateX() + 1);
										setCoordinateY(getCoordinateY() + 1);
										if(getCoordinateY() + 1 < currentHeight() && getCoordinateX() + 1 < currentWidth())
										{
											setCoordinateY(getCoordinateY() + 1);
											setCoordinateX(getCoordinateX() + 1);
											if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
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
									
									
									if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
										right_temp = To_Right();
									setCoordinateX(getCoordinateX() - 1);
									if(getCoordinateX() - 1 >= 0)
									{
										
										setCoordinateX(getCoordinateX() - 1);
										if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
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
									if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
										left_temp = To_Left();
									setCoordinateX(getCoordinateX() + 1);
									if(getCoordinateX() + 1 < currentWidth())
									{
										setCoordinateX(getCoordinateX() + 1);
										if(currentgameCell(getCoordinateY(), getCoordinateX()) == 2)
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
				std::cout << "[" << getCoordinateY() << "," << (char)(getCoordinateX() + 'a')<< "]" << std::endl;
				return;
			}
			

			void ConnectFourAbstract::MakeMove()
			{
				std::cout << *this;
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
		//~
		// Check Mechanism
			int ConnectFourAbstract::Up_Down() const
			{
				int i = 1;
				bool Legal = true;
				while(Legal == true && getCoordinateY() + i < currentHeight() && currentgameCell(getCoordinateY(), getCoordinateX()) != -1)
				{
					if(currentgameCell(getCoordinateY(), getCoordinateX()) != currentgameCell(getCoordinateY() + i, getCoordinateX()))
						Legal = false;
					else
						++i;
				}
				return i;
			}


			int ConnectFourAbstract::Right_Down() const
			{
				int i = 1;
				if(getCoordinateY() >= currentHeight() - 1 || getCoordinateX() >= currentWidth() - 1);
				else
				{
					bool Legal = true;
					while(Legal == true && getCoordinateY() + i < currentHeight() && getCoordinateX() + i < currentWidth())
					{
						if(currentgameCell(getCoordinateY(), getCoordinateX()) != currentgameCell(getCoordinateY() + i, getCoordinateX() + i))
							Legal = false;
						else
							++i;
					}
				}
				return i;
			}

			int ConnectFourAbstract::Right_Up() const
			{
				int i = 1;
				if(getCoordinateY() <= 0 || getCoordinateX() >= currentWidth() - 1);
				else
				{
					bool Legal = true;
					while(Legal == true && getCoordinateY() - i >= 0 && getCoordinateX() + i < currentWidth())
					{
						if(currentgameCell(getCoordinateY(), getCoordinateX()) != currentgameCell(getCoordinateY() - i, getCoordinateX() + i))
							Legal = false;
						else
							++i;
					}
				}
				return i;
			}


			int ConnectFourAbstract::Left_Down() const
			{
				int i = 1;
				if(getCoordinateY() >= currentHeight() - 1 || getCoordinateX() <= 0);
				else
				{
					bool Legal = true;
					while(Legal == true && getCoordinateY() + i < currentHeight() && getCoordinateX() - i >= 0)
						{
							if(currentgameCell(getCoordinateY(), getCoordinateX()) != currentgameCell(getCoordinateY() + i, getCoordinateX() - i))
								Legal = false;
							else
								++i;
						}
				}
				return i;
			}


			int ConnectFourAbstract::Left_Up() const
			{
				int i = 1;
				if(getCoordinateY() <= 0 || getCoordinateX() <= 0);
				else
				{
					bool Legal = true;
					while(Legal == true && getCoordinateY() - i >= 0 && getCoordinateX() - i >= 0)
						{
							if(currentgameCell(getCoordinateY(), getCoordinateX()) != currentgameCell(getCoordinateY() - i, getCoordinateX() - i))
								Legal = false;
							else
								++i;
						}
				}
				return i;
			}


			int ConnectFourAbstract::To_Right() const
			{
				int i = 1;
				if(getCoordinateX() > currentWidth() - 1);
				else
				{
					bool Legal = true;
					while(Legal == true && getCoordinateX() + i < currentWidth())
					{
						if(currentgameCell(getCoordinateY(), getCoordinateX()) != currentgameCell(getCoordinateY(), getCoordinateX() + i))
							Legal = false;
						else
							++i;
					}
				}
				return i;
			}


			int ConnectFourAbstract::To_Left() const
			{
				int i = 1;
				if(getCoordinateX() < 1);
				else
				{
					bool Legal = true;
					while(Legal == true && getCoordinateX() - i >= 0)
					{
						if(currentgameCell(getCoordinateY(), getCoordinateX()) != currentgameCell(getCoordinateY(), getCoordinateX() - i))
							Legal = false;
						else
							++i;
					}
				}
				return i;
			}

			bool ConnectFourAbstract::WinSituation()
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

			bool ConnectFourAbstract::GameDraw() const
			{
				bool noplace = true;
				for(int i = 0; i < currentWidth() && noplace == true; ++i)
					if(currentgameCell(0, i).getInside() == 0)
						noplace = false;
				return noplace;
			}
		//~
		//	File operations.
			int ConnectFourAbstract::stringParser(const std::string & input, int & returnValue, const char param) const
			{
				int i = 0;
				returnValue = 0;
				for(i = 0; input[i] != param; ++i)
					returnValue = returnValue * 10 + (input[i] - '0');
				return i + 1;
			}


			int ConnectFourAbstract::createCells(const std::string & input)
			{
				createCells();
				for(int j = 0; j < currentHeight(); ++j)
				{
					for(int k = 0; k < currentWidth(); ++k)
					{
						if(input[k + j * currentWidth()] == '9')
							currentgameCell(j, k).setCell(-1);
						else
							currentgameCell(j, k).setCell((int)(input[k + j * currentWidth()] - '0'));
					}
				}
				return currentHeight() * currentWidth();
			}


			int ConnectFourAbstract::parseInput(const std::string & input)
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
				return position + 1;
			}


			std::string ConnectFourAbstract::fileInput(const std::string & filename, std::string & loaded)
			{
				loaded[0] = 0;
				std::ifstream input;
				input.open(filename);
				if(input.is_open())
				{
					input >> loaded;
					input.close();
				}
				else
					std::cerr << "Error opening file." << std::endl;
				return loaded;
			}


			void ConnectFourAbstract::Load(const std::string & filename)
			{
				std::string input;
				fileInput(filename, input);
				if(input[0] != 0)
					parseInput(input);
				std::cout << *this;
				return;
			}


			void ConnectFourAbstract::toString(std::string & output) const
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
				return;
			}

			void ConnectFourAbstract::Save(const std::string & filename) const
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

		//~
		//	Play Game
			void ConnectFourAbstract::PlayGame()
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
		//~
	//~ConnectFourAbstract
}
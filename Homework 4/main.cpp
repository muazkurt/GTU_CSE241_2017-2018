#include <iostream> 
#include <string>	//For string operations.
#include <cstdlib>	//For malloc, rand and srand functions
#include <ctime>	//For time function.
#include <fstream>
#include <vector>
#define SAVE "save"
#define LOAD "load"
#define MEMORY "./backup/"
#define BOARD "./board/"
#define Y_X 2
using namespace std;
class ConnectFour
{
public:
	//Constructer
		/*
			Creates 5x5 board as default
		*/
		ConnectFour(int square = 5);
		/*
			Creates WxH board.
		*/
		ConnectFour(int rectHeight, int rectWidth);
		//Big 3
			/*
				Copy constructer
			*/
			ConnectFour(const ConnectFour & other);
			/*
				Assignment operator
			*/
			const ConnectFour & operator =(const ConnectFour & other);
			/*
				Destructer.
			*/
			~ConnectFour();
		//~
		//FromFile
			ConnectFour(const string & input);
		//~
	//~
	//Getter
		inline int currentWidth() const { return width; }
		inline int currentHeight() const { return height; }
		inline int currentTurn() const { return turnCounter; }
		inline bool currentAI() const { return AI_open; }
	//~
	//livingcells
		/*
			Returns how many Cell have been created.
		*/
		inline static int livingCells() { return Cell::getLivingCells(); }
	//~
	//Play Game
		/*
			Driver function of all class.
		*/
		void PlayGame();
	//~
	//Bool
		/*
			Checks for objects if they are equal or not.
		*/
		bool operator ==(const ConnectFour & other) const;
		bool operator !=(const ConnectFour & other) const;
	//~
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
				Cell(int inside = 0);
				
				/*
					Declares that:
						info = 0
					and
					Calls:
						setCell(input, value);
				*/
				Cell(int value, char input);
				
				/*
					Calls
						setCell(input, value);
						setCell(info);
				*/
				Cell(int value, char input, int info);
			//~Constructer
			//Destructer
				~Cell();
			//~Destructer
			//Operators
				//Bool
					/* 
						== Compares objects info
					*/
					bool operator ==(const ConnectFour::Cell & other) const;

					/*
						!=
					*/
					bool operator !=(const ConnectFour::Cell & other) const;
				//
				//Incrimnet
					/*
						++ user1-> user2 | AI -> empty -> user1
					*/
					ConnectFour::Cell operator++(int);
					const ConnectFour::Cell & operator++();
				//
				//Decriment
					/*
						-- empty -> user1 -> user2 | AI -> empty
					*/
					ConnectFour::Cell operator--(int);
					const ConnectFour::Cell & operator--();

				//
			//~Operators
			//Setter
				/*
					Checks info for legal or not.
					Then checks if the cell is empty or not.
					if empty fills the cell.
					if filled Then checks if update is legal or not.
				*/
				void setCell(int info);
			//~Setter
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
			//~Getter
		private:
			inline void LivingCellDestroyed() { --LivingCells; }
			inline void LivingCellUpdate()		{ ++LivingCells; }
			/*
				Declaring Cell position
			*/
			void setCell(char input, int value);
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
		public:
			//Streams
					/*
						<< writes the output ostream file like:
							'x', 'X', 'O', 'o', ' ', '.'
					*/
					friend ostream & operator <<(ostream & file, const Cell & me);
					

					/*
						>> gets inputs '*', ' ' and '\n'
							and updates them like my inside format.
					*/
					friend istream & operator >>(istream & file, ConnectFour::Cell & me);
					
			//
		};
	//~
	//Setter
		void setHeight(int input);
		
		void setWidth(int input);
		
		void setAI(bool input);
		
		void setUser(int input);

	//~
	//Getting input from user
		// Only at start setters
			/*
				Asks user for info
			*/
				int heightFromUser() const;

				int widthFromUser() const;
			
				bool AIFromUser() const;
			//driver function.
				void setALL();
		// In each turn
			int choiceObject() const;

			int PositionY() const;

			void play(ConnectFour::Cell IDONTNEEDIT);
			
			void play();

			void MakeMove();
	//~
	//Char&String lover
		/*
			Takes a char and updates itself as lowercase
				if already lower, nothing changes
		*/
		void CharLover(char & letter) const;
		/*
			Uses charlover for all target string index,
				returns size of string size
		*/
		int stringLover(string & traget) const;
	//~
	//Prisntmap() -> Subfunctions.
		/*
			Prints 'a' to 'a'+width to ostream file
		*/
		void printHead(ostream & file) const;
		/*
			Prinst inside of map to ostream file.
		*/		
		void printBody(ostream & file) const;
	//~
	//Create Map.
		void createCells();
	//~
	//Destroy Map.
		void destroyCells();
	//~
	//Check Map
		/*
			Checks how much up way stacked from last played position.
			Returns the size of stack.
		*/
		int Up_Down() const;

		/*
			Checks how much Right down way stacked from last played position.
			Returns the size of stack.
		*/
		int Right_Down() const;


		/*
			Checks how much Right up way stacked from last played position.
			Returns the size of stack.
		*/
		int Right_Up() const;

		/*
			Checks how much Left-down way stacked from last played position.
			Returns the size of stack.
		*/
		int Left_Down() const;
		/*
			Checks how much Left-up way stacked from last played position.
			Returns the size of stack.
		*/
		int Left_Up() const;

		/*
			Checks how much right way stacked from last played position.
			Returns the size of stack.
		*/
		int To_Right() const;

		/*
			Checks how much left way stacked from last played position.
			Returns the size of stack.
		*/
		int To_Left() const;

	//~
	// Check Game
		/*
			Returns true if game finished.
		*/
		bool WinSituation();
	//~
	//Coordinate Getter
		inline int getCoordinateY() const { return coordinate[0]; }
		inline int getCoordinateX() const { return coordinate[1]; }
	//~
	//Coordinate Setter
		inline void setCoordinateY(const int & input) { coordinate[0] = input; }
		inline void setCoordinateX(const int & input) { coordinate[1] = input; }
	//~
	//GameCell Getter
		const ConnectFour::Cell & currentgameCell(const int & y, const int & x) const
		{ return gameCell[y][x];}
	//~
	//GameCell Setter
		ConnectFour::Cell & currentgameCell(const int & y, const int & x)
		{ return gameCell[y][x];}
	//~
	//Load & Save
		/*
			Parses the string to param item. Counts item through param and returns it.
			Updates return value with each item of string throug param.
			Acts like there is a int throug param from start of string.
		*/
		int stringParser(const string & input, int & returnValue, const char param = '/') const;
		
		/*
			Takes Cell info from a string.
		*/
		int createCells(const string & input);
		
		/*
			Reads each member of class from string.
		*/
		void parseInput(const string & input);
		
		/*
			Opens filename and reads it's contet to loadad parameter.
		*/
		string fileInput(const string & filename, string & loaded);
		
		/*
			Fills string with all members of class
		*/
		void toString(string & output) const;
		/*
			Opens file, reads contet, updates objec
		*/
		void Load(const string & filename);
		
		/*
			Opens file, writes info
		*/
		void Save(const string & filename) const;
	//~
	//Members
		Cell ** gameCell;
		int height;
		int width;
		int turnCounter;
		bool AI_open;
		int coordinate[Y_X];
	//~
public:
	//Cell File opts
		/*
			<< writes the output ostream file like:
				'x', 'X', 'O', 'o', ' ', '.'
		*/
		friend ostream & operator <<(ostream & file, const ConnectFour::Cell & me);
		
		/*
			>> gets inputs '*', ' ' and '\n'
				and updates them like my inside format.
		*/
		friend istream & operator >>(istream & file, ConnectFour::Cell & me);
	//~
	//ConnectFour opts
		/*
			<< Prints the class to ostream file.
		*/
		friend ostream & operator <<(ostream & file, const ConnectFour & me);
	//~
};
ostream & operator <<(ostream & file, const ConnectFour & me);
ostream & operator <<(ostream & file, const ConnectFour::Cell & me);
istream & operator >>(istream & file, ConnectFour::Cell & me);


int ConnectFour::Cell::LivingCells = 0;

int main(void)
{
	srand(time(NULL));
	ConnectFour ina;
	ina.PlayGame();
	return 0;
}



//ConnectFour
	// ConnectFour functions.
		//Constructer Basic
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

		ConnectFour::ConnectFour(const string & input) : width(0), height(0), turnCounter(1), AI_open(false)
		{
			string parser;
			{
				ifstream filename;
				filename.open(input);
				if(!filename.is_open())
				{
					cerr << "failed to open file." << endl;
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
							cerr << "Unknown format" << endl;
							exit(1);
							break;
					}
				}
				filename.close();
			}
			createCells(parser);
		}
		// Cpy 
		ConnectFour::ConnectFour(const ConnectFour & other) : ConnectFour()
		{
			*this = other;
		}
		//Asign
		const ConnectFour & ConnectFour::operator =(const ConnectFour & other)
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
			void ConnectFour::destroyCells()
			{
				for(int i = 0; i < currentHeight(); ++i)
					delete [] gameCell[i];
				delete [] gameCell;
				return;
			}
		ConnectFour::~ConnectFour()
		{
			destroyCells();
			gameCell = nullptr;
		}
	//~
	//Operators
		//Boolian opt
			bool ConnectFour::operator ==(const ConnectFour & other) const
			{
				if(currentHeight() == other.currentHeight() && currentWidth() == other.currentWidth())
					for(int i = 0; i < currentHeight(); ++i)
						for(int j = 0; j < currentWidth(); ++j)
							if(gameCell[i][j] != other.gameCell[i][j])
								return false;
				else return false;
				return true;
			}
		
			bool ConnectFour::operator !=(const ConnectFour & other) const
			{
				return !(*this == other);
			}
		//
	//~
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

	//~
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
			cout << "Please give file name or width/height." << endl;
			string input;
			cin >> input;
			if(input.size() < 3)
			{
				setWidth(stoi(input));
				setHeight(heightFromUser());
				setAI(AIFromUser());
				createCells();
			}
			else
			{
				input = BOARD + input;
				*this = ConnectFour(input);
				setAI(AIFromUser());				
			}
			return;
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
	//~
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
	//~
	//Map printing
		void ConnectFour::printHead(ostream & file) const
		{
			char a = 'a';
			for(int i = 0; i < currentWidth(); ++i)
			{
				file << a++;
				if(i != currentWidth() - 1)
					file << '-';
			}
			file << endl;
			return;
		}

		void ConnectFour::printBody(ostream & file) const
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
				file << endl;
			}
			if(won > 0)
				file << "User " << won << " won!" << endl;
			return;
		}

		ostream & operator <<(ostream & file, const ConnectFour & object)
		{
			object.printHead(file);
			object.printBody(file);
			file << "Living Cells: " << object.livingCells() << endl;
			return file;
		}
	//~
	//Map Creaters
		void ConnectFour::createCells()
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
		int ConnectFour::PositionY() const
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
							cerr << getCoordinateY() << "This is not legal." << endl;
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
			cout << "[" << getCoordinateY() << "," << (char)(getCoordinateX() + 'a')<< "]" << endl;
			return;
		}
		

		void ConnectFour::MakeMove()
		{
			cout << *this;
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
		int ConnectFour::Up_Down() const
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


		int ConnectFour::Right_Down() const
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

		int ConnectFour::Right_Up() const
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


		int ConnectFour::Left_Down() const
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


		int ConnectFour::Left_Up() const
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


		int ConnectFour::To_Right() const
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


		int ConnectFour::To_Left() const
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
	//~
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
			cout << *this;;
			return;
		}


		void ConnectFour::toString(string & output) const
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
				toString(info);
				output << info;
				output.close();
			}
			cout << *this;;
		}

	//~
	//	Play Game
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
				cout << *this;;
			//	destroyCells();
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
							if(*this == obj2)
								cout << "Object 1 is equal to Object 2" << endl;
							else
								cout << "Object 2 is not equal to Object 1" << endl;
							if(*this == obj3)
								cout << "Object 1 is equal to Object 3" << endl;
							else
								cout << "Object 3 is not equal to Object 1" << endl;
							if(*this == obj4)
								cout << "Object 1 is equal to Object 4" << endl;
							else
								cout << "Object 4 is not equal to Object 1" << endl;
							if(*this == obj5)
								cout << "Object 1 is equal to Object 5" << endl;
							else
								cout << "Object 5 is not equal to Object 1" << endl;
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
	//~
//~ConnectFour
//Cell
	//Constructer	
		ConnectFour::Cell::Cell(int inside) : positionY(0), positionX('a'), Inside(inside)
		{
			if(inside > 0)
				LivingCellUpdate();
			else; 
		}


		ConnectFour::Cell::Cell(int value, char input):  Inside(0)
		{
			setCell(input, value);
		}

		ConnectFour::Cell::Cell(int value, char input, int info) : Inside(0)
		{
			setCell(input, value);
			setCell(info);
		}
	//~Constructer
	//Destructer
		ConnectFour::Cell::~Cell()
		{
			int temp;
			temp = getInside();
			if(temp > 0 && temp < 5)
				LivingCellDestroyed();
		}
	//~Destructer
	//Operators
		//Bool
		/* 
			== 
		*/
		bool ConnectFour::Cell::operator ==(const ConnectFour::Cell & other) const
		{
			return (getInside() == other.getInside());
		}

		/*
			!=
		*/
		bool ConnectFour::Cell::operator !=(const ConnectFour::Cell & other) const
		{
			return !(*this == other);
		}
		//Incriments
			/*
				++
			*/
			ConnectFour::Cell ConnectFour::Cell::operator++(int)
			{
				ConnectFour::Cell temp = (*this);
				if(Inside == 2)
					Inside = 0;
				else 
					++Inside;
				return temp;
			}
			const ConnectFour::Cell & ConnectFour::Cell::operator++()
			{
				if(Inside == 2)
					Inside = 0;
				else 
					++Inside;
				return *this;
			}

			/*
				--
			*/
			ConnectFour::Cell ConnectFour::Cell::operator--(int)
			{
				ConnectFour::Cell temp = (*this);
				if(Inside == 0)
					Inside = 2;
				else
					--Inside;
				return temp;
			}
			const ConnectFour::Cell & ConnectFour::Cell::operator--()
			{
				if(Inside == 0)
					Inside = 2;
				else
					--Inside;
				return (*this);
			}
		//
	//~Operators
	//getter / Setter
		void ConnectFour::Cell::setCell(char input, int value)
		{
			if(input >= 'a' && input <= 'z' && value >= 0)
			{
				positionX = input;
				positionY = value;
			}
			else
				cerr << "Error while setting Cell Row/Column" << endl;
		}

		void ConnectFour::Cell::setCell(int info)
		{
			if(info >= 0 && info < 5)
			{
				if(Inside == 0)
				{
					Inside = info;
					if(info < 3 && info > 0)
						LivingCellUpdate();
				}
				else if((Inside == 1 && info == 3) || (Inside == 2 && info == 4))
					Inside = info;
				else
					cerr << "This cell is filled." << endl;
			}
			else
				Inside = info;
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
	//~
//~Cell
//File operations.
	ostream & operator <<(ostream & file, const ConnectFour::Cell & me)
	{
		switch(me.getInside())
			{
				case 0:
					file << '.';
					break;
				case 1:
					file << 'X';
					break;
				case 2:
					file << 'O';
					break;
				case 3:
					file << 'x';
					break;
				case 4:
					file << 'o';
					break;
				default:
					file << ' ';
					break;
			}
		
		return file;
	}



	istream & operator >>(istream & file, ConnectFour::Cell & me)
	{
		char temp = 0;
		file >> temp;
		if(temp == '*')
			me.Inside = 0;
		else if(temp == ' ')
			me.Inside = -1;
		else if(temp >= '0' && temp < 5)
			me.Inside = temp - '0';
		return file;
	}
//~file
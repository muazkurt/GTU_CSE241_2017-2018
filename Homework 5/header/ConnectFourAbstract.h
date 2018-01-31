#ifndef CONNECTFOURABSTRACT_H
	#define CONNECTFOURABSTRACT_H 
	#include "./Cell.h"
	#include <string>	//For string operations.
	#define Y_X 2
	#define SAVE "save"
	#define LOAD "load"
	#define UNDO "undo"
	#define BOARD "./board/"
	#define MEMORY "./backup/"
	namespace MuazKurt
	{
		//Char & string lover
			/*
				Takes a char and updates itself as lowercase
					if already lower, nothing changes
			*/
			void CharLover(char & letter);
			/*
				Uses charlover for all target std::string index,
					returns size of std::string size
			*/
			int stringLover(std::string & traget);
		//~
		class ConnectFourAbstract
		{
		public:
			//Constructer
				/*
					Creates 5x5 board as default
				*/
				ConnectFourAbstract(int square = 5);
				/*
					Creates WxH board.
				*/
				ConnectFourAbstract(int rectHeight, int rectWidth);
				//Big 3
					/*
						Copy constructer
					*/
					ConnectFourAbstract(const ConnectFourAbstract & other);
					/*
						Assignment operator
					*/
					const ConnectFourAbstract & operator =(const ConnectFourAbstract & other);
					/*
						Destructer.
					*/
					~ConnectFourAbstract();
				//~
				//FromFile
					ConnectFourAbstract(const std::string & input);
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
				bool operator ==(const ConnectFourAbstract & other) const;
				bool operator !=(const ConnectFourAbstract & other) const;
			//~
		protected:
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
					int PositionY() const;

					void play(Cell IDONTNEEDIT);
					
					void play();

					void MakeMove();
			//~
			//Prisntmap() -> Subfunctions.
				/*
					Prints 'a' to 'a'+width to std::ostream file
				*/
				void printHead(std::ostream & file) const;
				/*
					Prinst inside of map to std::ostream file.
				*/		
				void printBody(std::ostream & file) const;
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

				/*
					Returns true if game is draw.
				*/
				bool GameDraw() const;
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
				const Cell & currentgameCell(const int & y, const int & x) const
				{ return gameCell[y][x];}
			//~
			//GameCell Setter
				Cell & currentgameCell(const int & y, const int & x)
				{ return gameCell[y][x];}
			//~
			//Load & Save
				/*
					Parses the std::string to param item. Counts item through param and returns it.
					Updates return value with each item of std::string throug param.
					Acts like there is a int throug param from start of std::string.
				*/
				int stringParser(const std::string & input, int & returnValue, const char param = '/') const;
				
				/*
					Takes Cell info from a std::string.
				*/
				int createCells(const std::string & input);
				
				/*
					Reads each member of class from std::string.
				*/
				int parseInput(const std::string & input);
				
				/*
					Opens filename and reads it's contet to loadad parameter.
				*/
				std::string fileInput(const std::string & filename, std::string & loaded);
				
				/*
					Opens file, reads contet, updates objec
				*/
				void Load(const std::string & filename);
				
				/*
					Fills std::string with all members of class
				*/
				void toString(std::string & output) const;
				
				/*
					Opens file, writes info
				*/
				void Save(const std::string & filename) const;
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
			//ConnectFourAbstract opts
				/*
					<< Prints the class to std::ostream file.
				*/
				friend std::ostream & operator <<(std::ostream & file, const ConnectFourAbstract & me);
			//~
		};
		
		std::ostream & operator <<(std::ostream & file, const ConnectFourAbstract & me);
	}
#endif
#include "../header/Cell.h"
namespace MuazKurt
{
	int Cell::LivingCells = 0;
	//Cell
		//Constructer
			Cell::Cell(int inside) : positionY(0), positionX('a'), Inside(inside)
			{
				if(inside > 0)
					LivingCellUpdate();
				else; 
			}


			Cell::Cell(int value, char input):  Inside(0)
			{
				setCell(input, value);
			}

			Cell::Cell(int value, char input, int info) : Inside(0)
			{
				setCell(input, value);
				setCell(info);
			}
		//~Constructer
		//Destructer
			Cell::~Cell()
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
			bool Cell::operator ==(const Cell & other) const
			{
				return (getInside() == other.getInside());
			}

			/*
				!=
			*/
			bool Cell::operator !=(const Cell & other) const
			{
				return !(*this == other);
			}
			//Incriments
				/*
					++
				*/
				Cell Cell::operator++(int)
				{
					Cell temp = (*this);
					if(Inside == 2)
						Inside = 0;
					else 
						++Inside;
					return temp;
				}
				const Cell & Cell::operator++()
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
				Cell Cell::operator--(int)
				{
					Cell temp = (*this);
					if(Inside == 0)
						Inside = 2;
					else
						--Inside;
					return temp;
				}
				const Cell & Cell::operator--()
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
			void Cell::setCell(char input, int value)
			{
				if(input >= 'a' && input <= 'z' && value >= 0)
				{
					positionX = input;
					positionY = value;
				}
				else
					std::cerr << "Error while setting Cell Row/Column" << std::endl;
			}

			void Cell::setCell(int info)
			{
				if(info == 0)
				{
					if(Inside > 0 && Inside < 3)
						LivingCellDestroyed();
					Inside = info;
				}
				if(info > 0 && info < 5)
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
						std::cerr << "This cell is filled." << std::endl;
				}
				else
					Inside = info;
				return;
			}

			char Cell::getRow() const
			{
				return positionX;
			}

			int Cell::getColumn() const
			{
				return positionY;
			}

			int Cell::getInside() const
			{
				return Inside;
			}
		//~
		//File operations.
			std::ostream & operator <<(std::ostream & file, const Cell & me)
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



			std::istream & operator >>(std::istream & file, Cell & me)
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
	//~Cell
}
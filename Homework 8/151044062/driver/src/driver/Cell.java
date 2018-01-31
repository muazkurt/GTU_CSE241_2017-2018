/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package driver;
import java.awt.Color;

import javax.swing.JButton;
/**
 * Class Cell extends JButton
 * @author Muaz Kurt - 151044062
 * @version 1.0.0
 * @since 05.01.2017
 */
public class Cell extends JButton
{
	//Where am i: X
	int _positionX;
	//Where am i: Y
	int _positionY;
	//Am i filled, if so who filled me.
	int _UserInformation;

	//Cell(0, 0, user)
	public Cell(int user)
	{
		this(0, 0, user);
	}//end of Cell
	
	//Cell(Y, X, 0)
	public Cell(int Y, int X)
	{
		this(Y, X, 0);
	}//end of Cell
	
	/**
	 * Creates button, then update its porperties.
	 * @param Y Y position.
	 * @param X X position.
	 * @param info user info 0, 1, 2, 3, 4.
	 */
	public Cell(int Y, int X, int info)
	{
		super();
		setActionCommand("" + X);				
		setCell(Y, X);
		setCell(info);
	}//end of Cell
		
	/**
	 * Checks two cell's info are same.
	 * @param other Cell will be checked
	 * @return true if both same.
	 */
	protected boolean equals(Cell other)
	{
		return (getInside() == other.getInside());
	}//end of equals


	/**
	 * Set cell's Y and X as input.
	 * inputs cant be less than 0
	 * @param Y Y position.
	 * @param X X position.
	 */
	private void setCell(int Y, int X)
	{
		if(Y >= 0 && X >= 0)
		{
			_positionX = X;
			_positionY = Y;
		}
		else
			System.err.println("Error while setting Cell Row/Column");
	}//end of setCell

	/**
	 * setter for Cell info.
	 * 0: empty cell
	 * 1, 2: users
	 * 3: user 1 won
	 * 4: user 2 won
	 * @param info user information, can be: {0, 1, 2, 3, 4}
	 */
	public void setCell(int info)
	{
		if(info == 0)
			_UserInformation = info;
		else if(info > 0 && info < 5)
		{
			if(_UserInformation == 0)
				_UserInformation = info;
			else if((_UserInformation == 1 && info == 3) || (_UserInformation == 2 && info == 4))
				_UserInformation = info;
			else
				System.err.println("This cell is filled.");
		}
		else
			_UserInformation = info;
		switch(_UserInformation)
		{
			case 0:
				setBackground(Color.WHITE);
				break;
			case 1:
				setBackground(Color.RED);
				break;
			case 2:
				setBackground(Color.BLACK);
				break;
			case 3:
				setBackground(Color.PINK);
				break;
			case 4:
				setBackground(Color.GREEN);
				break;
			default:
				break;
		}
		return;
	}//end of setCell

	/**
	 * Get X position.
	 * @return X position.
	 */
	public int getRow() 
	{
		return _positionX;
	}//end of getRow

	/**
	 * Get Y position.
	 * @return Y position.
	 */
	public int getColumn() 
	{
		return _positionY;
	}//end of getColumn


	/**
	 * Get User information.
	 * @return User information.
	 */
	public int getInside() 
	{
		return _UserInformation;
	}//end of getInside
	

	/**
	 * Returns it's info as a string.
	 * Return string contents are all integers like _userInformation
	 * @return Filled String by user info
	 */
	public String toString()
	{
		String input = new String();
		switch(getInside())
			{
				case 0:
					input += '0';
					break;
				case 1:
					input += '1';
					break;
				case 2:
					input += '2';
					break;
				case 3:
					input += '3';
					break;
				case 4:
					input += '4';
					break;
				default:
					break;
			}
		return input;
	}//end of toString
}
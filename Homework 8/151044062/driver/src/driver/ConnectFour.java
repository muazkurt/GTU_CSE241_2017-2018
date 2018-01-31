/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package driver;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.security.InvalidParameterException;
import java.util.Random;
import java.util.Scanner;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
/**
 * Class ConnectFour extends JFrame
 * @author Muaz Kurt - 151044062
 * @version 1.0.0
 * @since 05.01.2017
 */
public class ConnectFour extends JFrame
{
    /**
     * Creats a panel to contain Cell objects.
     */
    private JPanel _container;                          // -- Button Panel
    /**
     * Game properties container.
     */
    private JTextField _userPanel;
    /**
     * Right panel of frame.
     */
    private JPanel _rightPanel;
    /**
     * Log parse of the game.
     */
    private JTextArea logArea;    
    /**
     * Game containers.
     */
    private Cell [][] _map;                     // -- buttons.
    /**
     * Current map' s constant.
     */
    private final int Y_X = 2;                  //
    /**
     * Last moved position info.
     * 0 index = Y position.
     * 1 index = X position.
     */
    private int [] coordinate = new int [Y_X];  //
    /**
     * Game' s size property.
     */
    public int _size;                           // 
    /**
     * Turn changer. If false -- 1st user.
     *                  true  -- 2nd user.
     */
    private boolean _turn;                      // -- to static
    /**
     * Game property, does game pwp or pwc?
     * If true-- PWP
     *    false-- PWC
     */
    private boolean _aiopen;                    // -- if true, ai closed.


    /**
     * Geter for last moved vertical position.
     * @return Last moved Vertical Position.
     */
    private int getCoordinateY()
    {
        return coordinate[0];
    }//end of getCoordinateY.
    /**
     * Getter for last moved horisontal position.
     * @return Last moved Horisontal position.
     */
    private int getCoordinateX()
    {
        return coordinate[1];
    }// end of getCoordinateX.
    
    
    /**
     * Setter for next moving vertical position.
     * @param input moving Vertical Position.
     */
    public void setCoordinateY(int input)
    {
        coordinate[0] = input;
    }//end of setCoordinateY.


    /**
     * Setter for next moving horisontal position.
     * @param input moving Horisontal position.
     */
    public void setCoordinateX(int input)
    {
        coordinate[1] = input;
    }//end of setCoordinateX.


    /**
     * Getterf for the given index's Cell information.
     * @param y Vertical index.
     * @param x Horisontal index
     * @return game fields (y,x) index.
     */
    public Cell currentgameCell(int y, int x)
    {
        return _map[y][x];
    }//end of currentgameCell.
    
    
    /**
     * @return current Turn.
     */
    public boolean currentTurn() { return _turn; }
    
    
    /**
     * @return current game's AI property.
     */
    public boolean currentAI() { return _aiopen; }
    
    
    /**
     * Takes the Logic not of the _turn.
     */
    public void switchTurn()
    {
        _turn = !_turn;
        _userPanel.setText("USER " + (!_turn ? 1: 2)  +  "\n PWC: " + (!_aiopen ? "true" : "false"));            
    }//end of switchTurn.


    //ConnectFour(10, false)
    public ConnectFour()
    {
        this(10);
    }

    /**
     * ConnectFour(size_input, false)
     * @param size_input property of game size.
     */
    public ConnectFour(int size_input)
    {
            this(size_input, false);
    }
      
    /**
     * Copy Constructer.
     * @param other , Creates this as other's properties.
     */
    public ConnectFour( ConnectFour other)
    {
        this(other._size, other._aiopen);
        for(int i = 0; i < _size; ++i)
            for(int j = 0; j < _size; ++j)
                _map[i][j] = new Cell(i, j, other._map[i][j].getInside());
    }

    /**
     * @param size_input property of game size.
     * @param ai_info  property of game PWP or PWC.
     * @exception InvalidParameterException if size_input is less than 4.
     * Game won't be playable then.
     */
    public ConnectFour(int size_input, boolean ai_info) throws InvalidParameterException
    {
        super("Connect Four");                      //Name of the frame.
        if(size_input <= 4)
            throw new InvalidParameterException();
        _size = size_input;
        _turn = false;
        _aiopen = ai_info;
        setSize( 70 * _size, 70 * _size );        
        setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        setLayout(new BorderLayout() );
        frameCreate();                              //Updates the game frame properties.
    }//end of ConnectFour.

    /**
     * Checks if two objects are same or not.
     * @param other the object that will be chacked.
     * @return if both are equal, true.
     */
    public boolean equals( ConnectFour other) 
    {
        boolean FLAG = true;
        if(_size == other._size)
            for(int i = 0; i < _size && FLAG == true; ++i)
                for(int j = 0; j < _size && FLAG == true; ++j)
                    if(_map[i][j] != other._map[i][j])
                        FLAG = false;
        else
            FLAG = false;
        return FLAG;
    }//end of equals
    
    
    /**
     * fill a string with '-' and return it for line breaker.
     * @return filled head of the stringly game.
     */
    private String printHead() 
    {
        String returString = new String();
        for(int i = 0; i < _size; ++i)
            returString += "- ";
        returString += "\n";
        return returString;
    }//end of printHead

    /**
     * fill a string with Cell's indexes toString method.
     * @return filled string for body of the stringly game. 
     */
    private String printBody()
    {
        String returnString = new String();
        int won = 0;
        for(int i = 0; i < _size; ++i)
        {
            for(int j = 0; j < _size; ++j)
            {
                returnString += currentgameCell(i, j);
                if(currentgameCell(i, j).getInside() == 3)
                    won = 1;
                else if(currentgameCell(i, j).getInside() == 4)
                    won = 2;
            }
            returnString += "\n";
        }
        if(won > 0)
            returnString += "User " + won + " won!";
        return returnString;
    }//end of printBody

    /**
     * Fills array with: head and body.
     * @return filled string for the stringly game.
     */
    public String toString()
    {
        String returnString = new String();
        returnString += printHead();
        returnString += printBody();
        return returnString;
    }//end of toString
    
    
    /**
     * Empty all Cells and frame componnent's index.
     * Give the next turn to 1st user.
     */
    private void refreshMap()
    {
        for(int i = 0; i < _size; ++i)
            for(int j = 0; j < _size; ++j)
                currentgameCell(i, j).setCell(0);
        _turn = false;
        _userPanel.setText("USER " + (!_turn ? 1: 2)  +  "\n PWC: " + (!_aiopen ? "true" : "false"));            
        logArea.setText(logArea.getText() + this.toString());
    }//end of refreshMap
    
    /**
     * Creates cell objects to play game on. 
     * Need to know _size property. 
     * Creates Cells and add them into _container.
     */
    private void createArea()
    {
        _turn = false;
    	_map = new Cell [_size][];                                          //Create Cell Buttons.
        for(int i = 0; i < _size; ++i)
        {
            _map[i] = new Cell [_size];            
            for(int j = 0; j < _size; ++j)
            {
                _map[i][j] = new Cell(i, j, 0);
                _map[i][j].addActionListener( new ActionListener(){
                
                    @Override
                    public void actionPerformed(ActionEvent event)
                    {
                        if(!WinSituation() && !GameDraw())                  //Check game finished? if not move
                        {
                            setCoordinateX(new Integer(event.getActionCommand()));
                            int Y = PositionY();                            //Declare next move.
                            if(Y > -1)                                      //If playable move.
                            {
                                setCoordinateY(Y);
                                playUser();                                 //Move and update turn
                                if(!WinSituation() && !GameDraw())          //Check game finished? if not move
                                {
                                    if(currentAI() == true);                //If pwp wait next user to make action
                                    else playPC();                          //If pwc make pc to move.
                                }
                                else refreshMap();                          //Game finished: REfresh map
                            }
                        }
                        else refreshMap();                                  //Game finished: Refresh Map.
                    }
                });
                _container.add(_map[i][j]);                                 //Add buttons to game panel.
            }
        }
    }//end of createArea
    
    
    /**
     * Create a TextArea for stringly game,
     *        two Buttons for reset and update settings.
     * Then add them in _rightPanel.
     */
    private void rightPanel()
    {
        _rightPanel = new JPanel( new BorderLayout() );
        JPanel rightBottom = new JPanel( new GridLayout(2, 1) );        //Create field for reset and settings
        JButton restart = new JButton("Restart Game");                  //Create a button for reset game.
        restart.addActionListener( new ActionListener(){                //Add it's action.
            
                @Override
                public void actionPerformed(ActionEvent event)
                {
                    if(JOptionPane.showConfirmDialog(null, "Are you sure to restart this game?", "Confirm", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
                        refreshMap();                                   //Ask user does he/she sure? if YES-- Refresh Map
                }
            });
        rightBottom.add(restart);                                       //Add reset button to field.
        JButton settings = new JButton("Setting");                      //Create a button for settings.
        settings.addActionListener(new ActionListener(){
            
                @Override
                public void actionPerformed(ActionEvent event) {
                    Integer input = Integer.parseInt( JOptionPane.showInputDialog("Please give the size of board") );
                    while(input <= 4)                                    //Ask for new size
                        input = Integer.parseInt( JOptionPane.showInputDialog("This is not legal \n Please give another size") );
                    boolean AI = true;
                    if(JOptionPane.showConfirmDialog(null, "Do you want to play with\nPWC: YES or PWP: NO", "PWP or PWC", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
                        AI = false;                                     //Ask for PWP or PWC?
                    if(JOptionPane.showConfirmDialog(null, "Are you sure to change properties?", "WARNING!", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
                    {                                                   //If user is sure, then refresh map.
                        _size = input;
                        _aiopen = AI;
                        setSize( 70 * _size, 70 * _size );
                        remove(_container);
                        _container = new JPanel( new GridLayout(_size, _size) );            //Create a grid panel.
                        createArea();
                        add(_container, BorderLayout.CENTER);
                        refreshMap();
                    }

                }
            });
        rightBottom.add(settings);                                      //Add setting to field.
        logArea = new JTextArea(this.toString());                       //Create stringly game field.
        logArea.setEditable(false);
        logArea.setLineWrap(true);
        logArea.setAutoscrolls(true);
        JScrollPane SPAN = new JScrollPane(logArea);
        _rightPanel.add(SPAN, BorderLayout.CENTER);
        _rightPanel.add(rightBottom, BorderLayout.SOUTH);
    }//end of rightPanel

    
    /**
     * Update frame properties.
     */
    private void frameCreate()
    {
        setLocationRelativeTo(null);
        setVisible( true );
        _container = new JPanel( new GridLayout(_size, _size) );            //Create a grid panel.
        _userPanel = new JTextField("USER " + (!_turn ? 1: 2)  +  "\n PWC: " + (!_aiopen ? "true" : "false"));
        _userPanel.setEditable(false);
        createArea();
        rightPanel();                                                       //Create _rightPanel
        add(_userPanel, BorderLayout.NORTH);                                //add Properties to north
        add(_container, BorderLayout.CENTER);                               //add game to center
        add(_rightPanel, BorderLayout.EAST);                                //add _rightPanel to east
    }//end of frameCreate
    
    
    /**
     * Takes next moved position and searches over it Vertical way.
     * @return -1 for no such position to move, an unsigned int less than _size othervise
     */
    public int  PositionY() 
    {
        if(currentgameCell(0, getCoordinateX()).getInside() < 1)
        {
            int i = _size - 1;
            for(; currentgameCell(i, getCoordinateX()).getInside() > 0 && i > 0; --i);
            if(currentgameCell(i, getCoordinateX()).getInside() == 0)
                return i;
        }
        return -1;
    }//end of PositionY
    
    /**
     * Takes next move position and updates it by _turn.
     */    
    public void playUser()
    {
        if(currentTurn())
            currentgameCell(getCoordinateY(),getCoordinateX()).setCell(2);
        else
            currentgameCell(getCoordinateY(),getCoordinateX()).setCell(1);
        switchTurn();
        logArea.setText(logArea.getText() + this.toString());
        return;
    }//end of playUser

    /**
     * Checks all possible finishes from last moved position,
     * if there is not, looks if it can finish?
     * if not then play randomly.
     */
    private void playPC()
    {
        int i = 0;
        boolean PositionFound = false;
        while(PositionFound == false)
        {
            switch(i)
            {
                //Watch out for Up to down.
                case 0:						
                    if(Up_Down() > 2 && getCoordinateY() > 0 && 
                        currentgameCell(getCoordinateX(), getCoordinateY() - 1).getInside() == 0)
                        {
                            PositionFound = true;
                            setCoordinateY(getCoordinateY() - 1);
                        }
                        
                        
                    break;
                //	Watch out for right down + left up and if it is possible to win for user 1,
                //		then breake it by putting right down .coordinate.
                case 1:
                    if(getCoordinateY() == _size - 1 || getCoordinateX() == _size - 1);
                    else
                    {
                        int right_temp = Right_Down();
                        if(right_temp + Left_Up() - 1 > 2)
                        {
                            if((getCoordinateY() + right_temp < _size) && (getCoordinateX() + right_temp < _size))
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
                    if(getCoordinateY() == 0 || getCoordinateX() == _size - 1);
                    else
                    {
                        int right_temp = Right_Up();
                        if(right_temp + Left_Down() - 1 > 2)
                        {
                            if((getCoordinateY() - right_temp >= 0) && getCoordinateX() + right_temp < _size)
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
                    if(getCoordinateY() == _size - 1 || getCoordinateX() == 0);
                    else
                    {
                        int left_temp = Left_Down();
                        if(left_temp + Right_Up() - 1 > 2)
                        {
                            if((getCoordinateY() + left_temp < _size) && (getCoordinateX() - left_temp >= 0))
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
                    if(getCoordinateX() == _size - 1);
                    else
                    {
                        int right_temp = To_Right();
                        if(right_temp + To_Left() - 1 > 2)
                        {
                            if(getCoordinateX() + right_temp < _size)
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
                        PositionFound == false && getCoordinateX() < _size - 1
                        && getCoordinateY() >= 0; 
                        setCoordinateX(getCoordinateX() + 1), setCoordinateY(PositionY()))
                    {
                        if(getCoordinateY() + 1 < _size)
                        {
                            setCoordinateY(getCoordinateY() + 1);
                            if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
                                if(Up_Down() > 1)
                                    PositionFound = true;
                            setCoordinateY(getCoordinateY() - 1);
                            // The way like '\' if i can check right down
                            if(PositionFound == false && getCoordinateX() + 1 < _size)
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
                                if(getCoordinateY() - 1 >= 0 && getCoordinateX() + 1 < _size)
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
                            if(getCoordinateX() + 1 < _size)
                            {
                                setCoordinateY(getCoordinateY() - 1);
                                setCoordinateX(getCoordinateX() + 1);
                                int right_temp = 0;
                                if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() == 2)
                                    right_temp = Right_Up();
                                setCoordinateX(getCoordinateX() - 1);
                                setCoordinateY(getCoordinateY() + 1);
                                if(getCoordinateY() + 1 < _size && getCoordinateX() - 1 >= 0)
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
                                if(getCoordinateY() + 1 < _size && getCoordinateX() + 1 < _size)
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
                        
                        if(PositionFound == false && getCoordinateX() + 1 < _size)
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
                            if(getCoordinateX() + 1 < _size)
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
                    Random random_gen = new Random();
                    temp =  random_gen.nextInt(_size);
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
                    getCoordinateX() > _size ||
                    getCoordinateX() < 0 ||
                    getCoordinateY() > _size)
                    PositionFound = false;
            ++i;
        }
        currentgameCell(getCoordinateY(),getCoordinateX()).setCell(2);
        logArea.setText(logArea.getText() + this.toString());
        switchTurn();
    }//end of playPC
    
    
    /**
     * Watches last moved position and searches vertically.
     * @return Count of Stack.
     */
    private int  Up_Down() 
    {
        int i = 1;
        boolean Legal = true;
        while(Legal == true && getCoordinateY() + i < _size && currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != -1)
        {
            if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY() + i, getCoordinateX()).getInside())
                Legal = false;
            else
                ++i;
        }
        return i;
    }//end of Up_Down

    /**
     * Watches from last moved position as Right+Down way.
     * @return Count of stack
     */
    private int  Right_Down() 
    {
        int i = 1;
        if(getCoordinateY() >= _size - 1 || getCoordinateX() >= _size - 1);
        else
        {
            boolean Legal = true;
            while(Legal == true && getCoordinateY() + i < _size && getCoordinateX() + i < _size)
            {
                if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY() + i, getCoordinateX() + i).getInside())
                    Legal = false;
                else
                    ++i;
            }
        }
        return i;
    }//end of Right_Down

    /**
     * Watches from last moved position as Right+UP way.
     * @return Count of stack
     */
    private int  Right_Up() 
    {
        int i = 1;
        if(getCoordinateY() <= 0 || getCoordinateX() >= _size - 1);
        else
        {
            boolean Legal = true;
            while(Legal == true && getCoordinateY() - i >= 0 && getCoordinateX() + i < _size)
            {
                if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY() - i, getCoordinateX() + i).getInside())
                    Legal = false;
                else
                    ++i;
            }
        }
        return i;
    }//end of Right_Up

    /**
     * Watches from last moved position as Left+Down way.
     * @return Count of stack
     */
    private int  Left_Down() 
    {
        int i = 1;
        if(getCoordinateY() >= _size - 1 || getCoordinateX() <= 0);
        else
        {
            boolean Legal = true;
            while(Legal == true && getCoordinateY() + i < _size && getCoordinateX() - i >= 0)
                {
                    if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY() + i, getCoordinateX() - i).getInside())
                        Legal = false;
                    else
                        ++i;
                }
        }
        return i;
    }//end of Left_Down

    /**
     * Watches from last moved position as Left+UP way.
     * @return Count of stack
     */
    private int  Left_Up() 
    {
        int i = 1;
        if(getCoordinateY() <= 0 || getCoordinateX() <= 0);
        else
        {
            boolean Legal = true;
            while(Legal == true && getCoordinateY() - i >= 0 && getCoordinateX() - i >= 0)
                {
                    if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY() - i, getCoordinateX() - i).getInside())
                        Legal = false;
                    else
                        ++i;
                }
        }
        return i;
    }//end of Left_Up

    /**
     * Watches from last moved position as right way.
     * @return Count of stack
     */
    private int  To_Right() 
    {
        int i = 1;
        if(getCoordinateX() > _size - 1);
        else
        {
            boolean Legal = true;
            while(Legal == true && getCoordinateX() + i < _size)
            {
                if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY(), getCoordinateX() + i).getInside())
                    Legal = false;
                else
                    ++i;
            }
        }
        return i;
    }//end of To_Right

    /**
     * Watches from last moved position as left way.
     * @return Count of stack
     */
    private int  To_Left() 
    {
        int i = 1;
        if(getCoordinateX() < 1);
        else
        {
            boolean Legal = true;
            while(Legal == true && getCoordinateX() - i >= 0)
            {
                if(currentgameCell(getCoordinateY(), getCoordinateX()).getInside() != currentgameCell(getCoordinateY(), getCoordinateX() - i).getInside())
                    Legal = false;
                else
                    ++i;
            }
        }
        return i;
    }//end of To_Left

    /**
     * Checks is there a stack that more than 3 size.
     * If so updates the cells of game.
     * @return true if somebody won.
     */
    private boolean  WinSituation()
    {
        int y = 0,
            x = 0,
            filler = 0;
        boolean win = false;
        filler = currentgameCell(getCoordinateY(), getCoordinateX()).getInside();
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
        if(win == true)
            logArea.setText("User " + (_turn ? 1 : 2) + "won\n");
            
        return win;
    }//end of WinSituation

    /**
     * Checks all top positions, if there is no empty place
     * then there is no place to move. Game finished as draw.
     * @return true if game is draw.
     */
    private boolean GameDraw() 
    {
        boolean noplace = true;
        for(int i = 0; i < _size && noplace; ++i)
            if(currentgameCell(0, i).getInside() == 0)
                noplace = false;
        if(noplace)
            logArea.setText( "Game finished as draw\n" );
            
        return noplace;
    }//end of GameDraw
}//end of class ConnectFour
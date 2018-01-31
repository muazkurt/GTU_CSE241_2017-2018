/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package driver;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

/**
 * Class drive
 * @author Muaz Kurt - 151044062
 * @version 1.0.0
 * @since 05.01.2017
 */
public class Driver {

     /**
     * Create a game object and start it with consturcter.
     */
    public static void main( String args[] )
    {
        Integer input = Integer.parseInt( JOptionPane.showInputDialog("Please give the size of board") );
        while(input < 4)
            input = Integer.parseInt( JOptionPane.showInputDialog("This is not legal \n Please give another size") );
        boolean AI = true;
        if(JOptionPane.showConfirmDialog(null, "Do you want to play with\nPWC: YES or PWP: NO", "PWP or PWC", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
            AI = false;
        ConnectFour game = new ConnectFour(input, AI); // create GAME
    } // end main
    
}

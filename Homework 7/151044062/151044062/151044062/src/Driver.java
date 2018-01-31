/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.security.InvalidParameterException;

import javafx.util.Pair;


/**
 * @author Muaz Kurt, 151044062
 * @version 1.00, 24.12.2017
 * Driver class 
 */
public class Driver
{
    /**
     * Main function of the driver class.
     * returns : void
     * @param array (String)
     */
    public static void main(String[] array)
    {
        try
        {
            GTUSet<Integer> k = new GTUSet<>(10);
            GTUSet<Integer> l = new GTUSet<>(k);
            GTUSet<Integer> m = new GTUSet<>(k.begin(), k.end());
            GTUSet<Integer> n = new GTUSet<>();
            System.out.println("k: " + k.size() + "l: " + l.size() + "m: " + m.size() + "n: " + n.size());
            System.out.println("k: " + k.max_size() + "l: " + l.max_size() + "m: " + m.max_size() + "n: " + n.max_size());

            for(int a = 0; a < 2; ++a)
                k.insert(a);
            for(int b = 0; b < 4; ++b)
                l.insert(b);
            for(int c = 0; c < 6; ++c)
                m.insert(c);
            for(int d = 0; d < 8; ++d)
                n.insert(d);
            
            System.out.println("k: " + k.size() + "l: " + l.size() + "m: " + m.size() + "n: " + n.size());
            System.out.println("k: " + k.max_size() + "l: " + l.max_size() + "m: " + m.max_size() + "n: " + n.max_size());
            
            for(int b = 2; b < 4; ++b)
                l.erase(b);
            while(m.empty())
            {
                m.clear();
                System.out.println("m, cleared.");
            }
            try
            {
                for(int d = 0; d < 8; ++d)
                    n.insert(d);
            }
            catch (InvalidParameterException e)
            {
                System.out.println("Inserted again");
            }
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
            System.out.println("k: " + k.size() + "l: " + l.size() + "m: " + m.size() + "n: " + n.size());
            System.out.println("k: " + k.max_size() + "l: " + l.max_size() + "m: " + m.max_size() + "n: " + n.max_size());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");

            System.out.println("k10: " + k.find(1).index());
            System.out.println("l10: " + l.find(1).index());
            System.out.println("m10: " + m.find(1).index());
            System.out.println("n10: " + n.find(1).index());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
            
            System.out.println("Tracking by iterator:");
            System.out.println("K:");
            for(GTUIterator<Integer> start = k.begin(); start.hasNext(); start.next())
                System.out.println("\t" + start.index());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");

            System.out.println("L:");            
            for(GTUIterator<Integer> start = l.begin(); start.hasNext(); start.next())
                System.out.println("\t" + start.index());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");

            System.out.println("M:");            
            for(GTUIterator<Integer> start = m.begin(); start.hasNext(); start.next())
                System.out.println("\t" + start.index());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");

            System.out.println("N:");            
            for(GTUIterator<Integer> start = n.begin(); start.hasNext(); start.next())
                System.out.println("\t" + start.index());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");

            System.out.println("Reverse tracking by iterator:");            
            System.out.println("K:");
            for(GTUIterator<Integer> start = k.end(); start.hasPrevious(); )
                System.out.println("\t" + start.previous());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
            
            System.out.println("L:");
            for(GTUIterator<Integer> start = l.end(); start.hasPrevious(); )
                System.out.println("\t" + start.previous());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");

            System.out.println("M:");
            for(GTUIterator<Integer> start = m.end(); start.hasPrevious(); )
                System.out.println("\t" + start.previous());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");

            System.out.println("N:");
            for(GTUIterator<Integer> start = n.end(); start.hasPrevious();)
                System.out.println("\t" + start.previous());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
   

            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
            System.out.println("k: " + k);
            System.out.println("l: " + l);
            System.out.println("m: " + m);
            System.out.println("n: " + n);
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
        }
        catch (InvalidParameterException e)
        {
            System.out.println("Try-Catch");
        }

        try
        {
            GTUMap<Integer, String> k = new GTUMap<>(10);
            GTUMap<Integer, String> l = new GTUMap<>(k);
            GTUMap<Integer, String> m = new GTUMap<>(k.begin(), k.end());
            GTUMap<Integer, String> n = new GTUMap<>();
            System.out.println("k: " + k.size() + "l: " + l.size() + "m: " + m.size() + "n: " + n.size());
            System.out.println("k: " + k.max_size() + "l: " + l.max_size() + "m: " + m.max_size() + "n: " + n.max_size());

            for(int a = 0; a < 2; ++a)
                k.insert(new Pair<>(a, "k"));
            for(int b = 0; b < 4; ++b)
                l.insert(new Pair<>(b, "l"));
            for(int c = 0; c < 6; ++c)
                m.insert(new Pair<>(c, "m"));
            for(int d = 0; d < 8; ++d)
                n.insert(new Pair<>(d, "n"));

            
            System.out.println("k: " + k.size() + "l: " + l.size() + "m: " + m.size() + "n: " + n.size());
            System.out.println("k: " + k.max_size() + "l: " + l.max_size() + "m: " + m.max_size() + "n: " + n.max_size());
            
            for(int b = 2; b < 4; ++b)
                l.erase(b);
            while(m.empty())
            {
                m.clear();
                System.out.println("m, cleared.");
            }
            try
            {
                for(int d = 0; d < 8; ++d)
                    n.insert(new Pair<>(d, "n"));
            }
            catch (InvalidParameterException e)
            {
                System.out.println("Inserted again");
            }
            
            
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
            System.out.println("k: " + k.size() + "l: " + l.size() + "m: " + m.size() + "n: " + n.size());
            System.out.println("k: " + k.max_size() + "l: " + l.max_size() + "m: " + m.max_size() + "n: " + n.max_size());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");

            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
            System.out.println("k10: " + k.find(1).index());
            System.out.println("l10: " + l.find(1).index());
            System.out.println("m10: " + m.find(1).index());
            System.out.println("n10: " + n.find(1).index());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");


            
            System.out.println("Tracking by iterator:");
            
            System.out.println("K:");            
            for(GTUIterator<Pair<Integer, String>> start = k.begin(); start.hasNext(); start.next())
                System.out.println("\t" + start.index());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
                
            System.out.println("L:");            
            for(GTUIterator<Pair<Integer, String>> start = l.begin(); start.hasNext(); start.next())
                System.out.println("\t" + start.index());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
                
            System.out.println("M:");
            for(GTUIterator<Pair<Integer, String>> start = m.begin(); start.hasNext(); start.next())
                System.out.println("\t" + start.index());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
                
            System.out.println("N:");
            for(GTUIterator<Pair<Integer, String>> start = n.begin(); start.hasNext(); start.next())
                System.out.println("\t" + start.index());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
                

            
            System.out.println("Reverse tracking by iterator:");

            System.out.println("K:");
            for(GTUIterator<Pair<Integer, String>> start = k.end(); start.hasPrevious();)
                System.out.println("\t" + start.previous());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
            
            System.out.println("L:");
            for(GTUIterator<Pair<Integer, String>> start = l.end(); start.hasPrevious();)
                System.out.println("\t" + start.previous());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");

            
            System.out.println("M:");
            for(GTUIterator<Pair<Integer, String>> start = m.end(); start.hasPrevious();)
                System.out.println("\t" + start.previous());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");


            System.out.println("N:");            
            for(GTUIterator<Pair<Integer, String>> start = n.end(); start.hasPrevious();)
                System.out.println("\t" + start.previous());
            System.out.println("~~~~~~~~~~~~~~~~~~~~~~~~~~");
            
            
            
            System.out.println("k: " + k);
            System.out.println("l: " + l);
            System.out.println("m: " + m);
            System.out.println("n: " + n);



            System.out.println("K n L : ");
            for(GTUIterator<Pair<Integer, String>> start = k.intersection(l).end(); start.hasPrevious();)
                System.out.println("\t" + start.previous());
            
            System.out.println("L n M : ");
            for(GTUIterator<Pair<Integer, String>> start = l.intersection(m).end(); start.hasPrevious();)
                System.out.println("\t" + start.previous());
            
            System.out.println("M n N : " );
            for(GTUIterator<Pair<Integer, String>> start = m.intersection(n).end(); start.hasPrevious();)
                System.out.println("\t" + start.previous());
            l.insert(new Pair<>(0, "ğ"));
            for(int i = 0; i < 4; ++i)
                System.out.println(l.at(i));
        }
        catch (InvalidParameterException e)
        {
            System.out.println("Another try-catch");
        }
    }
}
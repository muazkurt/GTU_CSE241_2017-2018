/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.security.InvalidParameterException;



/**
 * @author Muaz Kurt, 151044062
 * @version 1.00, 24.12.2017
 * GTUSetInt class 
 * @param <T> for the type of Set or Map. Could be T or Pair
 */
public interface GTUSetInt<T>
{
    /**
     * @return If the object is empty or not.
     */
    public boolean empty();
    /**
     * @return The usage count of the object. The size must be positive.
     */
    public int size();
    /**
     * @return The capacity of given object. The size must be positive.
     */
    public int max_size();
    /**
     * Checeks if there is an element as input. If there is one, throws exception.
     * @param input is a generic type.
     * @exception InvalidParameterException 
     */
    public void insert(Object input) throws InvalidParameterException;

    /**
     * Searches for all same indexes in this and other. Creates a new object with these indexes.
     * @return a new GTUSetInt
     * @param other for searching indexes.
     */
    public GTUSetInt<T> intersection(GTUSetInt<T> other);
    
    /**
     * Deletes given value and connects this hole with next objects.
     * Decreas size by 1.
     * @param input for deleting value.
     */
    public void erase(Object input);
    
    /**
     * Clears all values indexed. Creates new default 10 sized java array for use.
     */
    public void clear();

    /**
     * Searches for given input in this object. 
     * @param input for searching input.
     * @return GTUIterator.
     */
    public GTUIterator<T> find(Object input);
    
    /**
     * Searches for given input's count in this object. Input count can't be more then one.
     * @param input for searching object.
     * @return 0 or 1 is waiting. If it is more than 1 it's a problem.
     */
    public int count(Object input);

    /**
     * @return the begin of object's iterator.
     */
    public GTUIterator<T> begin();
    /**
     * @return the end of the object's iterator.
     */
    public GTUIterator<T> end();
}
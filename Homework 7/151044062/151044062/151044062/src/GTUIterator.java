/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.NoSuchElementException;
/**
 *
 * @author Muaz Kurt, 151044062
 * @param <T> is for input object type.
 * GtuIterator Class
 */
public class GTUIterator<T>
{
    private final T[] _object;
    private int _position;
    private final int _capacity;

    /**
     * Class Constructer
     * @param input Generic type java array.
     * @param position iterating position of input param.
     * @param capacity max_size of input param.
     */
    public GTUIterator(T[] input, int position, int capacity)
    {
        _position = position;
        _capacity = capacity;
        _object = input;
    }

    public T index()
    {
        return _object[_position];
    }

    /**
     * @return If there is one more item next.
     */
    public boolean hasNext()
    {
        return _position < _capacity;
    }

    /**
     * @return Next items index.
     */
    public T next() throws NoSuchElementException
    {
        if(!hasNext())
            throw new NoSuchElementException();
        ++_position;
        return index();
    }

    /**
     * @return If there is one more item previous.
     */
    public boolean hasPrevious()
    {
        return _position - 1 >= 0;
    }

    /**
     * @return Previous item index.
     */
    public T previous() throws NoSuchElementException
    {
        if(!hasPrevious())
            throw new NoSuchElementException();
        --_position;
        return index();
    }

    /**
     * @param other
     * @return If two iterators are same.
     */
    public boolean compare(GTUIterator<T> other)
    {
        return (this._object[_position] == other._object[other._position]);
    }

    /**
     * @return Items index as string.
     */
    @Override
    public String toString()
    {
        String value = "";
        value += _object[_position];
        return value;
    }
}
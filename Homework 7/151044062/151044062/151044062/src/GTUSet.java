/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.security.InvalidParameterException;

/**
 *
 * @author Muaz Kurt, 151044062
 * @param <T>
 */
public class GTUSet<T> implements GTUSetInt<T>
{
    private Object[] _set;
    private int _size;
    private int _capacity;
    public GTUSet()
    {
        _size = 0;
        _capacity = 10;
        _set = (T[]) new Object [_capacity];
    }
    
    public GTUSet(int input)
    {
        _size = 0;
        if(input > 0)
            _capacity = input;
        else
            _capacity = 10;
        _set = (T[]) new Object [_capacity];
    }

    public GTUSet(GTUSetInt<T> other)
    {
        _size = 0;
        _capacity = other.max_size();
        _set = (T[]) new Object [_capacity];
        for(GTUIterator<T> friend = other.begin(); friend.hasNext(); friend.next())
            insert(friend.index());
    }

    public GTUSet(GTUIterator<T> start, GTUIterator<T> finish)
    {
        _size = 0;
        _capacity = 10;
        _set = (T[]) new Object [_capacity];
        for(GTUIterator<T> friend = start; friend.hasNext();)
            insert(friend.next());
    }

    @Override
    public boolean empty()
    {
        return !(_size > 0);
    }
    @Override
    public int size()
    {
        return _size;
    }
    @Override
    public int max_size()
    {
        return _capacity;
    }
    @Override
    public void insert(Object input) throws InvalidParameterException
    {
        if(count(input) > 0)
            throw new InvalidParameterException();
        if(_size == _capacity - 1)
        {
            T [] temp = (T[])_set;
            _capacity *= 2;
            _set = (T[]) new Object [_capacity];
            for(int i = 0; i < _size; ++i)
                _set[i] = temp[i];
        }
        _set[_size++] = input;
    }
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other)
    {
        GTUSet<T> intersect = new GTUSet<>();
        for(GTUIterator<T> my = begin(); my.hasNext(); my.next())
            if(other.count(my.index()) == 1)
                intersect.insert(my.index());
        return intersect;
    }
    
    @Override
    public void erase(Object input)
    {
        if(count((T) input) == 1)
            for(int i = 0; i < _size; ++i)
                if(_set[i] == (T) input)
                {
                    --_size;
                    while(i < _size)
                    {
                        _set[i] = _set[i + 1];
                        ++i;
                    }
                }
    }
    
    @Override
    public void clear()
    {
        _size = 0;
        _capacity = 10;
        _set = (T[]) new Object [_capacity];
    }
    
    @Override
    public GTUIterator<T> find(Object input)
    {
        int i;
        for(i = 0; i < _size; ++i)
            if(_set[i] == (T) input)
                break;
        return new GTUIterator<>((T[])_set, i, _size);
    }
    
    @Override
    public int count(Object input)
    {
        int counter = 0;
        for(int i = 0; i < _size && counter == 0; ++i)
            if(_set[i] == (T) input)
                ++counter;
        return counter;
    }

    @Override
    public GTUIterator<T> begin()
    {
        return new GTUIterator<>((T[])_set, 0, _size);
    }

    @Override
    public GTUIterator<T> end()
    {
        return new GTUIterator<>((T[])_set, _size, _size);
    }
    @Override
    public String toString()
    {
        String value = "{\n";
        for(GTUIterator<T> search = begin(); search.hasNext(); search.next())
        {
            value += "\t";
            value += search;
            value += "\n";
        }
        value += "}";
       return value; 
    }
}
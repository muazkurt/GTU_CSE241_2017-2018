/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.security.InvalidParameterException;
import javafx.util.Pair;

/**
 *
 * @author Muaz Kurt, 151044062
 * @param <K> for the Key object type.
 * @param <V> for the Value object type.
 */
public class GTUMap<K, V> extends GTUSet<Pair<K, V>>
{
    public GTUMap()
    {
        super();
    }
    public GTUMap(int size)
    {
        super(size);
    }
    public GTUMap(GTUSetInt<Pair<K,V>> other)
    {
        super(other);
    }
    public GTUMap(GTUIterator<Pair<K, V>> start, GTUIterator<Pair<K, V>> end)
    {
        super(start, end);
    }
    
    /**
     * Takes the given key and searches it for this set. If there is no Key such
     * this input, then returns null.
     * @param k for the searching Key value.
     * @return V type object. The object is the object of given Key.
     * 
     */
    public V at(K k)
    {
        for(GTUIterator<Pair<K, V>> search = begin(); search.hasNext(); search.next())
            if(search.index().getKey() == k)
                return search.index().getValue();
        return null;
    }
    
    @Override
    public int count(Object input)
    {
        int count = 0;
        for(GTUIterator<Pair<K, V>> search = begin(); search.hasNext(); search.next())
            if(search.index().getKey().equals(((Pair<K, V>) input).getKey()))
                ++count;
        return count;
    }

    @Override
    @SuppressWarnings("empty-statement")
    public GTUIterator<Pair<K,V>> find(Object input)
    {
        GTUIterator<Pair<K, V>> search = begin();
        for(; !search.index().getKey().equals((K)input) && search.hasNext(); search.next());
        return search;
    }

    @Override
    @SuppressWarnings("empty-statement")
    public void erase(Object input)
    {
        GTUIterator<Pair<K, V>> search = begin();
        for(; !search.index().getKey().equals((K) input) && search.hasNext(); search.next());
        if(search.index().getKey().equals((K) input))
            super.erase(search.index());
    }

}
package model.adt;


import model.excep.ExecutionException;

import java.util.Map;
import java.util.Set;

public interface MyIDict<K,V> {
    void put(K k,V v) throws ExecutionException;
    public V remove(K key);
    boolean isDefined(K k);
    public Set<K> keySet();
    V lookup(K k) ;

    MyIDict<K,V> copy() throws ExecutionException;

    boolean containsKey(K id);
    public Map<K, V> getContent();
}
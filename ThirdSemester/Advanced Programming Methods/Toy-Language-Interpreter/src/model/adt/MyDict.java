package model.adt;

import model.excep.ExecutionException;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class MyDict<K, V> implements MyIDict<K, V> {
    HashMap<K,V> map;

    public MyDict() {

        map = new HashMap<>();
    }

    @Override
    public boolean containsKey(K id) {
        synchronized (this){
            return map.containsKey(id);
        }

    }

    @Override
    public Map<K, V> getContent() {

        return map;
    }

    public void put(K k, V v) throws ExecutionException {
        synchronized (this){
            map.put(k, v);}
    }



    public boolean isDefined(K k) {

        return map.get(k) != null;
    }

    public V lookup(K k) {
        synchronized (this){
            return map.get(k);
        }

    }
    public V remove(K key){
        synchronized (this){
            return map.remove(key);
        }

    }
    @Override
    public String toString() {

        return "Dictionary{" + "map=" + map + '}';
    }

    public Map<K, V> getMap() {
        synchronized (this){
            return map;
        }

    }

    public Set<K> keySet() {

        return map.keySet();
    }
    @Override
    public MyIDict<K, V> copy() throws ExecutionException{
        MyIDict<K,V> cop = new MyDict<>();
        for(K key : map.keySet()){
            cop.put(key, lookup(key));
        }
        return cop;
    }
}


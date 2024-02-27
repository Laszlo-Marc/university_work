package model.adt;


import model.excep.ExecutionException;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.function.Consumer;

public class MyList<T> implements MyIList<T> {
    private List<T> output;

    public MyList() {

        output = new LinkedList<T>();
    }

    public void add(T e) {

        output.add(e);
    }

    public void clear() {

        output.clear();
    }
    @Override
    public String toString() {
        return "List{" + "output=" + output + '}';
    }

    public List<T> getOutput() {

        return output;
    }

    public T get(int index) throws ExecutionException {
        if (index < 0 || index >= output.size())
            throw new ExecutionException("Index out of bounds!");
        try {
            return output.get(index);
        } catch (Exception exception) {
            throw new ExecutionException(exception.getMessage());
        }
    }

    public int size() {
        return output.size();
    }

    @Override
    public Iterator<T> iterator() {

        return output.iterator();
    }

    @Override
    public void forEach(Consumer<? super T> action) {
        output.forEach(action);
    }



}

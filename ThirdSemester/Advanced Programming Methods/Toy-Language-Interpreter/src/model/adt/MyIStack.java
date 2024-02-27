package model.adt;

import java.util.List;
import java.util.Stack;

public interface MyIStack<T> extends Iterable<T>{
    T pop();
    void push(T e);
    boolean isEmpty();
    List<T> getReversed();

    T peek();

    public Stack<T> getStack();
}

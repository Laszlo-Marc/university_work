package model.adt;


import java.util.*;

public class MyStack<T> implements MyIStack<T> {
    Stack<T> stack;

    public MyStack() {
        this.stack = new Stack<T>();
    }

    public T pop() {
        return this.stack.pop();
    }

    public void push(T e) {
        this.stack.push(e);
    }

    public boolean isEmpty() {
        return this.stack.isEmpty();
    }
    public T peek() {

        return stack.peek();
    }

    @Override
    public List<T> getReversed() {
        List<T> list = Arrays.asList((T[]) stack.toArray());
        Collections.reverse(list);
        return list;
    }
    @Override
    public String toString() {
        return "Stack{" + "stack=" + stack + '}';
    }

    public Stack<T> getStack() {
        return stack;
    }

    public void setStack(Stack<T> stack) {
        this.stack = stack;
    }

    @Override
    public Iterator<T> iterator() {
        return null;
    }
}

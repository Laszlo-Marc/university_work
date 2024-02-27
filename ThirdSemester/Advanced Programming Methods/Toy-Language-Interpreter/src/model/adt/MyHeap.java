package model.adt;

import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.values.IValue;

import java.util.HashMap;
import java.util.Map;

public class MyHeap implements IHeap {
    private final Map<Integer, IValue> map;
    private Integer freeValue;

    public Integer newValue() {

        this.freeValue = 1;
        while (map.containsKey(freeValue))
            freeValue = freeValue + 1;
        return freeValue;
    }

    public MyHeap(Map<Integer, IValue> map) {
        this.map = map;
        freeValue = newValue();
    }

    public MyHeap() {
        map = new HashMap<>();
        freeValue = newValue();

    }

    @Override
    public Integer getFreeValue() {

        synchronized (this) {
            return freeValue;
        }
    }

    @Override
    public Map<Integer, IValue> getContent() {
        synchronized (this) {
            return map;
        }
    }

    @Override
    public void setContent(Map<Integer, IValue> newMap) {
        synchronized (this) {
            map.clear();
            for (Integer k : newMap.keySet())
                map.put(k, newMap.get(k));
        }
    }

    @Override
    public Integer add(IValue value) {
        synchronized (this) {
            map.put(freeValue, value);
            Integer freeAddress = freeValue;
            freeValue = newValue();
            return freeAddress;
        }
    }

    @Override
    public void update(Integer position, IValue value) throws ExecutionException {
        synchronized (this) {
            if (!map.containsKey(position))
                throw new ExecutionException(position + " is not a valid position!");

            map.put(position, value);
        }
    }


    @Override
    public IValue get(Integer position) throws EvaluationException {
        synchronized (this) {
            if (!map.containsKey(position))
                throw new EvaluationException(position + " is not a valid position!");
            return map.get(position);
        }
    }
}

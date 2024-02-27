package model.adt;

import model.excep.ExecutionException;

public interface ILatchTable  extends MyIDict<Integer, Integer> {
    int put(Integer value) throws ExecutionException;
    int get(int position) throws ExecutionException;
    int getFirstFreeLocation();
}

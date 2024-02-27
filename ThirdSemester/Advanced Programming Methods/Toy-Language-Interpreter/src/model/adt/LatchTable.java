package model.adt;

import model.excep.ExecutionException;

public class LatchTable  extends MyDict<Integer, Integer> implements ILatchTable {

    private int nextFreeLocation;

    public LatchTable() {
        super();
        this.nextFreeLocation = 1;
    }

    @Override
    public void put(Integer key, Integer value)throws ExecutionException {
        super.put(key, value);
        synchronized (this) {
            nextFreeLocation++;
        }
    }

    @Override
    public int put(Integer value) throws ExecutionException {
        super.put(nextFreeLocation, value);
        synchronized (this) {
            nextFreeLocation++;
        }
        return nextFreeLocation-1;
    }

    @Override
    public int get(int position) throws ExecutionException {
        synchronized (this) {
            if (!this.getMap().containsKey(position))
                throw new ExecutionException(String.format("%d is not present in the table!", position));
            return this.map.get(position);
        }
    }

    @Override
    public int getFirstFreeLocation(){
        int locationAddress = 1;
        while (this.getMap().get(locationAddress) != null)
            locationAddress++;
        return locationAddress;
    }

}

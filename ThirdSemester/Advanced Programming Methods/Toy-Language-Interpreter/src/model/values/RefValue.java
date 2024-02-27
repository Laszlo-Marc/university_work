package model.values;

import model.types.IType;
import model.types.RefType;

public class RefValue implements IValue{
    int address;
    IType locationType;

    @Override
    public IType getType() {
        return new RefType(locationType);
    }

    public RefValue(int addr,IType locationType){
        this.address=addr;
        this.locationType=locationType;
    }

    public RefValue(){

    }

    public int getAddr(){
        return address;
    }

    public IType getLocationType(){
        return locationType;
    }

    public String toString() {
        return "ReferenceValue{"+address+" -> "+locationType+"}";
    }


}

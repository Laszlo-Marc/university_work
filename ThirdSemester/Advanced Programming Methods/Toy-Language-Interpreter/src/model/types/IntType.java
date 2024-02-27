package model.types;

import model.values.IValue;
import model.values.IntValue;

public class IntType implements IType{
    public boolean equals(Object another) {
        return another instanceof IntType;
    }

    public IntType() {
    }

    public IType getType() {
        return new IntType();
    }
    @Override
    public IValue getDefault() {
        return new IntValue(0);
    }

    public String toString() {
        return "int";
    }
}

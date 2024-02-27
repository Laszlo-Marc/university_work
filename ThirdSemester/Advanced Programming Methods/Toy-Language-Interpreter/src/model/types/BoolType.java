package model.types;

import model.values.BoolValue;
import model.values.IValue;

public class BoolType implements IType{
    public boolean equals(Object another) {
        return another instanceof BoolType;
    }

    @Override
    public IType getType() {
        return new BoolType();
    }

    @Override
    public IValue getDefault() {
        return new BoolValue(false);
    }

    public String toString() {
        return "boolean";
    }
}

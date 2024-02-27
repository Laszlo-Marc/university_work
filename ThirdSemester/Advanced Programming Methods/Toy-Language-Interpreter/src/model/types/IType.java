package model.types;

import model.values.IValue;

public interface IType {
    IType getType();
    IValue getDefault();

    public String toString();
}


package model.values;

import model.types.IType;

public interface IValue {
    IType getType();

    public String toString();
}

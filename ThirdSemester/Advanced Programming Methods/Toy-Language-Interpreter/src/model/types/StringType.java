package model.types;

import model.values.IValue;
import model.values.StringValue;

public class StringType implements IType{

    public boolean equals(Object another) {
        return another instanceof StringType;
    }

    public StringType(){

    }

    @Override
    public IType getType() {
        return new StringType();
    }

    @Override
    public IValue getDefault() {
        return new StringValue(" ");
    }

    @Override
    public String toString() {
        return "String";
    }

}

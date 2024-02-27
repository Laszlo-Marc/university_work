package model.values;

import model.types.IType;
import model.types.StringType;

public class StringValue implements IValue{
    String stringValue;
    public StringValue(String str){

        stringValue=str;
    }
    @Override
    public IType getType() {
        return new StringType();

    }

    @Override
    public boolean equals(Object obj) {
        if(obj instanceof StringValue castObj){
            return stringValue.equals(castObj.stringValue);

        }
        return false;
    }
    public String getStringValue(){

        return stringValue;
    }
    public String toString(){

        return stringValue;
    }
}

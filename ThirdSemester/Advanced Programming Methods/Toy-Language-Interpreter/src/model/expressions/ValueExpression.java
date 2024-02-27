package model.expressions;

import model.adt.IHeap;
import model.adt.MyIDict;
import model.types.IType;
import model.values.IValue;

public class ValueExpression implements IExpression{
    public IValue value;

    public ValueExpression(IValue value) {
        this.value = value;
    }

    @Override
    public String toString() {
        return value.toString();
    }

    @Override
    public IValue eval(MyIDict<String, IValue> tbl, IHeap heap) {
        return value;
    }

    public IType typeCheck(MyIDict<String, IType> typeEnv) {
        return value.getType();
    }
}

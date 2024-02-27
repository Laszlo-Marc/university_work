package model.expressions;

import model.adt.IHeap;
import model.adt.MyIDict;
import model.excep.EvaluationException;
import model.types.IType;
import model.values.IValue;

public class VarExpression implements IExpression {
    private final String var;
    public VarExpression(String var){
        this.var=var;
    }
    public String toString(){
        return var;
    }

    @Override
    public IValue eval(MyIDict<String, IValue> tbl, IHeap heap) throws EvaluationException {
        return tbl.lookup(var);
    }

    @Override
    public IType typeCheck(MyIDict<String, IType> typeEnv) throws EvaluationException {
        return typeEnv.lookup(var);
    }
}

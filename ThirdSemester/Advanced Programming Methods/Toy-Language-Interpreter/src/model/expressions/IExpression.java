package model.expressions;

import model.adt.IHeap;
import model.adt.MyIDict;
import model.excep.EvaluationException;
import model.types.IType;
import model.values.IValue;

public interface IExpression {
    IValue eval(MyIDict<String, IValue> tbl, IHeap heap) throws EvaluationException;
    IType typeCheck(MyIDict<String, IType> typeEnv) throws EvaluationException;


}

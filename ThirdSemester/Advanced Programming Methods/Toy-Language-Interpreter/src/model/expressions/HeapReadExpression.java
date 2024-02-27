package model.expressions;

import model.adt.IHeap;
import model.adt.MyIDict;
import model.excep.EvaluationException;
import model.types.IType;
import model.types.RefType;
import model.values.IValue;
import model.values.RefValue;

public class HeapReadExpression implements IExpression{
    private final IExpression expression;
    @Override
    public IValue eval(MyIDict<String, IValue> tbl, IHeap heap) throws EvaluationException {
        IValue evaluated = expression.eval(tbl,heap);
        if(!(evaluated instanceof RefValue refValue))
            throw new EvaluationException(evaluated + " is of type Ref!");
        return heap.get(refValue.getAddr());
    }

    @Override
    public IType typeCheck(MyIDict<String, IType> typeEnv) throws EvaluationException {
        IType type=expression.typeCheck(typeEnv);
        if(type instanceof RefType refType){
            return refType.getInner();
        }else
            throw new EvaluationException("The heap read argument is not of ref type!");

    }

    public HeapReadExpression(IExpression exp){
        this.expression=exp;
    }

    public String toString() {
        return "ReadHeap{"+expression+"}";
    }
}

package model.expressions;

import model.adt.IHeap;
import model.adt.MyIDict;
import model.excep.EvaluationException;
import model.types.BoolType;
import model.types.IType;
import model.values.BoolValue;
import model.values.IValue;

public class NotExpression implements IExpression{
    IExpression expression;
    public NotExpression(IExpression expression) {
        this.expression = expression;
    }

    @Override
    public IValue eval(MyIDict<String, IValue> tbl, IHeap heap) throws EvaluationException {
        IValue v1;
        v1 = expression.eval(tbl, heap);
        if (v1.getType().equals(new BoolType())) {
            BoolValue b1 = (BoolValue) v1;
            boolean firstBool = b1.getVal();
            return new BoolValue(!firstBool);
        } else
            throw new EvaluationException("First operand is not an boolean");
    }

    @Override
    public IType typeCheck(MyIDict<String, IType> typeEnv) throws EvaluationException {
        IType type1;
        type1 = expression.typeCheck(typeEnv);
        if (type1.equals(new BoolType())) {
            return new BoolType();
        }else
            throw new EvaluationException("First operand is not an boolean");
    }

    @Override
    public String toString() {
        return "!" + expression.toString();
    }
}

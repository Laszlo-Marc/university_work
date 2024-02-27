package model.expressions;

import model.adt.IHeap;
import model.adt.MyIDict;
import model.excep.EvaluationException;
import model.types.BoolType;
import model.types.IType;
import model.types.IntType;
import model.values.BoolValue;
import model.values.IValue;

public class LogicalExpression implements IExpression{
    IExpression e1;
    IExpression e2;
    String op;

    public IValue eval(MyIDict<String,IValue> tbl, IHeap heap) throws EvaluationException {
        IValue v1 = e1.eval(tbl,heap);
        IValue v2 = e2.eval(tbl,heap);
        if (!v1.getType().equals(new BoolType())) {
            throw new EvaluationException("The first operand is not an integer!");
        }
        if (!v2.getType().equals(new BoolType())) {
            throw new EvaluationException("The second operand is not an integer!");
        }
        BoolValue bool1 = (BoolValue)  v1;
        BoolValue bool2 = (BoolValue) v2;

        return switch(op){
            case "and"->new BoolValue(bool1.getVal() && bool2.getVal());
            case "or"->new BoolValue(bool1.getVal() || bool2.getVal());
            default->throw new EvaluationException("Invalid operation!");
        };

    }

    @Override
    public IType typeCheck(MyIDict<String, IType> typeEnv) throws EvaluationException {
        IType type1, type2;
        type1 = e1.typeCheck(typeEnv);
        type2 = e2.typeCheck(typeEnv);
        if (type1.equals(new BoolType())) {
            if (type2.equals(new BoolType())) {
                return new IntType();
            } else
                throw new EvaluationException("Second operand is not an int");
        } else
            throw new EvaluationException("First operand is not an integer");
    }

    public LogicalExpression(IExpression e1,IExpression e2,String op){
        this.e1 = e1;
        this.e2 = e2;
        this.op = op;
    }

    public String toString(){
        return e1.toString() +" "+op+" "+ e2.toString();
    }
}


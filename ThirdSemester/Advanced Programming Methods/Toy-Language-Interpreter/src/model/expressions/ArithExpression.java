package model.expressions;

import model.adt.IHeap;
import model.adt.MyIDict;
import model.excep.EvaluationException;
import model.types.IType;
import model.types.IntType;
import model.values.IValue;
import model.values.IntValue;

public class ArithExpression implements IExpression {
    IExpression e1;
    IExpression e2;
    char op;

    public IValue eval(MyIDict<String,IValue> tbl, IHeap heap) throws EvaluationException {
        IValue v1 = e1.eval(tbl,heap);
        IValue v2 = e2.eval(tbl,heap);
        if (!v1.getType().equals(new IntType())) {
            throw new EvaluationException("The first operand is not an integer!");
        }
        if (!v2.getType().equals(new IntType())) {
            throw new EvaluationException("The second operand is not an integer!");
        }
        IntValue int1 = (IntValue) v1;
        IntValue int2 = (IntValue) v2;

        switch(op){
            case '+':
                return new IntValue(int1.getVal()+ int2.getVal());
            case '-':
                return new IntValue(int1.getVal()- int2.getVal());
            case '*':
                return new IntValue(int1.getVal() * int2.getVal());
            case '/':
                if(int2.getVal()==0){
                    throw new EvaluationException("Division by zero!");
                }
                return new IntValue(int1.getVal() / int2.getVal());
            default:
                throw new EvaluationException("Invalid operation!");
        }

    }

    @Override
    public IType typeCheck(MyIDict<String, IType> typeEnv) throws EvaluationException {
        IType type1, type2;
        type1 = e1.typeCheck(typeEnv);
        type2 = e2.typeCheck(typeEnv);
        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new IntType();
            } else
                throw new EvaluationException("Second operand is not an integer");
        } else
            throw new EvaluationException("First operand is not an integer");
    }

    public ArithExpression(IExpression e1,IExpression e2,char op){
        this.e1 = e1;
        this.e2 = e2;
        this.op = op;
    }

    public String toString(){
        return e1.toString() + " "+ op + " "+ e2.toString();
    }
}

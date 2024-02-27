package model.expressions;

import model.adt.IHeap;
import model.adt.MyIDict;
import model.excep.EvaluationException;
import model.types.BoolType;
import model.types.IType;
import model.types.IntType;
import model.values.BoolValue;
import model.values.IValue;
import model.values.IntValue;

public class RelationalExpression implements IExpression{
    IExpression e1;
    IExpression e2;
    String op;
    public RelationalExpression(IExpression e1,IExpression e2,String op){
        this.e1=e1;
        this.e2=e2;
        this.op=op;
    }
    @Override
    public IValue eval(MyIDict<String, IValue> tbl, IHeap heap) throws EvaluationException {
        IValue value1=e1.eval(tbl,heap);
        IValue value2=e2.eval(tbl,heap);
        if(!value1.getType().equals(new IntType())){
            throw new EvaluationException("The first operand is not an integer!");

        }
        if(!value2.getType().equals(new IntType())){
            throw new EvaluationException("The second operand is not an integer!");
        }

        IntValue int1=(IntValue) value1;
        IntValue int2=(IntValue) value2;

        return switch(op){
            case "<="-> new BoolValue(int1.getVal()<=int2.getVal());
            case "<"-> new BoolValue(int1.getVal()<int2.getVal());
            case ">"-> new BoolValue(int1.getVal()>int2.getVal());
            case ">="-> new BoolValue(int1.getVal()>=int2.getVal());
            case "=="-> new BoolValue(int1.getVal()==int2.getVal());
            case "!="-> new BoolValue(int1.getVal()!=int2.getVal());
            default -> throw new EvaluationException("Invalid relational operator");
        };

    }

    @Override
    public IType typeCheck(MyIDict<String, IType> typeEnv) throws EvaluationException {
        IType type1,type2;
        type1=e1.typeCheck(typeEnv);
        type2=e2.typeCheck(typeEnv);

        if(type1.equals(new IntType())){
            if(type2.equals(new IntType())){
                return new BoolType();
            }else
                throw new EvaluationException("Second operand is not an integer!");
        }else
            throw new EvaluationException("First operand is not an integer!");
    }

    public String toString(){
        return this.e1.toString() + op+ this.e2.toString();
    }
}

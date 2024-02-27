package model.statements;

import model.adt.MyIDict;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.expressions.IExpression;
import model.types.BoolType;
import model.types.IType;
import model.values.BoolValue;
import model.values.IValue;

public class IfStmt implements IStatement{
    private final IExpression exp;
    private final IStatement thenStmt;

    private final IStatement elseStmt;

    public IfStmt(IExpression exp,IStatement thenStmt,IStatement elseStmt){
        this.exp = exp;
        this.elseStmt = elseStmt;
        this.thenStmt = thenStmt;
    }

    public PrgState execute(PrgState state) throws EvaluationException {
        IValue value = exp.eval(state.getSymTable(),state.getHeap());
        if(!value.getType().equals(new BoolType())){
            throw new EvaluationException(String.format("Condition %s is not of type bool therefor it can't be evaluated!",value));
        }
        BoolValue condition = (BoolValue) value;
        if(condition.getVal()){
            state.getExStack().push(thenStmt);
        }
        else{
            state.getExStack().push(elseStmt);

        }
        return null;
    }

    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> type) throws EvaluationException, ExecutionException {
        IType expType = exp.typeCheck(type);
        if(expType.equals(new BoolType())){
            thenStmt.typeCheck(type.copy());
            elseStmt.typeCheck(type.copy());
            return type;
        }
        else throw new EvaluationException("The condition is not of type boolean!");
    }
    public String toString() {
        return String.format("if(%s) then(%s) else(%s)", exp.toString(), thenStmt.toString(), elseStmt.toString());
    }
}

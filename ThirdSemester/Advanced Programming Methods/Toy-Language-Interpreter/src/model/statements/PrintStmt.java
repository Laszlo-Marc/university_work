package model.statements;

import model.adt.MyIDict;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.expressions.IExpression;
import model.types.IType;

public class PrintStmt implements IStatement{
    private final IExpression exp;
    public PrintStmt(IExpression exp){
        this.exp = exp;
    }

    public PrgState execute(PrgState state) throws EvaluationException {
        state.getOut().add(exp.eval(state.getSymTable(), state.getHeap()).toString());
        return null;
    }
    public MyIDict<String, IType> typeCheck(MyIDict<String,IType> type) throws EvaluationException{
        exp.typeCheck(type);
        return type;
    }

    @Override
    public String toString() {
        return String.format("print(%s)",exp.toString());
    }
}

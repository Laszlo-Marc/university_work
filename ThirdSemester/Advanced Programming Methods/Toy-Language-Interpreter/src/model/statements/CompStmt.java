package model.statements;

import model.adt.MyIDict;
import model.adt.MyIStack;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.types.IType;

public class CompStmt implements IStatement{
    IStatement first;
    IStatement second;
    public String toString(){
        return "CompStatement("+first.toString()+";"+second.toString()+")";
    }

    public CompStmt(IStatement first,IStatement second){
        this.first= first;
        this.second = second;
    }
    public PrgState execute(PrgState state){
        MyIStack<IStatement> stack = state.getExStack();
        stack.push(second);
        stack.push(first);
        return null;

    }
    public MyIDict<String, IType> typeCheck(MyIDict<String,IType> type) throws EvaluationException, ExecutionException {
        return second.typeCheck(first.typeCheck(type));
    }
}

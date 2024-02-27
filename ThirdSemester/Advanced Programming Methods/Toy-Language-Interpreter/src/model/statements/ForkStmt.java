package model.statements;

import model.adt.MyIDict;
import model.adt.MyIStack;
import model.adt.MyStack;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.types.IType;

public class ForkStmt implements IStatement{
    private final IStatement statement;
    public ForkStmt(IStatement statement){
        this.statement=statement;
    }
    @Override
    public PrgState execute(PrgState state) throws ExecutionException, EvaluationException {
        MyIStack<IStatement> newExeStack=new MyStack<>();
        newExeStack.push(statement);
        return new PrgState(newExeStack,state.getSymTable().copy(), state.getOut(), state.getFileTable(), state.getHeap(),state.getLatchTable());
    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> type) throws EvaluationException,ExecutionException {
        statement.typeCheck(type.copy());
        return type;
    }

    public String toString(){
        return "Fork{"+statement+"}\n";
    }
}

package model.statements;

import model.adt.MyIDict;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.types.IType;
import model.values.IValue;

public class VarDecStmt implements IStatement{
    String name;
    IType type;
    public VarDecStmt(String name, IType type){
        this.name= name;
        this.type = type;

    }

    public PrgState execute(PrgState state) throws EvaluationException, ExecutionException {
        MyIDict<String, IValue> symTable = state.getSymTable();
        if(symTable.containsKey(name)){
            throw new EvaluationException(String.format("Variable %s has already been defined!",name));
        }
        symTable.put(name,type.getDefault());
        return null;
    }
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> type) throws EvaluationException, ExecutionException {
        type.put(name, this.type);
        return type;
    }

    @Override
    public String toString() {
        return String.format("%s %s", type.toString(), name);
    }
}

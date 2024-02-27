package model.statements;

import model.adt.MyIDict;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.expressions.IExpression;
import model.types.IType;
import model.values.IValue;

public class AssignStmt implements IStatement {
    public String id;
    public IExpression exp;
    public AssignStmt(String id,IExpression exp){
        this.id = id;
        this.exp=exp;
    }
    public PrgState execute(PrgState state)throws ExecutionException, EvaluationException {
        MyIDict<String, IValue> symTable = state.getSymTable();
        IType type = symTable.lookup(id).getType();
        IValue value = exp.eval(symTable, state.heap);

        if (!value.getType().equals(type)) {
            throw new ExecutionException("Mismatch between variable type and assigned expression!");
        }
        if (!symTable.containsKey(id)) {
            throw new ExecutionException("Variable" + id + "was not declared in this scope!");
        }
        symTable.put(id,value);
        return null;
    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> type) throws EvaluationException {
        IType typeVar = type.lookup(id);
        IType expType = exp.typeCheck(type);
        if(typeVar.equals(expType))
            return type;
        else
            throw new EvaluationException("Assigment error: type mismatch!");

    }

    public String toString() {
        return id + "=" + exp;
    }
}

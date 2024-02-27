package model.statements;

import model.adt.IHeap;
import model.adt.MyIDict;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.expressions.IExpression;
import model.types.IType;
import model.types.RefType;
import model.values.IValue;
import model.values.RefValue;

public class HeapWriteStmt implements IStatement{
    private final String varName;
    private final IExpression exp;

    public HeapWriteStmt(String varName,IExpression exp){
        this.exp=exp;
        this.varName=varName;
    }

    @Override
    public PrgState execute(PrgState state) throws ExecutionException, EvaluationException {
        MyIDict<String, IValue> symTable=state.getSymTable();
        IHeap heap=state.getHeap();
        if(!symTable.containsKey(varName))
            throw  new EvaluationException(varName + " is not present in the sym table!");
        IValue varValue=symTable.lookup(varName);
        if(!(varValue instanceof RefValue refValue))
            throw new EvaluationException(varValue + " variable is not of ref type!");
        IValue evaluated=exp.eval(symTable,heap);
        if(!evaluated.getType().equals(refValue.getLocationType()))
            throw new EvaluationException(evaluated + " is not of type " + refValue.getLocationType());
        heap.update(refValue.getAddr(),evaluated);
        return null;
    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> type) throws EvaluationException {
        if(type.lookup(varName).equals(new RefType(exp.typeCheck(type))))
            return type;
        throw new EvaluationException("HeapWrite error: type mismatch!");
    }

    public String toString() {
        return "WriteHeap{" + varName + ", " + exp + "}";
    }
}

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

public class HeapNewStmt implements IStatement{
    private final String varName;
    private final IExpression exp;

    public HeapNewStmt(String varName,IExpression exp){
        this.varName=varName;
        this.exp=exp;
    }

    @Override
    public PrgState execute(PrgState state) throws ExecutionException, EvaluationException {
        MyIDict<String, IValue> symTable= state.getSymTable();;
        IHeap heap= state.getHeap();
        if(!symTable.containsKey(varName))
            throw new ExecutionException(varName+ " is not in he sym table!");
        IValue varValue=symTable.lookup(varName);
        if(!(varValue.getType() instanceof RefType))
            throw new EvaluationException(varName + " is not of type RefType");

        IValue evaluated = exp.eval(symTable,heap);
        IType locationType=((RefValue) varValue).getLocationType();
        if(!locationType.equals(evaluated.getType()))
            throw new EvaluationException(varName + " not of type "+evaluated.getType());
        Integer newPosition=heap.add(evaluated);
        symTable.put(varName,new RefValue(newPosition,locationType));
        return null;

    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> type) throws EvaluationException {
        IType typeVariable=type.lookup(varName);
        IType typeExp=exp.typeCheck(type);
        if(!typeVariable.equals(new RefType(typeExp)))
            throw new EvaluationException("New error: mismatch between types!");
        return type;
    }
    public String toString() {
        return "New{"+varName+", "+exp+"}";
    }
}

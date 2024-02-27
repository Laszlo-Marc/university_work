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

public class WhileStmt implements IStatement{
    private final IExpression expression;
    private final IStatement statement;

    public WhileStmt(IExpression expression, IStatement statement) {
        this.expression = expression;
        this.statement = statement;
    }

    @Override
    public PrgState execute(PrgState state) throws ExecutionException, EvaluationException {
        IValue value=expression.eval(state.getSymTable(), state.getHeap());
        if(!value.getType().equals(new BoolType()))
            throw new EvaluationException(value + " is not of type bool!");
        BoolValue boolValue=(BoolValue) value;
        if(boolValue.getVal()){
            state.getExStack().push(this);
            state.getExStack().push(statement);
        }
        return null;
    }

    @Override
    public MyIDict<String, IType> typeCheck(MyIDict<String, IType> typeEnv) throws EvaluationException,ExecutionException {
        IType type= expression.typeCheck(typeEnv);
        if(type.equals(new BoolType())){
            statement.typeCheck(typeEnv.copy());
            return typeEnv;
        }
        throw new EvaluationException("The condition of the while statement is not of bool type!");
    }

    public String toString() {
        return "While("+expression+"){\n"+statement+"}";
    }
}

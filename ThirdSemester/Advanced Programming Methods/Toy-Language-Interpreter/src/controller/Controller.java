package controller;

import model.adt.MyDict;
import model.adt.MyIDict;
import model.adt.PrgState;
import model.excep.EvaluationException;
import model.excep.ExecutionException;
import model.excep.StackException;
import model.statements.IStatement;
import model.types.IType;
import model.values.IValue;
import model.values.RefValue;
import repository.IRepository;
import repository.Repository;

import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

public class Controller {
    public IRepository repo;
    public boolean displayFlag;
    public String logFilePath;
    public ExecutorService executor;

    public Controller(String lfp,boolean displayFlag){
        this.logFilePath = lfp;
        this.repo=new Repository(logFilePath);
        this.displayFlag=displayFlag;
    }

    public Controller(IRepository r){
        logFilePath=r.getLogFilePath();
        repo=r;
        this.displayFlag=false;
    }
    public void addProgram(IStatement statement) {

        repo.add(new PrgState(statement));
    }

    public Map<Integer, IValue> unsafeGarbageCollector(Set<Integer> symTblAddr, Map<Integer,IValue> heap){
        return heap.entrySet().
                stream().
                filter(e->symTblAddr.contains(e.getKey())).
                collect(Collectors.toMap(Map.Entry::getKey,Map.Entry::getValue));
    }
    /*
    Map<Integer, IValue> safeGarbageCollector(MyIDict<String, IValue> symbols, Map<Integer, IValue> heap) {
        HashMap<Integer, IValue> newHeap = new HashMap<>();

        for (IValue val : Collections.list(symbols.elements())) {
            if (val instanceof RefValue) {
                int address = ((RefValue) val).getAddr();
                if (heap.containsKey(address)) {
                    newHeap.put(address, heap.get(address));
                }

                if (val.getType() instanceof RefType) {
                    if (heap.containsKey(address)) {
                        IValue value = heap.get(address);
                        while (value instanceof RefValue) {
                            int address2 = ((RefValue) value).getAddr();
                            if (heap.containsKey(address2)) {
                                newHeap.put(address2, heap.get(address2));
                            }
                            value = heap.get(address2);
                        }
                    }
                }
            }
        }
        return newHeap;
    }

     */
    public void runTypeChecker() throws EvaluationException, ExecutionException {
        for (PrgState state : repo.getProgramStates()) {
            MyIDict<String, IType> typeTable = new MyDict<>();
            state.getExStack().peek().typeCheck(typeTable);
        }
    }


    public void takeAStepForGUI() throws EvaluationException, ExecutionException, StackException {
        executor = Executors.newFixedThreadPool(16);
        List<PrgState> prgList = removeCompletedPrograms(repo.getProgramStates());

        // problematic if left unchecked
//        Scanner inputBestie = new Scanner(System.in);

//        int stepCount = 1;
//        String inputForStep;

        if (prgList.size() > 0) {
//            System.out.println("Step " + stepCount + ":");
//            inputForStep = inputBestie.nextLine();
//            stepCount++;
            oneStepForEachProgram(prgList);
            //remove the completed programs
            prgList = removeCompletedPrograms(repo.getProgramStates());
        }

        executor.shutdownNow();

        // HERE the repository still contains at least one Completed Prg
        // and its List<PrgState> is not empty. Note that oneStepForAllPrg calls the method
        // setPrgList of repository in order to change the repository
        //
        // update the repository state
        repo.setProgramStates(prgList);

    }
    public Set<Integer> getAddrFromSymTable(List<Collection<IValue>> symTableValues, Map<Integer,IValue> heap){
        Set<Integer> toReturn = new TreeSet<>();
        symTableValues.forEach(symTable -> symTable.stream()
                .filter(v -> v instanceof RefValue)
                .forEach(v -> {
                    while (v instanceof RefValue) {
                        toReturn.add(((RefValue) v).getAddr());
                        v = heap.get(((RefValue) v).getAddr());
                    }
                }));

        return toReturn;
    }
    public void oneStepForEachProgram(List<PrgState> programStateList) throws EvaluationException, ExecutionException {

        List<Callable<PrgState>> callList = programStateList.stream()
                .map((PrgState p) -> (Callable<PrgState>) (p::oneStep))
                .collect(Collectors.toList());


        List<PrgState> newProgramsList = null;
        try {
            newProgramsList = executor.invokeAll(callList).stream()
                    .map(future ->
                    {
                        try {
                            return future.get();
                        } catch (java.util.concurrent.ExecutionException | InterruptedException ex) {
                            System.out.println(ex.getMessage());
                        }
                        return null;
                    })
                    .filter(p->p!=null).collect(Collectors.toList());

        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
        }

        programStateList.addAll(newProgramsList);

        programStateList.forEach(prg -> {
            prg.getHeap().setContent(unsafeGarbageCollector(getAddrFromSymTable(
                            programStateList.stream().map(programState -> programState.getSymTable().getContent().values()).collect(Collectors.toList()),
                            prg.getHeap().getContent()
                    ),
                    prg.getHeap().getContent()));
        });



        programStateList.forEach(p -> {
            try {
                this.repo.logProgramStateExec(p);
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        });

        this.repo.setProgramStates(programStateList);
    }
    //public void allSteps() throws EvaluationException, ExecutionException , IOException {
    //     PrgState prg = repo.getCrtPrg();
    //     repo.logProgramStateExec(prg);
    //     while(!prg.getExStack().isEmpty()){
    //         oneStep(prg);
    //         repo.logProgramStateExec(prg);
    //         prg.getHeap().setContent(safeGarbageCollector(prg.getSymTable(), prg.getHeap().getContent()));
    //     }
    //}

    public void allSteps() throws ExecutionException, EvaluationException, StackException {

        executor = Executors.newFixedThreadPool(2);
        //remove the completed programs
        List<PrgState> prgList = removeCompletedPrograms(repo.getProgramStates());
        while (!prgList.isEmpty()) {
            oneStepForEachProgram(prgList);
            //remove the completed programs
            prgList = removeCompletedPrograms(repo.getProgramStates());

            //System.out.println(prgList.get(0).getHeap().toString());
        }

        executor.shutdownNow();
        repo.setProgramStates(prgList);
    }
    /*
        public void setDisplayFlag(boolean flag){

            this.displayFlag=flag;
        }


        public void display(){
            if(displayFlag){
                System.out.println(repo.getCrtPrg());
            }

        }


     */
    public IRepository getRepository() {

        return this.repo;
    }

    List<PrgState> removeCompletedPrograms(List<PrgState> programStateList){
        return programStateList.stream().filter(PrgState::isNotCompleted).collect(Collectors.toList());
    }


}


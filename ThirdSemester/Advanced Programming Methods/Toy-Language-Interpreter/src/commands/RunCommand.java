package commands;

import controller.Controller;
import model.statements.IStatement;

public class RunCommand extends Command{
    private final Controller controller;
    IStatement command;

    public RunCommand(IStatement s1, String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
        this.command = s1;
    }

    @Override
    public void execute() {
        try {
            controller.allSteps();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        //System.out.println("Result: " + controller.getRepository().getCrtPrg().outToString());
    }
}

import { categories } from "@/constants/categories";
import { categoryIconMap } from "@/constants/categoryIcons";
import { faker } from "@faker-js/faker";
import Expense from "./Expense";
export default class ExpenseRepository {
  private expenses: Expense[] = [];

  constructor() {
    for (let i = 0; i < 10; i++) {
      const randomCategory =
        categories[Math.floor(Math.random() * categories.length)];
      var expense = new Expense(
        i,
        randomCategory,
        faker.commerce.productName(),
        faker.number.int(1000),
        new Date(),
        faker.finance.accountName(),
        faker.company.name(),
        categoryIconMap[randomCategory]
      );

      this.expenses.push(expense);
    }
  }

  getExpenses(): Expense[] {
    return this.expenses;
  }

  addExpense(expense: Expense): Expense {
    this.expenses.push(expense);
    return expense;
  }
  updateExpense(updatedExpense: Expense): Expense | null {
    try {
      const index = this.expenses.findIndex((e) => e.id === updatedExpense.id);
      if (index === -1) throw new Error("Expense not found");
      this.expenses[index] = updatedExpense;
      return updatedExpense;
    } catch (error: any) {
      console.error("Failed to update expense:", error.message);
      return null;
    }
  }

  deleteExpense(id: number): boolean {
    try {
      const index = this.expenses.findIndex((e) => e.id === id);
      if (index === -1) throw new Error("Expense not found");
      this.expenses.splice(index, 1);
      return true;
    } catch (error: any) {
      console.error("Failed to delete expense:", error.message);
      return false;
    }
  }
}

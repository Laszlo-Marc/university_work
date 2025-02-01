import Expense from "../data/Expense";

const BASE_URL = "http://192.168.1.156:3000";

export const fetchExpenses = async (): Promise<Expense[]> => {
  const response = await fetch(`${BASE_URL}/expenses`);
  if (!response.ok) throw new Error("Failed to fetch expenses.");
  const data = await response.json();
  return data.map(
    (e: any) =>
      new Expense(
        e.id,
        e.category,
        e.description,
        e.amount,
        new Date(e.date),
        e.account,
        e.merchant,
        e.icon
      )
  );
};

export const addExpense = async (
  expense: Omit<Expense, "id">
): Promise<void> => {
  const response = await fetch(`${BASE_URL}/expenses`, {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(expense),
  });
  if (!response.ok) throw new Error("Failed to add expense.");
};

export const updateExpense = async (expense: Expense): Promise<void> => {
  const response = await fetch(`${BASE_URL}/expenses/${expense.id}`, {
    method: "PUT",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(expense),
  });
  if (!response.ok) throw new Error("Failed to update expense.");
};

export const deleteExpense = async (id: number): Promise<void> => {
  const response = await fetch(`${BASE_URL}/expenses/${id}`, {
    method: "DELETE",
  });
  if (!response.ok) throw new Error("Failed to delete expense.");
};

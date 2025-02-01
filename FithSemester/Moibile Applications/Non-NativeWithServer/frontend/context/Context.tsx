import React, {
  createContext,
  useContext,
  useEffect,
  useRef,
  useState,
} from "react";
import { toast } from "react-toastify";
import { SERVER_URL, SOCKET_URL } from "../constants/urls";
import Expense from "../data/Expense";
type RepoContextType = {
  expenses: Expense[];
  setExpenses?: React.Dispatch<React.SetStateAction<Expense[]>>;
  addExpense: (expense: Omit<Expense, "id">) => Promise<void>;
  updateExpense: (expense: Expense) => Promise<void>;
  deleteExpense: (id: number) => Promise<void>;
};

const RepoContext = createContext<RepoContextType | undefined>(undefined);

export const RepoProvider: React.FC<{ children: React.ReactNode }> = ({
  children,
}) => {
  const [expenses, setExpenses] = useState<Expense[]>([]);
  const ws = new WebSocket(SOCKET_URL);
  const hasFetched = useRef(false); // Ref to track if expenses are already fetched

  const fetchExpenses = async () => {
    if (hasFetched.current) return; // Skip if already fetched
    try {
      const response = await fetch(`${SERVER_URL}/expenses`);
      if (!response.ok) {
        throw new Error("Failed to fetch expenses.");
      }
      const data = await response.json();
      setExpenses(
        data.map(
          (e: any) =>
            new Expense(
              e.id,
              e.category,
              e.description,
              e.amount,
              new Date(e.date),
              e.transactionAccount,
              e.merchant,
              e.icon
            )
        )
      );
      hasFetched.current = true; // Mark as fetched
      console.log("[DEBUG] Expenses fetched successfully");
    } catch (error: any) {
      console.error("[ERROR] Fetch expenses:", error.message);
    }
  };
  // Fetch initial data from server
  useEffect(() => {
    fetchExpenses();
  }, []);

  // WebSocket for real-time updates
  useEffect(() => {
    ws.onmessage = (event) => {
      const message = JSON.parse(event.data);
      console.log("[DEBUG] WebSocket message:", message);
      switch (message.action) {
        case "create":
          setExpenses((prev) => [
            ...prev,
            new Expense(
              message.expense.id,
              message.expense.category,
              message.expense.description,
              message.expense.amount,
              new Date(message.expense.date),
              message.expense.transactionAccount,
              message.expense.merchant,
              message.expense.icon
            ),
          ]);
          console.log("[DEBUG] Expense created:", message.expense);
          break;
        case "update":
          setExpenses((prev) =>
            prev.map((e) =>
              e.id === message.expense.id
                ? new Expense(
                    message.expense.id,
                    message.expense.category,
                    message.expense.description,
                    message.expense.amount,
                    new Date(message.expense.date),
                    message.expense.transactionAccount,
                    message.expense.merchant,
                    message.expense.icon
                  )
                : e
            )
          );
          console.log("[DEBUG] Expense updated:", message.expense);
          break;
        case "delete":
          setExpenses((prev) => prev.filter((e) => e.id !== message.id));
          console.log("[DEBUG] Expense deleted:", message.id);
          break;
        default:
          console.warn("[WARN] Unknown WebSocket action:", message.action);
      }
    };

    ws.onerror = (error) => console.error("[ERROR] WebSocket error:", error);
    ws.onclose = () => console.log("[DEBUG] WebSocket connection closed");

    return () => ws.close();
  }, []);

  // Add an expense
  const addExpense = async (expense: Omit<Expense, "id">) => {
    try {
      const response = await fetch(`${SERVER_URL}/expenses`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(expense),
      });
      if (!response.ok) {
        throw new Error("Failed to add expense.");
      }
      console.log("[DEBUG] Expense added:", expense);
    } catch (error: any) {
      toast.error("Failed to add expense.Please try again later.");
      console.error("[ERROR] Add expense:", error.message);
    }
  };

  // Update an expense
  const updateExpense = async (expense: Expense) => {
    try {
      const response = await fetch(`${SERVER_URL}/expenses/${expense.id}`, {
        method: "PUT",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(expense),
      });
      if (!response.ok) {
        throw new Error("Failed to update expense.");
      }
      console.log("[DEBUG] Expense updated:", expense);
    } catch (error: any) {
      toast.error("Failed to update expense.Please try again later.");
      console.error("[ERROR] Update expense:", error.message);
    }
  };

  const deleteExpense = async (id: number) => {
    try {
      const response = await fetch(`${SERVER_URL}/expenses/${id}`, {
        method: "DELETE",
      });
      if (!response.ok) {
        throw new Error("Failed to delete expense.");
      }
      // Update the local state immediately after a successful deletion
      setExpenses((prev) => prev.filter((expense) => expense.id !== id));
      console.log("[DEBUG] Expense deleted locally:", id);
    } catch (error: any) {
      toast.error("Failed to delete expense. Please try again later.");
      console.error("[ERROR] Delete expense:", error.message);
    }
  };

  return (
    <RepoContext.Provider
      value={{ expenses, addExpense, updateExpense, deleteExpense }}
    >
      {children}
    </RepoContext.Provider>
  );
};

export const useRepo = (): RepoContextType => {
  const context = useContext(RepoContext);
  if (!context) {
    throw new Error("useRepo must be used within a RepoProvider");
  }
  return context;
};

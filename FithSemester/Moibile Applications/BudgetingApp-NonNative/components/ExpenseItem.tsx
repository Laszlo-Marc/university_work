import { FontAwesome6, MaterialIcons } from "@expo/vector-icons";
import React from "react";
import { Pressable, StyleSheet, Text, View } from "react-native";
import Expense from "../data/Expense";

interface ExpenseItemProps {
  expense: Expense;
  onEdit: () => void;
  onDelete: () => void;
  onPress: () => void;
}

const ExpenseItem: React.FC<ExpenseItemProps> = React.memo(
  ({ expense, onEdit, onDelete, onPress }) => {
    return (
      <Pressable
        onPress={onPress}
        style={({ pressed }) => [styles.item, pressed && styles.pressed]}
      >
        <View style={styles.left}>
          <FontAwesome6
            name={expense.icon as keyof typeof MaterialIcons.glyphMap}
            size={24}
            style={styles.categoryIcon}
          />
          <View style={styles.details}>
            <Text style={styles.category}>{expense.category}</Text>
            <Text style={styles.description}>{expense.description}</Text>
          </View>
        </View>
        <View style={styles.right}>
          <Text style={styles.amount}>${expense.amount.toFixed(2)}</Text>
          <View style={styles.actions}>
            <Pressable onPress={onEdit} style={styles.actionButton}>
              <MaterialIcons name="edit" size={20} color="#4CAF50" />
            </Pressable>
            <Pressable onPress={onDelete} style={styles.actionButton}>
              <MaterialIcons name="delete" size={20} color="#F44336" />
            </Pressable>
          </View>
        </View>
      </Pressable>
    );
  },
  (prevProps, nextProps) =>
    prevProps.expense === nextProps.expense &&
    prevProps.onEdit === nextProps.onEdit &&
    prevProps.onDelete === nextProps.onDelete &&
    prevProps.onPress === nextProps.onPress
);

export default ExpenseItem;

const styles = StyleSheet.create({
  item: {
    flexDirection: "row",
    justifyContent: "space-between",
    alignItems: "center",
    padding: 12,
    marginVertical: 6,
    backgroundColor: "#fff",
    borderRadius: 8,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.1,
    shadowRadius: 4,
    elevation: 3,
  },
  pressed: {
    opacity: 0.8,
  },
  left: {
    flexDirection: "row",
    alignItems: "center",
    flex: 1,
  },
  categoryIcon: {
    marginRight: 12,
  },
  details: {
    flex: 1,
  },
  category: {
    fontSize: 14,
    fontWeight: "600",
  },
  description: {
    fontSize: 14,
    color: "#555",
  },
  right: {
    alignItems: "flex-end",
  },
  amount: {
    fontSize: 16,
    fontWeight: "bold",
    color: "#333",
  },
  actions: {
    flexDirection: "row",
    marginTop: 4,
  },
  actionButton: {
    marginLeft: 8,
  },
});

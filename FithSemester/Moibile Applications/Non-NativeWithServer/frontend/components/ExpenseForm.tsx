import { yupResolver } from "@hookform/resolvers/yup";
import DateTimePicker from "@react-native-community/datetimepicker";
import React from "react";
import { Controller, useForm } from "react-hook-form";
import {
  KeyboardAvoidingView,
  Platform,
  ScrollView,
  Text,
  TextInput,
  TouchableOpacity,
} from "react-native";
import * as Yup from "yup";
import { theme } from "../assets/themes/form-theme";
import { useRepo } from "../context/Context";

// Validation Schema
const schema = Yup.object().shape({
  category: Yup.string().required("Category is required"),
  description: Yup.string().required("Description is required"),
  amount: Yup.number()
    .required("Amount is required")
    .positive("Amount must be positive"),
  date: Yup.date().required("Date is required"),
  transactionAccount: Yup.string().required("Transaction account is required"),
  merchant: Yup.string().required("Merchant is required"),
});

interface ExpenseFormProps {
  onSubmit: (data: any) => void;
  defaultValues: {
    category: string;
    description: string;
    amount: number;
    date: Date;
    transactionAccount: string;
    merchant: string;
  };
}

export default function ExpenseForm({
  onSubmit,
  defaultValues,
}: ExpenseFormProps) {
  const repo = useRepo();
  const handleFormSubmit = (data: {
    category: string;
    description: string;
    amount: number;
    date: Date;
    transactionAccount: string;
    merchant: string;
  }) => {
    onSubmit(data);
  };

  const {
    control,
    handleSubmit,
    formState: { errors },
  } = useForm({
    resolver: yupResolver(schema),
    defaultValues: defaultValues || {},
  });

  return (
    <KeyboardAvoidingView
      style={{ flex: 1 }}
      behavior={Platform.OS === "ios" ? "padding" : "height"}
    >
      <ScrollView contentContainerStyle={{ padding: 16 }}>
        <Controller
          control={control}
          name="category"
          render={({ field }) => (
            <>
              <Text>Category</Text>
              <TextInput
                style={theme.input}
                value={field.value}
                onChangeText={field.onChange}
              />
              {errors.category && (
                <Text style={{ color: "red" }}>{errors.category.message}</Text>
              )}
            </>
          )}
        />

        <Controller
          control={control}
          name="description"
          render={({ field }) => (
            <>
              <Text>Description</Text>
              <TextInput
                style={theme.input}
                value={field.value}
                onChangeText={field.onChange}
              />
              {errors.description && (
                <Text style={{ color: "red" }}>
                  {errors.description.message}
                </Text>
              )}
            </>
          )}
        />

        <Controller
          control={control}
          name="amount"
          render={({ field }) => (
            <>
              <Text>Amount</Text>
              <TextInput
                style={theme.input}
                keyboardType="numeric"
                value={field.value ? String(field.value) : ""}
                onChangeText={(value) =>
                  field.onChange(value ? parseFloat(value) : null)
                }
              />
              {errors.amount && (
                <Text style={{ color: "red" }}>{errors.amount.message}</Text>
              )}
            </>
          )}
        />

        <Controller
          control={control}
          name="date"
          render={({ field }) => (
            <>
              <Text>Date</Text>
              <DateTimePicker
                value={field.value || new Date()}
                mode="date"
                onChange={(event, selectedDate) => {
                  if (selectedDate) field.onChange(selectedDate);
                }}
              />
              {errors.date && (
                <Text style={{ color: "red" }}>{errors.date.message}</Text>
              )}
            </>
          )}
        />

        <Controller
          control={control}
          name="transactionAccount"
          render={({ field }) => (
            <>
              <Text>Account</Text>
              <TextInput
                style={theme.input}
                value={field.value}
                onChangeText={field.onChange}
              />
              {errors.transactionAccount && (
                <Text style={{ color: "red" }}>
                  {errors.transactionAccount?.message}
                </Text>
              )}
            </>
          )}
        />

        <Controller
          control={control}
          name="merchant"
          render={({ field }) => (
            <>
              <Text>Company</Text>
              <TextInput
                style={theme.input}
                value={field.value}
                onChangeText={field.onChange}
              />
              {errors.merchant && (
                <Text style={{ color: "red" }}>{errors.merchant?.message}</Text>
              )}
            </>
          )}
        />

        <TouchableOpacity
          style={theme.button}
          onPress={handleSubmit(handleFormSubmit)}
        >
          <Text style={{ color: "white" }}>Submit</Text>
        </TouchableOpacity>
      </ScrollView>
    </KeyboardAvoidingView>
  );
}

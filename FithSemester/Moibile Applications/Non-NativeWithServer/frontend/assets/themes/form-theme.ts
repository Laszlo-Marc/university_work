import { FlexAlignType } from "react-native";

export const theme = {
  input: {
    borderWidth: 1,
    borderColor: "#ccc",
    borderRadius: 8,
    padding: 12,
    marginVertical: 8,
    fontSize: 16,
    backgroundColor: "#f9f9f9",
  },
  button: {
    backgroundColor: "#007bff",
    padding: 12,
    borderRadius: 8,
    alignItems: "center" as FlexAlignType,
    marginTop: 16,
    shadowColor: "#000",
    shadowOffset: { width: 0, height: 4 },
    shadowOpacity: 0.1,
    shadowRadius: 6,
    elevation: 5,
  },
  label: {
    fontSize: 14,
    color: "#333",
    marginBottom: 4,
  },
  errorText: {
    color: "red",
    fontSize: 12,
    marginTop: -6,
    marginBottom: 8,
  },
};

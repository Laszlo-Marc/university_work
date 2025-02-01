const express = require("express");
const bodyParser = require("body-parser");
const cors = require("cors");
const db = require("./db");
const WebSocket = require("ws");
const winston = require("winston");

const app = express();
const PORT = 3000;

// Middleware
app.use(
  cors({
    origin: "*", // Allow all origins for testing.
  })
);
app.use(bodyParser.json());

// Logger setup
const logger = winston.createLogger({
  level: "debug",
  format: winston.format.combine(
    winston.format.timestamp(),
    winston.format.printf(({ timestamp, level, message }) => {
      return `[${timestamp}] ${level.toUpperCase()}: ${message}`;
    })
  ),
  transports: [new winston.transports.Console()],
});

// WebSocket server setup
const wss = new WebSocket.Server({ noServer: true });
const clients = new Set();

wss.on("connection", (ws) => {
  clients.add(ws);
  ws.on("close", () => clients.delete(ws));
});

// Notify WebSocket clients of updates
const broadcast = (message) => {
  clients.forEach((client) => {
    if (client.readyState === WebSocket.OPEN) {
      client.send(JSON.stringify(message));
    }
  });
};

// Root route to check if the server is running
app.get("/", (req, res) => {
  res.send("Server is running correctly!");
});

// Routes
app.get("/expenses", (req, res) => {
  db.all("SELECT * FROM expenses", [], (err, rows) => {
    if (err) {
      logger.error(`Error fetching expenses: ${err.message}`);
      res.status(500).send("Database error.");
    } else {
      logger.debug("Expenses fetched successfully.");
      res.json(rows);
    }
  });
});

app.post("/expenses", (req, res) => {
  const { category, description, amount, date, account, merchant, icon } =
    req.body;

  db.run(
    `INSERT INTO expenses (category, description, amount, date, transactionAccount, merchant, icon)
     VALUES (?, ?, ?, ?, ?, ?, ?)`,
    [category, description, amount, date, account, merchant, icon],
    function (err) {
      if (err) {
        logger.error(`Error adding expense: ${err.message}`);
        res.status(500).send("Database error.");
      } else {
        const newExpense = { id: this.lastID, ...req.body };
        logger.debug(`Expense added with ID: ${this.lastID}`);
        broadcast({ action: "create", expense: newExpense });
        res.status(201).json(newExpense);
      }
    }
  );
});

app.put("/expenses/:id", (req, res) => {
  const { id } = req.params;
  const { category, description, amount, date, account, merchant, icon } =
    req.body;

  db.run(
    `UPDATE expenses SET category = ?, description = ?, amount = ?, date = ?, transactionAccount = ?, merchant = ?, icon = ? WHERE id = ?`,
    [category, description, amount, date, account, merchant, icon, id],
    function (err) {
      if (err) {
        logger.error(`Error updating expense ID ${id}: ${err.message}`);
        res.status(500).send("Database error.");
      } else {
        logger.debug(`Expense updated with ID: ${id}`);
        broadcast({ action: "update", expense: { id, ...req.body } });
        res.sendStatus(204);
      }
    }
  );
});

app.delete("/expenses/:id", (req, res) => {
  const { id } = req.params;

  // Check if the expense exists
  db.get("SELECT * FROM expenses WHERE id = ?", [id], (err, row) => {
    if (err) {
      logger.error(`Error checking expense ID ${id}: ${err.message}`);
      return res.status(500).send("Database error.");
    }
    if (!row) {
      logger.warn(`Attempt to delete non-existent expense ID ${id}`);
      return res.status(404).send("Expense not found.");
    }

    // Proceed with deletion if exists
    db.run(`DELETE FROM expenses WHERE id = ?`, [id], function (err) {
      if (err) {
        logger.error(`Error deleting expense ID ${id}: ${err.message}`);
        res.status(500).send("Database error.");
      } else {
        logger.debug(`Expense deleted with ID: ${id}`);
        broadcast({ action: "delete", id });
        res.sendStatus(204);
      }
    });
  });
});

const initializeDB = () => {
  const categories = [
    "Shopping",
    "Food",
    "Entertainment",
    "Utilities",
    "Health",
    "Transport",
    "Other",
  ];
  const categoryIconMap = {
    Food: "bowl-food",
    Transport: "car",
    Shopping: "basket-shopping",
    Entertainment: "gamepad",
    Other: "spinner",
    Utilities: "gear",
    Health: "hospital",
  };

  for (let i = 0; i < 10; i++) {
    // Generate random data
    const randomCategory =
      categories[Math.floor(Math.random() * categories.length)];
    const description = `Item ${i + 1}`;
    const amount = Math.floor(Math.random() * 1000) + 1; // Random amount between 1 and 1000
    const date = new Date(
      Date.now() - Math.floor(Math.random() * 1e9)
    ).toISOString(); // Random date in the recent past
    const transactionAccount = `Account-${Math.floor(Math.random() * 100) + 1}`;
    const merchant = `Merchant-${Math.floor(Math.random() * 50) + 1}`;
    const icon = categoryIconMap[randomCategory];

    // Insert into database
    db.run(
      `INSERT INTO expenses (category, description, amount, date, transactionAccount, merchant, icon)
       VALUES (?, ?, ?, ?, ?, ?, ?)`,
      [
        randomCategory,
        description,
        amount,
        date,
        transactionAccount,
        merchant,
        icon,
      ],
      function (err) {
        if (err) {
          logger.error(`Error adding expense: ${err.message}`);
        } else {
          logger.debug(`Expense added with ID: ${this.lastID}`);
        }
      }
    );
  }
};

const clearDB = () => {
  db.run("DELETE FROM expenses", function (err) {
    if (err) {
      logger.error(`Error clearing database: ${err.message}`);
    } else {
      logger.debug("Database cleared.");
    }
  });
};

// Start server and WebSocket handling
const server = app.listen(PORT, "0.0.0.0", () => {
  //console.log("Clearing database...");
  //clearDB();
  //console.log("Initializing database...");
  // initializeDB();
  console.log(`Server running on http://0.0.0.0:${PORT}`);
});

server.on("upgrade", (request, socket, head) => {
  wss.handleUpgrade(request, socket, head, (ws) => {
    wss.emit("connection", ws, request);
  });
});

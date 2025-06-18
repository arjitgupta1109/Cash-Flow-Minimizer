# 💰 Cash Flow Minimizer (C++ Version)

This project implements a **Cash Flow Minimization System** in C++, aimed at optimizing financial transactions among multiple banks. It calculates net balances and minimizes the number of transactions needed to settle debts, ensuring efficient fund transfers between institutions.

---

## 🧠 Objective

Reduce interbank transaction overhead by computing net balances and matching creditors with debtors efficiently using priority queues (heaps). The final output provides a clear settlement instruction set with minimal transactions.

---

## 📌 Key Features

- Supports any number of banks and transactions.
- Calculates net credit/debit for each bank.
- Minimizes the total number of money transfers using a greedy approach.
- Displays payment instructions with randomized payment modes (SWIFT, NEFT, RTGS, IMPS).
- User-friendly prompts and error validation.

---

## 🛠️ Technologies Used

- **C++ STL**: `vector`, `priority_queue`, `string`
- Randomization: `srand()`, `rand()` for payment modes
- Command-line based interaction

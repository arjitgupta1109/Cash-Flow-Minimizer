#include<bits/stdc++.h>

using namespace std;

class BankNetwork {
private:
    int num_banks;
    vector<vector<int>> graph;
    vector<string> bank_names;

public:
    BankNetwork(int n) {
        num_banks = n;
        graph.resize(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            bank_names.push_back("Bank_" + to_string(i + 1));
        }
        srand(time(0));
    }

    void add_transaction(int debtor, int creditor, int amount) {
        graph[debtor][creditor] += amount;
    }

    vector<int> calculate_net_balances() {
        vector<int> net_balance(num_banks, 0);
        for (int i = 0; i < num_banks; ++i) {
            for (int j = 0; j < num_banks; ++j) {
                net_balance[i] += graph[j][i] - graph[i][j];
            }
        }
        return net_balance;
    }

    void minimize_transactions() {
        vector<int> net = calculate_net_balances();

        // Display initial net balances
        cout << "\nInitial Net Balances: {";
        for (int i = 0; i < num_banks; ++i) {
            cout << bank_names[i] << ": " << net[i];
            if (i < num_banks - 1) cout << ", ";
        }
        cout << "}\n\n";

        priority_queue<pair<int, int>> creditors;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> debtors;

        for (int i = 0; i < num_banks; ++i) {
            if (net[i] > 0)
                creditors.push({net[i], i});
            else if (net[i] < 0)
                debtors.push({net[i], i});
        }

        while (!debtors.empty() && !creditors.empty()) {
            auto [debt_amount, debtor] = debtors.top(); debtors.pop();
            auto [credit_amount, creditor] = creditors.top(); creditors.pop();

            int settled_amount = min(-debt_amount, credit_amount);
            int debt_remaining = debt_amount + settled_amount;
            int credit_remaining = credit_amount - settled_amount;

            cout << bank_names[debtor] << " pays " << settled_amount
                 << " to " << bank_names[creditor]
                 << " via World Bank [Payment Mode: " << get_payment_mode() << "]\n";

            if (debt_remaining < 0)
                debtors.push({debt_remaining, debtor});
            if (credit_remaining > 0)
                creditors.push({credit_remaining, creditor});
        }
    }

    string get_payment_mode() {
        vector<string> modes = {"SWIFT", "RTGS", "NEFT", "IMPS"};
        return modes[rand() % modes.size()];
    }
};

int main() {
    cout << "🏦 Welcome to the Bank Transaction Minimizer System\n";

    int n, t;
    while (true) {
        cout << "Enter the Number of Banks (no limit): ";
        cin >> n;
        if (n <= 0) {
            cout << "Number of banks must be positive.\n";
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter the Number of Transactions (no limit): ";
        cin >> t;
        if (t < 0) {
            cout << "Number of transactions cannot be negative.\n";
            continue;
        }
        break;
    }

    BankNetwork network(n);

    cout << "\nEnter each transaction in the format:\n";
    cout << "(Debtor Bank Number) (Creditor Bank Number) (Amount > 0)\n";

    for (int i = 0; i < t; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        if (a >= 0 && a < n && b >= 0 && b < n && c > 0) {
            network.add_transaction(a, b, c);
        } else {
            cout << "⚠️ Invalid transaction input. Ensure bank numbers are correct and amount > 0. Skipped.\n";
        }
    }

    network.minimize_transactions();

    return 0;
}

#include <iostream> 
#include <stack>
#include <vector>
#include <string>
#include <sstream> // for parsing commands
using namespace std;

// it's been given in the question that the block world has 0 < n < 25 
pair<int, int> find_block(vector<vector<int>>& table, int label) {
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            if (table[i][j] == label) {
                return {i, j}; 
                // match-case
            }
        }
    }
    return {-1, -1}; 
    // the case where we don't find the block, which shouldn't happen
}

void return_blocks(vector<vector<int>>& table, int a) {
    auto [ax, ay] = find_block(table, a);
    
    // loaded the block coordinates
    while (table[ax].back() != a) {
        table[table[ax].back()].push_back(table[ax].back());
        table[ax].pop_back();
    }
}

void move_onto(vector<vector<int>>& table, int a, int b) {
    auto [ax, ay] = find_block(table, a);
    auto [bx, by] = find_block(table, b); 

    // loaded the block coordinates
        
    while (table[ax].back() != a) {
        table[table[ax].back()].push_back(table[ax].back());
        table[ax].pop_back();
    }
    
    // reset the blocks on top of block 'a'
    while (table[bx].back() != b) {
        table[table[bx].back()].push_back(table[bx].back());
        table[bx].pop_back();
    }
    
    // reset the blocks on top of block 'b'
    table[bx].push_back(a);
}

void move_over(vector<vector<int>>& table, int a, int b) {
    return_blocks(table, a);
    // return blocks piled above a
    
    auto [bx, by] = find_block(table, b);
    // loaded block coordinates
    
    table[bx].push_back(a);
    // move operation
}

void pile_onto(vector<vector<int>>& table, int a, int b) {
    auto [ax, ay] = find_block(table, a);
    auto [bx, by] = find_block(table, b);
    
    return_blocks(table, b); 
    
    while (table[ax].back() != a) {
        table[bx].push_back(table[ax].back());
        // target stack: gets the elements starting from the bottom of the pile to the end of the vector, till when an element of a vector exists at the index which originally contained the bottom of the stack.
        table[ax].pop_back();
    }
    table[bx].push_back(a);
    table[ax].pop_back(); // remove 'a' from its old position
}

void pile_over(vector<vector<int>>& table, int a, int b) {
    auto [ax, ay] = find_block(table, a);
    auto [bx, by] = find_block(table, b);
    
    while (table[ax].back() != a) {
        table[bx].push_back(table[ax].back());
        // target stack: gets the elements starting from the bottom of the pile to the end of the vector, till when an element of a vector exists at the index which originally contained the bottom of the stack. But this time we don't return the blocks that are above 'b.
        table[ax].pop_back();
    }
    table[bx].push_back(a);
    table[ax].pop_back(); // remove 'a' from its old position
}

void print(vector<vector<int>>& table) {
    // Print the final state of the table
    for (int i = 0; i < table.size(); i++) {
        cout << i << " " << ":";
        if (!table[i].size()) {
            cout << " " << endl;
        } else {
            for (int block: table[i]) {
                cout << block << " ";
            }
        }
        cout << endl; 
    }
}

void parse(string s, vector<vector<int>>& table) {
    string operation, blockA, blockB;
    int a, b;
    stringstream ss(s);
    ss >> operation;
    
    if (operation == "quit") return;
    else if (operation == "move") {
        ss >> blockA >> blockB;
        a = stoi(blockA);
        b = stoi(blockB);
        if (blockA == "onto") {
            move_onto(table, a, b);
        } else if (blockA == "over") {
            move_over(table, a, b);
        }
    } else if (operation == "pile") {
        ss >> blockA >> blockB;
        a = stoi(blockA);
        b = stoi(blockB);
        if (blockA == "onto") {
            pile_onto(table, a, b);
        } else if (blockA == "over") {
            pile_over(table, a, b);
        }
    }
}

int main() {
    int n;
    cin >> n; 
    // number of blocks, arranged in a single line initially.
    
    vector<vector<int>> table(n); 
    // table arrangement represented as a vector of stacks
    
    for (int i = 0; i < n; i++) {
        table[i].push_back(i); 
        // init the block world
    }
    
    string command;
    while (cin >> ws && getline(cin, command)) {
        if (command == "quit") break;
        parse(command, table);
    }
    
    print(table); // print the final state of the blocks
    return 0;
}

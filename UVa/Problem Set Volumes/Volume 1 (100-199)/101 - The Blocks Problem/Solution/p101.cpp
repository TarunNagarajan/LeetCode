#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // Initialize n stacks, one for each block
    vector<vector<int>> world(n);
    // Track position of each block: (stack_index, height_in_stack)
    vector<pair<int, int>> positions(n);
    
    // Initially, each block is in its own stack
    for (int i = 0; i < n; i++) {
        world[i].push_back(i);
        positions[i] = {i, 0};
    }
    
    string line;
    while (getline(cin >> ws, line)) {
        stringstream ss(line);
        string cmd, preposition;
        int a, b;
        
        ss >> cmd;
        if (cmd == "quit") break;
        
        ss >> a >> preposition >> b;
        
        // Avoid invalid operations
        if (a == b || positions[a].first == positions[b].first) 
            continue;
        
        int a_stack = positions[a].first;
        int a_pos = positions[a].second;
        int b_stack = positions[b].first;
        int b_pos = positions[b].second;
        
        // Collect blocks to be moved (from a upwards)
        vector<int> blocks_to_move;
        
        if (cmd == "move") {
            // Return blocks above 'a' to their original positions
            for (int i = a_pos + 1; i < world[a_stack].size(); i++) {
                int block = world[a_stack][i];
                world[block].push_back(block);
                positions[block] = {block, world[block].size() - 1};
            }
            // Only move block 'a'
            blocks_to_move.push_back(a);
            // Resize a_stack
            world[a_stack].resize(a_pos);
        } else { // pile
            // Move all blocks from a upwards
            blocks_to_move.assign(world[a_stack].begin() + a_pos, world[a_stack].end());
            // Resize a_stack
            world[a_stack].resize(a_pos);
        }
        
        if (preposition == "onto") {
            // Return blocks above 'b' to their original positions
            for (int i = b_pos + 1; i < world[b_stack].size(); i++) {
                int block = world[b_stack][i];
                world[block].push_back(block);
                positions[block] = {block, world[block].size() - 1};
            }
            // Resize b_stack
            world[b_stack].resize(b_pos + 1);
        }
        
        // Now perform the actual move
        for (int block : blocks_to_move) {
            world[b_stack].push_back(block);
            positions[block] = {b_stack, world[b_stack].size() - 1};
        }
    }
    
    // Print the final state
    for (int i = 0; i < n; i++) {
        cout << i << ":";
        for (int block : world[i]) {
            cout << " " << block;
        }
        cout << endl;
    }
    
    return 0;
}

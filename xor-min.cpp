// xor-min.cpp
// Yifei Yin (c) 2018 Dec 15
// See the problem at https://dmoj.ca/src/1142317
//
// Licensed under GNU GPLv3. See license at https://fsf.org/
//
#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

typedef int ValType;
int NBITS = sizeof(ValType) * 8;


struct Node {
    ValType val = -1;
    bool isEnd = true;
    Node * left = nullptr;
    Node * right = nullptr;
};

//================================
inline bool GetBit(ValType val, int level) {
    return bool(val & (1 << level));
}

void AddToTrie(Node * parent, int index, ValType valueToAdd, int level = NBITS - 1) {
    if (level == -1) {
        parent->val = (parent->val == -1? index : std::min(parent->val, index));

    } else {

        if (GetBit(valueToAdd, level)) {
            if (parent->right == nullptr) {
                parent->isEnd = false;
                parent->right = new Node;
            }
            AddToTrie(parent->right, index, valueToAdd, level - 1);
        } else {
            if (parent->left == nullptr) {
                parent->isEnd = false;
                parent->left = new Node;
            }
            AddToTrie(parent->left, index, valueToAdd, level - 1);
        }

    }

}


Node * GenerateTrie(int length, int * values) {
    Node * rootNode = new Node;
    for (int i = 0; i < length; i++) {
        AddToTrie(rootNode, i, values[i]);
    }
    return rootNode;
}


void PrintNodeTree(Node * node, int level = 0, string str_rep = "") {
    if (node->isEnd) {
        cout << string(level, '.') << node->val << " " + str_rep << endl;
    } else {

        if (node->left != nullptr) {
            cout << string(level, ' ') << "0" << endl;
            PrintNodeTree(node->left, level + 1, str_rep + "0");
        } else {
            cout << string(level, ' ') << "l" << endl;
        }

        if (node->right != nullptr) {
            cout << string(level, ' ') << "1" << endl;
            PrintNodeTree(node->right, level + 1, str_rep + "1");
        } else {
            cout << string(level, ' ') << "r" << endl;
        }
    }
}


ValType FindMin(Node * parent, ValType xorNumber, int level = NBITS - 1) {
    if (level == -1) {
        return parent->val;
    }

    if (GetBit(xorNumber, level)) {
        // Perfer to the right (aka 1) first
        if (parent->right != nullptr) {
            return FindMin(parent->right, xorNumber, level - 1);
        } else if (parent->left != nullptr) {
            return FindMin(parent->left, xorNumber, level - 1);
        } else {
            return -1;
        }
    } else {
        // Perfer to the left (aka 0) first
        if (parent->left != nullptr) {
            return FindMin(parent->left, xorNumber, level - 1);
        } else if (parent->right != nullptr) {
            return FindMin(parent->right, xorNumber, level - 1);
        } else {
            return -1;
        }
    }
    int a = 1 / 0;
    return 0;
}


int main() {
    /*
    Node * root = new Node;
    for (;;) {
        ValType foo;
        cin >> foo;
        if (foo == 0) {
            break;
        }
        AddToTrie(root, foo);
        PrintNodeTree(root);
    }

    for (;;) {
        ValType bar;
        cin >> bar;
        if (bar == 0) {
            break;
        }
        cout << FindMin(root, bar) << endl;
    }

    return 0;
    */
    int sequenceSize, inputSize;
    cin >> sequenceSize;
    cin >> inputSize;

    // vector<ValType> sequence;
    int * sequence = new int [sequenceSize];

    for (int i = 0; i < sequenceSize; i++) {
        cin >> sequence[i];
    }

    Node * root = GenerateTrie(sequenceSize, sequence);

    ValType xorSoFar = 0;
    ValType value;
    string output;

    for (int i = 0; i < inputSize; i++) {
        cin >> value;
        xorSoFar ^= value;
        output += std::to_string(FindMin(root, xorSoFar)) + "\n";
    }

    cout << output;
    return 0;
}


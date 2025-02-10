#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, string code, map<char, string>& huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

void printPreorder(Node* root, map<char, string>& huffmanCode) {
    if (!root) return;
    if (root->ch != '$') {
        cout << huffmanCode[root->ch] << " ";
    }
    printPreorder(root->left, huffmanCode);
    printPreorder(root->right, huffmanCode);
}

void buildHuffmanTree(string S, vector<int> f) {
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (int i = 0; i < S.size(); i++) {
        minHeap.push(new Node(S[i], f[i]));
    }
    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        Node* newNode = new Node('$', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        minHeap.push(newNode);
    }
    Node* root = minHeap.top();
    map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);
    printPreorder(root, huffmanCode);
    cout << endl;
}

int main() {
    string S = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};
    buildHuffmanTree(S, f);
    return 0;
}

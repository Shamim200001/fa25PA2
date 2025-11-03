//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
   ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        //Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
           ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
           freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
//Using MinHeap to always get the smallest node from the heap
// will keep getting sorted by weightArr
int buildEncodingTree(int nextFree) {
    MinHeap heap;
    for (int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);

       }
//This loop will keep checking the nodes to finally reach the root
//The heap keep checking the right and left children to find the smallest node
   while (heap.size > 1) {
        int leftIdx = heap.pop(weightArr);
        int rightIdx = heap.pop(weightArr);
//The heap has to be checked
//the new internal node that been cretaed will combine the right and left children
        weightArr [nextFree] = weightArr[leftIdx] + weightArr[rightIdx];
       leftArr[nextFree] = leftIdx;
       rightArr[nextFree] = rightIdx;
        charArr[nextFree] = '\0';
//This push will add a new combination node for heap
//The new node will be checked for the heap
        heap.push(nextFree, weightArr);
        nextFree++;
  }

    // TODO:
    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)
    return heap.pop(weightArr); // placeholder
}


// Step 4: Use an STL stack to generate codes
//We are using the stack<pair<int, string>> for the DFS traversal
//Each stack will be sorted in this tree
void generateCodes(int root, string codes[]) {

    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    stack<pair<int, string>> nodeStack;
    nodeStack.push(make_pair(root, ""));


    while (!nodeStack.empty()) {
        pair<int, string> node = nodeStack.top();
        nodeStack.pop();

        int nodeIndex = node.first;
        string currentCode = node.second;

        if (charArr[nodeIndex] != '\0') {
            int charIndex = charArr[nodeIndex] - 'a';
            codes[nodeIndex] = currentCode;
        }

        if (leftArr[nodeIndex] != -1) {
            nodeStack.push(make_pair(leftArr[nodeIndex], currentCode + "0"));
        }
        if (rightArr[nodeIndex] != -1) {
            nodeStack.push(make_pair(rightArr[nodeIndex], currentCode + "1"));
        }
    }
}

// Step 5: Print table and encoded message
//This part is for the display
//This part will display the code table and convert the input text to encoded message

void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}
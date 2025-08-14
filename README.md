# Huffman-File-Compression
This project is a Command-Line Interface (CLI) based file compression tool written in C++ that implements Huffman coding. It reads an input text file, analyzes character frequencies, generates Huffman codes, and encodes the file into a compressed binary format (compression.bin). The compression is lossless, meaning the original file can be perfectly reconstructed if the Huffman tree is saved and decoding logic is implemented.
<br>
Huffman coding is a popular data compression technique used in many real-world applications (e.g., ZIP files, JPEG image compression) because it efficiently represents frequent symbols with fewer bits.
<br><br>
Features
<br><br>
Frequency Analysis: Reads the input file and counts how many times each character occurs.
<br>
Huffman Tree Construction: Uses a priority queue (min-heap) to build an optimal prefix-free code tree.
<br>
Code Generation: Assigns shorter binary codes to frequent characters and longer codes to rare characters.
<br>
Bit Packing: Groups the generated binary codes into 8-bit bytes for efficient binary file storage.
<br>
Binary Output: Saves compressed data into compression.bin in raw binary format.
<br>
Lossless Compression: Original data can be recovered exactly (if Huffman tree is preserved and decoding is implemented).
<br>
Automatic Padding: Handles cases where the bit count is not a multiple of 8 by adding zero-padding to the last byte.
<br>
Data Structure
<br><br>
struct Node {<br>
    char ch;            // Character stored in the node<br>
    int freq;           // Frequency of the character<br>
    Node *left;         // Pointer to left child<br>
    Node *right;        // Pointer to right child<br>
};
<br><br>
Core Functions
<br><br>
map<char, int> buildFrequencyTable(string filename)
<br>
Reads the input file in binary mode.
<br>
Counts the frequency of each byte value (0–255).
<br>
Returns a map where the key is a character and the value is its frequency.
<br><br>
priority_queue<Node*, vector< Node*>, Compare> buildMinHeap(map<char, int> freqTable)
<br><br>
Creates a min-heap from all characters based on frequency.
<br>
Lowest frequency nodes get highest priority.
<br><br>
Node* buildHuffmanTree(priority_queue<Node*, vector< Node*>, Compare> &pq)
<br><br>
Repeatedly extracts two lowest-frequency nodes from the min-heap.
<br>
Merges them into a new node whose frequency is the sum of the two.
<br>
Pushes the merged node back into the heap.
<br>
Continues until only one node remains — the root of the Huffman tree.
<br><br>
void generateCodes(Node* root, string code, map<char, string> &huffmanCode)
<br><br>
Recursively traverses the Huffman tree.
<br>
Assigns "0" when moving left, "1" when moving right.
<br>
Saves the resulting Huffman codes into a map.
<br><br>
string encodeFile(string filename, map<char, string> &huffmanCode)
<br><br>
Re-reads the file.
<br>
Replaces each character with its corresponding Huffman code.
<br>
Returns a long string of bits (0s and 1s).
<br><br>
void writeBinaryFile(string bitString, string outputFilename)
<br><br>
Groups the bit string into chunks of 8 bits.
<br>
Converts each chunk into an unsigned char (byte).
<br>
Writes bytes to the output file in binary mode.
<br>
Adds zero-padding if the final byte is incomplete.
<br><br>
How to Run
<br><br>
Prepare the input file<br>
Place the file you want to compress in the project directory.<br>
Example: file.txt<br>
<br>
Compile the program
<br>
g++ main.cpp -o huffman
<br>
<br>
Run the executable
<br>
./huffman
<br>
<br>
Result
<br><br>
The program will create a binary compressed file named compression.bin.
<br>
The file will not be human-readable.
<br>
Example Compression Process
<br>
Input file (file.txt):
<br>
aaaabbc
<br>
<br>
Frequency Table:
<br><br>
a: 4<br>
b: 2<br>
c: 1<br>
<br>
<br>
Generated Codes:
<br>
a → 0<br>
b → 10<br>
c → 11<br>
<br>
<br>
Encoded Bit String:
<br>
0 0 0 0 10 10 11  → 0000101011
<br>
<br>
Binary File Output:
<br>
Stored in compression.bin as packed bytes.
<br>
Concepts Implemented
<br><br>
File Handling in Binary Mode – reading/writing raw bytes.
<br>
Priority Queue (Min-Heap) – efficient retrieval of smallest frequency nodes.
<br>
Tree Data Structure – storing Huffman tree nodes.
<br>
Recursion – traversing the Huffman tree to generate codes.
<br>
Bit Manipulation – packing 0/1 strings into bytes.
<br>
Lossless Data Compression – preserving original data exactly.
<br><br>
Credits
<br><br>
Developer: Ritika Bhasin, B.Tech IT Student, IPU (Batch 2028)<br>
Library Used: (None — implemented from scratch in C++)<br>
Concepts Implemented: File handling, priority queues, recursion, binary data writing, and CLI-based workflow design.<br>

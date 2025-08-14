#include<iostream>
#include<fstream>
#include<queue>
#include<map>
using namespace std;
struct Node{
        char ch;
        int freq;
        Node* left;
        Node* right;
        Node(char c,int f){
            ch=c;
            freq=f;
            left=right=nullptr;
        }
};
struct compare{
    bool operator()(Node* a,Node* b){
        return a->freq>b->freq;
    }
};
//to fil huffmancode with codes of all frequencies number cause codes depend on frequencies
void generatecode(Node* root,string code,map<char,string>&huffmancode){
    if(!root){
        return;
    }
    if(root->ch!='\0'){
        huffmancode[root->ch]=code;
    }
    //go to left of root
    generatecode(root->left,code+"0",huffmancode);
    //go to right of root
    generatecode(root->right,code+"1",huffmancode);
}

void writetofile(string &encoded){
    ofstream file("compression.bin",ios::binary);
    unsigned char currentbyte = 0;
    int bit;
    int bytecount=0;
    for(char bitchar : encoded){
        int bit = bitchar - '0'; //converting character '1' into 1 integer //49-48
        currentbyte = (currentbyte<<1) | bit; //this shifts the bit the just converted integer at the rightmost place 
        bytecount++;
        if(bytecount==8){
            file.put(currentbyte);
            bytecount = 0;
            currentbyte = 0;
        }
    }
    if(bytecount>0){
        currentbyte <<= (8 - bytecount); //shift remaining bits to rightmost to fill the byte
        file.put(currentbyte);
    }
    file.close();
}

int main(){
    int freq[256]={0}; //256 covers all ASCII codes
    ifstream file("file.txt",ios::binary);
    if(!file.is_open()){
        cout<<"error opening file!";
        return 1;
    }
    char ch;
    while(file.get(ch)){
        freq[(unsigned char)ch]++; //unsigned char changes to ASCII, key is ascii codes of alphabets
    }
    file.close();
    //display frequencies table
    cout << "Character | ASCII Code | Frequency\n";
    cout << "-----------------------------------\n";
    for(int i=0;i<256;i++){
        if(freq[i]>0){ //accessing values which is frequency
            if(i=='\n'){
                cout<<"\\n";
            }
            else if(i=='\r'){
                cout<<"\\r";
            }
            else if(i==' '){
                cout<<"' '";
            }
            else{
                cout<<(char)i;
            }
            cout<<"     "<<i<<"      "<<freq[i]<<"\n";
        }
    }
    //create minHeap to store all contents in it in order
    priority_queue<Node*,vector<Node*>,compare> minHeap;
    for(int i=0;i<256;i++){
        if(freq[i]>0){//here freq is array or dictionary
            Node* newNode = new Node((char)i,freq[i]);
            minHeap.push(newNode);
        }
    }
    //build huffman tree 
    while(minHeap.size()>1){
        //smallest
        Node* left=minHeap.top();
        minHeap.pop();
        //second smallest
        Node* right=minHeap.top();
        minHeap.pop();
        //merged new node
        Node* merged = new Node('\0',left->freq+right->freq);
        //link childern
        merged->left=left;
        merged->right=right;
        //push merged into minHeap at last so that when all normal elements used then these merged ones would create new merged ones until only 1 is left
        minHeap.push(merged); //minHeap's node root must be the whole tree formed pointers left right to acess all the elements of the tree
        /*
        When we merge nodes into the Huffman tree, the path to each leaf is different — one will end up on the left branch (0), and the other will end up on the right branch (1).
        So even with identical frequencies, the position in the tree ensures unique codes.
        */
    }
    //now only the one root will be left
    Node* root = minHeap.top();
    cout<<"\nHuffman Tree built successfully! Root frequency = "<<root->freq<<"\n";
    map<char,string> huffmancode;
    generatecode(root,"",huffmancode); //huffmancode is some sort of map having 2 variables character and string we will be putting all the codes in this of characters
    //re read the whole file so that all the characters of the file ke code are stored in this string encoded
    ifstream file2("file.txt",ios::binary);
    if(!file2.is_open()){
        cout<<"Error opening file!";
    }
    string encoded;
    while(file2.get(ch)){
        encoded+=huffmancode[ch];
    }
    file2.close();
    /*//just for checking output
    cout << "\nEncoded bit string (first 100 bits shown):\n";
    cout << encoded.substr(0, 100) << "...\n"; // just to avoid huge output
    cout << "Total bits: " << encoded.size() << "\n";
    */
   writetofile(encoded);
    return 0;
}
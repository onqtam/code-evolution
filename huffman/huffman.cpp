#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <set>

using namespace std;

unsigned int masks[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216};

class Huffman {
private:
	
	//a struct for containing the current 2 objects with lowest values
	struct LowestSum {
		Huffman* tree[2];
		int sum[2];
		
		LowestSum() :
			tree({0, 0}),
			sum({0, 0})
		{}
		
		//checks if the probe has a sum less than one of the current lowest ones, recorded in tree[] and sum[], and replaces the bigger of the current smallest with the probe
		void check(Huffman* probe) {
			int theOne = ( sum[( sum[0] < sum[1] ? 0 : 1 )] == 0 ) ? ( sum[0] < sum[1] ? 0 : 1 ) : (probe->sum < sum[( sum[0] < sum[1] ? 1 : 0 )] ? (( sum[0] < sum[1] ? 1 : 0 )) : (-1));
			if(theOne != -1) {
				sum[theOne] = probe->sum;
				tree[theOne] = probe;
			}
		}
	};
	
	//stores the 2 children of the node (if any)
	Huffman* children [2];
	//the cost of all nodes below (used when creating tree from frequency table and not when building from encoded file)
	int sum;
	//the character (if the node is a leaf)
	char ch;
	//all the leafs (only for root node of fully constructed tree)
	map<char, Huffman*>* leafs;
	//the code (only for leaf nodes)
	string code;
	//all nodes that arent leafs have children
	bool hasChildren;
	
	//constructor
	Huffman(int _sum, char _ch, Huffman* left = 0, Huffman* right = 0) :
		children({left,right}),
		sum(_sum),
		ch(_ch),
		leafs(0), 
		code(""),
		hasChildren( left && right ? true : false )
	{}
	
public:
	
	//destructor - takes care of memory leaks
	~Huffman() {
		if(hasChildren) {
			delete children[0];
			delete children[1];
		}
		if(leafs)
			delete leafs;
	}
	
	//builds a tree for the data in buffer
	static Huffman* buildTree(char* buffer, size_t length) {
		int fTable[256];
		memset(fTable, 0, 256 * sizeof(int));
		//frequency table generation
		for(size_t i = 0; i < length; i++) fTable[((unsigned char*)buffer)[i]]++;
		//initial leaf only trees building
		set<Huffman*> trees;
		for(size_t i = 0; i < 256; i++)
			if(fTable[i])
				trees.insert(new Huffman(fTable[i], (char)i));
		//save leafs to add only to the root node in a map structure for easy browsing with a char as a key
		map<char, Huffman*>* temp = new map<char, Huffman*>();
		for(set<Huffman*>::iterator it = trees.begin(); it != trees.end(); it++)
			temp->insert(pair<char, Huffman*> ((*it)->ch, *it));
		//while more than 1 tree (not all united into 1)
		while(trees.size() > 1) {
			//find the lowest 2
			LowestSum lowest;
			for(set<Huffman*>::iterator it = trees.begin(); it != trees.end(); it++) lowest.check(*it);
			//join the lowest 2 into 1 and add the new one to the set of trees
			trees.insert(new Huffman( lowest.sum[0] + lowest.sum[1], -1, lowest.tree[0], lowest.tree[1] ));
			//remove the old lowest 2
			trees.erase(trees.find(lowest.tree[0]));
			trees.erase(trees.find(lowest.tree[1]));
		}
		//adds the leafs to the main tree - the newly generated huffman tree (only one left in trees)
		(*trees.begin())->leafs = temp;
		//makes the tree to traverse itself and fill its leaves with the codes, corresponding to their position in the tree
		(*trees.begin())->fillCodes();
		
		return *trees.begin();
	}
	
	//encodes the data in buffer with tree and writes to out the decoded data
	static void encode(ifstream& in, ofstream& out) {
		size_t length = 0;
		char* buffer = 0;
		char temp = 0;
		size_t k = 0;
		string code;
		//get whole file in memory
		in.seekg (0, ios::end);
		length = in.tellg();
		in.seekg (0, ios::beg);
		buffer = new char [length];
		in.read (buffer,length);
		//builds a tree by analyzing the buffer
		Huffman* tree = buildTree(buffer, length);
		//write the length of bytes to be encoded in beggining of encoded file
		out << length << " ";
		//write the tree for encoding/decoding of the data 
		tree->writeTree(out);
		//write a separator
		out << endl;
		//go through all bytes of the uncoded stream to encode
		for(size_t i = 0; i < length; i++) {
			//get the code of the current character from the stream
			code = (*tree->leafs)[buffer[i]]->code;
			//go through all the zeroes and ones of the code of the character
			for(size_t m = 0; m < code.size(); m++) {
				//each zero or one is written in a new bit of the 8 bits, sequentially
				temp = temp | masks[k]*((code[m] == '1' ? 1 : 0));
				//if the temp byte is full, write it to the encoded stream and reset counter from 7/8 to 0
				if(++k == 8) {
					out << temp;
					//cout << (unsigned int)temp << endl;
					temp = 0;
					k = 0;
				}
			}
		}
		//if the last written byte hasnt been filled and therefore not written, flush.
		if(k != 0) out << temp;
		delete [] buffer;
		delete tree;
	}
	
	//decodes the in stream and writes the decoded data to out using the tree.
	static void decode(ifstream& in, ofstream& out) {
		size_t length = 0;
		Huffman* tree = readTree(in, &length);
		//set node to root - traversing begins from there
		Huffman* temp = tree;
		size_t numRead = 0;
		char c[1];
		size_t k = 7;
		//while not whole data is read
		while(numRead < length) {
			//increment bit counter and if the whole byte's bits have been traversed, get new byte
			if(++k == 8) {
				k = 0;
				in.read(c, 1);
			}
			//if node has children, set node to appropriate child (depending on the bit from the byte)
			if(temp->hasChildren)
				temp = temp->children[ (c[0] & masks[k]) ? 1 : 0 ];
			else {
				//or else get data from leaf, reset node to root and decrement bit from byte counter because no downward node traversing has occured
				numRead++;
				out << temp->ch;
				k--;
				temp = tree;
			}
		}
		delete tree;
	}
	
	//reads the huffman tree from the begining of the encoded file and the ammount of bytes the data should be after decoding
	static Huffman* readTree(ifstream& in, size_t* length) {
		//get length of data after tree and step 1 byte forward (separator)
		in >> *length;
		//build recursively the tree (inly input stream needed) and then fill codes of leafs
		Huffman* tree = new Huffman(0, -1);
		tree->recBuild(in);
		tree->fillCodes();
		
		//skip the last space and newline separators
		in.get();
		in.get();
		
		return tree;
	}
	
	//builds recursively the tree using only a stream of characters
	void recBuild(ifstream& in) {
		int temp;
		in >> temp;
		//666 is the code for not a leaf and therefore has children - call recursive build on them too (if not 666 - its a leaf and we store its symbol)
		if(temp == 666) {
			hasChildren = true;
			children[0] = new Huffman(0, -1);
			children[0]->recBuild(in);
			children[1] = new Huffman(0, -1);
			children[1]->recBuild(in);
		} else ch = (char)temp;
	}
	
	//writes the tree in a cpecial format in the beginning of the encoded file, so that the encoded file is standalone
	void writeTree(ofstream& out) {
		if(hasChildren) {
			out << "666 ";
			children[0]->writeTree(out);
			children[1]->writeTree(out);
		} else out << (int)ch << " ";
	}
	
	//traverses the tree and fills the leafs with their codes from the root node
	void fillCodes(string _code = "") {
		if(hasChildren) {
			children[0]->fillCodes(_code + "0");
			children[1]->fillCodes(_code + "1");
		} else code = _code;
	}
	
	//outputs the leafs - their characters, ammount and codes
	void traverse() {
		if(hasChildren) {
			children[0]->traverse();
			children[1]->traverse();
		} else cout << ch << " " << setw(6) << sum << " " << setw(15) << code << endl;
	}
};

int main(int argc, char* argv[])
{
	if(argc != 3) {
		cout << "this.exe <input_filename> <mode>" << endl;
		cout << "where 1 for mode means encode and 2 means decode" << endl;
		return 1;
	}
	
	string filename = (argv[1]);
	
	if(atoi(argv[2]) == 1) {
		ifstream in(filename, ifstream::binary);
		ofstream out((filename + ".huff").c_str(), ofstream::binary);
		if(!in.is_open() || !out.is_open())
			return 1;
		
		Huffman::encode(in, out);
		out.close();
		in.close();
	} else {
		ifstream in((filename).c_str(), ofstream::binary);
		ofstream out((filename + ".dec").c_str(), ofstream::binary);
		if(!in.is_open() || !out.is_open())
			return 1;
		
		Huffman::decode(in, out);
		out.close();
		in.close();
	}
	return 0;
}

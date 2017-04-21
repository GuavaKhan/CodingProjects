// pktemple; Temple, Parker
#include <iostream>
#include <string.h>
#include "structures.h"
#include "handy.h"
using namespace std;
typedef unsigned char byte;
typedef unsigned int ui;
typedef TreeNode<byte> tnb;

void byteToBits(byte value, byte bits[8]){
	for(int i = 0; i < 8; i++){
		bits[i] = value % 2;
		value /= 2;
	}
}//byteToBits()

void bitsToBitsLSB(byte bits[8]){
	byte temp[8];
	for(int i = 0; i < 8; i++)
		temp[i] = bits[i];
	for(int i = 7, j = 0; i>= 0; i--, j++)
		bits[i] = temp[j];
}//bitsToBitsLSB

byte bitsToByteLSB(byte bits[8]){
	byte b = 0;
	int sum = 0;
	for(int i = 7; i >= 0; i--){
		sum <<= 1;
		sum += (int) (bits[i] - '0');
	}
	b = (byte) sum;
	return b;
}//bitsToBytesLSB

byte bitsToByte(byte bits[8]){
	int sum = 0;
	byte b = 0;
	for(int i = 0; i < 8; i++){
		sum <<= 1;
		sum += (int) (bits[i] - '0');
	}//for i
	b = (byte) sum;
	return b;
}//bitsToByte

void outputCookieFreqs(ui *asciis){
	ui x = 0;
	byte c = 0;
	cout.write("HUFFMA2\0", 8);
	for(int i = 0; i < 256; i++){
		x = asciis[i];
		for(int j = 0; j < 4; j++){
			c = (byte) (x >> (j*8));
			cout.put(c);
		}
	}//for
}//outputCookieFreqs()

void outputCode(string *code){
	//pads code at end of last byte's bits
	int mod = code->size() % 8;
	if(mod){													//if not divisible by 8, pad with zeroes
		for(int j = 0; j < 8 - mod; j++)
			*code += '0';
	}//if mod

	//print code in chars*************************************************************************
	byte *bits = new byte[8];
	byte b;
	
	for(ui i = 0; i < code->size() / 8; i++){
		for(ui j = 0; j < 8; j++){
			bits[j] = code->at(i*8 + j);
		}//for ui j
		bitsToBitsLSB(bits);
		b = bitsToByte(bits);
		cout.put(b);
	}//for ui i
	
	delete []bits;
}//outputCode()

void getCompressFreqs(unsigned int *asciis, MinHeap<tnb*> *minheap){
	//get rid of cookie
	char *s = new char[8];
	cin.read(s, 8);
	delete []s;

	//get freqs
	for(int i = 0; i < 256; i++){
		ui x = 0;
		ui t = 0;
		byte c = 0;
		for(int j = 0; j < 4; j++){
			c = (byte) cin.get();
			t = (ui) c; 
			t <<= j*8;
			x += (ui) t;
		}//for j
		asciis[i] = x;
	}//for i

	for(int i = 0; i < 256; i++){
		if(asciis[i] != 0)
			minheap->push(new tnb(NULL, NULL, (byte) i, asciis[i]));
	}//for i
}//getCompressFreqs()

void getFileFreqs(unsigned int *asciis, MinHeap<tnb*> *minheap){
	//
	char ch = 0;
	byte c = 0;
	unsigned int loc = 0;
	cin.get(ch);
	while(cin.good()){
		c = (byte) ch;
		loc = (unsigned int) c;
		asciis[loc]++;
		cin.get(ch);
	}//while
	cin.clear();
	cin.seekg(0, ios::beg);
	
	for(int i = 0; i < 256; i++){
		if(asciis[i] != 0){
			minheap->push(new tnb(NULL, NULL, (byte) i, asciis[i]));
		}//if
	}//for i
}//getFreqs

//HERE
void outputMessage(string *outputbits, MinHeap<tnb*> *minheap, HuffChar *codebook, int totalchars, int numcodes){
	string code = "";
	string temp ="";
	byte *b = new byte;
	ui count = 0;
	*b = 0;
	tnb* root = minheap->top();

	while(count < outputbits->size()){
		temp += outputbits->at(count);
		for(int i = 0; i < numcodes; i++){
			if(codebook[i].code == temp){
				cout.put((char) codebook[i].b);
				temp.clear();
			}//if codebook code == temp
		}//for i 
		count++;
	}//while

	delete b;
}//outputMessage()

void decompress(unsigned int *asciis, MinHeap<tnb*> *minheap){
	char ch = 0;
	byte *b = new byte;
	string *code = new string;
	string *outputbits = new string;
	*code = "";
	*outputbits = "";
	tnb* root;
	*b = 0;
	unsigned int *x = new unsigned int;

	//output decompressed data				//works if freqs the same
	root = minheap->top();
	cin.get(ch);
	*code = "";
	while(cin.good()){
		*b = (byte) ch;
		byte bits[8];
		byteToBits(*b, bits);
		for(int i = 0; i < 8; i++){
			bits[i] += '0';
			*code += (char) bits[i];
		}
		*outputbits += *code;
		code->clear();
		cin.get(ch);
	}//while

	//determine # of chars in msg, get rid of padding
	int n = 0;
	int c = 0;
	int total = 0;
	code->clear();
	for(int i = 0; i < 256; i++){
		if(asciis[i] != 0){
			c++;
			byte b = (byte) i;
			n += asciis[i];
			minheap->traverse(minheap->top(), b, code);
			total += (code->size() * asciis[i]);
			code->clear();
		}//if 
	}//for i
	outputbits->erase(total);			//erase padding

	//generate codebook
	int j = 0;
	HuffChar *codebook = new HuffChar[c];
	for(int i = 0; i < 256; i++){
		if(asciis[i] != 0){
			byte key = (byte) i;
			minheap->traverse(minheap->top(), key, code);
			codebook[j++] = HuffChar(key, *code);
			code->clear();
		}//if asciis[i] != 0
	}//for i

	//for(int i = 0; i < c; i++)
		//codebook[i].print();

	outputMessage(outputbits, minheap, codebook, n, c);
	
	delete []codebook;
	delete outputbits;
	delete code;
	delete b;
	delete x;
}//decompress()

void compress(unsigned int *asciis, MinHeap<tnb*> *minheap){
	char ch = 0;
	byte *b = new byte;
	string *code = new string;
	string *outputbits = new string;
	*code = "";
	*outputbits = "";
	tnb* root;
	unsigned int *x = new unsigned int;

	//output cookie and freqs
	outputCookieFreqs(asciis);			//works perfectly

	//output compressed data				//works if freqs the same
	root = minheap->top();
	cin.get(ch);
	*code = "";
	while(cin.good()){
		*b = (byte) ch;
		minheap->traverse(root, *b, code);
		*outputbits += *code;
		code->clear();
		cin.get(ch);
	}//while
	outputCode(outputbits);
	
	delete outputbits;
	delete code;
	delete b;
	delete x;
}//compress()

int main(int argc, char* argv[]){
	//variable inits
	bool decomp = 0;
	unsigned int asciis[256];
	initArray(asciis, 256, 0);
	MinHeap<tnb*> *minheap = new MinHeap<tnb*>(256);
	//test for cmd line argument
	if(argc > 1 && strpbrk(argv[1], "-d") != NULL)
		decomp = 1;
	
	//comp or decomp
	if(decomp == 1){
		getCompressFreqs(asciis, minheap);						//gets freqs correctly
		int n = minheap->heapSize;
		Huffman(minheap, n);
		decompress(asciis, minheap);
	}//if file needs to be decompressed
	else{
		getFileFreqs(asciis, minheap);		 		//minheap correctly generated
		int n = minheap->heapSize;
		Huffman(minheap, n);									//fixed
		compress(asciis, minheap);
	}//if file needs to be compressed
	
	//dealloc mem
	//delete []codebook;
	delete minheap;
	return 0;
}//main()

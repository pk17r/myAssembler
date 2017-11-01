// myAssembler.cpp : MIPS Assembly Code Generator
//
// code author: Prashant Kumar
//
// Computer Organization and Architecture Course Project 1
//
// Input: in command line call this executable along with input file name
// of the MIPS code file without its extension. Output assembly code will 
// be in the same folder with the same name and extension .obj

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

enum string_code {
	//https://stackoverflow.com/questions/650162/why-switch-statement-cannot-be-applied-on-strings
	add,
	addi,
	addiu,
	addu,
	and,
	andi,
	beq,
	bne,
	jr,
	lbu,
	lhu,
	ll,
	lui,
	lw,
	nor,
	or,
	ori,
	slt,
	slti,
	sltiu,
	sltu,
	sll,
	srl,
	sb,
	sc,
	sh,
	sw,
	sub,
	subu,
	unknown
};
string_code hashit(std::string const& inString) {
	if (inString == "add") return add;
	if (inString == "addi") return addi;
	if (inString == "addiu") return addiu;
	if (inString == "addu") return addu;
	if (inString == "and") return and;
	if (inString == "andi") return andi;
	if (inString == "beq") return beq;
	if (inString == "bne") return bne;
	if (inString == "jr") return jr;
	if (inString == "lbu") return lbu;
	if (inString == "lhu") return lhu;
	if (inString == "ll") return ll;
	if (inString == "lui") return lui;
	if (inString == "lw") return lw;
	if (inString == "nor") return nor;
	if (inString == "or") return or;
	if (inString == "ori") return ori;
	if (inString == "slt") return slt;
	if (inString == "slti") return slti;
	if (inString == "sltiu") return sltiu;
	if (inString == "sltu") return sltu;
	if (inString == "sll") return sll;
	if (inString == "srl") return srl;
	if (inString == "sb") return sb;
	if (inString == "sc") return sc;
	if (inString == "sh") return sh;
	if (inString == "sw") return sw;
	if (inString == "sub") return sub;
	if (inString == "subu") return subu;
	return unknown;
}

char opCodeType(string opcode) {
	switch (hashit(opcode))
	{
	case add: return 'R';
	case addi: return 'I';
	case addiu: return 'I';
	case addu: return 'R';
	case and: return 'R';
	case andi: return 'I';
	case beq: return 'I';
	case bne: return 'I';
	case jr: return 'R';
	case lbu: return 'I';
	case lhu: return 'I';
	case ll: return 'I';
	case lui: return 'I';
	case lw: return 'I';
	case nor: return 'R';
	case or: return 'R';
	case ori: return 'I';
	case slt: return 'R';
	case slti: return 'I';
	case sltiu: return 'I';
	case sltu: return 'R';
	case sll: return 'R';
	case srl: return 'R';
	case sb: return 'I';
	case sc: return 'I';
	case sh: return 'I';
	case sw: return 'I';
	case sub: return 'R';
	case subu: return 'R';
	default: return 'U';
	}
}

int hexToBinaryFn(string hex) {
	int binary = 0;
	for (int i = 0; i < hex.size(); i++) {
		char hexDigit = hex[i];
		int num;
		switch (tolower(hexDigit))
		{
		case '0': num = 0; break;
		case '1': num = 1; break;
		case '2': num = 10; break;
		case '3': num = 11; break;
		case '4': num = 100; break;
		case '5': num = 101; break;
		case '6': num = 110; break;
		case '7': num = 111; break;
		case '8': num = 1000; break;
		case '9': num = 1001; break;
		case 'a': num = 1010; break;
		case 'b': num = 1011; break;
		case 'c': num = 1100; break;
		case 'd': num = 1101; break;
		case 'e': num = 1110; break;
		case 'f': num = 1111; break;
		default: num = 0;
		}
		binary += num * pow(10000, hex.size() - 1 - i);
	}
	return binary;
}

string binaryToHexChart(int binary) {
	string num = "";
	switch (binary)
	{
	case 0: num = "0"; break;
	case 1: num = "1"; break;
	case 10: num = "2"; break;
	case 11: num = "3"; break;
	case 100: num = "4"; break;
	case 101: num = "5"; break;
	case 110: num = "6"; break;
	case 111: num = "7"; break;
	case 1000: num = "8"; break;
	case 1001: num = "9"; break;
	case 1010: num = "a"; break;
	case 1011: num = "b"; break;
	case 1100: num = "c"; break;
	case 1101: num = "d"; break;
	case 1110: num = "e"; break;
	case 1111: num = "f"; break;
	default: num = "-";
	}
	return num;
}

string binaryToHexFn(double binary) {
	string hex = "";
	double quotient = floor(binary / 10000);
	int remainder = binary - quotient * 10000;
	do {
		hex = binaryToHexChart(remainder) + hex;
		double binaryNew = quotient;
		quotient = floor(binaryNew / 10000);
		remainder = binaryNew - quotient * 10000;
	} while (quotient != 0);
	hex = binaryToHexChart(remainder) + hex;
	if (hex.size() == 1)
		hex = "000" + hex;
	else if (hex.size() == 2)
		hex = "00" + hex;
	else if (hex.size() == 3)
		hex = "0" + hex;
	return hex;
}

double decimalToBinaryFn(int decimal) {
	vector<int> num = {};
	int quotient = floor(decimal / 2);
	int remainder = decimal - quotient * 2;
	num.push_back(remainder);
	while (quotient > 0)
	{
		int decimalNew = quotient;
		quotient = floor(decimalNew / 2);
		remainder = decimalNew - quotient * 2;
		num.push_back(remainder);
	}
	double binary = 0;
	for (int i = 0; i < num.size(); i++)
	{
		binary += num[i] * pow(10, i);
	}
	return binary;
}

int registerToBinaryFn(string reg) {
	if (reg.size() == 0)
		return 0;
	if (reg[0] == '0')
		return 0;
	int num = reg[2] - 48;
	switch (reg[1])
	{
	case '0':
		return 0;
	case 'z':
		if(reg[2] == 'e' && reg[2] == 'r' && reg[2] == 'o')
			return 0;
		else
			throw new exception();
	case 'v':
		if (num >= 0 && num <= 1)
			return decimalToBinaryFn(num + 2);
		else
			throw new exception();
	case 'a':
		if (reg[2] == 't')
			return decimalToBinaryFn(1);
		else if (num >= 0 && num <= 3)
			return decimalToBinaryFn(num + 4);
		else
			throw new exception();
	case 't':
		if (num >= 0 && num <= 7)
			return decimalToBinaryFn(num + 8);
		else if (num >= 8 && num <= 9)
			return decimalToBinaryFn(num + 16);
		else
			throw new exception();
	case 's':
		if (reg[2] == 'p')
			return decimalToBinaryFn(29);
		else if (num >= 0 && num <= 7)
			return decimalToBinaryFn(num + 16);
		else
			throw new exception();
	case 'k':
		if (num >= 0 && num <= 1)
			return decimalToBinaryFn(num + 26);
		else
			throw new exception();
	case 'g':
		if (reg[2] == 'p')
			return decimalToBinaryFn(28);
		else
			throw new exception();
	case 'f':
		if (reg[2] == 'p')
			return decimalToBinaryFn(30);
		else
			throw new exception();
	case 'r':
		if (reg[2] == 'a')
			return decimalToBinaryFn(31);
		else
			throw new exception();
	default:
		break;
	}
}

int rTypeFunctVal(string opcode) {
	switch (hashit(opcode))
	{
	case add: return hexToBinaryFn("20");
	case addu: return hexToBinaryFn("21");
	case and: return hexToBinaryFn("24");
	case jr: return hexToBinaryFn("08");
	case nor: return hexToBinaryFn("27");
	case or : return hexToBinaryFn("25");
	case slt: return hexToBinaryFn("2a");
	case sltu: return hexToBinaryFn("2b");
	case sll: return hexToBinaryFn("00");
	case srl: return hexToBinaryFn("02");
	case sub: return hexToBinaryFn("22");
	case subu: return hexToBinaryFn("23");
	default: return 'U';
	}
}

int iTypeOpcodeBinaryVal(string opcode) {
	switch (hashit(opcode))
	{
	case addi: return hexToBinaryFn("8");
	case addiu: return hexToBinaryFn("9");
	case andi: return hexToBinaryFn("c");
	case beq: return hexToBinaryFn("4");
	case bne: return hexToBinaryFn("5");
	case lbu: return hexToBinaryFn("24");
	case lhu: return hexToBinaryFn("25");
	case ll: return hexToBinaryFn("30");
	case lui: return hexToBinaryFn("f");
	case lw: return hexToBinaryFn("23");
	case ori: return hexToBinaryFn("d");
	case slti: return hexToBinaryFn("a");
	case sltiu: return hexToBinaryFn("b");
	case sb: return hexToBinaryFn("28");
	case sc: return hexToBinaryFn("38");
	case sh: return hexToBinaryFn("29");
	case sw: return hexToBinaryFn("2b");
	default: return 'U';
	}
}

string handleRtype(string opcode, string rs, string rt, string rd, string shamt, string funct) {
	int opcodeBinary = 0;
	int rsBinary = registerToBinaryFn(rs);
	int rtBinary = registerToBinaryFn(rt);
	int rdBinary = registerToBinaryFn(rd);
	int shamtBinary = decimalToBinaryFn(stoi(shamt));
	int functBinary = rTypeFunctVal(opcode);
	double numLeft = opcodeBinary * pow(10, 10) + rsBinary * pow(10, 5) + rtBinary;
	double numRight = rdBinary * pow(10, 11) + shamtBinary * pow(10, 6) + functBinary;
	string hexCode = binaryToHexFn(numLeft) + binaryToHexFn(numRight);
	return hexCode;
}

string handleItype(string opcode, string rs, string rt, string immediate) {
	int opcodeBinary = iTypeOpcodeBinaryVal(opcode);
	int rsBinary = registerToBinaryFn(rs);
	int rtBinary = registerToBinaryFn(rt);
	double immediateBinary;
	bool negativeImmediate = false;
	if (immediate.size() > 2) {
		string immediateLeft = immediate.substr(0, immediate.size() - 2);
		string immediateRight = immediate.substr(immediate.size() - 2, 2);
		int right = stoi(immediateRight);
		int fullNumber;
		if (immediateLeft.size() == 1 && immediateLeft[0] == '-') {
			negativeImmediate = true;
			fullNumber = right;
		}
		else {
			int left = stoi(immediateLeft);
			if (left < 0) {
				negativeImmediate = true;
				fullNumber = abs(left) * pow(10, 2) + right;
			}
			else {
				fullNumber = left * pow(10, 2) + right;
			}
		}
		immediateBinary = decimalToBinaryFn(fullNumber);
	}
	else {
		int num = stoi(immediate);
		if (num < 0)
			negativeImmediate = true;
		immediateBinary = decimalToBinaryFn(abs(num));
	}
	//handle negative immediates (beq bne relative address labels)
	if (negativeImmediate) {
		//compute one's complement
		string immediateBinaryDoubleStr = to_string(immediateBinary);
		string immediateBinaryStr = "";
		for (int i = 0; i < immediateBinaryDoubleStr.size(); i++) {
			if (immediateBinaryDoubleStr[i] != '.') {
				immediateBinaryStr += immediateBinaryDoubleStr[i];
			}
			else
				break;
		}
		string onesComplement = "";
		string twosComplement = "";
		for (int i = 0; i < immediateBinaryStr.size(); i++) {
			if (immediateBinaryStr[i] == '0')
				onesComplement += '1';
			else
				onesComplement += '0';
		}
		while (onesComplement.size() < 16) {
			onesComplement = '1' + onesComplement;
		}
		//add one
		bool foundZero = false;
		int index = onesComplement.size() - 1;
		while (!foundZero) {
			if (onesComplement[index] == '0') {
				foundZero = true;
				twosComplement = '1' + twosComplement;
				for (int i = index-1; i >= 0; i--) {
					twosComplement = onesComplement[i] + twosComplement;
				}
			}
			else {	//it is 1
				twosComplement = '0' + twosComplement;
				index--;
				if (index < 0) {
					throw new exception();
					break;
				}
			}
		}
		double immediateBinaryNew = 0;
		for (int i = twosComplement.size() - 1; i >= 0; i--) {
			if (twosComplement[i] == '1')
				immediateBinaryNew += pow(10, twosComplement.size() - 1 - i);
		}
		immediateBinary = immediateBinaryNew;
	}

	double numLeft = opcodeBinary * pow(10, 10) + rsBinary * pow(10, 5) + rtBinary;
	double numRight = immediateBinary;
	string hexCode = binaryToHexFn(numLeft) + binaryToHexFn(numRight);
	return hexCode;
}

int main(int argc, char *argv[]) {
	//input MIPS file name
	string filename = argv[1];
	//cin >> filename;
	
	//open file 'filename.s'
	ifstream inFile;

	inFile.open(filename + ".s");
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	//read every line in a while loop
	int lineNumber = 0;
	string mipsLine;
	vector<vector<string>> mipsLineVectors = {};
	vector<string> assemblyLines = {};
	vector<string> labels = {};
	vector<int> labelLineNumber = {};
	try {
		while (inFile) {
			getline(inFile, mipsLine);
			if (mipsLine == "")
				continue;
			vector<string> mipsInstruction = {};
			//for every line separate out words in an string vector by removing the blanks and commas and ()
			string word = "";
			bool reverseImmidiateType = false;
			for (int i = 0; i < mipsLine.length(); i++) {
				if (mipsLine[i] == ')')
					reverseImmidiateType = true;
				if (mipsLine[i] != ' ' && mipsLine[i] != ',' && mipsLine[i] != '(' && mipsLine[i] != ')' && mipsLine[i] != '\t') {
					word += mipsLine[i];
				}
				else {
					if (word != "") {
						if (!reverseImmidiateType) {
							mipsInstruction.push_back(word);
						}
						else {
							string oldWord = mipsInstruction[mipsInstruction.size() - 1];
							mipsInstruction.push_back(oldWord);
							mipsInstruction[mipsInstruction.size() - 2] = word;
							reverseImmidiateType = false;
						}
						word = "";
					}
				}
			}
			if (word != "") {
				mipsInstruction.push_back(word);
				word = "";
			}

			//if line has only one word and last letter of this word is ':' then it is a label
			if (mipsInstruction.size() == 1) {
				word = mipsInstruction[0];
				if (word[word.length() - 1] == ':') {
					//label
					string lbl = word.substr(0, word.size() - 1);
					labels.push_back(lbl);
					labelLineNumber.push_back(lineNumber);
					continue;
				}
				else {
					throw new exception();
				}
			}
			else {
				mipsInstruction.push_back(mipsLine);
				mipsLineVectors.push_back(mipsInstruction);
				lineNumber++;
			}
		}
		//finishing the reading process earlier so as to know label address positions

		//now actually writing assembly code
		for (int j = 0; j < mipsLineVectors.size(); j++) {
			vector<string> mipsInstruction = mipsLineVectors[j];
			lineNumber = j;
			mipsLine = mipsInstruction[4];

			string assemblyCode = "";
			//line is an instruction with first word being the opcode
			string opcode = mipsInstruction[0];

			// refer to chart to find out if it is an R type or I type statement
			char insType = opCodeType(opcode);

			// based on type, assign the words as rs rt and rd or rs rt and immidiate
			string rs = "";
			string rt = "";
			string rd = "";
			string shamt = "0";
			string funct = "";
			string immediate = "0";

			// handle instruction based on the type
			switch (insType) {
			case 'R':
				if (opcode != "sll" && opcode != "srl") {
					rd = mipsInstruction[1];
					rs = mipsInstruction[2];
					rt = mipsInstruction[3];
				}
				else {
					rd = mipsInstruction[1];
					rt = mipsInstruction[2];
					shamt = mipsInstruction[3];
				}
				break;
			case 'I':
				if (opcode != "beq" && opcode != "bne") {
					rt = mipsInstruction[1];
					rs = mipsInstruction[2];
					immediate = mipsInstruction[3];
				}
				else {	//handle beq, bne and branching
					//https://www.cs.umd.edu/class/sum2003/cmsc311/Notes/Mips/jump.html
					rs = mipsInstruction[1];
					rt = mipsInstruction[2];
					immediate = mipsInstruction[3];
					for (int i = 0; i < labels.size(); i++)
					{
						if (immediate.compare(labels[i]) == 0) {
							int currentLineNum = j;
							int labelLineNum = labelLineNumber[i];
							int relativeAddr = labelLineNum - (currentLineNum + 1);
							immediate = to_string(relativeAddr);	//handle negative sign later
							break;
						}
					}
				}
			break;
			default:
				break;
			}

			//print out the assembly code for the instruction
			switch (insType) {
			case 'R':
				//assemblyCode = "R " + opcode + " rd=" + rd + " rt=" + rt + " rs=" + rs + " shamt=" + shamt;
				assemblyCode = handleRtype(opcode, rs, rt, rd, shamt, funct);
				break;
			case 'I':
				//assemblyCode = "I " + opcode + " rt=" + rt + " rs=" + rs + " immi=" + immediate;
				assemblyCode = handleItype(opcode, rs, rt, immediate);
				break;
			default:
				assemblyCode = "unknown " + opcode;
				break;
			}
			//goto next line
			assemblyLines.push_back(assemblyCode);
		}
	}
	catch (exception ex) {
		cout << "Cannot assemble " + mipsLine + " at line " + to_string(lineNumber + 1) << endl;
		//close 'filename.s'
		inFile.close();
		return 0;
	}

	//close 'filename.s'
	inFile.close();

	//save the assembly file as 'filename.obj'
	ofstream outputFile;
	outputFile.open(filename + ".obj");
	for (int i = 0; i < assemblyLines.size(); i++) {
		outputFile << assemblyLines[i] << endl;
	}
	outputFile.close();
	cout << "success!" << endl;
	return 0;
}
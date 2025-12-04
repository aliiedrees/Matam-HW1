#include <iostream>
#include <fstream>
#include <string>

#include "BlockChain.h"
#include "Utilities.h"

void opHash (ifstream& source, ofstream& target);
void opVerify (ifstream& source, ifstream& target);
void opFormat (ifstream& source, ofstream& target);
void opCompress (ifstream& source, ofstream& target);

using std::endl;
using std::cout;
using std::cerr;

int main(int argc, char** argv){
    if(argc != 4){
        getErrorMessage();
        return 1;
    }
    string op = argv[1];
    string source = argv[2];
    string target = argv[3];
    ifstream sourceFile(source);
    ofstream targetFile(target);
    if(op == "format"){
        opFormat(sourceFile, targetFile);
    }else if(op == "hash"){
        opHash(sourceFile, targetFile);
    } else if (op == "compress"){
        opCompress(sourceFile, targetFile);
        return 0;
    } else if(op == "verify"){
        targetFile.close();
        ifstream targetFile(target);
        opVerify(sourceFile, targetFile);
    }else{
        getErrorMessage();
        return 1;
    }
    return 0;
}

void opHash (ifstream& source, ofstream& target){
    BlockChain block = BlockChainLoad(source);
    BlockChainDumpHashed(block, target);
}

void opVerify (ifstream& source, ifstream& target){
    BlockChain block = BlockChainLoad(source);
    bool result = BlockChainVerifyFile(block, target);
    if(result){
        cout << "Verification passed" << endl;
    } else {
        cout << "Verification failed" << endl;
    }
}



 // abed

void opFormat (ifstream& source, ofstream& target){
    BlockChain blockchain = BlockChainLoad(source);
    BlockChainDump(blockchain, target);
}

void opCompress (ifstream& source, ofstream& target) {
    BlockChain blockchain = BlockChainLoad(source);
    BlockChainCompress(blockchain);
    BlockChainDump(blockchain, target);
}









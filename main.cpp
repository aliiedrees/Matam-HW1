#include <iostream>
#include <fstream>
#include <string>

#include "BlockChain.h"

using std::endl;
using std::cout;
using std::cerr;

int main(int argc, char** argv){
    if(argc != 3){
        cerr << "Usage: ./mtm_blockchain <op> <source> <target>" << endl;
        return 1;
    }
    string op = argv[0];
    string source = argv[1];
    string target = argv[2];
    
    if(op == "format"){
        
    }
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

void opFormat (ifstream source, ofstream target){
    BlockChain blockchain = BlockChainLoad(source);
    BlockChainDump(blockchain, target);
}

void opCompress (ifstream source, ofstream target) {
    BlockChain blockchain = BlockChainLoad(source);
    BlockChainCompress(blockchain);
    BlockChainDump(blockchain, target);
}









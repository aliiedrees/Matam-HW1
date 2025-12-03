#include <iostream>
#include <fstream>
#include <string>

#include "BlockChain.h"

int main(int argc, char** argv){
    if(argc != 3){
        return 1;
    }
    string op = argv[0];
    string source = argv[1];
    string target = argv[2];
    
    if(op == "format"){
        
    }
}
 void opHash (string source, string target){

 }

 void opVerify (string source, string target){}



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









#include <string>
#include <fstream>

#include "Transaction.h"
#include "BlockChain.h"
#define SENDER 1
#define RECEIVER 2
#define NONE 3
using std::string;
using std::ifstream;
using std::ofstream;
using std::endl;

void BlockChainDestroy(BlockChain& blockChain){
    BlockChain* currBlock = &blockChain;
    while(currBlock){
        BlockChain* toDelete = currBlock;
        currBlock = blockChain.prev_block;
        delete toDelete;
    }
}

//helper function to check if person is sender or receiver or none
static int CheckIfContributeToBlock(const BlockChain& blockChain, const string& name){
    if (blockChain.transaction.sender == name){
        return SENDER;
    } else if (blockChain.transaction.receiver == name){
        return RECEIVER;
    }
    return NONE;
}
int BlockChainPersonalBalance(const BlockChain& blockChain, const string& name){
    int balance = 0; //maybe unsigned .
    const BlockChain* current_block = &blockChain;
    while(current_block){
        int contribution = CheckIfContributeToBlock(*current_block, name);
        if(contribution == SENDER){
            balance -= current_block->transaction.value; // check if minus acceptable.
        } else if (contribution == RECEIVER){
            balance += current_block->transaction.value;
        }
        current_block = current_block->prev_block;
    }
    return balance;
}

BlockChain BlockChainLoad(ifstream& file){
    BlockChain blockChain = BlockChainInit();
    BlockChain* currBlock = &blockChain;

    while (!file.eof()){
        Transaction transaction;
        file >> transaction.sender;
        file >> transaction.receiver;
        file >> transaction.value;
        currBlock->transaction = transaction;
        file >> currBlock->timestamp;
        BlockChain head = BlockChainInit();
        currBlock->prev_block = &head;
        currBlock = &head;
    }
    return blockChain;
}

void BlockChainDumpHashed(const BlockChain& blockChain, ofstream& file){
    
}
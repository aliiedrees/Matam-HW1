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

void BlockChainDestroy(BlockChain& blockChain){
    while(blockChain){
        BlockChain* toDelete = blockChain;
        blockChain = blockChain->prev_block;
        delete toDelete;
    }
}

//helper function to check if person is sender or receiver or none
static int CheckIfContributeToBlock(const BlockChain& blockChain, const string& name){
    if (blockChain.sender == name){
        return SENDER;
    } else if (blockChain.receiver == name){
        return RECEIVER
    }
    return NONE;
}
int BlockChainPersonalBalance(const BlockChain& blockChain, const string& name){
    int balance = 0;
    BlockChain* current_block = &blockChain;
    while(current_block){
        int contribution = CheckIfContributeToBlock(current_block, name);
        if(contribution == SENDER){
            balance -= current_block->value;
        } else if (contribution == RECEIVER){
            balance += current_block->value;
        }
        current_block = current_block->prev_block;
    }
    return balance;
}
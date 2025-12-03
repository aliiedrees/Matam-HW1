#include <string>
#include <fstream>

#include "Transaction.h"
#include "BlockChain.h"

#include <iostream>
#define SENDER 1
#define RECEIVER 2
#define NONE 3
using std::string;
using std::ifstream;
using std::ofstream;
using std::endl;

BlockChain& BlockChainInit(){
    BlockChain* block = new BlockChain();
    block->transaction = TransactionInit();
    block->timestamp = "";
    block->prev_block = nullptr;

    return *block;
 }

void BlockChainDestroy(BlockChain& blockChain){
     BlockChain* currBlock = &blockChain;
    while(currBlock){
        BlockChain* toDelete = currBlock;
        currBlock = blockChain.prev_block;
        delete toDelete;
    }
}

int BlockChainGetSize(BlockChain& blockChain){
  int size = 0;
  BlockChain* currentBlock = &blockChain;
  while(currentBlock){
    size++;
    currentBlock = currentBlock->prev_block;
  }
  return size;
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
void BlockChainAppendTransaction(BlockChain blockchain,Transaction transaction , const string timestamp){
  BlockChain newblock = BlockChainInit();
  newblock.transaction = transaction;
  newblock.timestamp = timestamp;
  newblock.prev_block = &blockchain;
}
void BlockChainAppendTransaction(BlockChain blockchain,string sender, string receiver , int value , const string timestamp){
  BlockChain newblock = BlockChainInit();
  Transaction transaction = TransactionInit(sender, receiver, value);
  newblock.transaction = transaction;
  newblock.timestamp = timestamp;
  newblock.prev_block = &blockchain;
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
void BlockChainDump(BlockChain blockchain,ofstream& file){
  BlockChain* current_block = &blockchain;
  int cnt = 1;
  while(current_block){
    file << cnt << endl;
    TransactionDumpInfo(current_block->transaction,file);
    current_block = current_block->prev_block;
    cnt++;
  }
}
void BlockChainDumpHashed(BlockChain blockchain,ofstream& file) {
    BlockChain* current_block = &blockchain;
    while(current_block->prev_block != nullptr) {
        file << TransactionHashedMessage(current_block->transaction) << endl;
        current_block = current_block->prev_block;
    }
    file << TransactionHashedMessage(current_block->transaction);

}
bool BlockChainVerifyFile(BlockChain blockchain, ifstream& file){
  BlockChain* current_block = &blockchain;
  while(current_block != nullptr && !file.eof()) {
    Transaction currtransaction = current_block->transaction;
    string s;
    getline(file , s);
    if(TransactionVerifyHashedMessage(currtransaction, s) != true ){
        return false;
    }
    current_block = current_block->prev_block;
  }
  if(file.eof() == true && current_block == nullptr)
  return true;
  return false;
}
void BlockChainCompress(BlockChain& blockChain){
    BlockChain* currentBlock = &blockChain;
    BlockChain* blockToMerge = currentBlock->prev_block;

    while(blockToMerge){
        const string& sender = currentBlock->transaction.sender;
        const string& receiver = currentBlock->transaction.receiver;
        const string& toMergeSender = blockToMerge->transaction.sender;
        const string& toMergeReceiver = blockToMerge->transaction.receiver;
        if(sender == toMergeSender && receiver == toMergeReceiver){
            currentBlock->transaction.value += blockToMerge->transaction.value;
            BlockChain* blockToDelete = blockToMerge;
            blockToMerge = blockToMerge->prev_block;
            currentBlock->prev_block = blockToMerge;
            delete blockToDelete;
        } else {
            currentBlock = blockToMerge;
            blockToMerge = blockToMerge->prev_block;
        }
    }
}

 void BlockChainTransform(BlockChain& blockchain ,int (*func)(int)){
    BlockChain* current_block = &blockchain;
    while(current_block != nullptr){
        Transaction transaction = current_block->transaction;
        transaction.value = func((int)transaction.value);
        current_block->transaction = transaction;
        current_block = current_block->prev_block;
    }
}
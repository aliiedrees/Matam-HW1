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


BlockChain BlockChainInit(){
    BlockChain* block = new BlockChain();
    block.transaction = Transaction();
    block.timestamp = "";
    block.prev_block = nullptr;

    return newblock;
 }

void BlockChainDestroy(BlockChain& blockChain){
    while(blockChain){
        BlockChain* toDelete = blockChain;
        blockChain = blockChain->prev_block;
        delete toDelete;
    }
}

BlockChainGetSize(BlockChain& blockChain){
  int size = 0;
  while(blockChain){
    size++;
    blockChain = blockChain->prev_block;
  }
  return size;
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
    const BlockChain* current_block = &blockChain;
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
void BlockChainAppendTransaction(BlockChain blockchain,Transaction transaction , const string timestamp){
  BlockChain newblock = blockChainInit();
  newblock->transaction = transaction;
  newblock->timestamp = timestamp;
  newblock->prev_block = blockchain;
}
void BlockChainAppendTransaction(BlockChain blockchain,string sender, string receiver , int value , const string timestamp){
  BlockChain newblock = blockChainInit();
  Transaction transaction = transactionInit(sender, receiver, value, timestamp);
  newblock->transaction = transaction;
  newblock->timestamp = timestamp;
  newblock->prev_block = blockchain;
}

void BlockChainDump(BlockChain blockchain,ofstream& file){
  BlockChain* current_block = &blockchain;
  int cnt = 1;
  while(current_block){
    file << cnt << endl;
    TransactionDumpInfo(current_block->transaction,ofstream& file);
    current_block = current_block->prev_block;
    cnt++;
  }
}
bool BlockChainVerifyFile(BlockChain blockchain, ifstream& file){
  BlockChain* current_block = &blockchain;
  while(current_block && !file.eof) {
    Transiction currtransaction = current_block->transaction;
    string s = getline(file);
    if(TransactionVerifyHashedMessage(currtransaction, s) != true )
      return false;
  }
  if(file.eof == true && current_block = nullptr)
  return true;
  return false;
}
Blockchain& BlockChainTransform(BlockChain blockchain ,int (*func)(int)){
  BlockChain* current_block = &blockchain;
while(current_block){
  Transaction transaction = current_block->transaction;
  transaction.value = func(transaction.value);
  current_block->transiction = transaction;
  current_block = current_block->prev_block;
}
return blockchain;
}

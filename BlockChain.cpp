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
    Transaction& t = TransactionInit();
    block->transaction = t;
    block->timestamp = "";
    block->prevBlock = nullptr;

    delete &t;
    return *block;
}

void BlockChainDestroy(BlockChain& blockChain){
    BlockChain* currBlock = &blockChain;
    while(currBlock != nullptr){
        BlockChain* toDelete = currBlock;
        currBlock = currBlock->prevBlock;
        delete toDelete;
    }
}

int BlockChainGetSize(BlockChain& blockChain){
    int size = 0;
    BlockChain* currentBlock = &blockChain;
    while(currentBlock){
        size++;
        currentBlock = currentBlock->prevBlock;
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
    const BlockChain* currentBlock = &blockChain;
    while(currentBlock){
        int contribution = CheckIfContributeToBlock(*currentBlock, name);
        if(contribution == SENDER){
            balance -= currentBlock->transaction.value; // check if minus acceptable.
        } else if (contribution == RECEIVER){
            balance += currentBlock->transaction.value;
        }
        currentBlock = currentBlock->prevBlock;
    }
    return balance;
}

void BlockChainAppendTransaction(
    BlockChain& blockChain,
    const Transaction& transaction,
    const string& timestamp
){
    BlockChain newBlock = BlockChainInit();
    newBlock.transaction = transaction;
    newBlock.timestamp = timestamp;
    newBlock.prevBlock = &blockChain;
}

void BlockChainAppendTransaction(
    BlockChain& blockChain,
    unsigned int value,
    const string& sender,
    const string& receiver,
    const string& timestamp
){
    BlockChain newBlock = BlockChainInit();
    Transaction transaction = TransactionInit(sender, receiver, value);
    newBlock.transaction = transaction;
    newBlock.timestamp = timestamp;
    newBlock.prevBlock = &blockChain;
}

BlockChain BlockChainLoad(ifstream& file){
    BlockChain* currBlock = nullptr;
    BlockChain* head = nullptr;
    string sender, receiver, timestamp;
    int value;
    while(file >> sender >> receiver >> value >> timestamp){
        BlockChain& blockRef = BlockChainInit();
        BlockChain* block = &blockRef;
        
        Transaction& tRef = TransactionInit(sender, receiver, value);
        block->transaction = tRef;
        delete &tRef;

        block->timestamp = timestamp;

        if (head == nullptr){
            head = block;
            currBlock = block;
        } else {
            currBlock -> prevBlock = block;
            currBlock = block;
        }
    }

    if(head == nullptr){
        BlockChain& blockRef = BlockChainInit();
        BlockChain block = blockRef;
        delete &blockRef;
        return block;
    }

    BlockChain returnBlock = *head;
    head->prevBlock = nullptr;
    delete head;

    return returnBlock;
}

void BlockChainDump(const BlockChain& blockChain,ofstream& file){
    const BlockChain* currentBlock = &blockChain;
    int cnt = 1;
    file << "BlockChain Info:" << endl;
    while(currentBlock){
        file << cnt << "." << endl;
        TransactionDumpInfo(currentBlock->transaction,file);
        file << "Transaction timestamp: " << currentBlock->timestamp << endl;
        currentBlock = currentBlock->prevBlock;
        cnt++;
    }
}

void BlockChainDumpHashed(const BlockChain& blockChain,ofstream& file) {
    const BlockChain* currentBlock = &blockChain;
    while(currentBlock->prevBlock != nullptr) {
        file << TransactionHashedMessage(currentBlock->transaction) << endl;
        currentBlock = currentBlock->prevBlock;
    }
    file << TransactionHashedMessage(currentBlock->transaction);
}

bool BlockChainVerifyFile(const BlockChain& blockChain, ifstream& file){
    const BlockChain* currentBlock = &blockChain;
    while(currentBlock != nullptr && !file.eof()) {
        Transaction currTransaction = currentBlock->transaction;
        string s;
        getline(file , s);
        if(!TransactionVerifyHashedMessage(currTransaction, s)){
            return false;
        }
        currentBlock = currentBlock->prevBlock;
    }
    if(file.eof() == true && currentBlock == nullptr){
        return true;
    }
    return false;
}

void BlockChainCompress(BlockChain& blockChain){
    BlockChain* currentBlock = &blockChain;
    BlockChain* blockToMerge = currentBlock->prevBlock;

    while(blockToMerge){
        const string& sender = currentBlock->transaction.sender;
        const string& receiver = currentBlock->transaction.receiver;
        const string& toMergeSender = blockToMerge->transaction.sender;
        const string& toMergeReceiver = blockToMerge->transaction.receiver;
        if(sender == toMergeSender && receiver == toMergeReceiver){
            currentBlock->transaction.value += blockToMerge->transaction.value;
            BlockChain* blockToDelete = blockToMerge;
            blockToMerge = blockToMerge->prevBlock;
            currentBlock->prevBlock = blockToMerge;
            delete blockToDelete;
        } else {
            currentBlock = blockToMerge;
            blockToMerge = blockToMerge->prevBlock;
        }
    }
}

void BlockChainTransform(BlockChain& blockChain ,updateFunction function){
    BlockChain* currentBlock = &blockChain;
    while(currentBlock != nullptr){
        Transaction transaction = currentBlock->transaction;
        transaction.value = function((int)transaction.value);
        currentBlock->transaction = transaction;
        currentBlock = currentBlock->prevBlock;
    }
}
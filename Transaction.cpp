#include "Transaction.h"
#include <fstream>
#include "Utilities.h"
#include <string>


using std::string;
using std::ofstream;
using std::endl;
/**
 * TransactionDumpInfo - Prints the data of the transaction to a given file
 *
 * The data is printed in the following format:
 * Sender Name: <name>
 * Receiver Name: <name>
 * Transaction Value: <value>
 *
 * @param transaction Transaction to print
*/
void TransactionDumpInfo(const Transaction& transaction, ofstream& file){
    file << "Sender Name: " << transaction.sender << endl;
    file << "Receiver Name: " << transaction.receiver << endl;
    file << "Transaction Value: " << transaction.value << endl;
}

string TransactionHashedMessage(const Transaction& transaction){
    int key = transaction.value;
    string sender = transaction.sender;
    string receiver = transaction.receiver;
    return hash(key, sender, receiver);
}

bool TransactionVerifyHashedMessage(
        const Transaction& transaction,
        string hashedMessage
){
    string hashed = TransactionHashedMessage(transaction);
    if(hashed == hashedMessage){
        return true;
    } else {
        return false;
    }
}
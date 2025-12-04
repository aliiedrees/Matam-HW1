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
Transaction& TransactionInit() {
    Transaction* transaction = new Transaction();
    transaction->value = 0;;
    transaction->sender = "";
    transaction->receiver = "";
    return *transaction;
}
Transaction& TransactionInit(string sender, string receiver , int value) {
    Transaction* transaction = new Transaction();
    transaction->sender = sender;
    transaction->receiver = receiver;
    transaction->value = value;
    return *transaction;
}
void TransactionDumpInfo(const Transaction& transaction, ofstream& file){
    file << "Sender Name: " << transaction.sender << endl;
    file << "Receiver Name: " << transaction.receiver << endl;
    file << "Transaction Value: " << transaction.value << endl;
}

/**
 * TransactionHashMessage - Hashs the message of the transaction
 *
 * @param transaction Transaction to hash
 *
 * @return The hashed message
*/
string TransactionHashedMessage(const Transaction& transaction){
    int key = transaction.value;
    string sender = transaction.sender;
    string receiver = transaction.receiver;
    return hash(key, sender, receiver);
}

/**
 * TransactionVerifyHashedMessage - Verifies that a given transaction suits a given hashed message
 *
 * @param transaction Given transaction
 * @param hashedMessage Hashed message to verify
 *
 * @return true if the message given is suitable to this transaction, false otherwise
 *
*/
bool TransactionVerifyHashedMessage(
        const Transaction& transaction,
        string hashedMessage
){
    string hashed1 = TransactionHashedMessage(transaction);
    if(hashed1 == hashedMessage){
        return true;
    } else {
        return false;
    }
}
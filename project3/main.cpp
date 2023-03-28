// Project 3
// CS 2413 Data Structures
// Spring 2023
// Bilguunzaya Mijiddorj
#include <iostream>
#include <vector> // for array of transactions
#include <list> // for blockchain
#include <iterator> // for iterating through the list
using namespace std;
/*
 * Define the Transaction structure
 * The transaction class will hold information about one transaction.
 * each transaction object has transaction ID, fromID, toID, amount to be transferred finally timestamp which is the only string
 */
class transaction
{
    int tID; // transaction id
    int fromID; // source ID
    int toID; // target ID
    int tAmount; // how much is being transfered
    string timeStamp; // time of the transaction read from the input file
public:
    transaction(); // default constructor
    transaction(int temptID, int tempfromID, int temptoID, int temptAmount,
                string temptimeStamp)
                {
        tID = temptID;
        fromID = tempfromID;
        toID = temptoID;
        tAmount = temptAmount;
        timeStamp = temptimeStamp;

                };// non default constructor - default 100 for values

    // all setters and getters
    int gettID ()
    {
        return tID;
    };
    int getfromID ()
    {
        return fromID;
    };
    int gettoID ()
    {
        return toID;
    };
    int gettAmount ()
    {
        return tAmount;
    };
    string gettimeStamp(){
        return timeStamp;
    }
    void settID (int temptID)
    {
        tID = temptID;
    };
    void setfromID (int tempfromID)
    {
       fromID = tempfromID;
    };
    void settoID (int temptoID)
    {
        toID = temptoID;
    };
    void settAmount (int temptAmount)
    {
        tAmount = temptAmount;
    };
    void settimeStamp(string tempTimestamp){
        timeStamp = tempTimestamp;
    }

    /*
     * dispays the private variables of a transaction object with a space in between. Each object will have display and blockchain uses block display and block display uses transaction display methods.
    */
    void display(){
        cout << tID << " " << fromID << " " << toID << " " << tAmount << " " << timeStamp << endl;
    };

};
class block
{
    int blockNumber; // block number of the current block
    int currentNumTransactions; // how many transactions are currently in the block
    int maxNumTransactions; // how many maximum transactions can be in the block
    vector<transaction> bTransactions; // vector of transaction objects
public:
    block(); // default constructor

    block(int bNumber, int maxTransactions)
    {
        blockNumber = bNumber;
        maxNumTransactions = maxTransactions;
        currentNumTransactions = 0;
    };// non default constructor

// search method for searching through array of transactions
    int search (transaction* t){
        for(int i = 0; i < currentNumTransactions; i++)
        {
            if(bTransactions[i].gettID() == t->gettID())
            {
                return i;
            }
        }

        return -1;
    };

// insert method to insert a new transaction
    void insert (transaction* t) {
        if(currentNumTransactions < maxNumTransactions){
            bTransactions.push_back(*t);
            currentNumTransactions++;
        }

    };

// setters and getters as needed
    int getBlockNumber ()
    {
        return blockNumber;
    };
    int getCurrentNumTransactions ()
    {
        return currentNumTransactions;
    }
    void setBlockNumber (int bNumber)
    {
        blockNumber = bNumber;
    };
    void setCurrentNumTransactions (int cNumTransactions)
    {
        currentNumTransactions = cNumTransactions;
    }

    void display() {
        for(int i = 0; i < currentNumTransactions; i++)
        {
             bTransactions[i].display();
        }
    }; // displays current transaction objects of this block object. Calls transaction->display for each transaction object
};
class blockChain
{
    int transactionPerBlock; // so that I would be able to use it to construct block objects
    int currentNumBlocks = 0; // maintain the size of the list/block chain list
    list<block> bChain; // blockchain as a linked list

public:
    blockChain(); // default constructor
    blockChain(int tPerB){
        transactionPerBlock = tPerB;
    }; // non default constructor

void insert(transaction* t){
    if(currentNumBlocks == 0){ //  // Check if the blockchain is empty
        // Create a new block and add it to the blockchain
        cout << "Adding block #" << 1 << endl;
        block* b = new block(1, transactionPerBlock);
        currentNumBlocks++;
        cout << "Inserting transaction to block #1" << endl;
        b->insert(t);
        bChain.push_front(*b);
    }
    else if (bChain.front().getCurrentNumTransactions() == transactionPerBlock){ // Check if the current block is full
        // Create a new block and add it to the front of the list
        block* b = new block(currentNumBlocks+1, transactionPerBlock);
        currentNumBlocks++;
        b->insert(t);
        bChain.push_front(*b);
        cout << "Adding block #" << currentNumBlocks << endl;
        cout << "Inserting transaction to block #" << bChain.front().getBlockNumber() << endl;
    }
    else { // if not empty or full just adding to the current block
        bChain.front().insert(t);
        cout << "Inserting transaction to block #" << bChain.front().getBlockNumber() << endl;
    }
};// insert method to insert new transaction into the block chain - add new block if existing block is full. while inserting new block into list, insert front

// setters and getters as needed
int getCurrentNumBlocks(){
    return currentNumBlocks;
};
void setCurrentNumBlocks(int num){
    currentNumBlocks = num;
};


void display (){ // display each block objects in the blockchain
    // copying the list so that using reverse would not affect the bChain list in the private field
    list<block> copy;
    copy.assign(bChain.begin(), bChain.end());

    // reverse the copied list, because the block object at the front of the list is the last block object.
    copy.reverse();

    cout << "Current number of blocks: " << currentNumBlocks << endl;

    for(auto i : copy){ // C++ 11or higher version, ran into some problem when running it but debugging solves it
        cout << "Block Number: " << i.getBlockNumber() << " -- " << "Number of Transaction: " << i.getCurrentNumTransactions() << endl;

        i.display(); // calls the block display method
    }


}

};
int main()
{
    int numTransactionsPerBlock; // max transactions per block
    cin >> numTransactionsPerBlock;
    cout << "Number of transactions per block: " << numTransactionsPerBlock <<
         endl;
    int totalNumTransactions; // total transactions to be read from the input file
    cin >> totalNumTransactions;
    cout << "Total number of transactions: " << totalNumTransactions << endl;

// object of block chain
    blockChain* b1 = new blockChain(numTransactionsPerBlock);
    int tID; // transaction id
    int fromID; // source ID
    int toID; // target ID
    int tAmount; // how much is being transfered
    string timeStamp; // time of the transaction read from the input file

    for(int i = 0; i < totalNumTransactions; i++)
    {
        cin >> tID >> fromID >> toID >> tAmount >> timeStamp; // getting the inputs from the redirected file
        transaction* t = new transaction(tID, fromID, toID, tAmount, timeStamp); // creating a new transaction object with the given input from the file
        b1->insert(t); // insert the transaction object into the blockchain
    }
    b1->display(); // displays the contents of the blockchain

    return 0;
}
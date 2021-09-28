#include <string>
#include <functional>
#include <vector>
#include <iostream>
#include <ctime>
#include <bits/stdc++.h>

#define ll long long int
using namespace std;

hash<string> hashfunc;

typedef struct content
{
    string lastblock;
    // string block_hash;
    ll bno;
    // double amount;
} block;

string getTime(){
    return to_string(time(nullptr));
}

class Transaction
{
    public:
    Transaction(){

    }
    Transaction(string sender, string receiver, double amt)
    {
        senderAddress = sender;
        receiverAddress = receiver;
        amount = amt;
    }
    
    void printDetails(){
        cout << "Sender:\t" << senderAddress << endl;
        cout << "Receiver:\t" << receiverAddress << endl;
        cout << "Amount:\t" << amount << endl;
    }
    double getAmount(){
        return amount;
    }
    string getReceiver(){
        return receiverAddress;
    }
    string getSender(){
        return senderAddress;
    }
    protected:
    string senderAddress;
    string receiverAddress;
    double amount;
};

class Node
{
    public:
    Node(const Transaction a, ll num, string lastblock){
        nodeTransaction = a;
        current.lastblock = lastblock;
        current.bno = num;
    }
    block getDetails(){
        return current;
    }
    void printDetails(){
        cout << "\nTransaction Info:\n";
        nodeTransaction.printDetails();

        cout << "\n\nBlock Info:\n";
        cout << "Block number:\n" << current.bno << endl;
        cout << "Hash of last block:\n" << current.lastblock << endl;
    }
    private:
    Transaction nodeTransaction;
    block current;

};

string hashNode(Node a){
    block details = a.getDetails();
    string t = getTime() + details.lastblock + to_string(details.bno);

    return to_string(hashfunc(t));

}
class User
{
    public:
    User(string seed){
        address = hashfunc(seed);
    }
    string getAddress(){
        return address;
    }
    void receiveToken(double amt){
        balance += amt;
    }
    int sendToken(double amt){
        if(amt <= balance){
            balance -= amt;
            return 0;
        }
        else{
            return -1;
        }
    }
    void createTransaction(){

    }
    private:
    string address;
    double balance;
};

class Contract: protected Transaction{ 
// You can customize this class by extending it, but it should always inherit Transaction.
// Also, it MUST contain the boolean function validate(), returning a boolean value.
// An atomic contract (ie., the most basic contract) involves two users and a transaction. 
    public:
    Contract(){
        num = 0;
    }
    bool validate(const string a, const string b, Node n){
        num++;
        if (num%2)
            return false;
        else
            return true;
        
    }
    protected:
    void transit(){

    }
    int num;

};

class Ledger
{
    public:
    vector<Node> getLedger()
    {
        return ledger;
    }
    void addToLedger(Node a)
    {
        const Node b = a;
        cout << "addToLedger() invoked...";
        ledger.push_back(b);
    }
    ll ledgerLength(){
        return ledger.size();
    }
    void printInstance(int i){
        ledger[i].printDetails();
    }
    Node getInstance(int i){
        return ledger[i];
    }
    private:
    vector<Node> ledger;
};

Node makeNode(string usr1, string usr2, double amt, string THash, ll bnum)
{
    Transaction tx = Transaction(usr1, usr2, amt);
    Node nNode = Node(tx, bnum, THash);

    return nNode;
}
bool validate(User a, User b, Transaction t)
{

}

int main()
{
    Ledger ledgerInstance = Ledger();
    
    cout << "\nEnter number of mock transactions to generate:\n";
    int n;
    cin >> n;

    Node genesisBlock = Node(Transaction("__init__","__init__",0.00), 1, to_string(hashfunc("0")));    
    cout << "\n" << "Genesis block:\nHash: " << hashNode(genesisBlock) << "\n";
    string THash = hashNode(genesisBlock);
    Contract democontract = Contract();

    string u1 = "abc";
    string u2 = "def";
    ledgerInstance.addToLedger(genesisBlock);

    for(int i = 0; i < n-1; i++){
        cout << "\n\nMaking new block..." << endl;
        // Transaction tx = Transaction("abc", "def", 0.00);
        cout << "Hash of last block: " << THash << endl;

        // tx.printDetails();
        Node nd = makeNode(u1, u2, 0.00, THash, i+2);
        nd.printDetails();
        if(democontract.validate(u1, u2, nd)){
            THash = hashNode(nd);
            cout << "Hash of current block: " << THash << endl;
            ledgerInstance.addToLedger(nd);
        }
        else{
            cout << "Block is not valid according to contract. Discarding block...";
        }
        // free(*nd);
        
    }
    cout << "\n\n--------------------------------- Printing Ledger ---------------------------------" << endl;
    for(int i = 0; i < ledgerInstance.ledgerLength(); i++){
        cout << "\n\n---------------------------------" << endl;
        if(i > 0){
            ledgerInstance.printInstance(i);
        }
        else{
            cout << "\n\nGenesis block";
        }
        cout << "\n\n---------------------------------" << endl;
    }

    // tinstance.getDetails();
    return 0;
}
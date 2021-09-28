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
    ll bno;
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
    Node(const Transaction &a, ll num, string lastblock){
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
    Transaction getTransaction(){
        return nodeTransaction;
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
    User(string seed, double amt){
        address = to_string(hashfunc(seed));
        balance = amt;
    }
    string getAddress(){
        return address;
    }
    bool receiveToken(double amt){      
        if(amt >= 0){
            balance += amt;
            return true;
        }
        else{
            cout << "\n\nCannot receive negative amount of tokens.\n\n";
            return false;
        }
    }
    bool sendToken(double amt){
        if(amt <= balance && amt>=0){
            balance -= amt;
            return true;
        }
        else{
            return false;
        }
    }
    void getDetails(){
        cout << "\nUser address:\t" << address;
        cout << "\nBalance:\t" << balance << "\n\n";
    }
    void createTransaction(){

    }
    private:
    string address;
    double balance;
};

User makeUser(double amt){
    string seed;
    cout << "\n\nEnter seed phrase:\n\n";
    cin >> seed;
    User newUser = User(seed, amt);
    return newUser;
}
class Contract: protected Transaction{ 
// You can customize this class by extending it, but it should always inherit Transaction.
// Also, it MUST contain the boolean functions validate() and transit(), returning a boolean value.
// An atomic contract (ie., the most basic contract) involves two users and a transaction. 
    public:
    Contract(){
        num = 0;
    }
    bool validate(User &a, User &b, Node &n){
        num++;
        if (num%2)
            return false;
        else{
            if(transit(a, b, n.getTransaction().getAmount())){
                return true;
            }
            else{
                return false;
            }
        }
        
    }
    protected:
    bool transit(User &sender, User &receiver, double amt){
        if(sender.sendToken(amt)){
            receiver.receiveToken(amt);
            cout << "\n\nTransaction complete!\n\n";
            return true;
        }
        else{
            cout << "\n\nTransaction couldn't be completed. Check the balance of sender, and the amount of tokens sent.\n\n";
            return false;
        }
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
    void addToLedger(const Node &a)
    {
        const Node b = a;
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

    cout << "\n\nEnter balance of sender to initialize with:";
    double a;
    cin >> a;
    User u1 = makeUser(10.00);
    string sender = u1.getAddress();

    cout << "\n\nEnter balance of receiver to initialize with:";
    cin >> a;
    User u2 = makeUser(0.00);
    string receiver = u2.getAddress();

    ledgerInstance.addToLedger(genesisBlock);

    for(int i = 0; i < n-1; i++){
        cout << "\n\n-----------------------------\n\nMaking new block..." << endl;
        // Transaction tx = Transaction("abc", "def", 0.00);
        cout << "Hash of last block: " << THash << endl;

        // tx.printDetails();
        cout << "Enter amount to be transacted for Transaction ID " << to_string(i+1) << ":\n";
        cin >> a;
        Node nd = makeNode(sender, receiver, a*1.00, THash, i+2);
        nd.printDetails();
        if(democontract.validate(u1, u2, nd)){
            THash = hashNode(nd);
            cout << "Hash of current block: " << THash << "\n\n-----------------------------\n\n";
            ledgerInstance.addToLedger(nd);
        }
        else{
            cout << "Block is not valid according to contract. Discarding block...\n\n-----------------------------\n\n";
        }        
    }
    cout << "\n\n--------------------------------- Printing Ledger ---------------------------------" << endl;
    for(int i = 0; i < ledgerInstance.ledgerLength(); i++){
        cout << "\n\n---------------------------------" << endl;
        if(i > 0){
            ledgerInstance.printInstance(i);
        }
        else{
            cout << "\n\nGenesis block (Block #1)";
        }
        cout << "\n\n---------------------------------" << endl;
    }

    cout << "Balance of sender now: " << endl;
    u1.getDetails();
    cout << "Balance of receiver now: " << endl;
    u2.getDetails();

    return 0;
}
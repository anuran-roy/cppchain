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
    
    void getDetails(){
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
    private:
    Transaction nodeTransaction;
    block current;

};

string hashNode(Node &a){
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
// You can customize this class, but it should always inherit Transaction.
// Also, it MUST contain the boolean function validate(), returning a boolean value.
    public:
    Contract(User &a, User &b){

    }
    protected:
    void transit(){

    }
    bool validate(){
        return true;
    }

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
        const Node &b = a;
        ledger.push_back(b);
    }
    ll ledgerLength(){
        return ledger.size();
    }
    private:
    vector<Node> ledger;
};

Node makeNode(Node last, const string &s)
{

}
bool validate(User &a, User &b, Transaction &t)
{

}

int main()
{
    cout << "\nHello world!\n";
    Ledger ledgerInstance = Ledger();
    
    cout << "\nEnter number of mock transactions to generate:\n";
    int n;
    cin >> n;

    Node genesisBlock = Node(Transaction("__init__","__init__",0.00), 1, to_string(hashfunc("0")));    
    cout << "\n" << "Genesis block:\nHash: " << hashNode(genesisBlock) << "\n";
    string THash = hashNode(genesisBlock);
    ledgerInstance.addToLedger(genesisBlock);
    for(int i = 0; i < n-1; i++){
        cout << "\n\nMaking new block..." << endl;
        Transaction tx = Transaction("abc", "def", 0.00);
        cout << "Hash of last block: " << THash << endl;

        tx.getDetails();
        Node nd = Node(tx, i+2, THash);
        THash = hashNode(nd);
        cout << "Hash of current block: " << THash << endl;
    }

    // tinstance.getDetails();
    return 0;
}
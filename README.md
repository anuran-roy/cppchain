# CPPChain

A simple C++ implementation of an elementary form of blockchain, built from scratch.

## Features

- User creation
- Proof-of-Work algorithm implementation
- Smart Contract Capability

### User Creation

User creation is pretty simple. You initialize a new User() object with a token balance.

### Proof-of-Work algorithm implementation

The proof-of-work algorithm can be customized as you wish. For simplicity, I kept it as a sleep timer of 5s.

### Smart Contract Capability

You can create simple smart contracts by extending the Contract() class, and initialize instances of your object.

NOTE: You MUST keep 2 boolean functions: transit() and validate() in your Smart Contract class definition. Else the smart contract won't work.
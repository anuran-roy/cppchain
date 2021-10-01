# CPPChain

A demo of an elementary form of blockchain in C++, built from scratch.

## Features

1. For Users:
- User account creation
- Proof-of-Elapsed Time (PoET) algorithm implementation for users
- Smart Contract Capability

2. For Miners:
  - Miner account creation
  - Proof-of-Work (PoW) algorithm implementation for Miners
  - **Self-adjusting mining incentivizer (with respect to blocks mined) to prevent concentration of computation power** 

3. Voting system for ledger copies with each user.

### User Creation

User creation is pretty simple. You initialize a new ```User()``` object with a token balance.

### Proof-of-Elapsed Time algorithm implementation

The proof-of-elapsed time algorithm can be customized as you wish. 
\
For simplicity, I kept it as a sleep timer of random duration within the range 10 +- 20s.

### Smart Contract Capability

You can create simple smart contracts by extending the ```Contract()``` class, and initialize instances of the same.

NOTE: You MUST keep 2 boolean functions: 
-  ```transit()```, and 
-  ```validate()```
in your Smart Contract class definition. Else the smart contract won't work.

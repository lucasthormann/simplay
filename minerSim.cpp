#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <functional>

// Sha256 Implementation is assumed to be provided
// #include 'sha256.h'

// Block class definition
class Block {
  public:
    std::string previousHash;
    std::string blockHash;
    std::string data;
    long timeStamp;
    int nonce;

    // Constructor for the Block class
    Block(std::string data, std::string previousHash) {
      this->data = data;
      this->previousHash = previousHash;
      this->timeStamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
      this->nonce = 0;
      this->blockHash = calculateHash();
    }

    // Function to calculate the hash of the block
    std::string calculateHash() const {
      std::stringstream ss;
      ss << previousHash << timeStamp << data << nonce;
      return ss.str();
      // return sha256(ss.str()); // sha256 is an hypothetical external function
    }

    // Proof of work: we will simulate a simple one
    void mineBlock(int difficulty) {
      std::string target(difficulty, '0');
      while(blockHash.substr(0, difficulty) != target) {
        nonce++;
        blockHash = calculateHash();
      }
      std::cout << "Block mined: " << blockHash << std::endl;

    }
};

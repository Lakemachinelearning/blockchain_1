#include <ctime>
#include <vector>

using namespace std;

// Transaction Data
struct TransactionData {
    double amount;
    string senderKey;
    string receiverKey;
    time_t timestamp;
}


// Block Class
class Block
{
    private:
        int index;
        size_t blockHash;
        size_t previousHash;
        size_t generateHash();


    public:
       // Constructor
       Block(int idx, TransactionData d, size_t prevHash);

       // Get Original Hash
       size_t getHash();

       // Get Previous Hash
       size_t getPreviousHash();

       // Transaction Data
       TransactionData data;

       // Validate Hash
       bool isHashValid();

};

// Constructor with params
Block::Block(int idx, TransactionData d, size_t prevHash)
{
    index = idx;
    data = d;
    previousHash = prevHash;
    blockHash = generateHash();
}

// Private functions
size_t Block::generateHash()
{
    hash<string> hash1;
    hash<size_t> hash2;
    hash<size_t> finalHash;
    string toHash = to_string(data.amount) + data.recieveKey + data.senderKey + to_string(data.timestamp);

    return finalHash(hash1(toHash) + hash2(previousHash));
}

// Public functions
size_t Block::getHash()
{
    return blockHash;
}

size_t Block::getPreviousHash()
{
    return previousHash;
}

bool Block::isHashValid()
{
    return generateHash() == blockHash;
}








// Blockchain Class
class Blockchain
{
    private:
        Block createGenesisBlock();


    public:
        // Public Chain
        vector<Block> chain;

        // Constructor
        Blockchain();

        // Public Functions
        void addBlock(TransactionData data);
        bool isChainValid();

        // Contrived Example For Demo Only
        Block *getLatestBlock();
}

// Blockchain Constructor
Blockchain::Blockchain()
{
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
}

Block Blockchain::createGenesisBlock()
{
    time_t current;
    TransactionData d;
    d.amount = 0;
    d.recieverKey = "None";
    d.senderKey = "None";
    d.timestamp = time(&current);

    hash<int> hash1;
    Block genesis(0, d, hash1(0));
    return genesis;
}


// Bad only for demo
Block *Blockchain::getLatestBlock()
{
    return &chain.back();
}

void Blockchain::addBlock(TransactionData d)
{
    int index = (int)chain.size() -1;
    Block newBlock(index, d, getLatestBlock()->getHash())
}



bool Blockchain::isChainValid()
{
    vector<Block>::iterator it;
    int chainLen = (int)chain.size();

    for (it = chain.begin(); it!= chain.end(); ++it)
    {
        Block currentBlock = *it;
        if(!currentBlock.isHashValid())
        {
            return false;
        }

        if(chainLen > 1)
        {
            Block previousBlock = *(it - 1);
            if(currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                // INVALID!!!
                return false;
            }
        }
    }
    return true;
}

int main()
{
    // Start Blockchain
    Blockchain LakeCoin;

    // Data for first added block
    TransactionData data1;
    time_t data1Time;
    data1.amount = 1.5;
    data1.receiverKey = "Lake";
    data1.senderKey = "Cassa";
    data1.timestamp = time(&data1Time);

    LakeCoin.addBlock(data1);

    cout << "Is chain valid?" << endl;
        << LakeCoin.isChainValid() << endl;
}

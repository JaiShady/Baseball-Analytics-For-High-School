 #include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

const int HASH_MAP_SIZE = 200;

//struct to represent player information
struct Player {
    std::string name;
    int jerseyNumber;
    std::string team;
    double obp; // On base percentage
    double slg; // Slugging percentage
    double ba;  // Batting average
    int sb;     // Stolen bases
    double fp;  // Fielding percentage

    Player* next; // ptr to the next player in case of collision
};

// Caesar's cipher encryption function
std::string caesarCipher(const std::string& name) {
    std::string encryptedName = name;
    for (char& c : encryptedName) {
        if (isalpha(c)) {
            c = ((c - 'A' + 3) % 26) + 'A'; // shift character by 3 positions in the alphabet
        }
    }
    return encryptedName;
}

// hash  for the Player struct
int hashFunction(int jerseyNumber, const std::string& team) {
    //  jersey # + team hash to get the final hash value
    int jerseyHash = jerseyNumber % HASH_MAP_SIZE;
    int teamHash = 0;
    for (char c : team) {
        teamHash += c;
    }
    return (jerseyHash + teamHash) % HASH_MAP_SIZE;
}

// arrays for buckets and linked lists for collision resolution
class HashMap {
private:
    Player* data[HASH_MAP_SIZE];

public:
    HashMap() {
        // initialzie all buckets to nullptr
        for (int i = 0; i < HASH_MAP_SIZE; ++i) {
            data[i] = nullptr;
        }
    }

    // deallocate memory
    ~HashMap() {
        // iterate over each bucket and delete the linked list
        for (int i = 0; i < HASH_MAP_SIZE; ++i) {
            Player* current = data[i];
            while (current != nullptr) {
                Player* next = current->next;
                delete current;
                current = next;
            }
        }
    }

    // insert method
    void insert(int jerseyNumber, const std::string& team, const Player& player) {
        int index = hashFunction(jerseyNumber, team);
        Player* newNode = new Player(player); 
        //  new node at the beginning of the linked list
        newNode->next = data[index];
        data[index] = newNode;
    }

    // Lookup method
    Player* get(int jerseyNumber, const std::string& team) {
        int index = hashFunction(jerseyNumber, team);
        // traverse the linked list to find the player
        Player* current = data[index];
        while (current != nullptr) {
            if (current->jerseyNumber == jerseyNumber && current->team == team) {
                return current; // found
            }
            current = current->next; // to the next node in case of collision
        }
        return nullptr; // not found
    }

    //get all players from a specific team
    void getPlayersFromTeam(const std::string& team) {
        for (int i = 0; i < HASH_MAP_SIZE; ++i) {
            Player* current = data[i];
            while (current != nullptr) {
                if (current->team == team) {
                    std::cout << "Player: " << current->name << ", Jersey Number: " << current->jerseyNumber << std::endl;
                    std::cout << "OBP: " << current->obp << ", SLG: " << current->slg << ", BA: " << current->ba << std::endl;
                    std::cout << "SB: " << current->sb << ", FP: " << current->fp << std::endl << std::endl;
                }
                current = current->next;
            }
        }
    }

    //get top three players based on composite score
    void getTopThreePlayers(const std::string& team) {
        Player* topPlayers[3] = {nullptr}; // Array to store top three players
        double maxScores[3] = {0}; // Array to store maximum composite scores
        double maxOBP = 0, minOBP = std::numeric_limits<double>::max();
        double maxSLG = 0, minSLG = std::numeric_limits<double>::max();
        double maxBA = 0, minBA = std::numeric_limits<double>::max();
        int maxSB = 0, minSB = std::numeric_limits<int>::max();
        double maxFP = 0, minFP = std::numeric_limits<double>::max();

        // iterate through all players to calculate max and min values for each stat
        for (int i = 0; i < HASH_MAP_SIZE; ++i) {
            Player* current = data[i];
            while (current != nullptr) {
                if (current->team == team) {
                    //  max and min values for each stat
                    if (current->obp > maxOBP) maxOBP = current->obp;
                    if (current->obp < minOBP) minOBP = current->obp;
                    if (current->slg > maxSLG) maxSLG = current->slg;
                    if (current->slg < minSLG) minSLG = current->slg;
                    if (current->ba > maxBA) maxBA = current->ba;
                    if (current->ba < minBA) minBA = current->ba;
                    if (current->sb > maxSB) maxSB = current->sb;
                    if (current->sb < minSB) minSB = current->sb;
                    if (current->fp > maxFP) maxFP = current->fp;
                    if (current->fp < minFP) minFP = current->fp;
                }
                current = current->next;
            }
        }

        // Iterate through all players to calculate composite score and find top three players
        for (int i = 0; i < HASH_MAP_SIZE; ++i) {
            Player* current = data[i];
            while (current != nullptr) {
                if (current->team == team) {
                    // normalize values
                    double normalizedOBP = (current->obp - minOBP) / (maxOBP - minOBP);
                    double normalizedSLG = (current->slg - minSLG) / (maxSLG - minSLG);
                    double normalizedBA = (current->ba - minBA) / (maxBA - minBA);
                    double normalizedSB = (current->sb - minSB) / (maxSB - minSB);
                    double normalizedFP = (current->fp - minFP) / (maxFP - minFP);

                    //  composite score
                    double compositeScore = (normalizedOBP * 0.25) + (normalizedSLG * 0.25) + (normalizedBA * 0.2) +
                                             (normalizedSB * 0.1) + (normalizedFP * 0.2);

                    // Find position to insert current player in topPlayers array
                    for (int j = 0; j < 3; ++j) {
                        if (compositeScore > maxScores[j]) {
                            // Shift players and scores to make space for the new top player
                            for (int k = 2; k > j; --k) {
                                topPlayers[k] = topPlayers[k - 1];
                                maxScores[k] = maxScores[k - 1];
                            }
                            // Insert the new top player
                            topPlayers[j] = current;
                            maxScores[j] = compositeScore;
                            break;
                        }
                    }
                }
                current = current->next;
            }
        }

        
        std::cout << "Top three players from team " << team << ":" << std::endl;
        for (int i = 0; i < 3; ++i) {
            if (topPlayers[i] != nullptr) {
                std::cout << "Player: " << topPlayers[i]->name << ", Jersey Number: " << topPlayers[i]->jerseyNumber << std::endl;
                std::cout << "Composite Score: " << maxScores[i] << std::endl;
            }
        }
    }
};

int main() {
    HashMap playersHashMap;

    //file containing player data
    std::ifstream inputFile("roster.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string playerName, team;
        int jerseyNumber;
        double obp, slg, ba, fp;
        int sb;
        if (iss >> playerName >> jerseyNumber >> team >> obp >> slg >> ba >> sb >> fp) {
            // encrpt the player's name using Caesar's cipher
            std::string encryptedName = caesarCipher(playerName);
            // Player object
            Player player = {encryptedName, jerseyNumber, team, obp, slg, ba, sb, fp, nullptr};
            // Insertr into the hash map
            playersHashMap.insert(jerseyNumber, team, player);
        } else {
            std::cerr << "Error: Invalid player data format." << std::endl;
        }
    }

   
    std::cout << "Choose operation:\n1. Search for a player\n2. Get stats for all players from a team\n3. Get top three players from a team\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        int jerseyNumber;
        std::string team;
        std::cout << "Enter the jersey number of the player: ";
        std::cin >> jerseyNumber;
        std::cout << "Enter the team name of the player: ";
        std::cin.ignore(); //  the newline character left in the stream
        std::getline(std::cin, team);

        // Retrieve the player from the hash map
        Player* foundPlayer = playersHashMap.get(jerseyNumber, team);
        if (foundPlayer != nullptr) {
            //  player's statistics
            std::cout << "Player found: " << foundPlayer->name << std::endl;
            std::cout << "OBP: " << foundPlayer->obp << ", SLG: " << foundPlayer->slg << ", BA: " << foundPlayer->ba << std::endl;
            std::cout << "SB: " << foundPlayer->sb << ", FP: " << foundPlayer->fp << std::endl;
        } else {
            std::cout << "Player not found." << std::endl;
        }
    } else if (choice == 2) {
        std::string team;
        std::cout << "Enter the team name: ";
        std::cin.ignore(); // the newline character left in the stream
        std::getline(std::cin, team);

        //  display stats for all players from the team
        playersHashMap.getPlayersFromTeam(team);
    } else if (choice == 3) {
        std::string team;
        std::cout << "Enter the team name: ";
        std::cin.ignore(); //  the newline character left in the stream
        std::getline(std::cin, team);

        //display top three players from the team
        playersHashMap.getTopThreePlayers(team);
    } else {
        std::cout << "Invalid choice." << std::endl;
    }

    return 0;
}


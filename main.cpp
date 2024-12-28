#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Sleep()
{
    for(int i=0;i<719992992;i++)
    {
    }
}
// AntFarm Class
class AntFarm {
public:
    string colonyName;
    string colonySpecies;
    int workerCount;
    int soldierCount;
    int totalKills;
    vector<string> defeatedColonies;
    int lifespan;
    bool isAlive;
    string destroyedBy;

    AntFarm(const string& name, const string& species) {
        colonyName = name;
        colonySpecies = species;
        workerCount = 0;
        soldierCount = 0;
        totalKills = 0;
        lifespan = 0;
        isAlive = true;
        destroyedBy = "";
    }

    void addResources(int workers, int soldiers) {
        if (!isAlive) return;
        workerCount += workers;
        soldierCount += soldiers;
    }

    void incrementKills(int kills) {
        if (!isAlive) return;
        totalKills += kills;
    }

    void addDefeatedColony(const string& colonyName) {
        if (!isAlive) return;
        defeatedColonies.push_back(colonyName);
    }

    void incrementLifespan() {
        if (isAlive) lifespan++;
    }

    void eliminate(const string& attackerName) {
        isAlive = false;
        destroyedBy = attackerName;
    }

    void displaySummary() const {
        cout << "----------------------------" << endl;
        cout << "AntFarm Summary: " << colonyName << endl;
        cout << "Species: " << colonySpecies << endl;
        cout << "Workers: " << workerCount << endl;
        cout << "Soldiers: " << soldierCount << endl;
        cout << "Total Kills: " << totalKills << endl;
        cout << "Defeated Colonies: " << defeatedColonies.size();
        if (!defeatedColonies.empty()) {
            cout << " (";
            for (size_t i = 0; i < defeatedColonies.size(); ++i) {
                cout << defeatedColonies[i];
                if (i < defeatedColonies.size() - 1) cout << ", ";
            }
            cout << ")";
        }
        cout << endl;
        cout << "| Lifespan (Ticks Alive): " << lifespan << endl;
        cout << "| Status: " << (isAlive ? "Alive" : "Destroyed by " + destroyedBy) << endl;
        cout << "| ----------------------------" << endl;
    }
};

// Singleton: Field Class
class Field {
private:
    static Field* instance;
    AntFarm** antFarms;
    int antFarmCount;
    static const int MAX_ANTFarmS = 14;

public:
    Field() {
        antFarms = new AntFarm*[MAX_ANTFarmS];
        antFarmCount = 0;
    }

    ~Field() {
        for (int i = 0; i < antFarmCount; ++i) {
            delete antFarms[i];
        }
        delete[] antFarms;
    }

    static Field* getInstance() {
        if (!instance) {
            instance = new Field();
        }
        return instance;
    }

    void createAntFarm(const string& name, const string& species) {
        if (antFarmCount < MAX_ANTFarmS) {
            antFarms[antFarmCount] = new AntFarm(name, species);
            antFarmCount++;
            cout << "| AntFarm " << name << " (Specie: " << species << ") successfully created!" << endl;
        } else {
            cout<<"! Error: Not possible! According to task formula species can only vary with 14 types and youi have occupied all be creating 14 ant farms."<<endl;

        }
    }

    void provideResources(int antFarmIndex, int workers, int soldiers) {
        if (antFarmIndex < 0 || antFarmIndex >= antFarmCount) {
            cout << "! Invalid antFarm index!" << endl;
            return;
        }
        antFarms[antFarmIndex]->addResources(workers, soldiers);
        cout << "| Resources allocated to antFarm " << antFarms[antFarmIndex]->colonyName << "!" << endl;
    }

    void advanceTick() {
        for (int i = 0; i < antFarmCount; ++i) {
            antFarms[i]->incrementLifespan();
        }
        cout << "| A new tick has passed!" << endl;
    }

    void battle(int attackerIndex, int defenderIndex) {
        if (attackerIndex < 0 || attackerIndex >= antFarmCount || defenderIndex < 0 || defenderIndex >= antFarmCount) {
            cout << "! Invalid antFarm index!" << endl;
            return;
        }

        AntFarm* attacker = antFarms[attackerIndex];
        AntFarm* defender = antFarms[defenderIndex];

        if (!attacker->isAlive || !defender->isAlive) {
            cout << "! Both antFarms must be alive to engage in battle!" << endl;
            return;
        }

        if (attacker->soldierCount > defender->soldierCount) {
            attacker->incrementKills(defender->workerCount + defender->soldierCount);
            attacker->addDefeatedColony(defender->colonyName);
            defender->eliminate(attacker->colonyName);
            cout <<"| "<< attacker->colonyName << " has defeated " << defender->colonyName << "!" << endl;
        } else {
            cout <<"| "<< defender->colonyName << " has successfully defended the attack!" << endl;
        }
    }

    void displaySummary(int antFarmIndex) {
        if (antFarmIndex < 0 || antFarmIndex >= antFarmCount) {
            cout << "! Invalid antFarm index!" << endl;
            return;
        }
        antFarms[antFarmIndex]->displaySummary();
    }

    void listAntFarms() {
        cout << "| Currently active AntFarms: " << endl;
        for (int i = 0; i < antFarmCount; ++i) {
            cout <<"| "<< i + 1 << ". " << antFarms[i]->colonyName << " (Specie: " << antFarms[i]->colonySpecies << ")" << endl;
        }
    }
};

Field* Field::instance = nullptr;

void processUserInput() {
    Field* field = Field::getInstance();
    bool running = true;

    while (running) {
    cout << "<-------------------------------------------------------->"<<endl;
    cout << "<------------- 1. Create AntFarm(limit:14) -------------->" << endl;
    cout << "<------------- 2. Provide Resources --------------------->" << endl;
    cout << "<------------- 3. Simulate Tick ------------------------->" << endl;
    cout << "<------------- 4. Battle AntFarms ----------------------->" << endl;
    cout << "<------------- 5. Display AntFarm Summary --------------->" << endl;
    cout << "<------------- 6. List AntFarms ------------------------->" << endl;
    cout << "<------------- 7. Quit ---------------------------------->" << endl;
    cout << "<-------------------------------------------------------->"<<endl;
    cout << "Enter your choice: ";
        int choice;
        cin >> choice;
    cout << "<--------------------------------------------------------->"<<endl;
        switch (choice) {
        case 1: {
                 string name, species;
            cout << "| Enter the name of the new antFarm: ";
            cin >> name;
            cout << "| Enter specie name: ";
            cin >> species;
            field->createAntFarm(name, species);
        }
        case 2: {
            int index, workers, soldiers;
            field->listAntFarms();
            cout << "| Enter antFarm index to provide resources: ";
            cin >> index;
            cout << "| Enter the number of workers: ";
            cin >> workers;
            cout << "| Enter the number of soldiers: ";
            cin >> soldiers;
            field->provideResources(index - 1, workers, soldiers);
    system("pause");
    system("cls");
            break;
        }
        case 3:
            field->advanceTick();
            system("pause");
            system("cls");
            break;
        case 4: {
            int attacker, defender;
            field->listAntFarms();
            cout << "| Enter attacker antFarm index: ";
            cin >> attacker;
            cout << "| Enter defender antFarm index: ";
            cin >> defender;
            field->battle(attacker - 1, defender - 1);
            system("pause");
            system("cls");
            break;
        }
        case 5: {
            int index;
            field->listAntFarms();
            cout << "| Enter antFarm index to display summary: ";
            cin >> index;
            field->displaySummary(index - 1);

    system("pause");
            system("cls");
            break;
        }
        case 6:
            field->listAntFarms();
    system("pause");
            system("cls");
            break;
        case 7:
            running = false;
            cout << "| Exiting simulation. Goodbye!" << endl;

            cout << "Press any key to continue..." << endl;
    system("pause");
            system("cls");
            break;
        default:
            cout << "| Invalid choice! Please try again." << endl;
    system("pause");
        }
    }
}

int main() {
    cout << "<========================================================>"<<endl;
    cout << "<================                            ============>"<<endl;
    cout << "<================     Ant Farm Simulation    ============>" << endl;
    cout << "<==================                        ==============>" << endl;
    cout << "<===================        \\   /         ===============>" << endl;
    cout << "<====================        o o        =================>" << endl;
    cout << "<=====================     (  -  )     ==================>" << endl;
    cout << "<=====================    (   |   )    ==================>" << endl;
    cout << "<=====================      (---)      ==================>" << endl;
    cout << "<=====================     / | | \\     ==================>" << endl;
    cout << "<=====================    /  / \\  \\    ==================>" << endl;
    cout << "<=====================   |         |   ==================>" << endl;
    cout << "<=====================  /           \\  ==================>" << endl;
    cout << "<========================================================>"<<endl;
    cout<<"Laoding..";
    Sleep();
    system("cls");
    processUserInput();
    return 0;
}

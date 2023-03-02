// Project Identifier: AD48FB4835AF347EB0CA8009E24C3B13F8519882
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <getopt.h>
#include "P2random.h"

// Namespace
using namespace std;


// Class & Struct
struct option ops[] = {
    {"verbose", no_argument, nullptr, 'v'},
    {"median", no_argument, nullptr, 'm'},
    {"general-eval", no_argument, nullptr, 'g'},
    {"watcher", no_argument, nullptr, 'w'},
    {nullptr, 0, nullptr, '\0'}
    
};

class RunningMedian {
private:
    priority_queue<uint32_t, vector<uint32_t>, greater<uint32_t> > top;
    priority_queue<uint32_t, vector<uint32_t>, less<uint32_t> > bottom;
    
public:
    RunningMedian(void) {
        top.push(UINT_MAX);
        bottom.push(0);
    }
    
    ~RunningMedian(void) {}
    
    uint32_t getMedian(void) const {
        if (top.size() != bottom.size()) {
            if(top.size() > bottom.size())
                return top.top();
            return bottom.top();
        }
        return (top.top() + bottom.top()) / ((uint32_t)2.0);
    }
    
    void push(uint32_t n) {
        if (n >= top.top()) top.push(n);
        else bottom.push(n);
    
        if (top.size() == bottom.size() + 2) {
            bottom.push(top.top());
            top.pop();
        } else if (top.size() == bottom.size() - 2) {
            top.push(bottom.top());
            bottom.pop();
        }
    }
    
    bool isEmpty(void) { return (top.size() == 1 && bottom.size() == 1); }
};

class Evaluation {
private:
    uint32_t sith = 0;
    uint32_t jedi = 0;
    uint32_t survivors = 0;

public:
    uint32_t getSith(void) const { return this->sith; }
    uint32_t getJedi(void) const { return this->jedi; }
    uint32_t getSurvivors(void) const { return this->survivors; }
    
    void setSith(uint32_t n) { this->sith = n; }
    void setJedi(uint32_t n) { this->jedi = n; }
    void setSurvivors(uint32_t n) { this->survivors = n; }
};


class Deployment {
private:
    uint32_t force = 0;
    uint32_t time = 0;
    uint32_t general = 0;
    uint32_t planet = 0;
    uint32_t troops = 0;
    uint32_t unique = 0;
    
public:
    uint32_t getForce(void) const { return this->force; }
    uint32_t getTime(void) const { return this->time; }
    uint32_t getGeneral(void) const { return this->general; }
    uint32_t getPlanet(void) const { return this->planet; }
    uint32_t getTroops(void) const { return this->troops; }
    uint32_t getUnique(void) const { return this->unique; }
    
    void setForce(uint32_t n) { this->force = n; }
    void setTime(uint32_t n) { this->time = n; }
    void setGeneral(uint32_t n) { this->general = n; }
    void setPlanet(uint32_t n) { this->planet = n; }
    void setTroops(uint32_t n) { this->troops = n; }
    void setUnique(uint32_t n) { this->unique = n; }
};

class Jedi {
public:
    bool operator() (const Deployment &d1, const Deployment &d2) {
        if (d1.getForce() != d2.getForce())
            return d1.getForce() > d2.getForce();
        else
            return d1.getUnique() > d2.getUnique();
    }
};

class Sith {
public:
    bool operator() (const Deployment &d1, const Deployment &d2) {
        if (d1.getForce() != d2.getForce())
            return d1.getForce() < d2.getForce();
        else
            return d1.getUnique() > d2.getUnique();
    }
};

class Planet {
private:
    priority_queue<Deployment, vector<Deployment>, Sith> sith;
    priority_queue<Deployment, vector<Deployment>, Jedi> jedi;

public:
    priority_queue<Deployment, vector<Deployment>, Sith> getSithPQ(void) { return this->sith; }
    priority_queue<Deployment, vector<Deployment>, Jedi> getJediPQ(void) { return this->jedi; }
};

class Ambush {
private:
    char condition = 'i';
    
    uint32_t timeSith = 0;
    uint32_t timeSith2 = 0;
    uint32_t forceSith = 0;
    uint32_t forceSith2 = 0;
    int timeJedi = -1;
    uint32_t forceJedi = 0;
    
public:
    char getCondition(void) const { return this->condition; }
    uint32_t getTimeSith(void) const { return this->timeSith; }
    uint32_t getTimeSith2(void) const { return this->timeSith2; }
    uint32_t getForceSith(void) const { return this->forceSith; }
    uint32_t getForceSith2(void) const { return this->forceSith2; }
    int getTimeJedi(void) const { return this->timeJedi; }
    uint32_t getForceJedi(void) const { return this->forceJedi; }
    
    void setCondition(char c) { this->condition = c; }
    void setTimeSith(uint32_t n) { this->timeSith = n; }
    void setTimeSith2(uint32_t n) { this->timeSith2 = n; }
    void setForceSith(uint32_t n) { this->forceSith = n; }
    void setForceSith2(uint32_t n) { this->forceSith2 = n; }
    void setTimeJedi(int n) { this->timeJedi = n; }
    void setForceJedi(uint32_t n) { this->forceJedi = n; }
};

class Attack {
private:
    char condition = 'i';

    uint32_t timeJedi = 0;
    uint32_t timeJedi2 = 0;
    uint32_t forceJedi = 0;
    uint32_t forceJedi2 = 0;
    int timeSith = -1;
    uint32_t forceSith = 0;

public:
    char getCondition(void) const { return this->condition; }
    uint32_t getTimeJedi(void) const { return this->timeJedi; }
    uint32_t getTimeJedi2(void) const { return this->timeJedi2; }
    uint32_t getForceJedi(void) const { return this->forceJedi; }
    uint32_t getForceJedi2(void) const { return this->forceJedi2; }
    int getTimeSith(void) const { return this->timeSith; }
    uint32_t getForceSith(void) const { return this->forceSith; }
    
    void setCondition(char c) { this->condition = c; }
    void setTimeJedi(uint32_t n) { this->timeJedi = n; }
    void setTimeJedi2(uint32_t n) { this->timeJedi2 = n; }
    void setForceJedi(uint32_t n) { this->forceJedi = n; }
    void setForceJedi2(uint32_t n) { this->forceJedi2 = n; }
    void setTimeSith(int n) { this->timeSith = n; }
    void setForceSith(uint32_t n) { this->forceSith = n; }
};



// Global Variables
bool bJedi = false, bIsJedi = false, bVerbose = false, bMedian = false, bGeneralEvaluation = false, bWatcher = false;
uint32_t numGenerals = 0, numPlanets = 0, randomSeed = 0, numDeployments = 0, arrivalRate = 0, totalBattles = 0, attackTime = 0;

vector <RunningMedian> medians;
vector <Evaluation> evaluations;
vector <Attack> attacks;
vector <Ambush> ambushes;
vector <Planet> planets;

// Functions
void ambush(uint32_t planet, uint32_t time, uint32_t force, string side) {
    Ambush &ambush = ambushes[planet];
    
    switch (ambush.getCondition()) {
        case 'b':
            if (side == "sith") {
                if (force > ambush.getForceSith2()) {
                    ambush.setForceSith2(force);
                    ambush.setTimeSith2(time);
                }
            } else {
                if (force < ambush.getForceSith2() && (force > ambush.getForceSith2() - (ambush.getForceSith() - ambush.getForceJedi()))) {
                    ambush.setForceJedi(force);
                    ambush.setTimeJedi(static_cast<int>(time));
                    
                    ambush.setForceSith(ambush.getForceSith2());
                    ambush.setTimeSith(ambush.getTimeSith2());
                }
            }
            break;
            
        case 's':
            if (side == "sith") {
                if (force > ambush.getForceSith2()) {
                    ambush.setForceSith(force);
                    ambush.setTimeSith(time);
                    
                    ambush.setForceSith2(force);
                    ambush.setTimeSith2(time);
                }
            }
            else {
                if (force <= ambush.getForceSith2()) {
                    char condition = 'b';
                    ambush.setCondition(condition);
                    
                    ambush.setForceJedi(force);
                    ambush.setTimeJedi(static_cast<int>(time));
                }
            }
            break;
            
        case 'i':
            if(side == "sith") {
                char condition = 's';
                ambush.setCondition(condition);
                
                ambush.setForceSith(force);
                ambush.setTimeSith(time);
                
                ambush.setForceSith2(force);
                ambush.setTimeSith2(time);
            }
            break;
            
        default:
            break;
    }
}

void attack(uint32_t planet, uint32_t time, uint32_t force, string side) {
    Attack &attack = attacks[planet];
    
    switch (attack.getCondition()) {
        case 'b':
            if (side == "jedi") {
                if (force < attack.getForceJedi2()) {
                    attack.setForceJedi2(force);
                    attack.setTimeJedi2(time);
                }
            }
            else {
                if (force > attack.getForceJedi2() && (force > (attack.getForceSith() - attack.getForceJedi()) + attack.getForceJedi2())) {
                    attack.setForceJedi(attack.getForceJedi2());
                    attack.setTimeJedi(attack.getTimeJedi2());
                    
                    attack.setForceSith(force);
                    attack.setTimeSith(static_cast<int>(time));
                }
            }
            break;
            
        case 'j':
            if (side == "jedi") {
                if (force < attack.getForceJedi2()) {
                    attack.setForceJedi(force);
                    attack.setTimeJedi(time);
                    
                    attack.setForceJedi2(force);
                    attack.setTimeJedi2(time);
                }
            }
            else {
                if (force >= attack.getForceJedi2()) {
                    char condition = 'b';
                    attack.setCondition(condition);
                    
                    attack.setForceSith(force);
                    attack.setTimeSith(static_cast<int>(time));
                }
            }
            break;
            
        case 'i':
            if (side == "jedi") {
                char condition = 'j';
                attack.setCondition(condition);
                
                attack.setForceJedi(force);
                attack.setTimeJedi(time);
                
                attack.setForceJedi2(force);
                attack.setTimeJedi2(time);
            }
            break;
            
        default:
            break;
    }
}

void attack(uint32_t a) {
    Deployment survivors;
    
    if (planets[a].getSithPQ().top().getTroops() > planets[a].getJediPQ().top().getTroops()) {
        survivors.setTime(planets[a].getSithPQ().top().getTime());
        survivors.setGeneral(planets[a].getSithPQ().top().getGeneral());
        survivors.setForce(planets[a].getSithPQ().top().getForce());
        survivors.setTroops(planets[a].getSithPQ().top().getTroops() - planets[a].getJediPQ().top().getTroops());
             
        medians[a].push(planets[a].getJediPQ().top().getTroops() * 2);
        
        if (bVerbose)
            cout << "General " << planets[a].getSithPQ().top().getGeneral() << "'s battalion attacksed General " << planets[a].getJediPQ().top().getGeneral() << "'s battalion on planet " << a << ". " << planets[a].getJediPQ().top().getTroops() * 2 << " troops were lost.\n";
        
        uint32_t troopsJedi = planets[a].getJediPQ().top().getTroops();
        uint32_t survivorsJedi = evaluations[planets[a].getJediPQ().top().getGeneral()].getSurvivors();
        uint32_t survivorsSith = evaluations[planets[a].getSithPQ().top().getGeneral()].getSurvivors();
        
        evaluations[planets[a].getJediPQ().top().getGeneral()].setSurvivors(troopsJedi + survivorsJedi);
        evaluations[planets[a].getSithPQ().top().getGeneral()].setSurvivors(troopsJedi + survivorsSith);
        
        planets[a].getSithPQ().pop();
        planets[a].getJediPQ().pop();
        planets[a].getSithPQ().push(survivors);
        
        return;
    } else if (planets[a].getSithPQ().top().getTroops() < planets[a].getJediPQ().top().getTroops()) {
        survivors.setTime(planets[a].getJediPQ().top().getTime());
        survivors.setGeneral(planets[a].getJediPQ().top().getGeneral());
        survivors.setForce(planets[a].getJediPQ().top().getForce());
        survivors.setTroops(planets[a].getJediPQ().top().getTroops() - planets[a].getSithPQ().top().getTroops());
        
        medians[a].push(planets[a].getSithPQ().top().getTroops() * 2);
        
        if (bVerbose) {
            cout << "General " << planets[a].getSithPQ().top().getGeneral() << "'s battalion attacksed General " << planets[a].getJediPQ().top().getGeneral();
            cout << "'s battalion on planet " << a << ". " << planets[a].getSithPQ().top().getTroops() * 2 << " troops were lost.\n";
        }
        
        uint32_t troopsSith = planets[a].getSithPQ().top().getTroops();
        uint32_t survivorsJedi = evaluations[planets[a].getJediPQ().top().getGeneral()].getSurvivors();
        uint32_t survivorsSith = evaluations[planets[a].getSithPQ().top().getGeneral()].getSurvivors();
        
        evaluations[planets[a].getJediPQ().top().getGeneral()].setSurvivors(troopsSith + survivorsJedi);
        evaluations[planets[a].getSithPQ().top().getGeneral()].setSurvivors(troopsSith + survivorsSith);
        
        planets[a].getSithPQ().pop();
        planets[a].getJediPQ().pop();
        planets[a].getJediPQ().push(survivors);
        
        return;
    } else {
        medians[a].push( planets[a].getJediPQ().top().getTroops() * 2);
        
        
        if (bVerbose) {
            cout << "General " << planets[a].getSithPQ().top().getGeneral() << "'s battalion attacksed General " << planets[a].getJediPQ().top().getGeneral();
            cout  << "'s battalion on planet " << a << ". " << planets[a].getJediPQ().top().getTroops() * 2 << " troops were lost.\n";
        }
        
        uint32_t troopsJedi = planets[a].getJediPQ().top().getTroops();
        uint32_t survivorsJedi = evaluations[planets[a].getJediPQ().top().getGeneral()].getSurvivors();
        uint32_t survivorsSith = evaluations[planets[a].getSithPQ().top().getGeneral()].getSurvivors();
        
        evaluations[planets[a].getJediPQ().top().getGeneral()].setSurvivors(troopsJedi + survivorsJedi);
        evaluations[planets[a].getSithPQ().top().getGeneral()].setSurvivors(troopsJedi + survivorsSith);
        
        planets[a].getJediPQ().pop();
        planets[a].getSithPQ().pop();
        
        return;
    }
}


void readFile(void) {
    string mode, type, comment, side;
    stringstream ss;
    
    char identifier;
    
    getline(cin, comment);
    cin >> type >> mode >> type >> numGenerals >> type >> numPlanets;
    
    medians.resize(numPlanets);
    evaluations.resize(numGenerals);
    attacks.resize(numPlanets);
    ambushes.resize(numPlanets);
    planets.resize(numPlanets);
    
    
    if (mode == "DL") {
        Deployment deployment;
        uint32_t id = 0, prevTime = 0;
        uint32_t time = deployment.getTime();
        
        while (cin >> time) {
            if (deployment.getTime() != prevTime) {
                if (deployment.getTime() < prevTime) {
                    cerr << "Invalid Time" << endl;
                    exit(1);
                }
                
                if (bMedian) {
                    for (uint32_t i = 0; i < numPlanets; i++)
                        if (!medians[i].isEmpty())
                            cout << "Median troops lost on planet " << i << " at time " << prevTime << " is " << medians[i].getMedian() << ".\n";
                };
                prevTime = deployment.getTime();
            }
            
            cin >> type;
            if (type == "JEDI") bIsJedi = true;
            else bIsJedi = false;
            
            uint32_t general = deployment.getGeneral();
            cin >> identifier;
            cin >> general;
            if (deployment.getGeneral() >= numGenerals) {
                cerr << "Invalid general ID" << endl;
                exit(1);
            }
            
            uint32_t planet = deployment.getPlanet();
            cin >> identifier;
            cin >> planet;
            if (deployment.getPlanet() >= numPlanets) {
                cerr << "Invalid planet ID" << endl;
                exit(1);
            }
            
            uint32_t force = deployment.getForce();
            cin >> identifier;
            cin >> force;
            if (deployment.getForce() <= 0) {
                cerr << "Invalid force sensntivity level" << endl;
                exit(1);
            }
            
            uint32_t troops = deployment.getTroops();
            cin >> identifier;
            cin >> troops;
            if (deployment.getTroops() <= 0) {
                cerr << "Invalid number of troops" << endl;
                exit(1);
            }
            
            deployment.setUnique(id);
            id++;
            
            if (bIsJedi) {
                side = "jedi";
                
                uint32_t jedi = evaluations[deployment.getGeneral()].getJedi();
                evaluations[deployment.getGeneral()].setJedi(jedi + deployment.getTroops());
                planets[deployment.getPlanet()].getJediPQ().push(deployment);
                
                bJedi = true;
                
                while ((!planets[deployment.getPlanet()].getSithPQ().empty() && !planets[deployment.getPlanet()].getJediPQ().empty()) && planets[deployment.getPlanet()].getSithPQ().top().getForce() >= planets[deployment.getPlanet()].getJediPQ().top().getForce()) {
                    
                    if (bJedi) attackTime = planets[deployment.getPlanet()].getJediPQ().top().getTime();
                    else attackTime = planets[deployment.getPlanet()].getSithPQ().top().getTime();
                    
                    attack(deployment.getPlanet());
                    totalBattles++;
                }
            } else {
                side = "sith";
                
                uint32_t sith = evaluations[deployment.getGeneral()].getSith();
                evaluations[deployment.getGeneral()].setSith(sith + deployment.getTroops());
                planets[deployment.getPlanet()].getSithPQ().push(deployment);
                
                while ((!planets[deployment.getPlanet()].getSithPQ().empty() && !planets[deployment.getPlanet()].getJediPQ().empty()) && planets[deployment.getPlanet()].getSithPQ().top().getForce() >= planets[deployment.getPlanet()].getJediPQ().top().getForce()) {
                    
                    if (bJedi) attackTime = planets[deployment.getPlanet()].getJediPQ().top().getTime();
                    else attackTime = planets[deployment.getPlanet()].getSithPQ().top().getTime();
                    
                    attack(deployment.getPlanet());
                    totalBattles++;
                }
            }
            bJedi = false;
            
            if (bWatcher) {
                ambush(deployment.getPlanet(), deployment.getTime(), deployment.getForce(), side);
                attack(deployment.getPlanet(), deployment.getTime(), deployment.getForce(), side);
            }
        }
        
        if (bMedian) {
            for (uint32_t i = 0; i < numPlanets; i++)
                if(!medians[i].isEmpty())
                    cout << "Median troops lost on planet " << i << " at time " << attackTime << " is " << medians[i].getMedian() << ".\n";
        }
    } else {
        Deployment deployment;
        uint32_t id = 0, prevTime = 0;
        uint32_t time = deployment.getTime();
        
        cin >> type >> randomSeed >> type >> numDeployments >> type >> arrivalRate;
        P2random::PR_init(ss, randomSeed, numGenerals, numPlanets, numDeployments, arrivalRate);
        
        while (ss >> time) {
            if (deployment.getTime() != prevTime) {
                if (deployment.getTime() < prevTime) {
                    cerr << "Invalid decreasing timestamp" << endl;
                    exit(1);
                }
                
                if (bMedian) {
                    for (uint32_t i = 0; i < numPlanets; i++)
                        if (!medians[i].isEmpty())
                            cout << "Median troops lost on planet " << i << " at time " << prevTime << " is " << medians[i].getMedian() << ".\n";
                };
                prevTime = deployment.getTime();
            }
            
            ss >> type;
            if (type == "JEDI") bIsJedi = true;
            else bIsJedi = false;
            
            
            uint32_t general = deployment.getGeneral();
            ss >> identifier;
            ss >> general;
            if (deployment.getGeneral() >= numGenerals) {
                cerr << "Invalid general ID" << endl;
                exit(1);
            }
            
            uint32_t planet = deployment.getPlanet();
            ss >> identifier;
            ss >> planet;
            if (deployment.getPlanet() >= numPlanets) {
                cerr << "Invalid planet ID" << endl;
                exit(1);
            }
            
            uint32_t force = deployment.getForce();
            ss >> identifier;
            ss >> force;
            if (deployment.getForce() <= 0) {
                cerr << "Invalid force sensntivity level" << endl;
                exit(1);
            }
            
            uint32_t troops = deployment.getTroops();
            ss >> identifier;
            ss >> troops;
            if (deployment.getTroops() <= 0) {
                cerr << "Invalid number of troops" << endl;
                exit(1);
            }
            
            deployment.setUnique(id);
            id++;
            
            if (bIsJedi) {
                side = "jedi";
                
                uint32_t jedi = evaluations[deployment.getGeneral()].getJedi();
                evaluations[deployment.getGeneral()].setJedi(jedi + deployment.getTroops());
                planets[deployment.getPlanet()].getJediPQ().push(deployment);
                
                bJedi = true;
                
                while ((!planets[deployment.getPlanet()].getSithPQ().empty() && !planets[deployment.getPlanet()].getJediPQ().empty()) && planets[deployment.getPlanet()].getSithPQ().top().getForce() >= planets[deployment.getPlanet()].getJediPQ().top().getForce()) {
                    
                    if (bJedi) attackTime = planets[deployment.getPlanet()].getJediPQ().top().getTime();
                    else attackTime = planets[deployment.getPlanet()].getSithPQ().top().getTime();
                    
                    attack(deployment.getPlanet());
                    totalBattles++;
                }
            } else {
                side = "sith";
                
                uint32_t sith = evaluations[deployment.getGeneral()].getSith();
                evaluations[deployment.getGeneral()].setSith(sith + deployment.getTroops());
                planets[deployment.getPlanet()].getSithPQ().push(deployment);
                
                while ((!planets[deployment.getPlanet()].getSithPQ().empty() && !planets[deployment.getPlanet()].getJediPQ().empty()) && planets[deployment.getPlanet()].getSithPQ().top().getForce() >= planets[deployment.getPlanet()].getJediPQ().top().getForce()) {
                    
                    if (bJedi) attackTime = planets[deployment.getPlanet()].getJediPQ().top().getTime();
                    else attackTime = planets[deployment.getPlanet()].getSithPQ().top().getTime();
                    
                    attack(deployment.getPlanet());
                    totalBattles++;
                }
            }
            bJedi = false;
            
            if (bWatcher) {
                ambush(deployment.getPlanet(), deployment.getTime(), deployment.getForce(), side);
                attack(deployment.getPlanet(), deployment.getTime(), deployment.getForce(), side);
            }
        }
        
        if (bMedian) {
            for (uint32_t i = 0; i < numPlanets; i++)
                if (!medians[i].isEmpty())
                    cout << "Median troops lost on planet " << i << " at time " << attackTime << " is " << medians[i].getMedian() << ".\n";
        }
    }
}

// Main Function
int main(int argc, char** argv) {
    int id = 0, op = 0;
    opterr = false;
    
    while ((op = getopt_long(argc, argv, "vmgw", ops, &id)) != -1) {
        switch (op) {
            case 'v':
                bVerbose = true;
                break;
                
            case 'm':
                bMedian = true;
                break;
                
            case 'g':
                bGeneralEvaluation = true;
                break;
                
            case 'w':
                bWatcher = true;
                break;
            
            default:
                exit(1);
                
        }
    }
    
    cout << "Deploymenting troops..." << endl;
    readFile();
    
    cout << "---End of Day---" << '\n';
    cout << "Battles: " << totalBattles << '\n';
    
    if (bGeneralEvaluation) {
        cout << "---General Evaluation---" << '\n';
        
        for (uint32_t i = 0; i < numGenerals; i++)
            cout << "General " << i << " deployed " << evaluations[i].getJedi() << " Jedi troops and " << evaluations[i].getSith() << " Sith troops, and " << (evaluations[i].getSith() + evaluations[i].getJedi()) - evaluations[i].getSurvivors() << "/" << evaluations[i].getSith() + evaluations[i].getJedi() << " troops survived." << '\n';
    } if (bWatcher) {
        cout << "---Movie Watcher---" << '\n';
        
        for (uint32_t i = 0; i < numPlanets; ++i) {
            if (ambushes[i].getTimeJedi() != -1)
                cout << "A movie watcher would enjoy an ambush on planet " << i << " with Sith at time " << ambushes[i].getTimeSith() << " and Jedi at time " << ambushes[i].getTimeJedi() << " with a force difference of " << ambushes[i].getForceSith() - ambushes[i].getForceJedi() << ".\n";
            else
                cout << "A movie watcher would enjoy an ambush on planet " << i << " with Sith at time -1 and Jedi at time -1 with a force difference of 0.\n";
            
            if (attacks[i].getTimeSith() != -1)
                cout << "A movie watcher would enjoy an attack on planet " << i << " with Jedi at time " << attacks[i].getTimeJedi() << " and Sith at time " << attacks[i].getTimeSith() << " with a force difference of " << attacks[i].getForceSith() - attacks[i].getForceJedi() << ".\n";
            else
                cout << "A movie watcher would enjoy an attack on planet " << i << " with Jedi at time -1 and Sith at time -1 with a force difference of 0.\n";
        }
    }
}

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//This is the player class that will hold the attributes for each player
class Player {
public:
    string name;
    string team;
    int age; 
    double minplayed, ppg, rpg, apg; 

    // Constructor
    Player(string name, string team, int age, double minplayed, double ppg, double rpg, double apg) 
        : name(name), team(team), age(age), minplayed(minplayed), ppg(ppg), rpg(rpg), apg(apg) {}

    // This will display the players' stats
    void display() {
        cout << "Name: " << name << "  Team: " << team << "  Age: " << age << "\nMinutes Played: " << minplayed
             << "  Points per Game: " << ppg << "\nRebounds per Game: " << rpg << "  Assists per Game: " << apg << "\n\n";
    }
};

// This class will hold the vector of all the players and the functions for the menu
class PlayerDatabase {
public:
    // This function loads the data in from the text file with the players' information 
    void loadFromFile() {
        ifstream file("csc211midtdata.txt");
        if (!file) {
            cout << "Error opening file!\n";
            return;
        }
        string name, team;
        int age; 
        double minplayed, ppg, rpg, apg;
        while (file >> name >> team >> age >> minplayed >> ppg >> rpg >> apg) {
            players.push_back(Player(name, team, age, minplayed, ppg, rpg, apg));
        }
        file.close();
    }

    // This function prints all the players with their respective stats
    void printAllPlayers() {
        for (int i = 0; i < players.size(); i++) {
            players[i].display();
        }
    }

    // This funtion prints the stats of a user inputted player
    void printPlayerStats(string playerName) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i].name == playerName) {
                players[i].display();
                return;
            }
        }
        cout << "Player not found!\n";
    }

    // This function displays the stats of the players of a user inputted team
    void printTeamStats(string teamName) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i].team == teamName) {
                players[i].display();
            }
        }
    }

    // This function updates the stats of a user inputted player
    void updatePlayerStats(string playerName, int age, double minplayed, double ppg, double rpg, double apg) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i].name == playerName) {
                players[i].age = age;
                players[i].minplayed = minplayed;
                players[i].ppg = ppg;
                players[i].rpg = rpg;
                players[i].apg = apg;
                cout << "Stats updated successfully!\n";
                return;
            }
        }
        cout << "Player not found!\n";
    }

    // This functions inserts a new player with stats inputted by the user
    void insertPlayer(string name, string team, int age, double minplayed, double ppg, double rpg, double apg) {
        players.push_back(Player(name, team, age, minplayed, ppg, rpg, apg));
        cout << "Player added successfully!\n";
    }

    // This funuction outputs the current data in the players vector in a seperate file called "output.txt"
    void exportToFile() {
        ofstream file("output.txt");
        for (int i = 0; i < players.size(); i++) {
            file << players[i].name << " " << players[i].team << " " << players[i].age << " " << players[i].minplayed << " "
                 << players[i].ppg << " " << players[i].rpg << " " << players[i].apg << endl;
        }
        file.close();
        cout << "Data exported successfully!\n";
    }
    private:
    vector<Player> players;
};

int main() {
    PlayerDatabase db;
    db.loadFromFile();

//Here is the do while loop that will loop with the while statement below is true
//Within the loop is a switch case statement to format the menu 
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Print all players and statistics\n";
        cout << "2. Print statistics for a specific player\n";
        cout << "3. Print all data for a specific team\n";
        cout << "4. Update a player's statistics\n";
        cout << "5. Insert a new player\n";
        cout << "6. Export data to file\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string name, team;
        int age; 
        double minplayed, ppg, rpg, apg;
        switch (choice) {
    //If the user inputs 1 then it'll print all stats for a specific player by invoking the printAllPlayers function 
        case 1:
            cout << endl;
            db.printAllPlayers();
            break;
    //If the user inputs 2 then a user inputted player's stats wull be displayed by invoking the printPlayerStats function
        case 2:
            cout << endl;
            cout << "Enter player name with the first name capitalized, an underscore, then the last name capitalized:\n";
            cin >> name;
            db.printPlayerStats(name);
            break;
    //If the user inputs 3 then the function below will print the players of that team and their respective stats 
        case 3:
            cout << endl;
            cout << "Enter team name capitalized: ";
            cin >> team;
            db.printTeamStats(team);
            break;
    //If user inputs 4, then the program will ask for inputs of name, team, and updated stats of the player and the info will be updated in the vector
        case 4:
            cout << endl;
            cout << "Enter player name with the first name capitalized, an underscore, then the last name capitalized:\n";
            cin >> name;
            cout << "Enter stats in the following order with a space in between(age, avg minutes played, avg points per game, avg rebounds per game, avg assists per game): ";
            cin >> age >> minplayed >> ppg >> rpg >> apg;
            db.updatePlayerStats(name, age, minplayed, ppg, rpg, apg);
            break;
    //If user inputs 5, then the user is asked for the team name and stats of the new player who will be added to the vector storing all the players
        case 5:
            cout << endl;
            cout << "Enter player name with the first name capitalized, an underscore, then the last name capitalized:\n";
            cin >> name;
            cout << "Enter team name: ";
            cin >> team;
            cout << "Enter stats in the following order with a space in between (age, avg minutes played, avg points per game, avg rebounds per game, avg assists per game): ";
            cin >> age >> minplayed >> ppg >> rpg >> apg;
            db.insertPlayer(name, team, age, minplayed, ppg, rpg, apg);
            break;
    //If user inputs 6, the players and their respective stats in vector of object db
        case 6:
            db.exportToFile();
            break;
    //If user inputs 7 the program is terminated 
        case 7:
            cout << endl;
            cout << "Exiting program...\n";
            break;
        //This will make sure that when an unwanted value is inputted the loop will set to default and output the message and continue
        default:
            cout << endl;
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
struct Team {
    string name;
    string localTown;
    string stadium;
};
struct Fixture {
    string homeTeam;
    string awayTeam;
    string homeStadium;
    string localTown;
    int leg;
    int weekend;
};
// prototypes
void importTeam(const string &filename, vector<Team> &teams);
void genFix(const vector<Team> &teams, vector<Fixture> &fixtures);
void disFix(const vector<Fixture> &fixtures);
void saveFix(const string &filename, const vector<Fixture> &fixtures);

// Menu system
int main() {
    vector<Team> teams;
    vector<Fixture> fixtures;
    int choice;

    do {
        cout << "---- ABC Premier League Fixture Generator ----" << endl;
        cout << "1. Import teams from CSV" << endl;
        cout << "2. Generate match fixtures" << endl;
        cout << "3. Display match fixtures" << endl;
        cout << "4. Save fixtures to CSV" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                importTeam("teams_csvFile.csv", teams);
            break;
            case 2:
                genFix(teams, fixtures);
            break;
            case 3:
                disFix(fixtures);
            break;
            case 4:
                saveFix("ABC_league_fixtures.csv", fixtures);
            break;
            case 0:
                cout << "Exiting..." << endl;
            break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
// Function to import teams from CSV file
void importTeam(const string &filename, vector<Team> &teams) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        Team team;
        // Assume the CSV is formatted as: Team Name, Local Town, Stadium
        size_t part1 = line.find(',');
        size_t part2 = line.find(',', part1 + 1);
        team.name = line.substr(0, part1);
        team.localTown = line.substr(part1 + 1, part2 - part1 - 1);
        team.stadium = line.substr(part2 + 1);
        teams.push_back(team);
    }
    file.close();
    cout << "Teams imported successfully!" << endl;
}

// Function to generate match fixtures
void genFix(const vector<Team> &teams, vector<Fixture> &fixtures) {
    fixtures.clear();
    int weekend = 1;
    int matchesPerWeekend = 0;

    // First Leg
    cout << "Generating Leg 1 fixtures..." << endl;
    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            // Home game (Leg 1)
            Fixture fixture1 = {teams[i].name, teams[j].name, teams[i].stadium, teams[i].localTown, 1, weekend};
            fixtures.push_back(fixture1);

            // switch to the next one if 2 matches are scheduled
            matchesPerWeekend += 2;
            if (matchesPerWeekend >= 4) {
                weekend += 1;
                matchesPerWeekend = 0;
            }
        }
    }

    // Reset
    matchesPerWeekend = 0;
    weekend += 1; // Start Leg 2 matches on a new set of weekends

    // Second Leg
    cout << "Generating Leg 2 fixtures..." << endl;
    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            // Away game (Leg 2)
            Fixture fixture2 = {teams[j].name, teams[i].name, teams[j].stadium, teams[j].localTown, 2, weekend};
            fixtures.push_back(fixture2);

            // switch to the next one if 2 matches are scheduled
            matchesPerWeekend += 2;
            if (matchesPerWeekend >= 4) {
                weekend += 1;
                matchesPerWeekend = 0;
            }
        }
    }
    cout << "Fixtures generated successfully!" << endl;
}

// Function to display match fixtures
void disFix(const vector<Fixture> &fixtures) {
    for (const auto &fixture : fixtures) {
        cout << "Weekend " << fixture.weekend << ": "
             << fixture.homeTeam << " vs " << fixture.awayTeam
             << " at " << fixture.homeStadium << " (" << fixture.localTown << ")"
             << " - Leg " << fixture.leg << endl;
    }
}

// Function to save fixtures to a CSV file
void saveFix(const string &filename, const vector<Fixture> &fixtures) {
    ofstream file(filename);

    // Write the CSV header
    file << "Weekend,Home Team,Away Team,Stadium,Local Town,Leg" << endl;

    // Write each fixture to the CSV file and print for debugging
    for (const auto &fixture : fixtures) {
        cout << "Saving: Weekend " << fixture.weekend << ", ";
        cout << fixture.homeTeam << " vs " << fixture.awayTeam;
        cout << " at " << fixture.homeStadium << " (" << fixture.localTown << ")";
        cout << " - Leg " << fixture.leg << endl;

        file << fixture.weekend << ",";
        file << fixture.homeTeam << ",";
        file << fixture.awayTeam << ",";
        file << fixture.homeStadium << ",";
        file << fixture.localTown << ",";
        file << fixture.leg << endl;
    }

    file.close();
    cout << "Fixtures saved to " << filename << " successfully!" << endl;
}

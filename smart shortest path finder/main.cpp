#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

const int V = 6;
const int INF = 1000000000;

string locations[V] = {
    "Railway Station",
    "Bus Station",
    "City Hospital",
    "University",
    "Shopping Mall",
    "Airport"
};

int graph[V][V] = {
    {0,   4,  10, INF, INF, INF},
    {4,   0,   3,   5, INF, INF},
    {10,  3,   0,   4,   6, INF},
    {INF, 5,   4,   0,   2,   8},
    {INF, INF, 6,   2,   0,   5},
    {INF, INF, INF, 8,   5,   0}
};

int dist[V][V];
int nextNode[V][V];

// Initialize and calculate shortest distances.
void floydWarshall() {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];

            if (graph[i][j] != INF && i != j) {
                nextNode[i][j] = j;
            } else {
                nextNode[i][j] = -1;
            }
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {

                if (dist[i][k] != INF &&
                    dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] =
                        dist[i][k] + dist[k][j];

                    nextNode[i][j] = nextNode[i][k];
                }
            }
        }
    }
}

// Display the direct-distance matrix.
void displayDirectMatrix() {
    cout << "\nDIRECT DISTANCE MATRIX (km)\n\n";

    cout << setw(18) << "Location";
    for (int j = 0; j < V; j++) {
        cout << setw(12) << ("L" + to_string(j));
    }
    cout << '\n';

    for (int i = 0; i < V; i++) {
        cout << setw(18) << locations[i];

        for (int j = 0; j < V; j++) {
            if (graph[i][j] == INF) {
                cout << setw(12) << "-";
            } else {
                cout << setw(12) << graph[i][j];
            }
        }
        cout << '\n';
    }

    cout << "\nL0 = Railway Station"
         << "\nL1 = Bus Station"
         << "\nL2 = City Hospital"
         << "\nL3 = University"
         << "\nL4 = Shopping Mall"
         << "\nL5 = Airport\n";
}

// Display the shortest-distance matrix.
void displayShortestMatrix() {
    cout << "\nALL-PAIRS SHORTEST DISTANCE MATRIX (km)\n\n";

    cout << setw(18) << "Location";

    for (int j = 0; j < V; j++) {
        cout << setw(12) << ("L" + to_string(j));
    }
    cout << '\n';

    for (int i = 0; i < V; i++) {
        cout << setw(18) << locations[i];

        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                cout << setw(12) << "INF";
            } else {
                cout << setw(12) << dist[i][j];
            }
        }
        cout << '\n';
    }
}

// Display the route and its total distance.
void findShortestPath() {
    int source, destination;

    cout << "\nAvailable Locations:\n";

    for (int i = 0; i < V; i++) {
        cout << i << ". " << locations[i] << '\n';
    }

    cout << "\nEnter source location number: ";
    if (!(cin >> source)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "Enter destination location number: ";
    if (!(cin >> destination)) {
        cout << "Invalid input.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (source < 0 || source >= V ||
        destination < 0 || destination >= V) {
        cout << "Invalid location number.\n";
        return;
    }

    if (dist[source][destination] == INF) {
        cout << "\nNo route exists between these locations.\n";
        return;
    }

    cout << "\nShortest Route:\n";
    cout << locations[source];

    int current = source;
    int steps = 0;

    while (current != destination) {
        current = nextNode[current][destination];

        if (current == -1 || ++steps > V) {
            cout << "\nUnable to reconstruct route.\n";
            return;
        }

        cout << " -> " << locations[current];
    }

    cout << "\n\nTotal Distance: "
         << dist[source][destination] << " km\n";
}

int main() {
    floydWarshall();

    int choice;

    do {
        cout << "\n====================================\n";
        cout << "   SMART SHORTEST PATH FINDER\n";
        cout << "====================================\n";
        cout << "1. Display City Locations\n";
        cout << "2. Display Direct Distance Matrix\n";
        cout << "3. Display Shortest Distance Matrix\n";
        cout << "4. Find Shortest Path\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\nCITY LOCATIONS\n";
                for (int i = 0; i < V; i++) {
                    cout << i << ". " << locations[i] << '\n';
                }
                break;

            case 2:
                displayDirectMatrix();
                break;

            case 3:
                displayShortestMatrix();
                break;

            case 4:
                findShortestPath();
                break;

            case 5:
                cout << "\nThank you for using Smart Shortest Path Finder!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
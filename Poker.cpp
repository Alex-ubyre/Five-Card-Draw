#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <map>
using namespace std;

string suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

struct Card {
    string rank;
    string suit;
};

vector<Card> createDeck() {
    vector<Card> deck;
    for (const string& suit : suits) {
        for (const string& rank : ranks) {
            deck.push_back({rank, suit});
        }
    }
    return deck;
}

void shuffleDeck(vector<Card>& deck) {
    srand(time(0));
    random_shuffle(deck.begin(), deck.end());
}

void printHand(const vector<Card>& hand) {
    for (const auto& card : hand) {
        cout << card.rank << " of " << card.suit << endl;
    }
}

vector<Card> dealHand(vector<Card>& deck, int count = 5) {
    vector<Card> hand(deck.begin(), deck.begin() + count);
    deck.erase(deck.begin(), deck.begin() + count);
    return hand;
}

void replaceCards(vector<Card>& hand, vector<Card>& deck) {
    cout << "Enter card positions (1-5) to replace (e.g., 1 3 5), or 0 to keep all: ";
    string input;
    cin.ignore();
    getline(cin, input);

    istringstream iss(input);
    int pos;
    while (iss >> pos) {
        if (pos >= 1 && pos <= 5) {
            hand[pos - 1] = deck.back();
            deck.pop_back();
        }
    }
}

int getCardValue(const string& rank) {
    if (rank == "J") return 11;
    if (rank == "Q") return 12;
    if (rank == "K") return 13;
    if (rank == "A") return 14;
    return stoi(rank);
}

// Simple hand evaluator: returns number of pairs (for demo purposes)
int evaluateHand(const vector<Card>& hand) {
    map<string, int> freq;
    for (const auto& card : hand) {
        freq[card.rank]++;
    }

    int pairs = 0;
    for (const auto& [rank, count] : freq) {
        if (count == 2) pairs++;
    }

    return pairs;  // returns number of pairs only
}

int main() {
    vector<Card> deck = createDeck();
    shuffleDeck(deck);

    vector<Card> playerHand = dealHand(deck);
    vector<Card> computerHand = dealHand(deck);

    cout << "Your hand:\n";
    printHand(playerHand);

    replaceCards(playerHand, deck);

    cout << "\nYour final hand:\n";
    printHand(playerHand);

    cout << "\nComputer's hand:\n";
    printHand(computerHand);

    int playerScore = evaluateHand(playerHand);
    int computerScore = evaluateHand(computerHand);

    cout << "\nResult: ";
    if (playerScore > computerScore)
        cout << "You win!\n";
    else if (playerScore < computerScore)
        cout << "Computer wins!\n";
    else
        cout << "It's a tie!\n";

    return 0;
}

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

int playerMoney = 1000; // จำนวนเงินเริ่มต้นของผู้เล่น
int bet, cardScores;

int betAmount(int bet, int& playerMoney) {
    while (true) {
        if (cin.fail()) {
            cout << "Plese enter the number" << endl;
            cin.clear(); // ล้าง error flag
            cin.ignore(1000, '\n'); // ล้างข้อมูลที่ค้างใน buffer
        } else if (bet <= 0) {
            cout << ">0" << endl;
        } else if (bet > playerMoney) {
            cout << "Deposit" << endl;
        } else {
            break; // หากเดิมพันถูกต้อง
        }
    }
    cout << "Bet: " << bet << " Baht" << endl;
    playerMoney -= bet; // หักเงินจากผู้เล่น
    return bet;
}

vector<string> initializeDeck() {
    string suits[] = {"D", "S", "H", "C"};
    string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K","A", "2", "3", "4", "5", "6", "7", "8", 
    "9", "10", "J", "Q", "K","A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K","A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    vector<string> deck;
    for (string suit : suits) {
        for (string rank : ranks) {
            deck.push_back(rank + suit);
        }
    }
    return deck;
}

void shuffleDeck(vector<string>& deck) {
    random_shuffle(deck.begin(), deck.end());
}

string drawCard(vector<string>& deck) {
    if (deck.empty()) {
        return "No more cards in the deck!";
    }
    string drawnCard = deck.back();
    deck.pop_back();
    return drawnCard;
}

int getCardScore(const string& card) {
    char k = card[0];
    if (k == 'J' || k == 'Q' || k == 'K' || k == '1') {
        return 10;
    } else if (k == 'A') {
        return 11;
    } else {
        return stoi(string(1, k));
    }
}

void playHand(vector<string>& deck, int& handScore) {
    int action;
    do {
        cout << "(1) Hit , (2) Stand : ";
        cin >> action;
        if (action == 1) {
            string newCard = drawCard(deck);
            handScore += getCardScore(newCard);
            cout << "New card: " << newCard << " (" << handScore << ")" << endl;
            if (handScore > 21) {
                cout << "Busted!" << endl;
                break;
            }
        }
    } while (action != 2);
}

void splitHand(vector<string>& deck, const string& card, int& playerMoney, int bet) {
    if (playerMoney >= bet) {
        playerMoney -= bet; // หักเงินเดิมพันสำหรับมือที่สอง
        string newCard1 = drawCard(deck);
        string newCard2 = drawCard(deck);
        cout << "Split hand: " << card << " + " << newCard1 << " and " << card << " + " << newCard2 << endl;
        
        int hand1Score = getCardScore(card) + getCardScore(newCard1);
        int hand2Score = getCardScore(card) + getCardScore(newCard2);
        
        cout << "Playing first hand..." << endl;
        playHand(deck, hand1Score);
        
        cout << "Playing second hand..." << endl;
        playHand(deck, hand2Score);
    } else {
        cout << "Not enough money to split." << endl;
    }
}

int doubleDown(vector<string>& deck, int& playerScore, int& playerMoney, int bet) {
    if (playerMoney >= bet) {
        playerMoney -= bet; // เพิ่มเดิมพันเป็นสองเท่า
        string newCard = drawCard(deck);
        playerScore += getCardScore(newCard);
        cout << "Double down! Drawn card: " << newCard << " (" << playerScore << ")" << endl;
        if (playerScore > 21) {
            cout << "Busted! You lose." << endl;
        }
        return playerScore;
    }
    cout << "Not enough money to double down." << endl;
    return playerScore;
}
void Calulate(int scoreplayer,int scoredealer){
    if(scoreplayer > 21 ){
        cout  << "Busted! You lose." << endl;
    }else if((21-scoreplayer) < (21-scoredealer)){
        cout << "Player win!\n";
    }else if((21-scoreplayer) > (21-scoredealer)){
        cout << "Dealer win!\n";
    }
}

bool Askplayagain(){
    char choice;
    cout << "Continue?(Y/N): ";
    cin >> choice;
    return(choice == 'Y');
}

int main() {
    int playerAction;
    bool playing = true;
    srand(time(0));
    vector<string> deck = initializeDeck();
    shuffleDeck(deck);
    string playerCard1 = drawCard(deck);
    string playerCard2 = drawCard(deck);
    string dealerCard1 = drawCard(deck);
    string dealerCard2 = drawCard(deck);
    while (playing)
    {
        cout << "Money remain: " << playerMoney << " Baht" << endl;
        cout << "Bet: ";
        cin >> bet;
        bet = betAmount(bet, playerMoney);
        cout << "Dealer card: " << dealerCard1 << " (One card is hidden) (" << getCardScore(dealerCard1) << ")" << endl;
        cout << "Player card: " << playerCard1 << " and " << playerCard2;
        int scorePlayer = getCardScore(playerCard1) + getCardScore(playerCard2);
        int scoreDealer =  getCardScore(dealerCard1) +  getCardScore(dealerCard2);
        cout << " (" << scorePlayer << ")" << endl;
        do {
            cout << "(1) Hit , (2) Stand , ";
            if (playerCard1 == playerCard2) cout << "(3) Split , ";
            if (playerMoney >= bet) cout << "(4) Double down , ";
            cout << "Select : ";
            cin >> playerAction;
        } while (playerAction != 1 && playerAction != 2 && playerAction != 3 && playerAction != 4);
        if (playerAction == 1) {
            
            do {
                string playerCard = drawCard(deck);
                scorePlayer += getCardScore(playerCard);
                cout << "New card: " << playerCard << " (" << scorePlayer << ")" << endl;
                if (scorePlayer > 21) {
                    //cout << "Busted! You lose." << endl;
                    break;
                }
                cout << "(1) Hit , (2) Stand : ";
                cin >> playerAction;
            } while (playerAction != 2);
        
        } else if (playerAction == 2) {
            
        } else if (playerAction == 3) {
            splitHand(deck, playerCard1, playerMoney, bet);
        } else if (playerAction == 4) {
            scorePlayer = doubleDown(deck, scorePlayer, playerMoney, bet);
        }
        cout <<"Dealer's card :"<< dealerCard1 <<" and "<< dealerCard2 << " (" << scoreDealer << ")\n";
        Calulate(scorePlayer,scoreDealer);
        playing = Askplayagain();
        }
    
}

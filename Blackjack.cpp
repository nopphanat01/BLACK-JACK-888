#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

int playerMoney = 1000; // จำนวนเงินเริ่มต้นของผู้เล่น
int bet;

int betAmount(int playerMoney) {
    do {
        cout << "Enter your bet: ";
        cin >> bet;

        if (cin.fail()) {
            cout << "Please enter a number!\n";
            cin.clear(); // ล้าง error flag
            cin.ignore(1000, '\n'); // ล้าง buffer
        } else if (bet <= 0) {
            cout << "Bet amount must be greater than 0!\n";
        } else if (bet > playerMoney) {
            cout << "Not enough balance! Your balance: " << playerMoney << " Baht\n";
        } else {
            break; // หากเดิมพันถูกต้อง
        }
    } while (true);

    cout << "You bet: " << bet << " Baht\n\n";
    return bet;
}

vector<string> initializeDeck() {
    string suits[] = {"D", "S", "H", "C"};
    string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    vector<string> deck;
    for (string suit : suits) {
        for (string rank : ranks) {
            deck.push_back(rank + suit);
        }
    }
    return deck;
}

void shuffleDeck(vector<string>& deck) {
    srand(time(0));
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
        return 11; // เริ่มต้นนับ Ace เป็น 11
    } else {
        return stoi(string(1, k)); // ถ้าเป็นไพ่ตัวเลข
    }
}

int calculateTotalScore(vector<string>& hand) {
    int totalScore = 0;
    int aceCount = 0;

    // คำนวณคะแนนรวมของไพ่ในมือ
    for (const string& card : hand) {
        totalScore += getCardScore(card);
        if (card[0] == 'A') {
            aceCount++;
        }
    }

    // ปรับ Ace เป็น 1 หากคะแนนรวมเกิน 21
    while (totalScore > 21 && aceCount > 0) {
        totalScore -= 10; // ลดคะแนน 10 สำหรับแต่ละ Ace ที่จะนับเป็น 1
        aceCount--;
    }

    return totalScore;
}


void printCard(vector<string>& hand) { // ปริ้นการ์ดบนมือ
    for (const string& card : hand) {
        cout << card << " ";
    }
}

vector<string> showhand(string card) {  // import การ์ดเข้า vector มือ
    vector<string> hand;
    hand.push_back(card);
    return hand;
}

void Calulate(int scorePlayer, int scoredealer) {
    if (scorePlayer > 21) {
        cout << "Busted! You lose this hand." << endl;
        playerMoney -= bet;  // Deduct bet for bust
    }
    else if (scoredealer > 21) {
        cout << "Dealer busted! Player wins this hand!" << endl;
        playerMoney += bet;  // Player wins if dealer busts
    }
    else if (scorePlayer > scoredealer) {
        cout << "Player wins this hand!" << endl;
        playerMoney += bet;  // Player wins if their score is greater
    }
    else if (scoredealer > scorePlayer) {
        cout << "Dealer wins this hand!" << endl;
        playerMoney -= bet;  // Dealer wins if their score is greater
    }
    else {
        cout << "It's a tie this hand!" << endl;
        // No money changes for a tie
    }
}

// ฟังก์ชันสำหรับให้ผู้เล่นตัดสินใจว่าจะเล่นต่อหรือไม่
bool Askplayagain() {
    char choice;
    cout << "Do you want to play again? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        return true;
    } else {
        return false;
    }
}

int playerdecision(vector<string>& deck, vector<string>& hand, int x, int& score, int& money, int scoredealer) {
    if (x == 1) { // Hit
        string newCard = drawCard(deck);
        hand.push_back(newCard);
        score += getCardScore(newCard);
        cout << "Your hand: ";
        printCard(hand);
        cout << "(" << score << ")\n";
        return score;
    }
    else if (x == 2) { // Stand
        cout << "Your hand: ";
        printCard(hand);
        cout << "(" << score << ")\n";
        return score;
    }
    else if (x == 3) { // Double down
        bet *= 2;
        money -= bet / 2;
        string newCard = drawCard(deck);
        score += getCardScore(newCard);
        hand.push_back(newCard);
        cout << "Your hand: ";
        printCard(hand);
        cout << " (" << score << ")\n";
        return score;
    }
    else if (x == 4) { // Split
        vector<string> hand1 = { hand[0], drawCard(deck) };
        vector<string> hand2 = { hand[1], drawCard(deck) };
        int bet2 = bet;
        money -= bet2;

        // Play the first hand
        int score1 = calculateTotalScore(hand1);
        cout << "Hand 1: ";
        printCard(hand1);
        cout << " (" << score1 << ")\n";

        while (score1 < 21) {
            int action;
            cout << "(1) Hit, (2) Stand: ";
            cin >> action;
            if (action == 1) {
                hand1.push_back(drawCard(deck));
                score1 += getCardScore(hand1.back());
                cout << "Hand 1: ";
                printCard(hand1);
                cout << "(" << score1 << ")\n";
            } else break;
        }

        // Play the second hand
        int score2 = calculateTotalScore(hand2);
        cout << "Hand 2: ";
        printCard(hand2);
        cout << " (" << score2 << ")\n";

        while (score2 < 21) {
            int action;
            cout << "(1) Hit, (2) Stand: ";
            cin >> action;
            if (action == 1) {
                hand2.push_back(drawCard(deck));
                score2 += getCardScore(hand2.back());
                cout << "Hand 2: ";
                printCard(hand2);
                cout << "(" << score2 << ")\n";
            } else break;
        }

        // Compare both hands with the dealer
        Calulate(score1, scoredealer);
        Calulate(score2, scoredealer);
    } else {
        cout << "(1) Hit  (2) Stand  ";
        if (score < 21) { cout << "(3) Double down  "; }
        if (hand[0] == hand[1]) cout << "(4) Split"; 
        cout << "\nSelect: ";
        cin >> x;
        return playerdecision(deck, hand, x, score, money, scoredealer); // Recursive call
    }
    return score;
}

int main() {
    int playerAction;
    bool playing = true;
    int cardCount = 2;
    vector<string> deck = initializeDeck();
    
    while (playing) {
        // bet
        cout << "Money remain: " << playerMoney << " Baht" << endl;
        betAmount(playerMoney);
        
        // shuffle deck
        shuffleDeck(deck);

        // player hand
        string playerCard1 = drawCard(deck);
        string playerCard2 = drawCard(deck); // ประกาศ playerCard2 ที่นี่
        vector<string> hand = showhand(playerCard1); 
        hand.push_back(playerCard2);

        // dealer hand
        string dealerCard1 = drawCard(deck);
        string dealerCard2 = drawCard(deck);
        vector<string> dealerhand = showhand(dealerCard1);
        dealerhand.push_back(dealerCard2);

        // show cards
        cout << "Dealer card: " << dealerCard1 << " (One card is hidden) (" << getCardScore(dealerCard1) << ")" << endl;
        int scorePlayer = calculateTotalScore(hand);
        cout << "Your hand: ";
        printCard(hand);
        cout << " (" << scorePlayer << ")" << endl;

        // player decision
        cout << "(1) Hit  (2) Stand  ";
        if (scorePlayer < 21) { cout << "(3) Double down  "; }
        if (playerCard1[0] == playerCard2[0]) cout << "(4) Split"; // ใช้ playerCard2
        cout << "\nSelect : ";
        cin >> playerAction;
        cout << endl;

        // dealer's score
        int scoredealer = calculateTotalScore(dealerhand);
        cout << "Dealer card: "; 
        printCard(dealerhand); 
        cout << " (" << scoredealer << ")" << endl;

        // player decision
        playerdecision(deck, hand, playerAction, scorePlayer, playerMoney,scoredealer);

        // decide win/loss
        Calulate(scorePlayer, scoredealer);

        // dealer action
        while (scoredealer < 17 && cardCount < 5) { 
            dealerhand.push_back(drawCard(deck));
            scoredealer += getCardScore(dealerhand.back());
            cardCount++; 
        }

        playing = Askplayagain(); // เรียกฟังก์ชันถามว่าต้องการเล่นต่อไหม
    }

    return 0;
}

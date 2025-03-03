#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;

bool hasPotion = true ; // ผู้เล่นเริ่มต้นมีน้ำยา 1 ครั้ง
const double potionChance = 0.75;

// โครงสร้าง Player และฟังก์ชันที่เกี่ยวข้อง
struct Player {
    string name;
    int money;
    int score;
    int gamesPlayed; // จำนวนเกมที่เล่น
    int highScore;   // คะแนนสูงสุด
};

void saveGame(const string& filename, const Player& player) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << player.name << endl;
        outFile << player.money << endl;
        outFile << player.score << endl;
        outFile << player.gamesPlayed << endl;
        outFile << player.highScore << endl;
        outFile.close();
        //cout << "Game is saved\n";
    } else {
        cout << "Save maidai\n";
    }
}

bool loadGame(const string& filename, Player& player) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        getline(inFile, player.name);
        inFile >> player.money;
        inFile >> player.score;
        inFile >> player.gamesPlayed;
        inFile >> player.highScore;
        inFile.close();
        cout << "Load\n";
        return true;
    } else {
        cout << "Cant load\n";
        return false;
    }
}

void updateStatistics(Player& player) {
    player.gamesPlayed++;
    if (player.money > player.highScore) {
        player.highScore = player.money;
    }
}

void showStatistics(const Player& player) {
    cout << "Your statics\n";
    cout << "Money remain: $" << player.money << endl;
   // cout << "Recent score: " << player.score << endl;
    cout << "Game played: " << player.gamesPlayed << endl;
    cout << "Highest money: $" << player.highScore << endl;
}

// ฟังก์ชันเดิมของเกม Blackjack
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
    random_device rd;
    mt19937 g(rd());
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

    for (const string& card : hand) {
        totalScore += getCardScore(card);
        if (card[0] == 'A') {
            aceCount++;
        }
    }

    while (totalScore > 21 && aceCount > 0) {
        totalScore -= 10; // ลดคะแนน 10 สำหรับแต่ละ Ace ที่จะนับเป็น 1
        aceCount--;
    }

    return totalScore;
}

void printCard(vector<string>& hand) {
    for (const string& card : hand) {
        cout << card << " ";
    }
}

vector<string> showhand(string card) {
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
void Calculatesplite(int scoreP , int scored){
    if (scoreP > 21) {
        cout << "Busted! You lose ";
        playerMoney -= bet;  // Deduct bet for bust
    }
    else if (scored > 21) {
        cout << "Dealer busted! Player wins ";
        playerMoney += bet;  // Player wins if dealer busts
    }
    else if (scoreP > scored) {
        cout << "Player wins ";
        playerMoney += bet;  // Player wins if their score is greater
    }
    else if (scored > scoreP) {
        cout << "Dealer wins your ";
        playerMoney -= bet;  // Dealer wins if their score is greater
    }
    else {
        cout << "It's a tie ";
        // No money changes for a tie
    }
}

bool Askplayagain() {
    string choice;
    cout << "Do you want to play again? (y/n): ";
    cin >> choice;
    if (choice == "y" || choice == "Y") {
        return true;
    } else if (choice == "n" || choice == "N") {
        return false;
    } else {
        cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        return Askplayagain();
    }
}

bool usePotion(vector<string>& hand, vector<string>& deck, int& score) {
    if (hand.empty()) return false; // ถ้ามือว่างไม่สามารถใช้ได้

    // ลบการ์ดใบล่าสุด
    string removedCard = hand.back();
    hand.pop_back();
    score -= getCardScore(removedCard);

    // จั่วการ์ดใหม่
    string newCard = drawCard(deck);
    hand.push_back(newCard);
    score += getCardScore(newCard);

    // ตรวจสอบและปรับแต้ม A หากคะแนนเกิน 21
    bool aceAdjusted = false;
    if (score > 21) {
        for (string& card : hand) {
            if (card[0] == 'A' && getCardScore(card) == 11) { // หาก A ถูกนับเป็น 11
                score -= 10; // ปรับ A เป็น 1
                aceAdjusted = true;
                break;
            }
        }
    }

    cout << "You used a magic potion! Removed " << removedCard << " and drew " << newCard << ".\n";
    cout << "Your new hand: ";
    printCard(hand);
    cout << " (" << score << ")\n";

    return true; // ใช้ Potion สำเร็จ
}

void checkAndUsePotion(vector<string>& hand, vector<string>& deck, int& score) {
    if (hasPotion && score > 21) {
        cout << "Your score is over 21! Do you want to use a magic potion? (y/n): ";
        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            // สุ่มโอกาส 75% ที่จะใช้ได้สำเร็จ
            double randomValue = (double)rand() / RAND_MAX;
            if (randomValue <= potionChance) {
                if (usePotion(hand, deck, score)) {
                    // ตรวจสอบคะแนนหลังใช้ Potion
                    if (score <= 21) {
                        hasPotion = false; // ใช้ Potion สำเร็จและคะแนนไม่เกิน 21
                    } else {
                        cout << "The potion was used, but your score is still over 21. You still have the potion.\n";
                        // ไม่ตั้งค่า hasPotion = false; เพราะ Potion ยังคงมีอยู่
                    }
                }
            } else {
                cout << "The potion failed! You still have potion.\n";
                // ไม่ตั้งค่า hasPotion = false; เพราะ Potion ยังคงมีอยู่
            }
        }
    }
}

int playerdecision(vector<string>& deck, vector<string>& hand,vector<string>& dealerhand, int x, int& score, int& money, int scoredealer) {
    char s1 = hand[0][0], s2 = hand[1][0];
    if (x == 1) {
        bool aceAdjusted = false;
        while (true) {
            string newCard = drawCard(deck);
            if(newCard == "No more cards in the deck!") {
                cout << "No more cards in the deck!\n";
                return score;
            }
            hand.push_back(newCard);
            score += getCardScore(newCard);

            if (score > 21 && !aceAdjusted) {
                for (string& card : hand) {
                    if (card[0] == 'A' && getCardScore(card) == 11) {
                        score -= 10;
                        aceAdjusted = true;
                        break;
                    }
                }
            }

            cout << "Your hand: ";
            printCard(hand);
            cout << " (" << score << ")\n";
            if (score > 21) {
                checkAndUsePotion(hand, deck, score);
                if (score <= 21) {
                    cout << "\nYour new score: " << score << "\n";
                    break;
                } else {
                    cout << "Your score is still over 21.\n";
                    bool hasPotion = true;
                }
            }

            if (score >= 21) {return score;}
            while(true){
                cout << "(1) Hit  (2) Stand\nSelect: ";
                cin >> x;
                if (x == 2 || x == 1) break;
            }
            if (x == 2) break;
        }
    }
    else if (x == 2) { // Stand
        cout <<"-----------------------------------------------------------------------------\n";
        cout << "Dealer card: "; 
        printCard(dealerhand); 
        bool aceAdjusted = false;
        if (scoredealer > 21 && !aceAdjusted) {
            for (string& card : dealerhand) {
                if (card[0] == 'A') {
                    scoredealer -= 10;
                    aceAdjusted = true;
                    break;
                }
            }
        }
        cout << " (" << scoredealer << ")" << endl;
        cout << "Your hand: ";
        printCard(hand);
        cout << " (" << score << ")" << endl;

        Calulate(score, scoredealer);
        cout <<"-----------------------------------------------------------------------------\n";
    }
    else if (x == 3 && score < 21) { // Double down
        bet *= 2;
        bool aceAdjusted = false;
        string newCard = drawCard(deck);
        hand.push_back(newCard);
        score += getCardScore(newCard);
            if (score > 21 && !aceAdjusted) {
                for (string& card : hand) {
                    if (card[0] == 'A') {
                        score -= 10;
                        aceAdjusted = true;
                        break;
                    }
                }
            }
        cout <<"-----------------------------------------------------------------------------\n";
        cout << "Dealer card: "; 
        printCard(dealerhand); 
        if (scoredealer > 21 && !aceAdjusted) {
            for (string& card : dealerhand) {
                if (card[0] == 'A') {
                    scoredealer -= 10;
                    aceAdjusted = true;
                    break;
                }
            }
        }
        cout << " (" << scoredealer << ")" << endl;

        cout << "Your hand: ";
        printCard(hand);
        cout << " (" << score << ")" << endl;

        Calulate(score, scoredealer);
        cout <<"-----------------------------------------------------------------------------\n";
    }
    else if (x == 4 && s1 == s2) { // Split
        vector<string> hand1 = { hand[0], drawCard(deck) };
        vector<string> hand2 = { hand[1], drawCard(deck) };
        int bet2 = bet;
        

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

                bool aceAdjusted = false;
                while (true) {
                    string newCard = drawCard(deck);
                    hand1.push_back(drawCard(deck));
                    score1 += getCardScore(hand1.back());
        
                    if (score1 > 21 && !aceAdjusted) {
                        for (string& card : hand1) {
                            if (card[0] == 'A') {
                                score1 -= 10;
                                aceAdjusted = true;
                                break;
                            }
                        }
                    }
                    break;
                }

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
                bool aceAdjusted = false;
                while (true) {
                    string newCard = drawCard(deck);
                    hand2.push_back(drawCard(deck));
                    score2 += getCardScore(hand2.back());
        
                    if (score2 > 21 && !aceAdjusted) {
                        for (string& card : hand2) {
                            if (card[0] == 'A') {
                                score2 -= 10;
                                aceAdjusted = true;
                                break;
                            }
                        }
                    }
                    break;
                }
                cout << "Hand 2: ";
                printCard(hand2);
                cout << "(" << score2 << ")\n";
            } else break;
        }

        // Compare both hands with the dealer
        cout <<"-----------------------------------------------------------------------------\n";
        cout << "Dealer card: "; 
        printCard(dealerhand); 
        bool aceAdjusted = false;
        if (scoredealer > 21 && !aceAdjusted) {
            for (string& card : dealerhand) {
                if (card[0] == 'A') {
                    scoredealer -= 10;
                    aceAdjusted = true;
                    break;
                }
            }
        }
        cout << " (" << scoredealer << ")" << endl;
        cout << "Hand 1: ";
        printCard(hand1);
        cout << "(" << score1 << ")\n";
        cout << "Hand 2: ";
        printCard(hand2);
        cout << "(" << score2 << ")\n";
        Calculatesplite(score1, scoredealer);
        cout << "Hand1\n";
        Calculatesplite(score2, scoredealer);
        cout << "Hand2\n";
        cout <<"-----------------------------------------------------------------------------\n";
    } else {
        cout << "(1) Hit  (2) Stand  ";
        if (score < 21) { cout << "(3) Double down  "; }
        if (hand[0] == hand[1]) cout << "(4) Split"; 
        cout << "\nSelect: ";
        cin >> x;
        return playerdecision(deck, hand,dealerhand, x, score, money, scoredealer); // Recursive call
    }
    return score,x;
}

int main() {
    string filename = "blackjack_save.txt";
    Player player;
    player.name = "Player";
    player.money = 1000;
    player.score = 0;
    player.gamesPlayed = 0;
    player.highScore = 1000;

    // โหลดข้อมูลผู้เล่น (ถ้ามี)
    if (loadGame(filename, player)) {
        playerMoney = player.money; // อัปเดตเงินผู้เล่นจากไฟล์
    }
    string ans;
    int playerAction;
    bool playing = true;
    vector<string> deck = initializeDeck();
    while (true)
    {
       
        cout << "Welcome to Blackjack! Would you like to (L)Load or (N)New game? : ";
        cin >> ans;
        if(ans == "n" || ans == "N"){
            playerMoney = 1000;
            player.score = 0;
            player.gamesPlayed = 0;
            player.highScore = 1000;
            break;
        }else if(ans == "l" || ans == "L"){
            break;
        }else{

        }
    }
        
    while (playing&&playerMoney>0) {
        //deck<10
        if(deck.size()<10) {
            deck = initializeDeck();
        }
        updateStatistics(player);
        // bet
        cout << "Money remain: " << playerMoney << " Baht" << endl;
        betAmount(playerMoney);

        // shuffle deck
        shuffleDeck(deck);

        // player hand
        vector<string> hand;
        string playerCard1 = drawCard(deck);
        string playerCard2 = drawCard(deck);
        
        hand.push_back(playerCard1);
        hand.push_back(playerCard2);

        // dealer hand
        vector<string> dealerhand;
        string dealerCard1 = drawCard(deck);
        string dealerCard2 = drawCard(deck);
         
        dealerhand.push_back(dealerCard1);
        dealerhand.push_back(dealerCard2);

        //show deck
        cout <<"----------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        printCard(deck);cout << "\n";
        cout <<"----------------------------------------------------------------------------------------------------------------------------------------------------------\n";

        // show cards
        cout << "Dealer card: " << dealerhand[0]<< " (One card is hidden) (" << getCardScore(dealerhand[0]) << ")" << endl;
        int scorePlayer = calculateTotalScore(hand);
        cout << "Your hand: ";
        printCard(hand);
        cout << " (" << scorePlayer << ")" << endl;

        // player decision
        cout << "(1) Hit  (2) Stand  ";
        if (scorePlayer < 21 && playerMoney>=2*bet) { cout << "(3) Double down  "; }
        if (playerCard1[0] == playerCard2[0] && playerMoney>=2*bet) {cout << "(4) Split";}
        cout << "\nSelect : ";
        cin >> playerAction;

        // dealer's score
        int scoredealer = calculateTotalScore(dealerhand);
        // dealer action
        bool aceAdjusted = false;
        while (scoredealer < 17) { 
            dealerhand.push_back(drawCard(deck));
            scoredealer += getCardScore(dealerhand.back());
            if (scoredealer > 21 && !aceAdjusted) {
                for (string& card : hand) {
                    if (card[0] == 'A') {
                        scoredealer -= 10;
                        aceAdjusted = true;
                        break;
                    }
                }
            }
            
        }
        if(playerAction == 1){
        cout << "\nDealer card: " << dealerhand[0] << " (One card is hidden) (" << getCardScore(dealerhand[0]) << ")" << endl;
        }

        // player decision
        playerdecision(deck, hand,dealerhand, playerAction, scorePlayer, playerMoney, scoredealer);
        
        // decide win/loss
        if(playerAction != 2 && playerAction != 4 && playerAction != 3){
            cout <<"-----------------------------------------------------------------------------\n";
            cout << "Dealer card: "; 
            printCard(dealerhand); 
            bool aceAdjusted = false;
            if (scoredealer > 21 && !aceAdjusted) {
                for (string& card : hand) {
                    if (card[0] == 'A') {
                        scoredealer -= 10;
                        aceAdjusted = true;
                        break;
                    }
                }
            }
            cout << " (" << scoredealer << ")" << endl;
            cout << "Your hand: ";
            printCard(hand);
            cout << " (" << scorePlayer << ")" << endl;

            Calulate(scorePlayer, scoredealer);
            cout <<"-----------------------------------------------------------------------------\n";
        }

        // อัปเดตสถิติผู้เล่น
        player.money = playerMoney;
        player.score = scorePlayer;
        

        // บันทึกเกม
        saveGame(filename, player);

        

        playing = Askplayagain(); // เรียกฟังก์ชันถามว่าต้องการเล่นต่อไหม
    }
// แสดงสถิติ
showStatistics(player);
    return 0;
}

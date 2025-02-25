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

    cout << "You bet: " << bet << " Baht\n";
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

void playHand(vector<string>& deck, vector<string>& playerHand, int& handScore) {
    int action;
    int aceCount = 0; // นับจำนวน Ace ทั้งหมดในมือ

    // ตรวจนับ Ace ที่มีอยู่ก่อนเริ่มเกม
    for (const string& card : playerHand) {
        if (card[0] == 'A') {
            aceCount++;
        }
    }

    do {
        cout << "(1) Hit , (2) Stand : ";
        cin >> action;

        // ตรวจสอบอินพุตไม่ใช่ตัวเลขหรืออยู่ในช่วงที่ถูกต้อง
        if (cin.fail() || (action != 1 && action != 2)) {
            cout << "Invalid input! Please enter 1 (Hit) or 2 (Stand).\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (action == 1) {
            string newCard = drawCard(deck);
            playerHand.push_back(newCard); // เพิ่มไพ่ใหม่เข้ามือ
            int cardValue = getCardScore(newCard);
            handScore += cardValue;

            // ถ้าไพ่ใบใหม่เป็น Ace ให้เพิ่มตัวนับ Ace
            if (newCard[0] == 'A') {
                aceCount++;
            }

            // ถ้า Bust (เกิน 21) และมี Ace ให้ลดค่าจาก 11 → 1
            while (handScore > 21 && aceCount > 0) {
                handScore -= 10; // ลดค่าของ Ace จาก 11 → 1
                aceCount--; // ลดจำนวน Ace ที่ใช้ค่า 11 ลง
            }

            cout << "New card: " << newCard << " (" << handScore << ")" << endl;

            if (handScore > 21) {
                cout << "Busted! You lose." << endl;
                break;
            }
        }

    } while (action != 2);
}

void splitHand(vector<string>& deck, const string& card1, const string& card2, int& playerMoney, int bet) {
    if (playerMoney >= bet) {
        playerMoney -= bet; // หักเงินเดิมพันสำหรับมือที่สอง
        string newCard1 = drawCard(deck);
        string newCard2 = drawCard(deck);
        vector<string> hand1 = {card1, newCard1};
        vector<string> hand2 = {card2, newCard2};
        int hand1Score = getCardScore(card1) + getCardScore(newCard1);
        int hand2Score = getCardScore(card2) + getCardScore(newCard2);
        
        // จั่วไพ่เพิ่มสำหรับทั้งสองมือที่แยกออก
        
        cout << "First hand: " << card1 << " " << newCard1<< " ("<<hand1Score<<")"<<endl;
        
        // สร้าง vector ของมือผู้เล่นสำหรับแต่ละมือ
        
        // แสดงคะแนนเริ่มต้นก่อนเล่นแต่ละมือ
        
        // เล่นมือแรก
        cout << "Playing first hand..." << endl;
        playHand(deck, hand1, hand1Score); // ส่งมือแรกให้ playHand
        cout<< " Second hand: " << card2 << " " << newCard2<< " ("<<hand2Score<<")"<<endl;

        // เล่นมือที่สอง
        cout << "Playing second hand..." << endl;
        playHand(deck, hand2, hand2Score); // ส่งมือที่สองให้ playHand
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
        playerMoney -= bet; // หักเงินจากผู้เล่น
    }
    else if (scoredealer > 21 && scoreplayer >21)
    {
        cout << "Dealer win!\n";
        playerMoney -= bet;
    }
     if(scoredealer > 21)
    {
        cout << "Player win!\n";
        playerMoney += bet;
    }else if((21-scoreplayer) < (21-scoredealer)){
        cout << "Player win!\n";
        playerMoney += bet; // หักเงินจากผู้เล่น
    }else if((21-scoreplayer) > (21-scoredealer)){
        cout << "Dealer win!\n";
        playerMoney -= bet; // หักเงินจากผู้เล่น
    }else if((21-scoreplayer) == (21-scoredealer))
    {
        cout << "Tie!\n";
        playerMoney+=0;
    }
}

bool Askplayagain()
{
    char choice;
    do {
        cout << "Continue? (Y/N): ";
        cin >> choice;
        if (cin.fail()) 
        {
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            continue;
        }
        if (choice == 'Y' || choice == 'y')
            return true;
        else if (choice == 'N' || choice == 'n')
            return false;
        cout << "Invalid input. Please enter Y or N.\n";
    } while (true); 
}

void printCard(vector<string>& hand) {
    cout << "Your hand: ";
    for (const string& card : hand) {
        cout << card << " ";
    }
    
}

vector<string> showhand(string card) {
    vector<string> hand;
    hand.push_back(card);
    return hand;
}
int acecount(string card)
{
    
}
int main() {
    int playerAction;
    bool playing = true;
    srand(time(0));
   
    while (playing)
    {
        vector<string> deck = initializeDeck();
        shuffleDeck(deck);
        string playerCard1 = drawCard(deck);
        string playerCard2 = drawCard(deck);
        string dealerCard1 = drawCard(deck);
        string dealerCard2 = drawCard(deck);
        string dealerCard[5] = {dealerCard1, dealerCard2, "" , "" , ""}; 
        vector<string> hand = showhand(playerCard1); 
        hand.push_back(playerCard2);
        int cardCount = 2;
        cout << "Money remain: " << playerMoney << " Baht" << endl;
        bet = betAmount(playerMoney);
        cout << "Dealer card: " << dealerCard1 << " (One card is hidden) (" << getCardScore(dealerCard1) << ")" << endl;
        printCard(hand);
        int scorePlayer = getCardScore(playerCard1) + getCardScore(playerCard2);
        if(scorePlayer > 21 && playerCard1[0] == 'A' )
        scorePlayer -= 10 ;
        else if(scorePlayer > 21 && playerCard2[1] == 'A' )
        scorePlayer -= 10 ;
        int scoredealer = getCardScore(dealerCard[0]) + getCardScore(dealerCard[1]);
        cout << " (" << scorePlayer << ")" << endl;
        do {
            cout << "(1) Hit , (2) Stand , ";
            if (playerCard1[0] == playerCard2[0]) cout << "(3) Split , ";
            if (playerMoney >= bet) cout << "(4) Double down , ";
            cout << "Select : ";
            cin >> playerAction;
        } while (playerAction != 1 && playerAction != 2 && playerAction != 3 && playerAction != 4);
        if (playerAction == 1) {
            
            do {
                if (scorePlayer >= 21)
                 {
                    if(playerCard1[0] == 'A'||playerCard2[0] == 'A')
                    scorePlayer-=10;
                }
                string playerCard = drawCard(deck);
                hand.push_back(playerCard);
                if (scorePlayer >= 21) 
                {
                    if(playerCard1[0] == 'A'||playerCard2[0] == 'A')
                    scorePlayer-=10;
                }
                scorePlayer += getCardScore(playerCard);
                printCard(hand);
                cout<< " (" << scorePlayer << ")" << endl;
                if(scorePlayer>21)
                break;
                
                cout << "(1) Hit , (2) Stand : ";
                cin >> playerAction;
            } while (playerAction != 2);
        
        } else if (playerAction == 2) {
            
        } else if (playerAction == 3)
         {
            splitHand(deck, playerCard1, playerCard2, playerMoney, bet);
        }
         else if (playerAction == 4) {
            scorePlayer = doubleDown(deck, scorePlayer, playerMoney, bet);
        }
        
        while (scoredealer < 17 && cardCount < 5) { 
            dealerCard[cardCount] = drawCard(deck);
            scoredealer += getCardScore(dealerCard[cardCount]);
            cardCount++; 
        }
        
        if (scorePlayer>21)
       {
        cout  << "Busted! You lose." << endl;
        playerMoney -= bet;
       }
       else if(scorePlayer == 21)
       {
        cout << "Dealer's cards: "<< dealerCard[1] << " "<< dealerCard[2]<< "(" << scoredealer << ")\n";
        Calulate(scorePlayer,scoredealer);
       }
        else
        {
            cout << "Dealer's cards: ";
        for (int i = 0; i < cardCount; i++) {
            cout << dealerCard[i] << " ";
        }
        cout << "(" << scoredealer << ")\n";
        
        Calulate(scorePlayer,scoredealer);
        
        }
        playing = Askplayagain();
        }
        
    
}

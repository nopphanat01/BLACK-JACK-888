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

void showPlayerWin() {
    cout << "\033[1;32m"; // ตัวหนาสีเขียว
    cout << R"(
██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗     ██╗    ██╗██╗███╗   ██╗
██╔══██╗██║     ██╔══██╗██║   ██║██╔════╝██╔══██╗    ██║    ██║██║████╗  ██║
██████╔╝██║     ███████║██║   ██║█████╗  ██║  ██║    ██║ █╗ ██║██║██╔██╗ ██║
██╔═══╝ ██║     ██╔══██║██║   ██║██╔══╝  ██║  ██║    ██║███╗██║██║██║╚██╗██║
██║     ███████╗██║  ██║╚██████╔╝███████╗██████╔╝    ╚███╔███╔╝██║██║ ╚████║
╚═╝     ╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚═════╝      ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝
    )" << endl;
    cout << "\033[0m"; // รีเซ็ตสี
}

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
        return 11;
    } else {
        return stoi(string(1, k));
    }
}

void splitHand(vector<string>& deck, string card1, string card2, int& money, int& bet) {
    vector<string> hand1 = {card1, drawCard(deck)};
    vector<string> hand2 = {card2, drawCard(deck)};
    int bet2 = bet; 
    money -= bet2;

    cout << "Playing first hand:\n";
    int score1 = getCardScore(hand1[0]) + getCardScore(hand1[1]);
    cout << "Hand 1: " << hand1[0] << " " << hand1[1] << " (" << score1 << ")\n";
    while (score1 < 21) {
        int action;
        cout << "(1) Hit, (2) Stand: ";
        cin >> action;
        if (action == 1) {
            hand1.push_back(drawCard(deck));
            score1 += getCardScore(hand1.back());
            cout << "Hand 1: ";
            for (string card : hand1) cout << card << " ";
            cout << "(" << score1 << ")\n";
        } else break;
    }

    cout << "Playing second hand:\n";
    int score2 = getCardScore(hand2[0]) + getCardScore(hand2[1]);
    cout << "Hand 2: " << hand2[0] << " " << hand2[1] << " (" << score2 << ")\n";
    while (score2 < 21) {
        int action;
        cout << "(1) Hit, (2) Stand: ";
        cin >> action;
        if (action == 1) {
            hand2.push_back(drawCard(deck));
            score2 += getCardScore(hand2.back());
            cout << "Hand 2: ";
            for (string card : hand2) cout << card << " ";
            cout << "(" << score2 << ")\n";
        } else break;
    }
}

int doubleDown(vector<string>& deck, int score, int& money, int& bet) {
    bet *= 2;
    money -= bet / 2;
    string newCard = drawCard(deck);
    score += getCardScore(newCard);
    cout << "Drew " << newCard << " (" << score << ")\n";
    return score;
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
        cout<<"\n---------------------------------------------------------\n\n";
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

   
    while (playing||playerMoney>0)
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
            if (playerMoney >= 2*bet) cout << "(4) Double down , ";

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
        for (int i = 0; scoredealer>scorePlayer || scoredealer == 21; i++) {
            cout << dealerCard[i] << " ";
            scoredealer += getCardScore(dealerCard[cardCount]);

        }
        cout << "(" << scoredealer << ")\n";
        
        Calulate(scorePlayer,scoredealer);
        
        }
        playing = Askplayagain();
        }
        
    
}

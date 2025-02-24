#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;

int playerMoney = 1000; // จำนวนเงินเริ่มต้นของผู้เล่น
int bet,cardScores;


int betAmount(int bet,int playerMoney)
{
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

}

vector<string> initializeDeck() {
    string suits[] = {"D", "S", "H", "C"};
    string ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int cardScores[] = {1,2,3,4,5,6,7,8,9,10,10,10,10};
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

int calDealerScore(int dealercard1, int dealercard2, int dealercard3) {
    int hand[] = {dealercard1, dealercard2, dealercard3};
    int sum = 0, aceCount = 0;

    for (int i = 0; i < 3; i++) {
        if (hand[i] == 1) {
            aceCount++;
            sum += 11;
        } else {
            sum += cardScores;
        }
    }

    while (sum > 21 && aceCount > 0) {
        sum -= 10;
        aceCount--;
    }

    return sum;
}
vector<string> deck = initializeDeck();
string playercard1 = drawCard(deck);
string playercard2 = drawCard(deck);
string dealercard1 = drawCard(deck);
string dealercard2 = drawCard(deck);


int main() {
    
    
    cout << "Money ramain: " << playerMoney << " Baht" << endl;
    cout << "Bet: ";
    cin >> bet;
    betAmount(bet,playerMoney);
    vector<string> deck = initializeDeck();
    shuffleDeck(deck);
    cout << "Dealer card: " << dealercard1 <<" One card is hidden"<<endl;
   // int dealerScore = calDealerScore(dealercard1, 0, 0); 
    cout << "Drawn card: " << playercard1 <<" and "<< playercard2<< endl;

    
   
   
}


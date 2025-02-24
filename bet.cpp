#include <iostream>
using namespace std;
int playerMoney = 1000; // จำนวนเงินเริ่มต้นของผู้เล่น
int bet;

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

int main() {
    
    
    cout << "Money ramain: " << playerMoney << " Baht" << endl;
    cout << "Bet: ";
    cin >> bet;
    betAmount(bet,playerMoney);
   
    return 0;
}


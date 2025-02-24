#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// ฟังก์ชันประกาศ
void startGame();
void dealInitialCards(int &playerScore, int &dealerScore, int &playerMoney, int &betAmount);
void playerTurn(int &playerScore, int &playerMoney, int &betAmount);
void dealerTurn(int &dealerScore);
bool askToPlayAgain();
void printStats(int wins, int losses, int ties, int playerMoney);
void loadStats(int &wins, int &losses, int &ties, int &playerMoney);
void saveStats(int wins, int losses, int ties, int playerMoney);

int main() {
    srand(time(0)); // ตั้งค่า seed สำหรับการสุ่ม
    bool playing = true;

    // สถิติ
    int wins = 0;
    int losses = 0;
    int ties = 0;
    int playerMoney = 1000; // เงินเริ่มต้นของผู้เล่น

    // โหลดสถิติและเงินจากไฟล์
    loadStats(wins, losses, ties, playerMoney);

    while (playing) {
        int playerScore = 0;
        int dealerScore = 0;
        int betAmount = 0;

        startGame();

        // รับเงินเดิมพัน
        cout << "คุณมีเงิน: " << playerMoney << " บาท" << endl;
        while (true) {
            cout << "กรุณาใส่เงินเดิมพัน: ";
            cin >> betAmount;

            if (betAmount <= 0) {
                cout << "เงินเดิมพันต้องมากกว่า 0!\n";
            } else if (betAmount > playerMoney) {
                cout << "คุณมีเงินไม่พอ!\n";
            } else {
                break;
            }
        }

        // เรียกใช้ฟังก์ชัน
        dealInitialCards(playerScore, dealerScore, playerMoney, betAmount);
        playerTurn(playerScore, playerMoney, betAmount);

        if (playerScore <= 21) { // ถ้าผู้เล่นไม่ Bust ให้ Dealer เล่น
            dealerTurn(dealerScore);
        }

        // เช็คผลแพ้ชนะและเก็บสถิติ
        if (playerScore > 21) {
            cout << "คุณแพ้! คะแนนเกิน 21!" << endl;
            losses++;
            playerMoney -= betAmount;
        } else if (dealerScore > 21) {
            cout << "ดีลเลอร์แพ้! คะแนนเกิน 21!" << endl;
            wins++;
            playerMoney += betAmount;
        } else if (playerScore > dealerScore) {
            cout << "คุณชนะ!" << endl;
            wins++;
            playerMoney += betAmount;
        } else if (playerScore < dealerScore) {
            cout << "คุณแพ้!" << endl;
            losses++;
            playerMoney -= betAmount;
        } else {
            cout << "เสมอ!" << endl;
            ties++;
        }

        // แสดงสถิติหลังเกม
        printStats(wins, losses, ties, playerMoney);

        // บันทึกสถิติและเงินลงไฟล์
        saveStats(wins, losses, ties, playerMoney);

        // ถามว่าจะเล่นต่อไหม
        playing = askToPlayAgain();
    }

    cout << "ขอบคุณที่เล่น Blackjack!" << endl;
    return 0;
}

void startGame() {
    cout << "ยินดีต้อนรับสู่เกม Blackjack!" << endl;
}

bool askToPlayAgain() {
    char choice;
    cout << "คุณต้องการเล่นอีกครั้ง (Y/N)? ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

void printStats(int wins, int losses, int ties, int playerMoney) {
    cout << "\n--- สถิติการเล่น ---" << endl;
    cout << "ชนะ: " << wins << " เกม" << endl;
    cout << "แพ้: " << losses << " เกม" << endl;
    cout << "เสมอ: " << ties << " เกม" << endl;
    cout << "เงินคงเหลือ: " << playerMoney << " บาท" << endl;
    cout << "----------------------\n" << endl;
}

void loadStats(int &wins, int &losses, int &ties, int &playerMoney) {
    ifstream inputFile("stats.txt");

    if (inputFile.is_open()) {
        inputFile >> wins >> losses >> ties >> playerMoney;
        inputFile.close();
    } else {
        cout << "ไม่พบไฟล์สถิติ บันทึกใหม่..." << endl;
    }
}

void saveStats(int wins, int losses, int ties, int playerMoney) {
    ofstream outputFile("stats.txt");

    if (outputFile.is_open()) {
        outputFile << wins << endl;
        outputFile << losses << endl;
        outputFile << ties << endl;
        outputFile << playerMoney << endl;
        outputFile.close();
    } else {
        cout << "ไม่สามารถบันทึกไฟล์สถิติได้!" << endl;
    }
}

void dealInitialCards(int &playerScore, int &dealerScore, int &playerMoney, int &betAmount) {
    playerScore = rand() % 11 + 2; // สุ่มคะแนนเริ่มต้นของผู้เล่น (2-12)
    dealerScore = rand() % 11 + 2; // สุ่มคะแนนเริ่มต้นของดีลเลอร์ (2-12)

    cout << "คุณได้คะแนนเริ่มต้น: " << playerScore << endl;
    cout << "ดีลเลอร์ได้คะแนนเริ่มต้น: " << dealerScore << endl;
}

void playerTurn(int &playerScore, int &playerMoney, int &betAmount) {
    char choice;
    while (playerScore <= 21) {
        cout << "คุณต้องการ (1) Hit หรือ (2) Stand? ";
        cin >> choice;

        if (choice == '1') {
            int newCard = rand() % 11 + 1; // สุ่มการ์ดใหม่ (1-11)
            playerScore += newCard;
            cout << "คุณได้การ์ดใหม่: " << newCard << " คะแนนรวม: " << playerScore << endl;

            if (playerScore > 21) {
                cout << "คุณ Bust! คะแนนเกิน 21!" << endl;
                break;
            }
        } else if (choice == '2') {
            break;
        } else {
            cout << "คำสั่งไม่ถูกต้อง กรุณาเลือก 1 หรือ 2!" << endl;
        }
    }
}

void dealerTurn(int &dealerScore) {
    cout << "ดีลเลอร์กำลังเล่น..." << endl;
    while (dealerScore < 17) {
        int newCard = rand() % 11 + 1; // สุ่มการ์ดใหม่ (1-11)
        dealerScore += newCard;
        cout << "ดีลเลอร์ได้การ์ดใหม่: " << newCard << " คะแนนรวม: " << dealerScore << endl;
    }
}
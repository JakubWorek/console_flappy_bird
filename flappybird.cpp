#include <iostream>
#include <ctime>
#include <Windows.h>
using namespace std;

const int y = 11;
const int x = 21;

int score = 0;
char plansza[y][x] = {};

void Grid() {
	//rogi
	plansza[0][0] = char(201);
	plansza[y - 1][0] = char(200);
	plansza[0][x - 1] = char(187);
	plansza[y - 1][x - 1] = char(188);
	//boki
	for (int i = 1; i < x - 1; i++) plansza[0][i] = char(205);
	for (int i = 1; i < x - 1; i++) plansza[y - 1][i] = char(205);
	for (int i = 1; i < y - 1; i++) plansza[i][0] = char(186);
	for (int i = 1; i < y - 1; i++) plansza[i][x - 1] = char(186);
	//srodek
	for (int i = 1; i < y - 1; i++) {
		for (int j = 1; j < x - 1; j++) {
			plansza[i][j] = ' ';
		}
	}
}

void Draw() {
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			cout << plansza[i][j];
		}
		cout << endl;
	}
	cout << "SCORE: " << score << endl;
}

void GameOver() {
	system("cls");
	cout << "Game Over" << endl;
	cout << "Final Score: " << score <<endl;
	if(score==0) cout << "NOOB" << endl;
	else cout << "GG " << endl;
	system("PAUSE");
}

void Update() {
	Grid();

	srand(time(NULL));

	int obsposx = x - 2;
	int obsposy = 2 + rand() % (y - 4);

	int posx = 3;
	int posy = y / 2;

	for(int i=1; i<y-1; i++) {plansza[i][obsposx]=char(178);}
	plansza[obsposy-1][obsposx] = ' ';
	plansza[obsposy][obsposx] = ' ';
	plansza[obsposy+1][obsposx] = ' ';
	plansza[posy][posx] = '>';

	Draw();

	while (true) {
		//obstacle movement
		for(int i=1; i<y-1; i++) {plansza[i][obsposx]=' ';}
		if (obsposx == 1) {
			score++;
			obsposx = x - 2;
			obsposy = 2 + rand() % (y - 4);
		}
		else {
			obsposx--;
		}
		for(int i=1; i<y-1; i++) {plansza[i][obsposx]=char(178);}
		plansza[obsposy-1][obsposx] = ' ';
		plansza[obsposy][obsposx] = ' ';
		plansza[obsposy+1][obsposx] = ' ';
		plansza[posy][posx] = '>';

		if (obsposx == posx) {
			if (obsposy != posy && obsposy-1 != posy && obsposy+1 != posy) {
				break;
				GameOver();
			}
		}

		//up
		if (GetKeyState(87) & 0x8000){
			posy--;
			if (posy == 0 || posy == y - 1) {
				break;
				GameOver();
			}
			else {
				plansza[posy + 1][posx] = ' ';
				plansza[posy][posx] = '>';
			}
		}

		//down
		if (GetKeyState(83) & 0x8000){
			posy++;
			if (posy == 0 || posy == y - 1) {
				break;
				GameOver();
			}
			else {
				plansza[posy - 1][posx] = ' ';
				plansza[posy][posx] = '>';
			}
		}

		//game update and draw
		Draw();
		Sleep(250);
		system("cls");
	}

	GameOver();
}

int main(){
	Update();
}
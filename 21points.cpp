#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
// save the number of cards and sum in human or computer process
struct result {
	float sum;
	int times;
};
void distribution(int card[4][13], int scard[2]);
void display(int record[20][2]); 
float num(int number);
result computer(int card[4][13], float sum1);
result human(int card[4][13]); 
void judgement(result tmp1, result tmp2);
void initialize(int card[4][13]);
// distribute all cards
void distribution(int card[4][13], int scard[2]) {
	bool flag = true;
	int number, color;
	while (flag) {
	    number = rand() * 13 / (RAND_MAX + 1);
		color = rand() * 4 / (RAND_MAX + 1);
        if (card[color][number] == 1) {
            card[color][number] = 0;
		    flag = 0;	
        }    
    }
    scard[0] = color;
    scard[1] = number;
}
// show the random cards
void display(int record[20][2]) {
	int i;
	for (i=0; i < 20; ++i) {
	    if (record[i][0] == 50) {
	        break;
	    }
		else {
	        switch (record[i][0]) {
    	        case 0: cout << "ºìÌÒ"; break; 
		        case 1: cout << "ºÚÌÒ"; break;
		        case 2: cout << "·½¿é"; break;
		        case 3: cout << "Ã·»¨"; break;
            }
	        switch (record[i][1]) {
    	        case 0: cout << 'A'; break;
    	        case 1: cout << '2'; break;
    	        case 2: cout << '3'; break;
    	        case 3: cout << '4'; break;
    	        case 4: cout << '5'; break;
    	        case 5: cout << '6'; break;
    	        case 6: cout << '7'; break;
    	        case 7: cout << '8'; break;
    	        case 8: cout << '9'; break;
    	        case 9: cout << "10"; break;
    	        case 10: cout << "J"; break;
    	        case 11: cout << "Q"; break;
    	        case 12: cout << "K"; break;
            }   
        }   
        cout << ' ';
	}  
}
// return a float number which can be added into the sum
float num(int number) {
	if (number > 0 and number < 10) {
		return float(number + 1);
	}
	switch (number) {
		case 0: return 1.0; break;
		default: return 0.5; break;
	}
}
// the computer process
result computer(int card[4][13], float sum1) {
	int i, card1[2], card2[2], newcard[2], record[20][2], index = 2, times;
	float sum;
	result tmp, mistake;
	mistake.sum = 0.0;
	mistake.times = 0; 
	cout << "computer's turn" << endl; 
	// initialize
	for (i = 0; i < 20; ++i) {
		record[i][0] = 50;
	}
	distribution(card, card1);
    distribution(card, card2);
    record[0][0] = card1[0];
	record[0][1] = card1[1];
	record[1][0] = card2[0];
	record[1][1] = card2[1];
	cout << "the computer gets:" << ' ';
	display(record);
	cout << endl; 
	times = 2;
	sum = num(card1[1]) + num(card2[1]);	
	while (sum < sum1) {
	    distribution(card, newcard);   // a new card
	    record[index][0] = newcard[0]; // save the new card by using an array
	    record[index][1] = newcard[1];
		++index;
		times += 1;
		cout << "one more" << ' ';
		display(record);
		cout << endl;
		sum += num(newcard[1]);
		if (sum > 21) {
			return mistake;
		}
	}
    tmp.times = times;
    tmp.sum = sum;
	return tmp;    // return the number and sum
}
// the human process
result human(int card[4][13]) {
    int i, card1[2], card2[2], newcard[2], times, record[20][2], index = 2;
	float sum;
	char judge;
	result tmp, mistake;
	mistake.sum = 0.0;
	mistake.times = 0;
	cout << "player's turn" << endl; 
	for (i = 0; i < 20; ++i) {
		record[i][0] = 50;
	}
	distribution(card, card1);
    distribution(card, card2);
    record[0][0] = card1[0];
	record[0][1] = card1[1];
	record[1][0] = card2[0];
	record[1][1] = card2[1];
	cout << "the player gets:" << ' ';
	display(record);
	cout << endl; 
	times = 2;  
	sum = num(card1[1]) + num(card2[1]);	
	cout << "do you want another card?(y/n)";
	try {
	    cin >> judge;
	    if (judge != 'y' and judge != 'n') throw judge;
    }
	catch (char) {
		while (judge != 'y' and judge != 'n') {
			    cerr << "sorry, your input is wrong, please input again";
			    cin >> judge;
		}
	} 
	while (judge == 'y') {
	    distribution(card, newcard);
	    record[index][0] = newcard[0];
	    record[index][1] = newcard[1];
		++index;
		times += 1;
		cout << "one more:" << ' ';
		display(record);
		cout << endl;
		sum += num(newcard[1]);
		if (sum > 21) {
			return mistake;
		}
		cout << "do you want another card?(y/n)";
	    try {
	        cin >> judge;
	        if (judge != 'y' and judge != 'n') throw judge;
        }
	    catch (char) {
		    while (judge != 'y' and judge != 'n') {
			        cerr << "sorry, your input is wrong, please input again";
			        cin >> judge;
		    }
	    }
	}
    tmp.times = times;
    tmp.sum = sum;
	return tmp;
}
// judge who wins
void judgement(result tmp1, result tmp2){
    float sum1, sum2;
    int times1, times2;
	sum1 = tmp1.sum;
    sum2 = tmp2.sum;
    times1 = tmp1.times;
    times2 = tmp2.times;
	// by rule
	if (sum1 > sum2) cout << "the player wins!";
    if (sum1 < sum2) cout << "the computer wins!";
    if (sum1 == sum2) {
    	if (times1 > times2) cout << "the player wins!";
    	if (times1 < times2) cout << "the computer wins!";
    	if (times1 == times1) cout << "the game is tied!";
    }
}
// every time we play a new game, we should initialize first  
void initialize(int card[4][13]) {
    int i, j;
	for (i = 0; i < 4; ++i) {
    	for (j = 0; j < 13; ++j) {
    		card[i][j] = 1;
    	}
    }
}
int main() {
	result tmp1, tmp2; // tmp is a structure which saves the sum and number of cards during the procedure
	char flag = 'y';
    int card[4][13];
	srand(time(NULL));
	while (flag == 'y') {
	    initialize(card);
		tmp1 = human(card);
	    if (tmp1.sum == 0) cout << "the computer wins!";    // if sum > 21 , then we let sum be 0, that means a failure 
	    else {
		    tmp2 = computer(card, tmp1.sum);
		    if (tmp2.sum == 0) cout << "the player wins!";
	        if (tmp1.sum != 0 and tmp2.sum != 0) {
	    	    judgement(tmp1,tmp2);
	        }
	    }
	    cout << endl << "do you want to play again?(y/n)";
	    try { 
		    cin >> flag;
	        if (flag != 'y' and flag != 'n') throw flag;
		}
	    catch (char) {
			while (flag != 'y' and flag != 'n') {
			    cerr << "sorry, your input is wrong, please input again";
			    cin >> flag;
		    }
	    }
    }
    return 0;
}

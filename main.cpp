#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <cmath>
#include "hand.h"

using namespace std;

		hand leftHand;
		hand rightHand;

		const int numSentences = 1;
		const int sentenceLength =11;

		int x = 0;
		int y = 0;
		int counter = 0;

		int distanceMovedDSK[numSentences];
		int distanceMovedQWERTY[numSentences];

	    string wordBank[5008];
		string sentenceBank[numSentences][sentenceLength];
		char QWERTY[11][4];
		char DSK[11][4];

		string typeSentence;

		char nextChar;
//data

	void populateWordBank()
		{
			int counter=0;

			ifstream file("5KCW.txt");

            string str; 

            while (getline(file, str))
			{
				wordBank[counter] = str;
				counter++;
			}
			counter = 0;		
		}

	void populateQWERTY()
		{
			QWERTY[0][0] = '1';
			QWERTY[0][1] = 'q';
			QWERTY[0][2] = 'a';
			QWERTY[0][3] = 'z';
			QWERTY[1][0] = '2';
			QWERTY[1][1] = 'w';
			QWERTY[1][2] = 's';
			QWERTY[1][3] = 'x';
			QWERTY[2][0] = '3';
			QWERTY[2][1] = 'e';
			QWERTY[2][2] = 'd';
			QWERTY[2][3] = 'c';
			QWERTY[3][0] = '4';
			QWERTY[3][1] = 'r';
			QWERTY[3][2] = 'f';
			QWERTY[3][3] = 'v';
			QWERTY[4][0] = '5';
			QWERTY[4][1] = 't';
			QWERTY[4][2] = 'g';
			QWERTY[4][3] = 'b';
			QWERTY[5][0] = '6';
			QWERTY[5][1] = 'y';
			QWERTY[5][2] = 'h';
			QWERTY[5][3] = 'n';
			QWERTY[6][0] = '7';
			QWERTY[6][1] = 'u';
			QWERTY[6][2] = 'j';
			QWERTY[6][3] = 'm';
			QWERTY[7][0] = '8';
			QWERTY[7][1] = 'i';
			QWERTY[7][2] = 'k';
			QWERTY[7][3] = ',';
			QWERTY[8][0] = '9';
			QWERTY[8][1] = 'o';
			QWERTY[8][2] = 'l';
			QWERTY[8][3] = '.';
			QWERTY[9][0] = '0';
			QWERTY[9][1] = 'p';
			QWERTY[9][2] = ';';
			QWERTY[9][3] = '/';
			QWERTY[10][0] = '-';
			QWERTY[10][1] = '[';
			QWERTY[10][2] = '\'';
			QWERTY[10][3] = 'S';
		}

	void populateDSK()
		{
			DSK[0][0] = '1';
			DSK[0][1] = '\'';
			DSK[0][2] = 'a';
			DSK[0][3] = ';';
			DSK[1][0] = '2';
			DSK[1][1] = ',';
			DSK[1][2] = 'o';
			DSK[1][3] = 'q';
			DSK[2][0] = '3';
			DSK[2][1] = '.';
			DSK[2][2] = 'e';
			DSK[2][3] = 'j';
			DSK[3][0] = '4';
			DSK[3][1] = 'p';
			DSK[3][2] = 'u';
			DSK[3][3] = 'k';
			DSK[4][0] = '5';
			DSK[4][1] = 'y';
			DSK[4][2] = 'i';
			DSK[4][3] = 'x';
			DSK[5][0] = '6';
			DSK[5][1] = 'f';
			DSK[5][2] = 'd';
			DSK[5][3] = 'b';
			DSK[6][0] = '7';
			DSK[6][1] = 'g';
			DSK[6][2] = 'h';
			DSK[6][3] = 'm';
			DSK[7][0] = '8';
			DSK[7][1] = 'c';
			DSK[7][2] = 't';
			DSK[7][3] = 'w';
			DSK[8][0] = '9';
			DSK[8][1] = 'r';
			DSK[8][2] = 'n';
			DSK[8][3] = 'v';
			DSK[9][0] = '0';
			DSK[9][1] = 'l';
			DSK[9][2] = 's';
			DSK[9][3] = 'z';
			DSK[10][0] = '[';
			DSK[10][1] = '/';
			DSK[10][2] = '-';
			DSK[10][3] = 'S';
		}

	int getRandomIndex()
		{
			int index;

            index = rand() % 5008;
			return index;
		}

	void populateSentenceBank()
		{
			int index;

			for (int i = 0; i<numSentences; i++)
			{
				for (int j = 0; j<sentenceLength; j++)
				{
					if (j+1 == sentenceLength)
					{
						sentenceBank[i][j] = '.';
					}
					else
					{
				    index = getRandomIndex();
					sentenceBank[i][j] = wordBank[index];
					}
				}
			}
		}

	char getNextChar(string currentWord, int position)
	{
		char returnChar;

		switch (currentWord[position]){
		case '.': returnChar = '.';
		case 'a': returnChar = 'a';
		case 'b': returnChar = 'b';
		case 'c': returnChar = 'c';
		case 'd': returnChar = 'd';
		case 'e': returnChar = 'e';
		case 'f': returnChar = 'f';
		case 'g': returnChar = 'g';
		case 'h': returnChar = 'h';
		case 'i': returnChar = 'i';
		case 'j': returnChar = 'j';
		case 'k': returnChar = 'k';
		case 'l': returnChar = 'l';
		case 'm': returnChar = 'm';
		case 'n': returnChar = 'n';
		case 'o': returnChar = 'o';
		case 'p': returnChar = 'p';
		case 'q': returnChar = 'q';
		case 'r': returnChar = 'r';
		case 's': returnChar = 's';
		case 't': returnChar = 't';
		case 'u': returnChar = 'u';
		case 'v': returnChar = 'v';
		case 'w': returnChar = 'w';
		case 'x': returnChar = 'x';
		case 'y': returnChar = 'y';
		case 'z': returnChar = 'z';
		case ';': returnChar = ';';
		case '\'': returnChar = '\'';
		case '-': returnChar = '-';
		}

		return returnChar;

	}

	void getCharPosition(int& posX, int& posY, char dummyKeyboard[11][4], char nextChar)
	{
		for (int i = 0; i<11; i++)
		{
			for (int j = 0; j<4; j++)
			{
				if(nextChar = dummyKeyboard[i][j])
				{
					posX = i;
					posY = j;
				}
			}
		}
	}

	void setTerritoryQWERTY()
	{
		leftHand.fingers[0].territory[0] = '1';
		leftHand.fingers[0].territory[1] = 'q';
		leftHand.fingers[0].territory[2] = 'a';
		leftHand.fingers[0].territory[3] = 'z';
		leftHand.fingers[1].territory[0] = '2';
		leftHand.fingers[1].territory[1] = 'w';
		leftHand.fingers[1].territory[2] = 's';
		leftHand.fingers[1].territory[3] = 'x';
		leftHand.fingers[2].territory[0] = '3';
		leftHand.fingers[2].territory[1] = 'e';
		leftHand.fingers[2].territory[2] = 'd';
		leftHand.fingers[2].territory[3] = 'c';
		leftHand.fingers[3].territory[0] = '4';
		leftHand.fingers[3].territory[1] = 'r';
		leftHand.fingers[3].territory[2] = 'f';
		leftHand.fingers[3].territory[3] = 'v';
		leftHand.fingers[3].territory[4] = '5';
		leftHand.fingers[3].territory[5] = 't';
		leftHand.fingers[3].territory[6] = 'g';
		leftHand.fingers[3].territory[7] = 'b';

		rightHand.fingers[0].territory[0] = '6';
		rightHand.fingers[0].territory[1] = 'y';
		rightHand.fingers[0].territory[2] = 'h';
		rightHand.fingers[0].territory[3] = 'n';
		rightHand.fingers[0].territory[0] = '7';
		rightHand.fingers[0].territory[1] = 'u';
		rightHand.fingers[0].territory[2] = 'j';
		rightHand.fingers[0].territory[3] = 'm';
		rightHand.fingers[1].territory[0] = '8';
		rightHand.fingers[1].territory[1] = 'i';
		rightHand.fingers[1].territory[2] = 'k';
		rightHand.fingers[1].territory[3] = ',';
		rightHand.fingers[2].territory[0] = '9';
		rightHand.fingers[2].territory[1] = 'o';
		rightHand.fingers[2].territory[2] = 'l';
		rightHand.fingers[2].territory[3] = '.';
		rightHand.fingers[3].territory[0] = '0';
		rightHand.fingers[3].territory[1] = 'p';
		rightHand.fingers[3].territory[2] = ';';
		rightHand.fingers[3].territory[3] = '/';
		rightHand.fingers[3].territory[4] = '-';
		rightHand.fingers[3].territory[5] = '[';
		rightHand.fingers[3].territory[6] = '\'';
	}

	void setTerritoryDSK()
	{
		leftHand.fingers[0].territory[0] = '1';
		leftHand.fingers[0].territory[1] = '\'';
		leftHand.fingers[0].territory[2] = 'a';
		leftHand.fingers[0].territory[3] = ';';
		leftHand.fingers[1].territory[0] = '2';
		leftHand.fingers[1].territory[1] = ',';
		leftHand.fingers[1].territory[2] = 'o';
		leftHand.fingers[1].territory[3] = 'q';
		leftHand.fingers[2].territory[0] = '3';
		leftHand.fingers[2].territory[1] = '.';
		leftHand.fingers[2].territory[2] = 'e';
		leftHand.fingers[2].territory[3] = 'j';
		leftHand.fingers[3].territory[0] = '4';
		leftHand.fingers[3].territory[1] = 'p';
		leftHand.fingers[3].territory[2] = 'u';
		leftHand.fingers[3].territory[3] = 'k';
		leftHand.fingers[3].territory[4] = '5';
		leftHand.fingers[3].territory[5] = 'y';
		leftHand.fingers[3].territory[6] = 'i';
		leftHand.fingers[3].territory[7] = 'x';

		rightHand.fingers[0].territory[0] = '6';
		rightHand.fingers[0].territory[1] = 'f';
		rightHand.fingers[0].territory[2] = 'd';
		rightHand.fingers[0].territory[3] = 'b';
		rightHand.fingers[0].territory[0] = '7';
		rightHand.fingers[0].territory[1] = 'g';
		rightHand.fingers[0].territory[2] = 'h';
		rightHand.fingers[0].territory[3] = 'm';
		rightHand.fingers[1].territory[0] = '8';
		rightHand.fingers[1].territory[1] = 'c';
		rightHand.fingers[1].territory[2] = 't';
		rightHand.fingers[1].territory[3] = 'w';
		rightHand.fingers[2].territory[0] = '9';
		rightHand.fingers[2].territory[1] = 'r';
		rightHand.fingers[2].territory[2] = 'n';
		rightHand.fingers[2].territory[3] = 'v';
		rightHand.fingers[3].territory[0] = '0';
		rightHand.fingers[3].territory[1] = 'l';
		rightHand.fingers[3].territory[2] = 's';
		rightHand.fingers[3].territory[3] = 'z';
		rightHand.fingers[3].territory[4] = '[';
		rightHand.fingers[3].territory[5] = '/';
		rightHand.fingers[3].territory[6] = '-';
	}

	void resetFingerPositions()
	{
		for (int i = 0; i<4; i++)
		{
			leftHand.fingers[i].lastPositionX = i;
			leftHand.fingers[i].lastPositionY = 2;
		}

		for (int j = 6; j <= 9; j++)
		{
			rightHand.fingers[j-6].lastPositionX = j;
			rightHand.fingers[j-6].lastPositionY = 2;
		}
	}

	void prepareSentence(int sentenceNumber)
	{
		typeSentence.clear();
		for (int i = 0; i<sentenceLength; i++)
		{
			typeSentence = typeSentence + sentenceBank[sentenceNumber][i];
		}
	}

void main()
{

	srand (time(NULL));
	
	populateQWERTY();
	populateDSK();
	populateWordBank();
	populateSentenceBank();

	for(int i = 0; i<numSentences; i++)
	{
		resetFingerPositions();
		prepareSentence(i);

		do{
			nextChar = getNextChar(typeSentence,counter);
			getCharPosition(x,y,QWERTY,nextChar);

			if (x<5)
			{
				distance
				leftHand.fingers[leftHand.findClosestFinger(nextChar)].lastPositionX = x;
			}
			else
			{
			}


			counter++;

		}while(nextChar != '.');
		
		

	}



	system("PAUSE");
}

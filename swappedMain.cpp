#include <iostream>//cout and such
#include <fstream> //for working with 5KCW.txt
#include <cstdlib>
#include <ctime> //random
#include <cmath> //sqrt
#include <string> //basically the whole project
using namespace std;

const int numSentences = 20000;  //numSentences*2 will be typed.
const int sentenceLength = 2;//change how many words in each sentence. Last one will always be '.'; for example, setting to 2 will
							  //cause all sentences to be one word + one period long.

float cSquared = 0; //for use in calculating the distance between a finger's position and the nextChar's position.
long float QWERTYDistanceTotal = 0; //for use in calculating the average distance used to type a sentence with QWERTY.
long float DSKDistanceTotal = 0;    // for  use in calculating the average distance used to type a sentence with DSK.

int x = 0;  //X position of nextChar.
int y = 0;  //Y position of nextChar.
int counter = 0; //Used to pass a position from the main() to the getCharPosition method.
int closestFinger = 0; //used to store the current closest finger.

float distanceMovedDSK[numSentences*2]; //array used to store the distances moved for each sentence on DSK
float distanceMovedQWERTY[numSentences*2]; //array used to store the distances moved for each sentence on QWERTY

string wordBank[5008]; //filled with words from 5KCW.txt
string sentenceBank[numSentences][sentenceLength];
string sentenceBank2[numSentences][sentenceLength];//filled with random sentences.
char QWERTY[11][4]; //QWERTY keyboard.
char DSK[11][4];    //Dvorak keyboard.

string typeSentence; //used to store concatenated words from the columns of sentenceBank.

char nextChar; //used to store the next char that a given finger must type.

class finger{

public:
	int positionX, positionY; // x and y positions of each finger

	char territory[8]; //array of characters used to store the letters/symbols that a given finger 
	//will be responsible for typing.

	//set the (X,Y) position of a finger to (A,B)
	void move(int a, int b)
	{
		positionX = a;
		positionY = b;
	}

};


class hand{

public:

	finger fingers[4]; //each hand has 4 fingers that will type. Thumbs are for spacebar use only.

	//given a character, returns the finger # that will type the next character.
	int findClosestFinger(char myChar){

		int closestFinger = 0;

		for (int i = 0; i<4; i++)
		{
			for (int j = 0; j<8; j++)
			{
				/*
				cout << " Comparing finger: " << i << endl;
				cout << " Comparing territory index: " << fingers[i].territory[j] << endl;
				*/
				if ((fingers[i].territory[j] == myChar) && (fingers[i].territory[j] != NULL))
				{
					/*
					cout << "SUCCESS" << endl;
					system("pause");
					*/
					closestFinger = i;
				}
			}
		}

		return closestFinger;

	}

};

hand leftHand;           //virtual jazz hands!
hand rightHand;

//return a random index between 0 and 5007.
int getRandomIndex()
{
	int index;
	index = rand() % 5008;
	return index;
}


//fill the word bank with all of the words from 5KCW.txt.
//fill sentenceBank and sentenceBank2 with random sentences.
void populateWordBank()
{
	int counter = 0;

	ifstream file("5KCW.txt");

	string str;

	while(getline(file,str))
	{
		wordBank[counter] = str;
		counter++;
	}

	int index;

	cout << "Filling sentence bank 1...\n";

	for (int i = 0; i<numSentences; i++)
	{
		for (int j = 0; j<sentenceLength; j++)
		{
			if (j + 1 == sentenceLength)
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

	cout<<"Sentence Bank 1 filled.\n";
	cout << "Filling sentence bank 2...\n";

	for (int i = 0; i<numSentences; i++)
	{
		for (int j = 0; j<sentenceLength; j++)
		{
			if (j + 1 == sentenceLength)
			{
				sentenceBank2[i][j] = '.';
			}
			else
			{
				index = getRandomIndex();
				sentenceBank2[i][j] = wordBank[index];
			}
		}
	}

	cout<<"Sentence Bank 2 filled.\n";
}

//populate the char QWERTY[11][4] structure to look like a QWERTY keyboard.
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
	QWERTY[10][3] = 'S'; //right shift key
}

//populate the char DSK[11][4] structure to look like a Dvorak keyboard.
void populateDSK()
{
	DSK[0][0] = '1';
	DSK[0][1] = '\'';
	DSK[0][2] = ';';
	DSK[0][3] = 'a';
	DSK[1][0] = '2';
	DSK[1][1] = ',';
	DSK[1][2] = 'q';
	DSK[1][3] = 'o';
	DSK[2][0] = '3';
	DSK[2][1] = '.';
	DSK[2][2] = 'j';
	DSK[2][3] = 'e';
	DSK[3][0] = '4';
	DSK[3][1] = 'p';
	DSK[3][2] = 'k';
	DSK[3][3] = 'u';
	DSK[4][0] = '5';
	DSK[4][1] = 'y';
	DSK[4][2] = 'x';
	DSK[4][3] = 'i';
	DSK[5][0] = '6';
	DSK[5][1] = 'f';
	DSK[5][2] = 'b';
	DSK[5][3] = 'd';
	DSK[6][0] = '7';
	DSK[6][1] = 'g';
	DSK[6][2] = 'm';
	DSK[6][3] = 'h';
	DSK[7][0] = '8';
	DSK[7][1] = 'c';
	DSK[7][2] = 'w';
	DSK[7][3] = 't';
	DSK[8][0] = '9';
	DSK[8][1] = 'r';
	DSK[8][2] = 'v';
	DSK[8][3] = 'n';
	DSK[9][0] = '0';
	DSK[9][1] = 'l';
	DSK[9][2] = 'z';
	DSK[9][3] = 's';
	DSK[10][0] = '[';
	DSK[10][1] = '/';
	DSK[10][2] = '-';
	DSK[10][3] = 'S'; //right shift key
}



//Given a position and a string, return the character from that position in that string.
char getNextChar(string currentWord, int position)
{
	char returnChar = ' ';

	switch (currentWord[position]){
	case '.': returnChar = '.';
		break;
	case 'a': returnChar = 'a';
		break;
	case 'b': returnChar = 'b';
		break;
	case 'c': returnChar = 'c';
		break;
	case 'd': returnChar = 'd';
		break;
	case 'e': returnChar = 'e';
		break;
	case 'f': returnChar = 'f';
		break;
	case 'g': returnChar = 'g';
		break;
	case 'h': returnChar = 'h';
		break;
	case 'i': returnChar = 'i';
		break;
	case 'j': returnChar = 'j';
		break;
	case 'k': returnChar = 'k';
		break;
	case 'l': returnChar = 'l';
		break;
	case 'm': returnChar = 'm';
		break;
	case 'n': returnChar = 'n';
		break;
	case 'o': returnChar = 'o';
		break;
	case 'p': returnChar = 'p';
		break;
	case 'q': returnChar = 'q';
		break;
	case 'r': returnChar = 'r';
		break;
	case 's': returnChar = 's';
		break;
	case 't': returnChar = 't';
		break;
	case 'u': returnChar = 'u';
		break;
	case 'v': returnChar = 'v';
		break;
	case 'w': returnChar = 'w';
		break;
	case 'x': returnChar = 'x';
		break;
	case 'y': returnChar = 'y';
		break;
	case 'z': returnChar = 'z';
		break;
	case ';': returnChar = ';';
		break;
	case '\'': returnChar = '\'';
		break;
	case '-': returnChar = '-';
		break;
	}

	return returnChar;

}

//Given a character and a keyboard layout, return the X and Y positions of that character on that layout.
void getCharPosition(int& posX, int& posY, char dummyKeyboard[11][4], char nextChar)
{
	for (int i = 0; i<11; i++)
	{
		for (int j = 0; j<4; j++)
		{
			if (nextChar == dummyKeyboard[i][j])
			{
				posX = i;
				posY = j;
			}
		}
	}
}


//set the position of each finger on each hand to its starting position on the home row.
void resetFingerPositions()
{
	for (int i = 0; i<4; i++)
	{
		leftHand.fingers[i].positionX = i;
		leftHand.fingers[i].positionY = 2;
	}

	for (int j = 6; j <= 9; j++)
	{
		rightHand.fingers[j - 6].positionX = j;
		rightHand.fingers[j - 6].positionY = 2;
	}
}

//concatenate the words from sentencebank[sentencenumber] into one string.
//store that string in typeSentence.
void prepareSentence(int sentenceNumber)
{
	typeSentence.clear();
	for (int i = 0; i<sentenceLength; i++)
	{
		typeSentence = typeSentence + sentenceBank[sentenceNumber][i];
	}
}

void prepareSentence2(int sentenceNumber)
{
	typeSentence.clear();
	for (int i = 0; i<sentenceLength; i++)
	{
		typeSentence = typeSentence + sentenceBank2[sentenceNumber][i];
	}
}



void main()
{
	srand (time(NULL));
	
	populateQWERTY();
	populateDSK();
	cout << "Let's go!\n";
	populateWordBank();

	cout << "Typing with DSK...\n";

	leftHand.fingers[0].territory[0] = '1';
	leftHand.fingers[0].territory[1] = '\'';
	leftHand.fingers[0].territory[2] = ';';
	leftHand.fingers[0].territory[3] = 'a';
	leftHand.fingers[1].territory[0] = '2';
	leftHand.fingers[1].territory[1] = ',';
	leftHand.fingers[1].territory[2] = 'q';
	leftHand.fingers[1].territory[3] = 'o';
	leftHand.fingers[2].territory[0] = '3';
	leftHand.fingers[2].territory[1] = '.';
	leftHand.fingers[2].territory[2] = 'j';
	leftHand.fingers[2].territory[3] = 'e';
	leftHand.fingers[3].territory[0] = '4';
	leftHand.fingers[3].territory[1] = 'p';
	leftHand.fingers[3].territory[2] = 'k';
	leftHand.fingers[3].territory[3] = 'u';
	leftHand.fingers[3].territory[4] = '5';
	leftHand.fingers[3].territory[5] = 'y';
	leftHand.fingers[3].territory[6] = 'x';
	leftHand.fingers[3].territory[7] = 'i';

	rightHand.fingers[0].territory[0] = '6';
	rightHand.fingers[0].territory[1] = 'f';
	rightHand.fingers[0].territory[2] = 'b';
	rightHand.fingers[0].territory[3] = 'd';
	rightHand.fingers[0].territory[4] = '7';
	rightHand.fingers[0].territory[5] = 'g';
	rightHand.fingers[0].territory[6] = 'm';
	rightHand.fingers[0].territory[7] = 'h';
	rightHand.fingers[1].territory[0] = '8';
	rightHand.fingers[1].territory[1] = 'c';
	rightHand.fingers[1].territory[2] = 'w';
	rightHand.fingers[1].territory[3] = 't';
	rightHand.fingers[2].territory[0] = '9';
	rightHand.fingers[2].territory[1] = 'r';
	rightHand.fingers[2].territory[2] = 'v';
	rightHand.fingers[2].territory[3] = 'n';
	rightHand.fingers[3].territory[0] = '0';
	rightHand.fingers[3].territory[1] = 'l';
	rightHand.fingers[3].territory[2] = 'z';
	rightHand.fingers[3].territory[3] = 's';
	rightHand.fingers[3].territory[4] = '[';
	rightHand.fingers[3].territory[5] = '/';
	rightHand.fingers[3].territory[6] = '-'; //put the hands in DSK typing mode


	for(int j = 0; j<numSentences; j++)
	{
	    resetFingerPositions(); //move all fingers back to home row before typing each sentence.
	    prepareSentence(j);     //concatenate the words of the current sentence into one string.
        counter = 0;            //reset the position of the nextChar in the current sentence. Start typing the new sentence from the first character.
		//cout<<"Typing sentence: "<< j+1 << " with DSK.\n";

		do{
			nextChar = getNextChar(typeSentence, counter);
			getCharPosition(x,y,DSK,nextChar);
		
			if (x<5) //all characters with x coordinate < 5 (to the left of the 6 key column) are left hand territory.
			{

				closestFinger = leftHand.findClosestFinger(nextChar);

				cSquared = 
				float(
					   (
					    (x - leftHand.fingers[closestFinger].positionX) * (x - leftHand.fingers[closestFinger].positionX)
					   )
				       +
					   (
				        (y - leftHand.fingers[closestFinger].positionY) * (y - leftHand.fingers[closestFinger].positionY)
					   )
					 );
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedDSK[j] = (distanceMovedDSK[j] + sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points				
				
				leftHand.fingers[closestFinger].move(x, y); //move that finger to the position of the char it just typed.

				/*
				if (nextChar == '.')
				{
					cout << "For sentence " << j+1 << ", DSK moved " << distanceMovedDSK[j] << " units.\n";
				}
				
				cout << "Nextchar is: " << nextChar << endl;
				cout << "Closest finger is: lefthand" << closestFinger << endl;
				cout << "lefthand finger " << closestFinger << " coordinates: x = " << leftHand.fingers[closestFinger].positionX <<
					" coordinates y = " << leftHand.fingers[closestFinger].positionY << endl;
				cout << "That finger moved a whole " << sqrt(cSquared) << " units!" << endl;
				cout << "For sentence "<< j+1 << ", the fingers have moved a total of "<< distanceMovedDSK[j] << " units!" << endl;
				system("PAUSE");
				*/

			}
			
			else
		
			{//all characters with x coordinate >= 5 (to the right of the 6 key column and including the 6 key column) are right hand territory.

			        closestFinger = rightHand.findClosestFinger(nextChar);

			cSquared = 
	   		float(
				   (
					(x-rightHand.fingers[closestFinger].positionX) * (x-rightHand.fingers[closestFinger].positionX)
				   )
				   +
				   (
				    (y-rightHand.fingers[closestFinger].positionY) * (y-rightHand.fingers[closestFinger].positionY)
				   )
				 );
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedDSK[j] = (distanceMovedDSK[j] + sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points
							
				rightHand.fingers[closestFinger].move(x,y); //move that finger the the position of the char it just typed.

				/*
				if (nextChar == '.')
				{
					cout << "For sentence " << j+1 << ", DSK moved " << distanceMovedDSK[j] << " units.\n";
				}

				cout << "Nextchar is: " << nextChar << endl;
				cout << "Closest finger is: righthand" << closestFinger << endl;
				cout << "righthand finger " << closestFinger << " coordinates: x = " << rightHand.fingers[closestFinger].positionX <<
					" coordinates y = " << rightHand.fingers[closestFinger].positionY << endl;
				cout << "That finger moved a whole " << sqrt(cSquared) << " units!" << endl;
				cout << "For sentence "<< j+1 << ", the fingers have moved a total of "<< distanceMovedDSK[j] << " units!"<< endl;
				system("PAUSE");
				*/
				
			}

			counter++;

		}while(nextChar != '.'); //stop after the period at the end of the sentence is typed, then increase j by one and do the next sentence. 
	}

	//type the additional sentences in the sentenceBank2 structure with DSK

		for(int j = 0; j<numSentences; j++)
	{
	    resetFingerPositions(); //move all fingers back to home row before typing each sentence.
	    prepareSentence2(j);     //concatenate the words of the current sentence into one string.
        counter = 0;            //reset the position of the nextChar in the current sentence. Start typing the new sentence from the first character.
		//cout << "Typing sentence: " << numSentences + (numSentences - ((numSentences-1) - j)) << " with DSK.\n";
		do{
			nextChar = getNextChar(typeSentence, counter);
			getCharPosition(x,y,DSK,nextChar);
		
			if (x<5) //all characters with x coordinate < 5 (to the left of the 6 key column) are left hand territory.
			{

				closestFinger = leftHand.findClosestFinger(nextChar);

				cSquared = 
				float(
					   (
					    (x - leftHand.fingers[closestFinger].positionX) * (x - leftHand.fingers[closestFinger].positionX)
					   )
				       +
					   (
				        (y - leftHand.fingers[closestFinger].positionY) * (y - leftHand.fingers[closestFinger].positionY)
					   )
					 );
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedDSK[(numSentences + (numSentences - ((numSentences-1) - j)))-1] = distanceMovedDSK[(numSentences + (numSentences - ((numSentences-1) - j)))-1] + (sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points				
				
				leftHand.fingers[closestFinger].move(x, y); //move that finger to the position of the char it just typed.

				/*
				if (nextChar == '.')
				{
					cout << "For sentence " << numSentences + (numSentences - ((numSentences-1) - j)) << ", DSK moved " << distanceMovedDSK[(numSentences + (numSentences - ((numSentences-1) - j)))-1] << " units.\n";
				}

				cout << "Nextchar is: " << nextChar << endl;
				cout << "Closest finger is: lefthand" << closestFinger << endl;
				cout << "lefthand finger " << closestFinger << " coordinates: x = " << leftHand.fingers[closestFinger].positionX <<
					" coordinates y = " << leftHand.fingers[closestFinger].positionY << endl;
				cout << "That finger moved a whole " << sqrt(cSquared) << " units!" << endl;
				cout << "For sentence "<< (numSentences + (numSentences - ((numSentences-1) - j))) << ", the fingers have moved a total of "<< distanceMovedDSK[(numSentences + (numSentences - ((numSentences-1) - j)))-1] << " units!" << endl;
				system("PAUSE");
				*/

			}
			
			else
		
			{//all characters with x coordinate >= 5 (to the right of the 6 key column and including the 6 key column) are right hand territory.

			        closestFinger = rightHand.findClosestFinger(nextChar);

			cSquared = 
	   		float(
				   (
					(x-rightHand.fingers[closestFinger].positionX) * (x-rightHand.fingers[closestFinger].positionX)
				   )
				   +
				   (
				    (y-rightHand.fingers[closestFinger].positionY) * (y-rightHand.fingers[closestFinger].positionY)
				   )
				 );
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedDSK[(numSentences + (numSentences - ((numSentences-1) - j)))-1] = distanceMovedDSK[(numSentences + (numSentences - ((numSentences-1) - j)))-1] + (sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points
							
				rightHand.fingers[closestFinger].move(x,y); //move that finger the the position of the char it just typed.

				/*
				if (nextChar == '.')
				{
					cout << "For sentence " << numSentences + (numSentences - ((numSentences-1) - j)) << ", DSK moved " << distanceMovedDSK[(numSentences + (numSentences - ((numSentences-1) - j)))-1] << " units.\n";
				}

				cout << "Nextchar is: " << nextChar << endl;
				cout << "Closest finger is: righthand" << closestFinger << endl;
				cout << "righthand finger " << closestFinger << " coordinates: x = " << rightHand.fingers[closestFinger].positionX <<
					" coordinates y = " << rightHand.fingers[closestFinger].positionY << endl;
				cout << "That finger moved a whole " << sqrt(cSquared) << " units!" << endl;
				cout << "For sentence "<< (numSentences + (numSentences - ((numSentences-1) - j))) << ", the fingers have moved a total of "<< distanceMovedDSK[(numSentences + (numSentences - ((numSentences-1) - j)))-1] << " units!"<< endl;
				system("PAUSE");
				*/
				
			}

			counter++;

		}while(nextChar != '.'); //stop after the period at the end of the sentence is typed, then increase j by one and do the next sentence. 
	} //end DSK typing mode.

	cout << "Typing with QWERTY...\n";

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
	rightHand.fingers[0].territory[4] = '7';
	rightHand.fingers[0].territory[5] = 'u';
	rightHand.fingers[0].territory[6] = 'j';
	rightHand.fingers[0].territory[7] = 'm';
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
	rightHand.fingers[3].territory[6] = '\''; //put the hands into QWERTY typing mode.

	for (int i = 0; i<numSentences; i++)
	{
		resetFingerPositions(); //move all fingers back to home row before typing each sentence.
		prepareSentence(i);     //concatenate the words of the current sentence into one string.
		counter = 0;            //reset the position of the nextChar in the current sentence. Start typing the new sentence from the first character.
		//cout << "Typing sentence: " << i+1 << " with QWERTY.\n";

		do{
			nextChar = getNextChar(typeSentence, counter);
			getCharPosition(x, y, QWERTY, nextChar);

			if (x<5) //all characters with x coordinate < 5 (to the left of the 6 key column) are left hand territory.
			{

			        closestFinger = leftHand.findClosestFinger(nextChar);

				cSquared = 
				float(
					   (
					    (x - leftHand.fingers[closestFinger].positionX) * (x - leftHand.fingers[closestFinger].positionX)
					   )
				       +
					   (
				        (y - leftHand.fingers[closestFinger].positionY) * (y - leftHand.fingers[closestFinger].positionY)
					   )
					 );
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedQWERTY[i] = (distanceMovedQWERTY[i] + sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points 


				leftHand.fingers[closestFinger].move(x, y); //move that finger to the position of the char it just typed

				/*
				if (nextChar == '.')
				{
					cout << "For sentence " << i+1 << ", QWERTY moved " << distanceMovedQWERTY[i] << " units.\n";
				}

				cout << "Nextchar is: " << nextChar << endl;
				cout << "Closest finger is: lefthand" << closestFinger << endl;
				cout << "lefthand finger " << closestFinger << " coordinates: x = " << leftHand.fingers[closestFinger].positionX <<
					" coordinates y = " << leftHand.fingers[closestFinger].positionY << endl;
				cout << "That finger moved a whole " << sqrt(cSquared) << " units!" << endl;
				cout << "For sentence "<< i+1 << ", the fingers have moved a total of "<< distanceMovedQWERTY[i] << " units!"<< endl;
				system("PAUSE");
				*/
			}
			
			else //all characters with x coordinate >= 5 (to the right of the 6 key column and including the 6 key column) are right hand territory.
				
			{
				closestFinger = rightHand.findClosestFinger(nextChar);

			cSquared = 
	   		float(
				   (
					(x-rightHand.fingers[closestFinger].positionX) * (x-rightHand.fingers[closestFinger].positionX)
				   )
				   +
				   (
				    (y-rightHand.fingers[closestFinger].positionY) * (y-rightHand.fingers[closestFinger].positionY)
				   )
				 );
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedQWERTY[i] = (distanceMovedQWERTY[i] + sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points 


				rightHand.fingers[closestFinger].move(x, y); //move that finger to the position of the char it just typed

				/*
				if (nextChar == '.')
				{
					cout << "For sentence " << i+1 << ", QWERTY moved " << distanceMovedQWERTY[i] << " units.\n";
				}
				
				cout << "Nextchar is: " << nextChar << endl;
				cout << "Closest finger is: righthand" << closestFinger << endl;
				cout << "righthand finger " << closestFinger << " coordinates: x = " << rightHand.fingers[closestFinger].positionX <<
					" coordinates y = " << rightHand.fingers[closestFinger].positionY << endl;
				cout << "That finger moved a whole " << sqrt(cSquared) << " units!" << endl;
				cout << "For sentence "<< i+1 << ", the fingers have moved a total of "<< distanceMovedQWERTY[i] << " units!"<< endl;
				system("PAUSE");
				*/
			}

			counter++;

		} while (nextChar != '.'); //stop after the period at the end of the sentence is typed, then increase i by one and do the next sentence. 
	} 

	//type the additional sentences in the sentenceBank2 structure with QWERTY.

	for (int i = 0; i<numSentences; i++)
	{
		resetFingerPositions(); //move all fingers back to home row before typing each sentence.
		prepareSentence2(i);     //concatenate the words of the current sentence into one string.
		counter = 0;            //reset the position of the nextChar in the current sentence. Start typing the new sentence from the first character.
		//cout << "Typing sentence: " << numSentences + (numSentences - ((numSentences-1) - i)) << " with QWERTY.\n";
		do{
			nextChar = getNextChar(typeSentence, counter);
			getCharPosition(x, y, QWERTY, nextChar);

			if (x<5) //all characters with x coordinate < 5 (to the left of the 6 key column) are left hand territory.
			{

			        closestFinger = leftHand.findClosestFinger(nextChar);

				cSquared = 
				float(
					   (
					    (x - leftHand.fingers[closestFinger].positionX) * (x - leftHand.fingers[closestFinger].positionX)
					   )
				       +
					   (
				        (y - leftHand.fingers[closestFinger].positionY) * (y - leftHand.fingers[closestFinger].positionY)
					   )
					 );
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedQWERTY[(numSentences + (numSentences - ((numSentences-1) - i)))-1] = distanceMovedQWERTY[(numSentences + (numSentences - ((numSentences-1) - i)))-1] + (sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points 


				leftHand.fingers[closestFinger].move(x, y); //move that finger to the position of the char it just typed

				/*
				if (nextChar == '.')
				{
					cout << "For sentence " << numSentences + (numSentences - ((numSentences-1) - i)) << ", QWERTY moved " << distanceMovedQWERTY[(numSentences + (numSentences - ((numSentences-1) - i)))-1] << " units.\n";
				}

				cout << "Nextchar is: " << nextChar << endl;
				cout << "Closest finger is: lefthand" << closestFinger << endl;
				cout << "lefthand finger " << closestFinger << " coordinates: x = " << leftHand.fingers[closestFinger].positionX <<
					" coordinates y = " << leftHand.fingers[closestFinger].positionY << endl;
				cout << "That finger moved a whole " << sqrt(cSquared) << " units!" << endl;
				cout << "For sentence "<< (numSentences + (numSentences - ((numSentences-1) - i))) << ", the fingers have moved a total of "<< distanceMovedQWERTY[(numSentences + (numSentences - ((numSentences-1) - i)))-1] << " units!"<< endl;
				system("PAUSE");
				*/
			}
			
			else //all characters with x coordinate >= 5 (to the right of the 6 key column and including the 6 key column) are right hand territory.
				
			{
				closestFinger = rightHand.findClosestFinger(nextChar);

			cSquared = 
	   		float(
				   (
					(x-rightHand.fingers[closestFinger].positionX) * (x-rightHand.fingers[closestFinger].positionX)
				   )
				   +
				   (
				    (y-rightHand.fingers[closestFinger].positionY) * (y-rightHand.fingers[closestFinger].positionY)
				   )
				 );
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedQWERTY[(numSentences + (numSentences - ((numSentences-1) - i)))-1] = distanceMovedQWERTY[(numSentences + (numSentences - ((numSentences-1) - i)))-1] + (sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points 


				rightHand.fingers[closestFinger].move(x, y); //move that finger to the position of the char it just typed

				/*
				if (nextChar == '.')
				{
					cout << "For sentence " << numSentences + (numSentences - ((numSentences-1) - i)) << ", QWERTY moved " << distanceMovedQWERTY[(numSentences + (numSentences - ((numSentences-1) - i)))-1] << " units.\n";
				}
				
				cout << "Nextchar is: " << nextChar << endl;
				cout << "Closest finger is: righthand" << closestFinger << endl;
				cout << "righthand finger " << closestFinger << " coordinates: x = " << rightHand.fingers[closestFinger].positionX <<
					" coordinates y = " << rightHand.fingers[closestFinger].positionY << endl;
				cout << "That finger moved a whole " << sqrt(cSquared) << " units!" << endl;
				cout << "For sentence "<< (numSentences + (numSentences - ((numSentences-1) - i))) << ", the fingers have moved a total of "<< distanceMovedQWERTY[(numSentences + (numSentences - ((numSentences-1) - i)))-1] << " units!"<< endl;
				system("PAUSE");
				*/
			}

			counter++;

		} while (nextChar != '.'); //stop after the period at the end of the sentence is typed, then increase i by one and do the next sentence. 
	}  //end QWERTY typing mode

	for (int k = 0; k < numSentences*2; k++)
	{
		QWERTYDistanceTotal = QWERTYDistanceTotal + distanceMovedQWERTY[k];
	}
	 //calculate the total distances moved for each layout. 

	for (int l = 0; l < numSentences*2; l++)
	{
		DSKDistanceTotal = DSKDistanceTotal + distanceMovedDSK[l];
	}

	/*
	for (int k = 0; k < numSentences*2; k++)
	{
		cout << "For sentence " << k+1 << ", QWERTY typist moved " << distanceMovedQWERTY[k]<< " units.\n";
	}

	for (int l = 0; l < numSentences*2; l++)
	{
		cout << "For sentence " << l+1 << ", DSK typist moved " << distanceMovedDSK[l]<< " units.\n";
	}
	*/

	float QWERTYDistanceTotalAverage = (QWERTYDistanceTotal/float(numSentences*2));
	float DSKDistanceTotalAverage = (DSKDistanceTotal/float(numSentences*2));

	cout<<"\n";
	cout<<numSentences*2<<" sentences were typed for each layout.\n";
	cout<<"On average, the QWERTY typist moved their fingers "<<QWERTYDistanceTotalAverage<<" units per sentence.\n";
	cout<<"On average, the DSK typist moved their fingers "<< DSKDistanceTotalAverage<<" units per sentence.\n";

	if (QWERTYDistanceTotalAverage > DSKDistanceTotalAverage)
	{
		cout<<"The DSK typist moved their fingers "<< ((QWERTYDistanceTotalAverage - DSKDistanceTotalAverage) / QWERTYDistanceTotalAverage) * 100 <<"% less on average.\n";
	}

	else if (QWERTYDistanceTotalAverage < DSKDistanceTotalAverage)
	{
		cout<<"The QWERTY typist moved their fingers "<< ((DSKDistanceTotalAverage - QWERTYDistanceTotalAverage) / DSKDistanceTotalAverage) * 100 <<"% less on average.\n";
	}

	else
	{
		cout<<"Both layouts performed equally well.\n";
	}


	system("PAUSE");
}

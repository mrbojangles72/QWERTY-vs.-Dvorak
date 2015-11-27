#include "hand.h"  //jazz hands
#include <iostream>//cout and such
#include <fstream> //for working with 5KCW.txt
#include <cstdlib>
#include <ctime> //random
#include <cmath> //sqrt
#include <string> //basically the whole project
using namespace std;

        hand leftHand;           //virtual jazz hands!
		hand rightHand;

		const int numSentences = 1;  //change how many sentences to type
		const int sentenceLength =11;//change how many words in each sentence. Last one will always be '.'    

		float cSquared = 0; //for use in calculating the distance between a finger's position and the nextChar's position.
		float QWERTYDistanceTotal = 0; //for use in calculating the average distance used to type a sentence with QWERTY.
		float DSKDistanceTotal = 0;    // for  use in calculating the average distance used to type a sentence with DSK.

		int x = 0;  //X position of nextChar.
		int y = 0;  //Y position of nextChar.
		int counter = 0; //Used to pass a position from the main() to the getCharPosition method.

		float distanceMovedDSK[numSentences]; //array used to store the distances moved for each sentence on DSK
		float distanceMovedQWERTY[numSentences]; //array used to store the distances moved for each sentence on QWERTY

	    string wordBank[5008]; //filled with words from 5KCW.txt
		string sentenceBank[numSentences][sentenceLength]; //filled with random sentences.
		char QWERTY[11][4]; //QWERTY keyboard.
		char DSK[11][4];    //Dvorak keyboard.

		string typeSentence; //used to store concatenated words from the columns of sentenceBank.

		char nextChar; //used to store the next char that a given finger must type.

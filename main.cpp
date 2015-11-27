#include "methods.h"

void main()
{
	srand (time(NULL));
	
	populateQWERTY();
	populateDSK();
	populateWordBank();
	populateSentenceBank();

	cout<<"Typing with QWERTY...\n";

	setTerritoryQWERTY(); //put the hands into QWERTY typing mode.

	for(int i = 0; i<numSentences; i++)
	{
		resetFingerPositions(); //move all fingers back to home row before typing each sentence.
		prepareSentence(i);     //concatenate the words of the current sentence into one string.
		counter = 0;            //reset the position of the nextChar in the current sentence. Start typing the new sentence from the first character.

		do{
			nextChar = getNextChar(typeSentence,counter); 
			getCharPosition(x,y,QWERTY,nextChar); 

			if (x<5) //all characters with x coordinate < 5 (to the left of the 6 key) are left hand territory.
			{
				cSquared = 
	   		float(((x-leftHand.fingers[leftHand.findClosestFinger(nextChar)].positionX) * (x-leftHand.fingers[leftHand.findClosestFinger(nextChar)].positionX)
				+
				(y-leftHand.fingers[leftHand.findClosestFinger(nextChar)].positionY) * (y-leftHand.fingers[leftHand.findClosestFinger(nextChar)].positionY)));
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedQWERTY[i] = (distanceMovedQWERTY[i] + sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points 
				
				
				leftHand.fingers[leftHand.findClosestFinger(nextChar)].move(x,y); //move that finger to the position of the char it just typed
			}
			/***********************/
			else
		    /***********************/
			{//all characters with x coordinate >= 5 (to the right of the 6 key and including the 6 key row) are right hand territory.
				cSquared = 
	   		float((((x-rightHand.fingers[rightHand.findClosestFinger(nextChar)].positionX) * (x-rightHand.fingers[rightHand.findClosestFinger(nextChar)].positionX))
				+
				((y-rightHand.fingers[rightHand.findClosestFinger(nextChar)].positionY) * (y-rightHand.fingers[rightHand.findClosestFinger(nextChar)].positionY))));
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedQWERTY[i] = (distanceMovedQWERTY[i] + sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points 
				
				
				rightHand.fingers[rightHand.findClosestFinger(nextChar)].move(x,y); //move that finger to the position of the char it just typed
			}

			counter++;

		}while(nextChar != '.'); //stop after the period at the end of the sentence is typed, then increase i by one and do the next sentence. 
	}  //end QWERTY typing mode

	cout<<"Typing with DSK...\n";
	/********************************************************************/
	setTerritoryDSK(); //put the hands in DSK typing mode and do it all again.
	/********************************************************************/

	for(int j = 0; j<numSentences; j++)
	{
		resetFingerPositions(); //move all fingers back to home row before typing each sentence.
		prepareSentence(j);     //concatenate the words of the current sentence into one string.
		counter = 0;            //reset the position of the nextChar in the current sentence. Start typing the new sentence from the first character.

		do{
			nextChar = getNextChar(typeSentence,counter);
			getCharPosition(x,y,QWERTY,nextChar); 

			if (x<5) //all characters with x coordinate < 5 (to the left of the 6 key) are left hand territory.
			{
				cSquared = 
	   		float(((x-leftHand.fingers[leftHand.findClosestFinger(nextChar)].positionX) * (x-leftHand.fingers[leftHand.findClosestFinger(nextChar)].positionX)
				+
				(y-leftHand.fingers[leftHand.findClosestFinger(nextChar)].positionY) * (y-leftHand.fingers[leftHand.findClosestFinger(nextChar)].positionY)));
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedDSK[j] = (distanceMovedDSK[j] + sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points 
				
				
				leftHand.fingers[leftHand.findClosestFinger(nextChar)].move(x,y); //move that finger to the position of the char it just typed.
			}
			/***********************/
			else
		    /***********************/
			{//all characters with x coordinate >= 5 (to the right of the 6 key and including the 6 key row) are right hand territory.
				cSquared = 
	   		float((((x-rightHand.fingers[rightHand.findClosestFinger(nextChar)].positionX) * (x-rightHand.fingers[rightHand.findClosestFinger(nextChar)].positionX))
				+
				((y-rightHand.fingers[rightHand.findClosestFinger(nextChar)].positionY) * (y-rightHand.fingers[rightHand.findClosestFinger(nextChar)].positionY))));
				//(x2-x1)^2 + (y2-y1)^2

				distanceMovedDSK[j] = (distanceMovedDSK[j] + sqrt(cSquared)); //sqrt(  (x2-x1)^2 + (y2+y1)^2   ); formula for distance between two points 
				
				
				rightHand.fingers[rightHand.findClosestFinger(nextChar)].move(x,y); //move that finger the the position of the char it just typed.
			}

			counter++;

		}while(nextChar != '.'); //stop after the period at the end of the sentence is typed, then increase i by one and do the next sentence. 
	}

	for (int k = 0; k < numSentences; k++)
	{
		QWERTYDistanceTotal = QWERTYDistanceTotal + distanceMovedQWERTY[k];
	}
	 //calculate the total distances moved for each layout. 

	for (int l = 0; l < numSentences; l++)
	{
		DSKDistanceTotal = DSKDistanceTotal + distanceMovedDSK[l];
	}

	cout<<"\n";
	cout<<numSentences<<" sentences were typed for each layout.\n";
	cout<<"On average, the QWERTY typist moved their fingers "<<(QWERTYDistanceTotal/float(numSentences))<<" units per sentence.\n";
	cout<<"On average, the DSK typist moved their fingers "<<(DSKDistanceTotal/float(numSentences))<<" units per sentence.\n";


	system("PAUSE");
}

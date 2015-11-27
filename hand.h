#include "finger.h"


class hand{	

	public:

		finger fingers[4]; //each hand has 4 fingers that will type. Thumbs are for spacebar use only.

		//given a character, returns the finger # that will type the next character.
		int findClosestFinger(char myChar){ 

			int closestFinger;

			for (int i = 0; i<4; i++)
			{
				for (int j = 0; j<8; j++)
				{
					if (fingers[i].territory[j] = myChar)
					{
						closestFinger = i;
					}
				}
			}

			return closestFinger;

		}

};

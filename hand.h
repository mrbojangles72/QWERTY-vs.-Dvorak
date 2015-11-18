#include "finger.h"


class hand{	

	public:

		int distanceMoved;
		int i,j;

		finger fingers[4];

		int findClosestFinger(char myChar){ //returns the finger # that will type the next character.

			int closestFinger;

			for (i = 0; i<4; i++)
			{
				for (j = 0; j<8; j++)
				{
					if (fingers[i].territory[j] = myChar)
					{
						closestFinger = i;
						i = 4;
						j = 6;
					}
				}
			}

			i = 0;
			j = 0;

			return closestFinger;

		}

};

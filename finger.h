class finger{

	public:
		int positionX,positionY; // x and y positions of each finger

		char territory[8]; //array of characters used to store the letters/symbols that a given finger 
						   //will be responsible for typing.
		
		//set the (X,Y) position of a finger to (A,B)
		void move(int a, int b)
		{
			positionX = a;     
			positionY = b;
		}

};

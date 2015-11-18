class finger{

	public:
		int positionX,positionY;
		int lastPositionX,lastPositionY;

		char territory[8];

		int getPositionX()
		{
			return positionX;
		}

		int getPositionY()
		{
			return positionY;
		}

		void setLastPosition()
		{
			lastPositionX = positionX;
			lastPositionY = positionY;
		}
		
		void move(int a, int b)
		{
			positionX = a;
			positionY = b;
		}

};

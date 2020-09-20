#include "Robots_Modified.h"
#include "randgen.h"
#include "MiniFW_Modified.h"

void myrobotMovement(Robot&myrobot) //this function is for the movements of the "myrobot" by pressing the some keys
{
	if (IsPressed(keyRightArrow))
	{
		myrobot.TurnFace(east);
		myrobot.Move();
	}
	else if (IsPressed(keyUpArrow))
	{
		myrobot.TurnFace(north);
		myrobot.Move();
	}
	else if (IsPressed(keyDownArrow))
	{
		myrobot.TurnFace(south);
		myrobot.Move();
	}
}

void monsterMovement(Robot&Monster1, Robot&Monster2, Robot&Monster3, Robot&Monster4) /* this function is for the movements of the "monster robots" 
by pressing some keys */
{
	RandGen random; //generating a random number
	int number = random.RandInt(1,4); //assigning the random number to a number to choose which monster robot has to move 

	// if the monster robots are not alive, they resurrect again
	if (!Monster1.IsAlive()) 
		Monster1.Resurrect();
	if (!Monster2.IsAlive())
		Monster2.Resurrect();
	if (!Monster3.IsAlive())
		Monster3.Resurrect();
	if (!Monster4.IsAlive())
		Monster4.Resurrect();

	if (number == 1) // if number 1 is chosen then Monster1 is performing its movement
	{
		if(!Monster1.FacingWall())
			Monster1.Move();
		else
		{
			Monster1.TurnBack();
			Monster1.Move();
		}
	}
	else if (number == 2) // if number 2 is chosen then Monster2 is performing its movement
	{
		if(!Monster2.FacingWall())
			Monster2.Move();
		else
		{
			while(Monster2.FacingWall()) //since there is a chance to face a wall although the monster2 turns right, while loop fixes that problem
			{
				Monster2.TurnRight();
			}
			Monster2.Move();
		}
	}
	else if (number == 3) // if number 3 is chosen then Monster3 is performing its movement
	{
		if(!Monster3.FacingWall())
			Monster3.Move();
		else
		{
			while(Monster3.FacingWall()) //since there is a chance to face a wall although the Monster3 turns right, while loop fixes that problem
			{
				Monster3.TurnRight();
			}
			Monster3.Move();
		}
	}
	else if (number == 4) // if number 4 is chosen then Monster4 is performing its movement
	{
		if(!Monster4.FacingWall())
			Monster4.Move();
		else
		{
			Monster4.TurnBack();
			Monster4.Move();
		}
	}
}

bool checker(Robot&myrobot) // this function checks the winning condition of the game which is x=14 & y=4
{
	if (myrobot.GetXCoordinate() == 14 && myrobot.GetYCoordinate() == 4)
	{
		if( myrobot.GetBagCount() >= 50)
			ShowMessage("Congratulations, you win!");
		else
			ShowMessage("You reached the end but could not gather enough things... You lost the Game!");
		return false;
	}
	return true;
}

int main()
{
	Robot myrobot (0, 4, east); //creating the robots according to given properties
	myrobot.SetColor(green);
	Robot Monster1 (3, 8, south);
	Monster1.SetColor(red);
	Robot Monster2 (6, 2, east);
	Monster2.SetColor(blue);
	Robot Monster3 (13, 5, east);
	Monster3.SetColor(blue);
	Robot Monster4 (13, 0, north);
	Monster4.SetColor(red);

	bool specialCond = false; /* special condition is basically this: if "space" is pressed and the "myrobot" has more than or equal to 20 things in its bag, 
	then specia condition kicks in */

	int lives = 3;
	while(myrobot.IsAlive() && lives > 0 && checker(myrobot)) //3 conditions to be able to continue to play the game
	{
		if(!specialCond) //when there is no special condition for the game
		{
			monsterMovement(Monster1, Monster2, Monster3, Monster4);
			myrobotMovement(myrobot);
			if (!myrobot.IsAlive()) //when the "myrobot" is not alive, this is the function to ressurect it and decreased its lives
			{
				lives--;
				if (lives == 2)
					ShowMessage("You have 2 lives!");
				else if (lives == 1)
					ShowMessage("You have only 1 life!");
				else if (lives == 0)
				{
					ShowMessage("You have no lives left");
					ShowMessage("You run out of lives... You lost the Game!");
				}
				myrobot.Resurrect();
				Monster1.Resurrect();
				Monster2.Resurrect();
				Monster3.Resurrect();
				Monster4.Resurrect();
			}
			if(IsPressed(keySpace) && myrobot.GetBagCount() >= 20) //this function is for the special condition
			{
				if ( (Monster2.GetXCoordinate() == 14 && Monster2.GetYCoordinate() == 4) || (Monster3.GetXCoordinate() == 14 && Monster3.GetYCoordinate() == 4) )
				{
					ShowMessage("You blocked the target.. You lost the Game!");
					lives = lives - 3; //the purpose is to exit the loop and reach the end of the game
				}	
				specialCond = true;
				for (int i=20; i > 0; i--) //decreasing the 20 things from "myrobot"s bag
				{
					myrobot.SetBagCount();
				}
			}
			myrobot.PickAllThings();
		} 
		else if (specialCond) //if the special condition kicks in (specialCond is true), this function works
		{
			myrobotMovement(myrobot); //the same actions happen except the monster robots' movements
			if (!myrobot.IsAlive())
			{
				lives--;
				if (lives == 2)
					ShowMessage("You have 2 lives left!");
				else if (lives == 1)
					ShowMessage("You have only 1 life left!");
				else if (lives == 0)
				{
					ShowMessage("You have no lives left");
					ShowMessage("You run out of lives... You lost the Game!");
				}
				myrobot.Resurrect();
				Monster1.Resurrect();
				Monster2.Resurrect();
				Monster3.Resurrect();
				Monster4.Resurrect();
			}
			myrobot.PickAllThings();
		}
	}
	return 0;
}
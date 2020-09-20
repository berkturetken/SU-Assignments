#include "robots.h"
#include <string>
//berk turetken

bool checker (Robot & r) // checking the robot whether it is crashing the wall or not
{
	if (r.FacingWall())
	{
		return false;
	}
	else 
	{
		return true;
	}
}

void TurnLeft (Robot & r) //instead of writing 3 times TurnRight to turn left each time, defining a TurnLeft function
{
	r.TurnRight();
	r.TurnRight();
	r.TurnRight();
}

void Movement_1 (Robot & r1, Robot & r2) // the function that makes the robots move 1 unit (square)
{
	r1.TurnRight();
	TurnLeft(r2);
	if (checker(r1))
	{
		r1.Move(1);
		r2.Move(1); /* do not have to check the each movement of the mirror robot because the mirror robot obviously
					doesn't face the wall if the original robot does not face the wall */
		r1.TurnRight();
		TurnLeft(r2);
		if (checker(r1))
		{
			r1.Move(1);
			r2.Move(1);
			r1.TurnRight();
			TurnLeft(r2);
		}
		else
			ShowMessage("Robots encountered a wall. End of the spiral.");
	}
	else
		ShowMessage("Robots encountered a wall. End of the spiral.");
}

void Movement_2(Robot & r1, Robot & r2)  // the function that makes the robots move 2 unit (square)
{
	if (checker(r1))
	{
		r1.Move();
		if (checker(r1))
		{
			r1.Move();
			r2.Move(2); /* do not have to check the each movement of the mirror robot because the mirror robot obviously
						doesn't face the wall if the original robot does not face the wall */
			r1.TurnRight();
			TurnLeft(r2);
			if (checker(r1))
			{
				r1.Move();
				if (checker(r1))
				{
					r1.Move();
					r2.Move(2); /* do not have to check the each movement of the mirror robot because the mirror robot obviously
								doesn't face the wall if the original robot does not face the wall */
					r1.SetColor(green); //changing the color of the robots if there is no crash until that movement
					r2.SetColor(purple);
					r1.TurnRight();
					TurnLeft(r2);
				}
				else
				{
					r2.Move();
					ShowMessage("Robots encountered a wall. End of the spiral.");
				}
			}
			else
				ShowMessage("Robots encountered a wall. End of the spiral.");
		}
		else
		{
			r2.Move();
			ShowMessage("Robots encountered a wall. End of the spiral.");
		}
	}
}

void Movement_3 (Robot & r1, Robot & r2) // the function that makes the robots move 3 unit (square)
{
	if (checker(r1))
	{
		r1.Move();
		if (checker(r1))
		{
			r1.Move();
			if (checker(r1))
			{
				r1.Move();
				r2.Move(3); /* do not have to check the each movement of the mirror robot because the mirror robot obviously
							doesn't face the wall if the original robot does not face the wall */
				r1.TurnRight();
				TurnLeft(r2);
				if (checker(r1))
				{
					r1.Move();
					if (checker(r1))
					{
						r1.Move();
						if (checker(r1))
						{
							r1.Move();
							r2.Move(3); /* do not have to check the each movement of the mirror robot because the mirror robot obviously
										doesn't face the wall if the original robot does not face the wall */
							r1.TurnRight();
							TurnLeft(r2);
						}
						else
						{
							r2.Move(2);
							ShowMessage("Robots encountered a wall. End of the spiral.");
						}
					}
					else
						ShowMessage("Robots encountered a wall. End of the spiral.");
				}
				else
					ShowMessage("Robots encountered a wall. End of the spiral.");
			}
			else
			{
				r2.Move(2);
				ShowMessage("Robots encountered a wall. End of the spiral.");
			}
		}
		else
			ShowMessage("Robots encountered a wall. End of the spiral.");
	}
}

void Movement_4 (Robot & r1, Robot & r2) // the function that makes the robots move 3 unit (square)
{
	if (checker(r1))
	{
		r1.Move();
		if (checker(r1))
		{
			r1.Move();
			if (checker(r1))
			{
				r1.Move();
				if (checker(r1))
				{
					r1.Move();
					r2.Move(4); /* do not have to check the each movement of the mirror robot because the mirror robot obviously
								doesn't face the wall if the original robot does not face the wall */
					r1.TurnRight();
					TurnLeft(r2);
					if (checker(r1))
					{
						r1.Move();
						if (checker(r1))
						{
							r1.Move();
							if (checker(r1))
							{
								r1.Move();
								if (checker(r1))
								{
									r1.Move();
									r2.Move(4); /* do not have to check the each movement of the mirror robot because the mirror robot obviously
												doesn't face the wall if the original robot does not face the wall */
									ShowMessage("Robots completed the spiral.");
								}
								else
								{
									r2.Move(3);
									ShowMessage("Robots encountered a wall. End of the spiral.");
								}
							}
							else
								ShowMessage("Robots encountered a wall. End of the spiral.");
						}
						else
							ShowMessage("Robots encountered a wall. End of the spiral.");
					}
					else
						ShowMessage("Robots encountered a wall. End of the spiral.");
				}
				else
				{
					r2.Move(3);
					ShowMessage("Robots encountered a wall. End of the spiral.");
				}
			}
			else
				ShowMessage("Robots encountered a wall. End of the spiral.");
		}
		else
			ShowMessage("Robots encountered a wall. End of the spiral.");
	}
}


int main()
{
	ShowMessage("This program moves the original robot in a clockwise spiral and the mirror robot in a counter-clockwise spiral for two rounds");
	int xcoor, ycoor;
	GetInput("Please enter X position of the robot", xcoor);
	if( xcoor >= 0 && xcoor < 12)
	{
		GetInput("Please enter Y position of the robot", ycoor);
		if( ycoor >= 0 && ycoor < 12)
		{
			Robot b(xcoor, ycoor); // creating the robots if the coordinates satisfy from the user
			Robot mirror_b(23 - xcoor, ycoor, west);

			b.SetColor(blue); // setting the inital colors of the robots
			mirror_b.SetColor(red);

			Movement_1(b, mirror_b); // calling the every movement functions 
			Movement_2(b, mirror_b);
			Movement_3(b, mirror_b);
			Movement_4(b, mirror_b);
		}
		else
			ShowMessage("Invalid Y coordinate!");
	}		
	else
		ShowMessage("Invalid X coordinate!");

	return 0;
}
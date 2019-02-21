# Fighter-Plane-Game
A 3D Game, similar to a general fighter plane game, made in OpenGL

***Operating Keys***
- w to move forward
- a to rotate towards left
- s to move backward
- d to rotate towards right
- q to rotate plane anticlockwise
- e to rotate plane clockwise
- f for Plane View
- g for Top View
- h for Tower View
- j for Follow-cam View
- k for Helicopter-cam View
- z for looping-the-loop
- x for barrel roll(Bonus)
- Up Arrow to ascend(Bonus)
- Down Arrow to desend
- Left Mouse Click to fire missile
- Right Mouse Click to drop bombs

***Objectives in Game***
- Checkpoints is pointed by the arrow, which has a cannon (cylinder going up and down) as the guardian. Destroy all cylinders to conquer each checkpoint and win the game. Destroy Parachutes for some points
- Avoid proximity to Volcano, else the game will end
- Red cubes are fuel cans, they fill your fuel tank (capacity and current limit shown by red meter)
- Green meter is to show the altitude
- Pass through rings for points
- As a bonus, a special enemy is also implemented, the rotating cylinder which you can see for yourself. It will be destroyed when you hit it close to the rotating point

* Run the game:
	```console
	user@linux:~/Fighter-Plane-Game$ mkdir output
	user@linux:~/Fighter-Plane-Game$ cd output
	user@linux:~/Fighter-Plane-Game/output$ cmake ..
	user@linux:~/Fighter-Plane-Game/output$ make
	user@linux:~/Fighter-Plane-Game/output$ ./plane_game

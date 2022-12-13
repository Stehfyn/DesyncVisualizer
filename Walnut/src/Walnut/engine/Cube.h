#pragma once
#include "object.h"
class Cube : public Object
{
  public:
	  // (Part 2): Derive from Object as a base, then oveerride createVertices to define a different object.
	Cube();
	// (Part 2): Overload createVertices with a new implementation. Since Object draws using triangles, then we gotta define our
	// vertex/ index pairs in a way that draws triangles to make the 6 faces of a cube
	void createVertices() override;
	// (Part 2): This program's implementation is pretty static, so this function, run on construction, will override the randomness of the cube in the Initialize() of the parent Object 
	void doRandomPositionOrientation();
	// (Part 2): Update our object on each frame, dt as a parameter but goes unused since I didn't fix the time-step.
	// Cube will update rotation and translation, and assumes our z-axis is the other axis in the plane that makes up the floor (y is to the sky)

	// member that dictates rotation, controlled by processInput() in engine.h/cpp
	bool m_Clockwise = true;
};


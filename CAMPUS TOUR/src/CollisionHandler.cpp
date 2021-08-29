//Aurthor: Peter Neve
//Version: 1
//Date: 29/08/2021
//Purpose: defines wall collision for environment

#include "CollisionHandler.h"

//Objects
Camera cam;

//--------------------------------------------------------------------------------------
// Set up bounding boxes for collsion detection
//--------------------------------------------------------------------------------------
void CreateBoundingBoxes()
{
	// chanc block
	cam.SetAABBMaxX(0, 35879.0);
	cam.SetAABBMinX(0, 33808.0);
	cam.SetAABBMaxZ(0, 22096.0);
	cam.SetAABBMinZ(0, 4688.0);

	// between chanc block and phys sci
	cam.SetAABBMaxX(1, 35999.0);
	cam.SetAABBMinX(1, 35730.0);
	cam.SetAABBMaxZ(1, 25344.0);
	cam.SetAABBMinZ(1, 22096.0);

	// phy sci block panel 1
	cam.SetAABBMaxX(2, 35879.0);
	cam.SetAABBMinX(2, 33808.0);
	cam.SetAABBMaxZ(2, 26752.0);
	cam.SetAABBMinZ(2, 25344.0);

	// phy sci block 1st doorway
	cam.SetAABBMaxX(3, 35879.0);
	cam.SetAABBMinX(3, 34256.0);
	cam.SetAABBMaxZ(3, 27559.0);
	cam.SetAABBMinZ(3, 26752.0);

	// phy sci block 2nd panel
	cam.SetAABBMaxX(4, 35375.0);
	cam.SetAABBMinX(4, 33808.0);
	cam.SetAABBMaxZ(4, 36319.0);
	cam.SetAABBMinZ(4, 27559.0);


	//START    // box collision for front wall you see when you walk in the new room
	cam.SetAABBMaxX(5, 37750.0);  // old value 5, 40000.0
	cam.SetAABBMinX(5, 37500.0);   // 5, 36050.0
	cam.SetAABBMaxZ(5, 37855.0);  // 5, 37855.0
	cam.SetAABBMinZ(5, 35338.0);  // 5, 36319.0

	// adding collision with wall left to entrance of new room, one with the no smoking sign 
	cam.SetAABBMaxX(19, 34300.0);
	cam.SetAABBMinX(19, 34226.0);
	cam.SetAABBMaxZ(19, 36657.0);
	cam.SetAABBMinZ(19, 36300.0);

	// wall left side #1
	cam.SetAABBMaxX(20, 35555.0);
	cam.SetAABBMinX(20, 35491.0);
	cam.SetAABBMaxZ(20, 36434.0);
	cam.SetAABBMinZ(20, 35314.0);

	cam.SetAABBMaxX(21, 36379.0); // left side wall #2
	cam.SetAABBMinX(21, 35556.0);
	cam.SetAABBMaxZ(21, 35414.0);
	cam.SetAABBMinZ(21, 35314.0);

	cam.SetAABBMaxX(22, 36272.0); // wall to right when entering 
	cam.SetAABBMinX(22, 35423.0);
	cam.SetAABBMaxZ(22, 39166.0);
	cam.SetAABBMinZ(22, 39013.0);

	cam.SetAABBMaxX(23, 37595.0);
	cam.SetAABBMinX(23, 37395.0); // wall. right of entrance to hallway
	cam.SetAABBMaxZ(23, 38987.0);
	cam.SetAABBMinZ(23, 38732.0);

	//END


	// phy sci block 3rd panel
	cam.SetAABBMaxX(6, 35375.0);
	cam.SetAABBMinX(6, 33808.0);
	cam.SetAABBMaxZ(6, 41127.0);
	cam.SetAABBMinZ(6, 37855.0);

	// drinks machine
	cam.SetAABBMaxX(7, 35879.0);
	cam.SetAABBMinX(7, 34704.0);
	cam.SetAABBMaxZ(7, 25344.0);
	cam.SetAABBMinZ(7, 24996.0);

	// bottom of steps
	cam.SetAABBMaxX(8, 33808.0);
	cam.SetAABBMinX(8, 0.0);
	cam.SetAABBMaxZ(8, 4688.0);
	cam.SetAABBMinZ(8, 0.0);

	// end of phy sci block exit (top of steps)
	cam.SetAABBMaxX(9, 35879.0);
	cam.SetAABBMinX(9, 34320.0);
	cam.SetAABBMaxZ(9, 43056.0);
	cam.SetAABBMinZ(9, 41127.0);

	// library end panel
	cam.SetAABBMaxX(10, 34320.0);
	cam.SetAABBMinX(10, 6514.0);
	cam.SetAABBMaxZ(10, 50000.0);
	cam.SetAABBMinZ(10, 43036.0);

	// KBLT
	cam.SetAABBMaxX(11, 28104.0);
	cam.SetAABBMinX(11, 25608.0);
	cam.SetAABBMaxZ(11, 43046.0);
	cam.SetAABBMinZ(11, 42754.0);

	// Canteen block
	cam.SetAABBMaxX(12, 2608.0);
	cam.SetAABBMinX(12, 0.0);
	cam.SetAABBMaxZ(12, 49046.0);
	cam.SetAABBMinZ(12, 0.0);

	// Telephones
	cam.SetAABBMaxX(13, 33892.0);
	cam.SetAABBMinX(13, 33872.0);
	cam.SetAABBMaxZ(13, 25344.0);
	cam.SetAABBMinZ(13, 25173.0);

	// Telephones
	cam.SetAABBMaxX(14, 34277.0);
	cam.SetAABBMinX(14, 34157.0);
	cam.SetAABBMaxZ(14, 25344.0);
	cam.SetAABBMinZ(14, 25173.0);

	// Telephones
	cam.SetAABBMaxX(15, 35462.0);
	cam.SetAABBMinX(15, 34541.0);
	cam.SetAABBMaxZ(15, 25344.0);
	cam.SetAABBMinZ(15, 25173.0);

	// Wall by Steps
	cam.SetAABBMaxX(16, 31548.0);
	cam.SetAABBMinX(16, 31444.0);
	cam.SetAABBMaxZ(16, 10395.0);
	cam.SetAABBMinZ(16, 4590.0);
}

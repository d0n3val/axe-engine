/**
@mainpage
@section	About

This lib will manage 3D geometric primitives like sphere, aabb, obb, frustum, etc.
API format is:

"create"		methods must be able to create any primitive from all other primitive types
"get_area"		will return the area of the occupied by the primitive
"intersect"		methods will return "true" or "false" is both primitives intersect in any form	
"get_distance"	 methods determine the max/mid/min distance to other primitive
"cut" method	will cut this primitive with another one, so creating another primitives
"get_center"	will return the 2D center position of the primitive, when it is not obvious
"transform"		metyhods will change the primitive with a matrix / quaternion / euler_angles ...

@copydoc axe_primitives.h
*/

/* $Id: readme.txt,v 1.1 2004/08/29 18:28:46 doneval Exp $ */
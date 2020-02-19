#pragma once
#ifndef SRC_POSE_H_
#define SRC_POSE_H_

/*******************************************************************************
* Includes
******************************************************************************/
#include <cmath>


/*******************************************************************************
* Namespaces
******************************************************************************/

/*******************************************************************************
* Class Definitions
******************************************************************************/
/**
* @brief A simple representation of the position/orientation of an entity
* within the Arena.
*
* NOTE: Origin (0,0) is at the upper left corner of the Arena.
*/
struct Pose {
public:
	/**
	* @brief Default constructor. Initialize the pose to (0,0,0)
	*/
	Pose() {}

	/**
	* @brief Constructor
	*
	* @param in_x The X component of the Pose.
	* @param in_y The Y component of the Pose.
	*/
	Pose(float in_x, float in_y) : x(in_x), y(in_y) {}

	Pose(float in_x, float in_y, float in_theta)
		: x(in_x),
		y(in_y),
		theta(in_theta) {}

	/**
	* @brief Default assignment operator. Simply copies the (x,y) values of
	* another Pose.
	*
	* @param other The Pose object to copy from.
	*
	* @return The left-hand-side Pose object that is now identical (in value)
	* to `other`.
	*/
	Pose &operator=(const Pose &other) = default;

	/**
	* @brief Overloaded - operator. Treats the poses as vectors, returns the difference of the two.
	*
	* @param rhs The Pose object on the right hand side of the - operator.
	*
	* @return The Pose of the vector difference of the two vectors.
	**/
	Pose operator-(const Pose &rhs) const {
		float x_new = x - rhs.x;
		float y_new = y - rhs.y;
		float theta_new = theta - rhs.theta;
		return Pose(x_new, y_new, theta_new);
	}

	/**
	* @brief Length. Returns the length of a Pose.
	**/
	float Length() const {
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	float x;
	float y;
	float theta;
};

/*******************************************************************************
* Forward Decls
******************************************************************************/
constexpr float deg2rad(float deg) { return deg * 3.1415 / 180.0; }
constexpr float rad2deg(float rad) { return rad * 180.0 / 3.1415; }



#endif /* SRC_POSE_H_ */

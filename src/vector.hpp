//Vector header - Best

#ifndef VECTOR_HPP
#define VECTOR_HPP

//Class definition, class member functions in Material.cpp
#include <iostream>
using namespace std;

class Vector3d
{
public:

   /// Constructor
   Vector3d();
   Vector3d(int &vectorID, float _x, float _y, float _z);

   /// Copy Constructor
   Vector3d(const Vector3d& V);

   /// Assignment Operator
   Vector3d& operator=(const Vector3d& V);

   /// Mutators
   void set_vectorID();
   void set_x(float _x);
   void set_y(float _y);
   void set_z(float _z);

   /// Accessors
   int get_vectorID();
   float get_x();
   float get_y();
   float get_z();

   /// Vector Addition
   Vector3d operator+(const Vector3d& V);
   Vector3d &operator+=(const Vector3d& V);

   /// Vector Subtraction
   Vector3d operator-(const Vector3d& V);
   Vector3d &operator-=(const Vector3d& V);

   /// Inner/Scalar/Dot Product
   float dotProduct(const Vector3d& V);

   /// Outer/Vector/Cross Product
   Vector3d crossProduct(const Vector3d& Va, const Vector3d& Vb);

   /// Print Result in Vector Format
   void print();

   /// Destructor
   ~Vector3d(){}

private:
   int vectorID;
   float x, y, z;
};

#endif

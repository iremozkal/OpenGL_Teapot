#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "mat.h"

class Mesh
{
public:
	Mesh();//constructor
	void LoadObjModel(const char *filename);//function to load obj model
	std::vector<vec3>returnMesh();//return the vertices of mesh data
private:
	std::vector<vec3> vertices;//to store vertex information of 3D model started with v
	std::vector<vec3> meshVertices;//to store all 3D model face vertices
	std::vector<int> faceIndex;//to store the number of face index started with f

};


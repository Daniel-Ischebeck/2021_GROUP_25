//Model class - Daniel

/*
Current status:
Can succesfully read from file, counting number of each of the relevant letters
Based on this list (std::vector), appropriate amount of memory is allocated
Reread file, extracting data necessary to create objects - so far only done for material class
Create instances of the material class based on this data
Save this data to a new file in the required format
*/

/*
//TODO:

*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory> //for managing vector list of different classes for shared_ptr

using namespace std;

//##################################################
//actual classes will be defined in header files but doing it here for testing purposes
class Material
{

public:
  Material();                                                                                         //constructor for when we are allocating memory but don't know values
  Material(int &materialIndex, float &materialDensity, string &materialColour, string &materialName); //example constructor - construcotr overloading
  ~Material();                                                                                        //Destructor

  int get_materialIndex();
  float get_materialDensity();
  string get_materialColour();
  string get_materialName();

private:
  int materialIndex;
  float materialDensity;
  string materialColour;
  string materialName;
};

Material::Material() {} //constructor for when values arent known and we are creating list of materials

Material::Material(int &materialIndex, float &materialDensity, string &materialColour, string &materialName)
{
  this->materialIndex = materialIndex;
  this->materialDensity = materialDensity;
  this->materialColour = materialColour;
  this->materialName = materialName;
}

Material::~Material() {} //Destructor code does nothing - good practice

//Accessor functions
int Material::get_materialIndex() { return this->materialIndex; }
float Material::get_materialDensity() { return this->materialDensity; }
string Material::get_materialColour() { return this->materialColour; }
string Material::get_materialName() { return this->materialName; }
//###########################################################

/*
class Vector3d
{

};
*/

class Vector3d
{
public:
  //constructor
  Vector3d();
  Vector3d(int &vectorID, float &x, float &y, float &z);
  ~Vector3d();
  //public here for ease of use

  int get_vectorID();
  float get_x();
  float get_y();
  float get_z();

private:
  int vectorID;
  float x;
  float y;
  float z;
};

Vector3d::Vector3d() {}

Vector3d::Vector3d(int &vectorID, float &x, float &y, float &z)
{
  this->vectorID = vectorID;
  this->x = x;
  this->y = y;
  this->z = z;
}

//accessor functions
int Vector3d::get_vectorID() { return this->vectorID; }
float Vector3d::get_x() { return this->x; }
float Vector3d::get_y() { return this->y; }
float Vector3d::get_z() { return this->z; }

Vector3d::~Vector3d() {}

class Cell
{
public:
  Cell();
  Cell(char &cellLetter, int &cellIndex); //prev version.

  Cell(char &cellLetter, int &cellIndex, Material &theMaterial, Vector3d &p0, Vector3d &p1, Vector3d &p2, Vector3d &p3); //tetrahdron
  //Cell(char &cellLetter, int &cellIndex, Vector3d &p0, Vector3d &p1, Vector3d &p2, Vector3d &p3); //pyramid
  //Cell(char &cellLetter, int &cellIndex, Vector3d &p0, Vector3d &p1, Vector3d &p2, Vector3d &p3); //hexahedron

  ~Cell();

  //Cell constructor with number of arguments for creating tetrahedron

  int get_cellIndex();
  char get_cellLetter();
  int get_cellMaterialIndex();
  int get_cellp0Index();
  int get_cellp1Index();
  int get_cellp2Index();
  int get_cellp3Index();
  int get_cellp4Index();
  int get_cellp5Index();
  int get_cellp6Index();
  int get_cellp7Index(); //this really doesnt feel sensible

  //virtual function allows the correct version of calculateVolume to be called for each shape
  virtual double calculateVolume();

protected:
  int cellIndex;
  char cellLetter;
  Material theMaterial;
  Vector3d p0, p1, p2, p3, p4, p5, p6, p7;
  //This doesnt feel that intelligent - not quite using inheriitance correctly
  //Questions regarding dynamic casting, how to use shared pointers properly
  //supposedly i should be able to access the shapes using pointers, not currenly clear how
};

Cell::Cell()
{
}

Cell::Cell(char &cellLetter, int &cellIndex)
{
  this->cellLetter = cellLetter;
  this->cellIndex = cellIndex;
}

Cell::Cell(char &cellLetter, int &cellIndex, Material &theMaterial, Vector3d &p0, Vector3d &p1, Vector3d &p2, Vector3d &p3)
{
  this->cellIndex = cellIndex;
  this->cellLetter = cellLetter;
  this->theMaterial = theMaterial;
  this->p0 = p0;
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;
}

int Cell::get_cellIndex() { return this->cellIndex; }
char Cell::get_cellLetter() { return this->cellLetter; }
int Cell::get_cellMaterialIndex() { return theMaterial.get_materialIndex(); }
int Cell::get_cellp0Index() { return p0.get_vectorID(); }
int Cell::get_cellp1Index() { return p1.get_vectorID(); }
int Cell::get_cellp2Index() { return p2.get_vectorID(); }
int Cell::get_cellp3Index() { return p3.get_vectorID(); }

double Cell::calculateVolume()
{
  return 0.;
}

Cell::~Cell() {}

//The Tetrahedron class is a child of the Cell class
class Tetrahedron : public Cell
{
public:
  Tetrahedron();
  ~Tetrahedron();

  Tetrahedron(int &cellIndex, char &cellLetter, Material &theMaterial, Vector3d &p0, Vector3d &p1, Vector3d &p2, Vector3d &p3);

  double calculateVolume();

  //cellIndex materialIndex  vectorIndexP0  vectorIndexP1 vectorIndexP2  vectorIndexP3
private:
  int cellIndex;
  char cellLetter;
  Material theMaterial;
  Vector3d p0, p1, p2, p3;
};

Tetrahedron::Tetrahedron() {}

// Tetrahedron class calling apporopraite Cell constructor to initialise the inherited variables
// not sure if itd be more sensible to call function with index of material, vector etc.? - think as passing by reference its okay, also clearer in function code
Tetrahedron::Tetrahedron(int &cellIndex, char &cellLetter, Material &theMaterial, Vector3d &p0, Vector3d &p1, Vector3d &p2, Vector3d &p3)
    : Cell(cellLetter, cellIndex, theMaterial, p0, p1, p2, p3)
{
  this->cellIndex = cellIndex;
  this->cellLetter = cellLetter;
  this->theMaterial = theMaterial;
  this->p0 = p0;
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;
}

double Tetrahedron::calculateVolume()
{
  return 11.3;
}

Tetrahedron::~Tetrahedron() {}

//#########################################################################

class Pyramid : public Cell
{
public:
  Pyramid();
  ~Pyramid();

  Pyramid(int &cellIndex, char &cellLetter, Material &theMaterial, Vector3d &p0, Vector3d &p1, Vector3d &p2, Vector3d &p3, Vector3d &p4);

  double calculateVolume();

private:
  int cellIndex;
  char cellLetter;
  Material theMaterial;
  Vector3d p0, p1, p2, p3, p4, p5;
};

Pyramid::Pyramid() {}

Pyramid::~Pyramid() {}

Pyramid::Pyramid(int &cellIndex, char &cellLetter, Material &theMaterial, Vector3d &p0, Vector3d &p1, Vector3d &p2, Vector3d &p3, Vector3d &p4)
    : Cell(cellLetter, cellIndex)
{
  this->cellIndex = cellIndex;
  this->cellLetter = cellLetter;
  this->theMaterial = theMaterial;
  this->p0 = p0;
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;
  this->p4 = p4;
}

double Pyramid::calculateVolume()
{
  return 12.345;
}
//##################################################################

class Hexahedron : public Cell
{
public:
  Hexahedron();
  ~Hexahedron();

  Hexahedron(int &cellIndex, char &cellLetter, Material &theMaterial,
             Vector3d &p0, Vector3d &p1, Vector3d &p2, Vector3d &p3,
             Vector3d &p4, Vector3d &p5, Vector3d &p6, Vector3d &p7);

  double calculateVolume();
  float customFunc();

private:
  int cellIndex;
  char cellLetter;
  Material theMaterial;
  Vector3d p0, p1, p2, p3, p4, p5, p6, p7;
};

Hexahedron::Hexahedron() {}

Hexahedron::~Hexahedron() {}

Hexahedron::Hexahedron(int &cellIndex, char &cellLetter, Material &theMaterial,
                       Vector3d &p0, Vector3d &p1, Vector3d &p2, Vector3d &p3,
                       Vector3d &p4, Vector3d &p5, Vector3d &p6, Vector3d &p7)
    : Cell(cellLetter, cellIndex)
{
  this->cellIndex = cellIndex;
  this->cellLetter = cellLetter;
  this->theMaterial = theMaterial;
  this->p0 = p0;
  this->p1 = p1;
  this->p2 = p2;
  this->p3 = p3;
  this->p4 = p4;
  this->p5 = p5;
  this->p6 = p6;
  this->p7 = p7;
}

double Hexahedron::calculateVolume()
{
  return 62.31;
}

float Hexahedron::customFunc()
{
  return 1.123;
}
//####################################################

class Model
{

public:
  //Model constructor - creating a model from your own set of cells?
  //Model Destructor

  int readFile(string &filePath); //funtion for reading from file - pass string of file name/path as argument

  int saveToFile(string &newFilePath);

  //Once we know how many of each letter we have, we go about creating them
  int declareMaterials(string &filePath);
  int declareVectors(string &filePath);
  int declareCells(string &filePath);
  //##############################
  //Accessor functions
  //Format get_
  vector<Material> get_listOfMaterials();
  vector<Vector3d> get_listOfVectors();
  //vector<Cell> get_listOfCells();
  vector<shared_ptr<Cell>> get_listOfCells();

  int get_numMaterials();
  int get_numVectors();
  int get_numCells();

  //Tetrahedron myTet = Tetrahedron();

private:
  int currentLine = 1;

  //std::vector is a convenient way of dynamically allocating arrays & manipulating
  //the following list of indexes tells us on which line in the file the desired letters are
  vector<int> materialLineIndexes;
  vector<int> vectorLineIndexes;
  vector<int> cellLineIndexes;

  //List to store the objects that are created once data is read from file
  vector<Material> listOfMaterials;
  vector<Vector3d> listOfVectors;
  //vector<Cell> listOfCells;
  //vector<Cell*> listOfCells;
  vector<shared_ptr<Cell>> listOfCells;
  //use shared pointer for this

  //Once we have read file and know how many of each object there are, we will need to resize above vector
  int numMaterials = 0, numVectors = 0, numCells = 0;
};

//Accessor functions
vector<Material> Model::get_listOfMaterials() { return this->listOfMaterials; }
vector<Vector3d> Model::get_listOfVectors() { return this->listOfVectors; }
vector<shared_ptr<Cell>> Model::get_listOfCells() { return this->listOfCells; }
//vector<Cell> Model::get_listOfCells() { return this->listOfCells; }

int Model::get_numMaterials() { return this->numMaterials; }
int Model::get_numVectors() { return this->numVectors; }
int Model::get_numCells() { return this->numCells; }

//#######################################

//Function to read from file
int Model::readFile(string &filePath) //arguments - file name/path as a string)
{
  //We first want to allocate all the memory necessary for the objects in the file
  //To do this, check for all the relevant letters and count them, assign relevant
  //Keep a track of the line on which the letters occur, so when we come to actually extract the data we already know which line it is on

  ifstream inputFile(filePath); //Open file

  string line; //declare string to represent each line in the file

  if (!inputFile.is_open())
  {
    cout << "Failed to open file";
    return (-1);
  }

  if (currentLine != 1)
  {
    currentLine = 1; //ensure we are reading from the beginning of the file
  }

  while (getline(inputFile, line))
  {
    //cout << "Current line: " << currentLine << "\n";
    if (!line.empty())
    {
      //cout << line[0];  //displays first character of each line
      //cout << '\n';
      switch (line[0]) //determine the first letter of the line and assign relevant data
      {
      case 'm':
        numMaterials++;
        materialLineIndexes.push_back(currentLine);
        break;
      case 'v':
        numVectors++;
        vectorLineIndexes.push_back(currentLine);
        break;
      case 'c':
        numCells++;
        cellLineIndexes.push_back(currentLine);
        break;
      }
    }
    currentLine++; //we have completed reading from a line, increment for next loop round
  }
  cout << "\nRead " << currentLine << " lines from file\n";
  cout << "\nNum m: " << numMaterials << "\tNum v: " << numVectors << "\tNum c: " << numCells << "\n";

  //dynamically allocating memory for the lists of objects we will need using std::vector wrapper/container
  //doing all at once due to overheads with dynamic memory allocation

  listOfMaterials.resize(numMaterials);
  listOfVectors.resize(numVectors);

  //DOnt bother with allocating cell memory in advance as we have to create new shapes
  //listOfCells.resize(numCells);

  //cout << "List of materials size " << listOfMaterials.size() << "\n";

  currentLine = 1; //reset current line back to 1 for future reads of the file
  return 0;
}

//Function to declare materials
int Model::declareMaterials(string &filePath)
{
  ifstream inputFile(filePath); //Open file

  string line; //declare string to represent each line in the file

  if (currentLine != 1)
  {
    currentLine = 1; //ensure we are reading from the beginning of the file
  }

  if (!inputFile.is_open())
  {
    cout << "Failed to open file";
    return (-1);
  }

  while (getline(inputFile, line))
  {
    //cout << "\nCurrent line: " << currentLine << "\n";

    if (!line.empty())
    {
      //cout << "Material line Indexes size: " << materialLineIndexes.size() << "\n";
      for (int i = 0; i < int(materialLineIndexes.size()); i++)
      {
        //cout << "Line index at i: " << materialLineIndexes.at(i) << "\n";

        if (int(materialLineIndexes.at(i)) == currentLine) //if the current line is one we previously determined was a material line
        {
          //cout << "\nLine " << currentLine << " contains material\n"; //displays line on which materials are

          istringstream iss(line);
          char lineLetter;
          int materialIndex;
          float materialDensity;
          string materialColour;
          string materialName;

          //currently assuming that the file is in the specified format - TODO?: Make it very robust to random whitespaces etc.?
          if (!(iss >> lineLetter >> materialIndex >> materialDensity >> materialColour >> materialName))
          {
            cout << "File formatting is wrong\n";
            return (-1);
          }
          else
          {
            //cout << "We have: " << lineLetter << " " << materialIndex << " " << materialDensity << " " << materialColour << " " << materialName << "\n";
            //call the constructor for the material class
            listOfMaterials.at(i) = Material(materialIndex, materialDensity, materialColour, materialName);
          }
        }
      }
    }
    currentLine++; //we have completed a line, increment for next loop round
  }
  return 0;
}

//Function to declare vectors
int Model::declareVectors(string &filePath)
{
  ifstream inputFile(filePath); //Open file

  string line; //declare string to represent each line in the file

  if (currentLine != 1)
  {
    currentLine = 1; //ensure we are reading from the beginning of the file
  }

  if (!inputFile.is_open())
  {
    cout << "Failed to open file";
    return (-1);
  }

  while (getline(inputFile, line))
  {
    //cout << "\nCurrent line: " << currentLine << "\n";

    if (!line.empty())
    {
      //cout
      for (int i = 0; i < int(vectorLineIndexes.size()); i++)
      {
        //cout <<

        if (int(vectorLineIndexes.at(i)) == currentLine) //if the current line is one we previously determined was a vectorline
        {
          //cout << "\nLine " << currentLine << " contains vector\n"; //displays line on which vectors are

          istringstream iss(line);
          char lineLetter;
          int vectorID;
          float x, y, z;

          //currently assuming that the file is in the specified format - TODO?: Make it very robust to random whitespaces etc.?
          if (!(iss >> lineLetter >> vectorID >> x >> y >> z))
          {
            cout << "File formatting is wrong\n";
            return (-1);
          }
          else
          {
            //cout << "We have: " << lineLetter << " " << vectorID << " "
            //                    << x  << " " << y << " " << z << "\n";
            //call the constructor for the vector class
            listOfVectors.at(i) = Vector3d(vectorID, x, y, z);
          }
        }
      }
    }
    currentLine++; //we have completed a line, increment for next loop round
  }

  return 0;
}

//Function to declare cells
int Model::declareCells(string &filePath)
{
  ifstream inputFile(filePath); //Open file
  string line;                  //declare string to represent each line in the file

  if (currentLine != 1)
  {
    currentLine = 1; //ensure we are reading from the beginning of the file
  }

  if (!inputFile.is_open())
  {
    cout << "Failed to open file";
    return (-1);
  }

  while (getline(inputFile, line))
  {
    //cout << "\nCurrent line: " << currentLine << "\n";

    if (!line.empty())
    {
      //cout
      for (int i = 0; i < int(cellLineIndexes.size()); i++)
      {
        //cout <<

        if (int(cellLineIndexes.at(i)) == currentLine) //if the current line is one we previously determined was a cell line
        {
          //cout << "\nLine " << currentLine << " contains cell\n"; //displays lines on which cels are

          istringstream iss(line);
          char lineLetter;
          int cellIndex;
          char cellLetter;
          int materialIndex;

          //currently assuming that the file is in the specified format - TODO?: Make it very robust to random whitespaces etc.?
          if (!(iss >> lineLetter >> cellIndex >> cellLetter))
          {
            cout << "File formatting is wrong\n";
            return (-1);
          }
          else
          {
            //cout << "We have: " << cellLetter << " with index " << cellIndex << "\n";

            int vectorIndexP0, vectorIndexP1, vectorIndexP2, vectorIndexP3,
                vectorIndexP4, vectorIndexP5, vectorIndexP6, vectorIndexP7; //defining all vector indices
            switch (cellLetter)                                             //how many verticies we need to read depends on shape
            {
            case 't':
              //tetrahedron has 4 points
              if (!(iss >> materialIndex >> vectorIndexP0 >> vectorIndexP1 >> vectorIndexP2 >> vectorIndexP3))
              {
                cout << "File formatting is wrong\n";
                return (-1);
              }
              else
              {
                cout << "We have: " << cellIndex << " " << cellLetter << " " << materialIndex << " "
                     << vectorIndexP0 << " " << vectorIndexP1 << " " << vectorIndexP2 << " " << vectorIndexP3 << "\n";

                //call constructor for tetrahedron
                //store tetrahedron in list of cells

                //Tetrahedron(int &cellIndex, Material &materialIndex, Vector3d &p0, Vector3d &p1, Vector3d &p2, Vector3d &p3);
                //cellIndex materialIndex  vectorIndexP0  vectorIndexP1 vectorIndexP2  vectorIndexP3

                //listOfCells.push_back(shared_ptr<Cell>(new Tetrahedron(arguments)));
                auto it = listOfCells.begin() + i;

                listOfCells.insert(it, shared_ptr<Cell>(new Tetrahedron(cellIndex, cellLetter,
                                                                        listOfMaterials.at(materialIndex),
                                                                        listOfVectors.at(vectorIndexP0), listOfVectors.at(vectorIndexP1),
                                                                        listOfVectors.at(vectorIndexP2), listOfVectors.at(vectorIndexP3))));
              }
              break;

            //TODO:still need to write code for creating pyramids and hexahedrons
            case 'p':
              //pyramid has 5 points
              if (!(iss >> materialIndex >> vectorIndexP0 >> vectorIndexP1 >> vectorIndexP2 >> vectorIndexP3 >> vectorIndexP4))
              {
                cout << "File formatting is wrong\n";
                return (-1);
              }
              else
              {
                cout << "We have: " << cellIndex << " " << cellLetter << " " << materialIndex << " "
                     << vectorIndexP0 << " " << vectorIndexP1 << " " << vectorIndexP2 << " " << vectorIndexP3 << " " << vectorIndexP4 << "\n";

                auto it = listOfCells.begin() + i;
                listOfCells.insert(it, shared_ptr<Cell>(new Pyramid(cellIndex, cellLetter,
                                                                    listOfMaterials.at(materialIndex),
                                                                    listOfVectors.at(vectorIndexP0), listOfVectors.at(vectorIndexP1),
                                                                    listOfVectors.at(vectorIndexP2), listOfVectors.at(vectorIndexP3),
                                                                    listOfVectors.at(vectorIndexP4))));
              }
              break;
            case 'h':

              //hexahedron has 8 points
              if (!(iss >> materialIndex >> vectorIndexP0 >> vectorIndexP1 >> vectorIndexP2 >> vectorIndexP3 >> vectorIndexP4 >> vectorIndexP5 >> vectorIndexP6 >> vectorIndexP7))
              {
                cout << "File formatting is wrong\n";
                return (-1);
              }
              else
              {
                cout << "We have: " << cellIndex << " " << cellLetter << " " << materialIndex << " "
                     << vectorIndexP0 << " " << vectorIndexP1 << " " << vectorIndexP2 << " " << vectorIndexP3 << " "
                     << vectorIndexP4 << " " << vectorIndexP5 << " " << vectorIndexP6 << " " << vectorIndexP7 << "\n";
                auto it = listOfCells.begin() + i;

                listOfCells.insert(it, shared_ptr<Cell>(new Hexahedron(cellIndex, cellLetter,
                                                                       listOfMaterials.at(materialIndex),
                                                                       listOfVectors.at(vectorIndexP0), listOfVectors.at(vectorIndexP1),
                                                                       listOfVectors.at(vectorIndexP2), listOfVectors.at(vectorIndexP3),
                                                                       listOfVectors.at(vectorIndexP4), listOfVectors.at(vectorIndexP5),
                                                                       listOfVectors.at(vectorIndexP6), listOfVectors.at(vectorIndexP7))));
              }
              break;
            }
          }
        }
      }
    }
    currentLine++; //we have completed a line, increment for next loop round
  }

  //as we have declared all objects and are done with this file it can be closed
  inputFile.close();
  return 0;
} //function end

//Function for saving read data to file
//TODO: write vector and cell data to the file
int Model::saveToFile(string &newFilePath)
{
  ofstream outputFile(newFilePath);
  outputFile << "# This is my file, there are many like it, but this one is mine\n"
             << endl;

  //write material data
  for (int i = 0; i < int(listOfMaterials.size()); i++)
  {
    outputFile << "m "
               << listOfMaterials.at(i).get_materialIndex() << " "
               << listOfMaterials.at(i).get_materialDensity() << " "
               << listOfMaterials.at(i).get_materialColour() << " "
               << listOfMaterials.at(i).get_materialName() << endl;
  }
  outputFile << "\n"; //sepeartae different parts of datat with newline

  //write vector data
  for (int i = 0; i < int(listOfVectors.size()); i++)
  {
    outputFile << "v "
               << listOfVectors.at(i).get_vectorID() << " "
               << listOfVectors.at(i).get_x() << " "
               << listOfVectors.at(i).get_y() << " "
               << listOfVectors.at(i).get_z() << endl;
  }

  outputFile << "\n";
  //write cell data
  //cout << "Num cells: " << listOfCells.size() << "\n";

  for (int i = 0; i < int(listOfCells.size()); i++)
  {
    outputFile << "c ";
    char myLetter = listOfCells.at(i)->get_cellLetter();
    //cout << myLetter << "\n";
    switch (myLetter)
    {

    case 't':
      outputFile << listOfCells.at(i)->get_cellIndex() << " "
                 << listOfCells.at(i)->get_cellLetter() << " "
                 << listOfCells.at(i)->get_cellMaterialIndex() << " "
                 << listOfCells.at(i)->get_cellp0Index() << " "
                 << listOfCells.at(i)->get_cellp1Index() << " "
                 << listOfCells.at(i)->get_cellp2Index() << " "
                 << listOfCells.at(i)->get_cellp3Index() << "\n";

      break;

    case 'h':
      outputFile << listOfCells.at(i)->get_cellIndex() << " "
                 << listOfCells.at(i)->get_cellLetter() << "\n";
      break;
    }
  }

  outputFile.close();
  cout << "\nSaved to file\n\n";
  return 0;
}

//########################################################################################

int main()
{
  Model myModel;

  string filePath = "../model_files/ExampleModel1.mod"; //  ExampleModel1.mod  //  testFile.mod

  int fileResult = myModel.readFile(filePath);
  if (fileResult) //if the file is not read successfully
  {
    cout << "Now what?\n"; //TODO - just a warning sufficent?
  }

  cout << "\n-------------------Testing Functionality-----------------\n";

  //------------------------------------------
  int modelResultM = myModel.declareMaterials(filePath);

  string nameOfMaterial1 = myModel.get_listOfMaterials().at(0).get_materialName();
  cout << "\n\nName of material 0: " << nameOfMaterial1 << "\n\n";

  int numberOfMaterials = myModel.get_numMaterials();
  cout << "Number of materials: " << numberOfMaterials << "\n\n";

  //--------------------------------------
  //declaring vectors
  int modelResultV = myModel.declareVectors(filePath);
  float vector_idk_xValue = myModel.get_listOfVectors().at(2).get_x();
  cout << "The vector at index idk (currently 2) has x value: " << vector_idk_xValue << "\n";
  //----------------------------------

  //declaring cells
  int modelResultC = myModel.declareCells(filePath);

  //char cell_idk_letter = myModel.get_listOfCells().at(1).get_cellLetter();

  char cell_idk_letter = myModel.get_listOfCells().at(0)->get_cellLetter();
  cout << "\nThe cell at index idk (currently 0) has the letter " << cell_idk_letter << "\n";

  //cout << modelResultM << " " << modelResultV << " " << modelResultC << "\n";

  //Testing inheritance
  double vol0 = myModel.get_listOfCells().at(0)->calculateVolume();
  cout << "Vol 0: " << vol0 << "\n";

  /*
  //below only vlaid if there are 2 cells present 
  double vol1 = myModel.get_listOfCells().at(1)->calculateVolume();
  cout << "Vol 1: " << vol1 << "\n";
  */

  // float testing = myModel.get_listOfCells().at(0)->customFunc();
  // cout << "Testing: " << testing << "\n";

  //Saving data to file
  string newFilePath = "../model_files/saveFile.mod";

  myModel.saveToFile(newFilePath);
}
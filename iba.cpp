#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <forward_list>
// Program

using namespace std;
const int max737 = 46000;
const int max767 = 116000;


// Cargo class for keeping information related to cargo
class Cargo
{
  // friend double kilotopound(Cargo);
  // friend bool operator==(const Cargo& lhs, const Cargo& rhs);

  protected:
    string uldtype;
    string abbrev;
    string uldid;
    int aircraft;
    double weight;
    string destination;

  public:
    ///Default constructor prototype
    Cargo();

    ///Full constructor prototype
    Cargo(const string& uld, const string& abb, const string& id, const int& air, const double& wght, const string& dest);

    Cargo(const Cargo& car1);

    ///Destructor prototype
    ~Cargo();

    ///Mutator (setters) prototypes
    void setuldtype(string);
    void setabbrev(string);
    void setuldid(string);
    void setaircraft(int);
    void setweight(double);
    void setdestination(string);
    
    ///Accessor (getters) prototypes
    string getuldtype() const;
    string getabbrev() const;
    string getuldid() const;
    int getaircraft() const;
    double getweight() const;
    string getdestination() const;

    virtual void maxweight(double&, double) = 0;
    void output();
  };

class B737 : public Cargo {
  private:
    int totalWeight;
  
  public:
    using Cargo :: Cargo;

    ~B737(){};
    
    void maxweight(double&, double) override;
};


class B767 : public Cargo {
  private:
    int totalWeight;

  public:
    using Cargo :: Cargo;

    ~B767(){};
    void maxweight(double&, double) override;
};

// Gather input
void input();

void confirmAircraft(int);
void confirmType(string);
void confirmAbbrev(string, int);

// Output information in a Cargo object
// void output(Cargo&);



// main
int main ()
{

  input();

  return 0;
}




// default constructor
Cargo::Cargo()  
{
    uldtype = "none";
    abbrev = "none";
    uldid = "none";
    aircraft = 0;
    weight = 0;
    destination = "none";
}

// Overloaded constructor
Cargo::Cargo(const string& uld, const string& abb, const string& id, const int& air, const double& wght, const string& dest)  // non default constructor
{
    uldtype = uld;
    abbrev = abb;
    uldid = id;
    aircraft = air;
    weight = wght;
    destination = dest;
}


Cargo::Cargo(const Cargo& car1) {
  uldtype = car1.uldtype;
  abbrev = car1.abbrev;
  uldid = car1.uldid;
  aircraft = car1.aircraft;
  weight = car1.weight;
  destination = car1.destination;
}


 // deconstructor
Cargo::~Cargo() 
{
  // cout << "Cargo destructor called\n";  // GOT RID OF THIS BECAUSE IT SPAMS A LOT OF MESSAGES
}

/*
Setters go here
*/
void Cargo::setuldtype(string type)
  {
      uldtype = type;
  }

void Cargo::setabbrev(string abb)
{
    abbrev = abb;
}

  void Cargo::setuldid(string id)
{
    uldid = id;
}

  void Cargo::setaircraft(int air)
{
    aircraft = air;
}

  void Cargo::setweight(double wght)
{
    weight = wght;
}

  void Cargo::setdestination(string dest)
{
    destination = dest;
}

/*
Getters go here
*/
string Cargo::getuldtype() const
{
    return uldtype;
}

string Cargo::getabbrev() const
{
    return abbrev;
}

string Cargo::getuldid() const
{
    return uldid;
}

int Cargo::getaircraft() const
{
    return aircraft;
}

double Cargo::getweight() const
{
    return weight;
}

string Cargo::getdestination() const
{
    return destination;
}



void load737(forward_list<B737> &forwardptr737, const string type, const string abb, const string id, const int air, const double wght, const string dest, double &totalweight737) {
  
  B737 object737(type, abb, id, air, wght, dest); 
  object737.maxweight(totalweight737, wght); 
  forwardptr737.push_front(object737); 

}


void load767(forward_list<B767> &forwardptr767, const string type, const string abb, const string id, const int air, const double wght, const string dest, double &totalweight767) {
  
  B767 object767(type, abb, id, air, wght, dest); 
  object767.maxweight(totalweight767, wght); 
  forwardptr767.push_front(object767); 

}


void B737::maxweight(double &totalweight737, double wght){

  if (totalweight737 > max737){

    totalweight737 -= wght; ///remove if overweight
    throw runtime_error("Weight exceeded maximum, cannot proceed...\n");
  }
}


void B767::maxweight(double &totalweight767, double wght){

  if (totalweight767 > max767){

    totalweight767 -= wght; ///remove if overweight
    throw runtime_error("Weight exceeded maximum, cannot proceed...\n");
  }
}


void Cargo::output() {
  cout << "output called\n\n";

  cout << "------------------------------------------------------------------" << endl;
  cout << setw(30) << left << "Unit load type: " << uldtype << endl;
  cout << setw(30) << left << "Unit load abbreviation: " << abbrev << endl;
  cout << setw(30) << left << "Unit identifier: " << uldid << endl;
  cout << setw(30) << left << "Aircraft type: " << aircraft << endl;
  cout << setw(30) << left << "Unit weight: " << weight << endl;
  cout << setw(30) << left << "Destination code: " << destination << endl;
  cout << "------------------------------------------------------------------" << endl;
}


//input function for cargo gather input
void input() {
  string filename;
  string cargostring;
  string type;
  string abb;
  string id;
  int air;
  double wght;
  string dest;
  ifstream inputFile;

  string trash;

  double totalweight737 = 0;
  double totalweight767 = 0;

  // B737 *object737ptr;
  // B767 *object767ptr;

  forward_list<B737> forwardptr737;
  forward_list<B767> forwardptr767;


  do{
    try{
      inputFile.clear();
      cout << "\n\nFile name:";

      getline(cin, filename);
      inputFile.open(filename);

      
      if (!inputFile)
      throw runtime_error(filename + " was not found...");

      cout << "File opened successfully...";
      }

    catch(runtime_error &excpt) {
    cout << filename << " " << excpt.what();
    }

  } while(!inputFile);


  while (inputFile >> type){
    try{
      inputFile >> abb;
      inputFile >> id;
      inputFile >> air;
      inputFile >> wght;
      inputFile >> dest;


      confirmType(type);///check for Container or Pallet
      confirmAircraft(air);///check for valid plane type via function


      if (air == 737) {
        confirmAbbrev(abb, air);
      

      totalweight737 += wght;

      load737(forwardptr737, type, abb, id, air, wght, dest, totalweight737);
      }

      if (air == 767) {
        confirmAbbrev(abb, air);
      


      totalweight767 += wght;
      load767(forwardptr767, type, abb, id, air, wght,dest, totalweight767);
      }

    } catch(runtime_error &excpt){

      cout << excpt.what();

    }
  }


    inputFile.close();
    int i, j;
    i = 0;
    j = 0;
    
    for (Cargo& out737 : forwardptr737){
      cout << "737 Unit# " << ++i << endl;
      out737.output();
    }
    for (Cargo& out767 : forwardptr767){
      cout << "767 Unit# " << ++j << endl;
      out767.output();
    }

    cout << "Boeing 737 total weight: " << totalweight737 << endl;
    cout << "Boeing 767 total weight: " << totalweight767 << endl;
  

}


void confirmAircraft(int air){

  if (air != 737 && air != 767) {
    throw runtime_error(to_string(air) + " not valid aircraft type\n");
  }
}


void confirmType(string type){

  if (type != "Container" && type != "Pallet") {
    throw runtime_error(type + " not valid load type...\n"); 
  }
}


void confirmAbbrev(string abb, int air){
  if (air == 737){

    if (abb != "AYF" && abb != "AYK" && abb != "AAA" && abb != "AYY" && abb != "PAG" && abb != "PMC" && abb != "PLA") { 

      throw runtime_error(abb + " bad type for 737\n\n");
    }
  }


  if (air == 767) {

    if (abb != "AKE" && abb != "APE" && abb != "AKC" && abb != "AQP" && abb != "AQF" && abb != "AAP" && abb != "P1P" && abb != "P6P") {

      throw runtime_error(abb + " bad type for 767\n\n");
    }
  }
}





// Output in neat format
// void output(Cargo& cargo)  
// {
//   cout << "output called\n\n";

//   cout << "------------------------------------------------------------------" << endl;
//   cout << setw(30) << left << "Unit load type: " << cargo.getuldtype() << endl;
//   cout << setw(30) << left << "Unit load abbreviation: " << cargo.getabbrev() << endl;
//   cout << setw(30) << left << "Unit identifier: " << cargo.getuldid() << endl;
//   cout << setw(30) << left << "Aircraft type: " << cargo.getaircraft() << endl;
//   cout << setw(30) << left << "Unit weight: " << cargo.getweight() << endl;
//   cout << setw(30) << left << "Destination code: " << cargo.getdestination() << endl;
//   cout << "------------------------------------------------------------------" << endl;
// }



// Friend function to convert kilograms to pounds

// double kilotopound(Cargo car) {
//   return car.weight * 2.2;
// }


// Friend function overloading == operator to compare equivalency of cargo objects
// bool operator==(const Cargo& lhs, const Cargo& rhs) {
//   if (lhs.abbrev != rhs.abbrev) {
//     return false;
//   }

//   if (lhs.uldid != rhs.uldid) {
//       return false;
//   }

//   return true;
// }
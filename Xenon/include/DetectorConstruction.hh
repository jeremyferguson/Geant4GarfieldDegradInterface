#ifndef DetectorConstruction_hh
#define DetectorConstruction_hh 1

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "DetectorMessenger.hh"
#include "G4UserLimits.hh"
#include "DetectorMessenger.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4RunManager.hh"
#include "G4FieldManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UniformMagField.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4Polycone.hh"
#include "G4Polyhedra.hh"
#include "G4UnionSolid.hh"
#include "G4Region.hh"
#include "G4Orb.hh"
#include "GasModelParameters.hh"
#include <unordered_map>


class G4VSolid;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4UniformMagField;


using namespace std;
/*! \class  DetectorConstruction*/
/*! \brief class derived from G4VUserDetectorConstruction*/

class DetectorConstruction : public G4VUserDetectorConstruction {
 public:
  DetectorConstruction(GasModelParameters*);
  virtual ~DetectorConstruction();

  // Mandatory methods
  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();

  //Setters for the dimensions and environment variables of the setup
  inline void CheckOverlaps(G4bool co){checkOverlaps=co;};
  inline void SetWorldHalfLength(G4double d){worldHalfLength=d;};
  inline void SetGasBoxR(G4double d){gasboxR=d;};
  inline void SetGasBoxH(G4double d){gasboxH=d;};
  inline void SetWallThickness(G4double d){wallThickness=d;};
  inline void SetCaloThickness(G4double d){caloThickness=d;};
  inline void SetGasPressure(G4double d){gasPressure=d;};
  inline void SetTemperature(G4double d){temperature=d;};
  inline void SetMainGasPercentage(G4double d){MainGasPercentage=d;};
  inline void SetSecondGasPercentage(G4double d){SecondGasPercentage=d;};
  inline void SetThirdGasPercentage(G4double d){ThirdGasPercentage=d;};
  void SetImpurityGasPercentage(G4double d) {
	  if (SecondGasPercentage > 0.0) {
		  SecondGasPercentage -= (d - ImpurityGasPercentage);
	  } else if (ThirdGasPercentage > 0.0){
	  	  ThirdGasPercentage -= (d - ImpurityGasPercentage);
	  } else {
		  MainGasPercentage -= (d - ImpurityGasPercentage);
	  }
	  ImpurityGasPercentage = d;
  }
  inline void SetMainGas(string s){mainGas = s;}
  inline void SetSecondGas(string s){secondGas = s;}
  inline void SetImpurityGas(string s){impurityGas = s;}
  inline void SetThirdGas(string s){impurityGas = s;}
  //Getters for the dimensions and environment variables of the setup
  inline G4double GetWorldHalfLength(){return worldHalfLength;};
  inline G4double GetGasBoxR(){return gasboxR;};
  inline G4double GetGasBoxH(){return gasboxH;};
  inline G4double GetWallThickness(){return wallThickness;};
  inline G4double GetCaloThickness(){return caloThickness;};
  inline G4double GetGasPressure(){return gasPressure;};
  inline G4double GetTemperature(){return temperature;};
  inline G4double GetMainGasPercentage(){return MainGasPercentage;};
  inline G4double GetSecondGasPercentage(){return SecondGasPercentage;};
  inline G4double GetThirdGasPercentage(){return ThirdGasPercentage;};
  inline G4double GetImpurityGasPercentage(){return ImpurityGasPercentage;};
  inline string GetMainGas(){return mainGas;}
  inline string GetSecondGas(){return secondGas;} 
  inline string GetImpurityGas(){return impurityGas;}
  inline string GetThirdGas(){return thirdGas;}
  inline string GetMainGeantName(){return gasNamesMap[mainGas][0];}
  inline string GetMainDegradNumber(){return gasNamesMap[mainGas][1];}
  inline string GetSecondGeantName(){return gasNamesMap[secondGas][0];}
  inline string GetSecondDegradNumber(){return gasNamesMap[secondGas][1];}
  inline string GetImpurityGeantName(){return gasNamesMap[impurityGas][0];}
  inline string GetImpurityDegradNumber(){return gasNamesMap[impurityGas][1];}
  inline string GetThirdGeantName(){return gasNamesMap[thirdGas][0];}
  inline string GetThirdDegradNumber(){return gasNamesMap[thirdGas][1];}
  inline G4double GetMainMolarMass(){return gasDensityMap[mainGas];}
  inline G4double GetSecondMolarMass(){return gasDensityMap[secondGas];}
  inline G4double GetImpurityMolarMass(){return gasDensityMap[impurityGas];}
  inline G4double GetThirdMolarMass(){return gasDensityMap[thirdGas];}
  inline G4double GetMainRIndex(){return gasRefractivityMap[mainGas];}
  inline G4double GetSecondRIndex(){return gasRefractivityMap[secondGas];}
  inline G4double GetImpurityRIndex(){return gasRefractivityMap[impurityGas];} 
  inline G4double GetThirdRIndex(){return gasRefractivityMap[thirdGas];}
  
 private:
  DetectorMessenger* detectorMessenger;
  G4LogicalVolume* logicGasBox;
  G4LogicalVolume* logicCalo;
  GasModelParameters* fGasModelParameters;
  G4bool checkOverlaps; // Check overlaps in the detector geometry if true
  G4double worldHalfLength; //World volume is a cube with side length = 2m;
  G4double gasboxR; // radius of tube filled with gas
  G4double gasboxH; // length of the tube
  G4double wallThickness; //thickness of the aluminum walls
  G4double caloThickness; // thickness of the silicon detector
  G4double gasPressure; // pressure in the gas
  G4double temperature; // temperature of the gas
  G4double MainGasPercentage;
  G4double SecondGasPercentage;
  G4double addmixturePercentage;
  G4double ImpurityGasPercentage;
  G4double ThirdGasPercentage;
  string mainGas;
  string secondGas;
  string impurityGas;
  string thirdGas;
  std::unordered_map <string, std::vector<string>> gasNamesMap = {
	  {"Xe", {"G4_Xe","7"}},
	  {"CO2",{"G4_CARBON_DIOXIDE","12"}},
	  {"CH4",{"G4_METHANE","8"}},
	  {"Ar",{"G4_Ar","2"}},
	  {"O2",{"G4_lO2","15"}},
	  {"iC4H10",{"G4_BUTANE","11"}},
	  {"H2O",{"G4_WATER_VAPOR","14"}}
  };
  std::unordered_map <string, G4double> gasDensityMap = {
	  {"Xe", 131.293},
	  {"CO2",44.01},
	  {"CH4",16.04},
	  {"Ar",39.948},
	  {"H2O",18.015},
	  {"O2",15.999},
	  {"iC4H10",58.12}
  };
  std::unordered_map <string, G4double> gasRefractivityMap = {
	  {"Xe",0.10},
	  {"Ar",0.104},
	  {"CO2",0.158},
	  {"CH4",0.397},
	  {"H2O",3.7},
	  {"O2",1.22}
  };
};
#endif

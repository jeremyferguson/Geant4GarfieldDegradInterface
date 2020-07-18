#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction* HPGeDet)
    : detector(HPGeDet) {
    miniDir = new G4UIdirectory("/Xenon/");
    miniDir->SetGuidance("Xenon specific controls");

    ////////////////////
    geometryDir = new G4UIdirectory("/Xenon/geometry/");
    geometryDir->SetGuidance("Xenon geometry specific controls");


    ////////////////////
    setGasPressCmd =
      new G4UIcmdWithADoubleAndUnit("/Xenon/geometry/SetGasPressure", this);

    setGasPressCmd->SetGuidance("Set gas pressure.");
    setGasPressCmd->SetUnitCategory("Pressure");
    setGasPressCmd->SetDefaultValue(0.3 * bar);
    setGasPressCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    setMainGasPerCmd =
      new G4UIcmdWithADouble("/Xenon/geometry/SetMainGasPercentage", this);

    setMainGasPerCmd->SetGuidance("Set percentage of the main gas in the mixture");
    setMainGasPerCmd->SetDefaultValue(100.0);
    setMainGasPerCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    setSecondGasPerCmd =
      new G4UIcmdWithADouble("/Xenon/geometry/SetSecondGasPercentage", this);

    setSecondGasPerCmd->SetGuidance("Set percentage of the second gas in the mixture");
    setSecondGasPerCmd->SetDefaultValue(100.0);
    setSecondGasPerCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    setImpurityGasPerCmd =
      new G4UIcmdWithADouble("/Xenon/geometry/SetImpurityGasPercentage", this);

    setImpurityGasPerCmd->SetGuidance("Set percentage of the impurity gas in the mixture");
    setImpurityGasPerCmd->SetDefaultValue(100.0);
    setImpurityGasPerCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    setThirdGasPerCmd =
      new G4UIcmdWithADouble("/Xenon/geometry/SetThirdGasPercentage", this);

    setThirdGasPerCmd->SetGuidance("Set percentage of the third gas in the mixture");
    setThirdGasPerCmd->SetDefaultValue(100.0);
    setThirdGasPerCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
    
    setMainGasCmd = 
	new G4UIcommand("/Xenon/geometry/SetMainGas",this);
    setMainGasCmd->SetGuidance("Set the main gas");
    G4UIparameter* mainGasName = new G4UIparameter("GasType", 's', false);
    mainGasName->SetParameterCandidates("Xe Ar");
    setMainGasCmd->SetParameter(mainGasName);

    setSecondGasCmd = 
        new G4UIcommand("/Xenon/geometry/SetSecondGas", this);
    setSecondGasCmd->SetGuidance("Set the second gas");
    G4UIparameter* secondGasName = new G4UIparameter("GasType", 's', false);
    secondGasName->SetParameterCandidates("Xe Ar CO2 CH4 He");
    setSecondGasCmd->SetParameter(secondGasName);
    
    setImpurityGasCmd = 
        new G4UIcommand("/Xenon/geometry/SetImpurityGas", this);
    setImpurityGasCmd->SetGuidance("Set the impurity gas");
    G4UIparameter* impurityGasName = new G4UIparameter("GasType", 's', false);
    impurityGasName->SetParameterCandidates("O2 H2O");
    setImpurityGasCmd->SetParameter(impurityGasName);
    
    setThirdGasCmd = 
        new G4UIcommand("/Xenon/geometry/SetThirdGas", this);
    setThirdGasCmd->SetGuidance("Set the third gas");
    G4UIparameter* thirdGasName = new G4UIparameter("GasType", 's', false);
    thirdGasName->SetParameterCandidates("Xe Ar CO2 CH4 He");
    setThirdGasCmd->SetParameter(thirdGasName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger() {
    delete miniDir;
    delete geometryDir;
    delete setGasPressCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValues) {
  if (command == setGasPressCmd)
    detector->SetGasPressure(setGasPressCmd->GetNewDoubleValue(newValues));
  else if (command == setMainGasPerCmd)
	  detector->SetMainGasPercentage(setMainGasPerCmd->GetNewDoubleValue(newValues));
  else if (command == setSecondGasPerCmd)
	  detector->SetSecondGasPercentage(setSecondGasPerCmd->GetNewDoubleValue(newValues));
  else if (command == setImpurityGasPerCmd)
	  detector->SetImpurityGasPercentage(setImpurityGasPerCmd->GetNewDoubleValue(newValues));
  else if (command == setThirdGasPerCmd)
	  detector->SetThirdGasPercentage(setThirdGasPerCmd->GetNewDoubleValue(newValues));
  else if (command == setMainGasCmd)
	  detector->SetMainGas(newValues);
  else if (command == setSecondGasCmd)
	  detector->SetSecondGas(newValues);
  else if (command == setImpurityGasCmd)
	  detector->SetImpurityGas(newValues);
  else if (command == setThirdGasCmd)
	  detector->SetThirdGas(newValues);
}

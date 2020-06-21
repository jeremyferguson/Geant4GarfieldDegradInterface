//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: GarfieldFastSimulationModel.hh 9999994 2015-12-11 14:47:43Z dpfeiffe $
//
/// \file GarfieldFastSimulationModel.hh
/// \brief Definition of the GarfieldFastSimulationModel class

#ifndef GarfieldVUVPhotonModel_h
#define GarfieldVUVPhotonModel_h 1

#include "G4VFastSimulationModel.hh"
#include "Medium.hh"
#include "GasBoxSD.hh"
#include "MediumMagboltz.hh"
#include "AvalancheMicroscopic.hh"

class GasModelParameters;
class DetectorConstruction;
class GasBoxSD;

class GarfieldVUVPhotonModel : public G4VFastSimulationModel
{
public:
  //-------------------------
  // Constructor, destructor
  //-------------------------
	GarfieldVUVPhotonModel(GasModelParameters*, G4String, G4Region*,DetectorConstruction*,GasBoxSD*);
  ~GarfieldVUVPhotonModel (){};

  //void SetPhysics(degradPhysics* fdegradPhysics);
  //void WriteGeometryToGDML(G4VPhysicalVolume* physicalVolume);

	virtual G4bool IsApplicable(const G4ParticleDefinition&);
	virtual G4bool ModelTrigger(const G4FastTrack &);
	virtual void DoIt(const G4FastTrack&, G4FastStep&);
	void GenerateVUVPhotons(const G4FastTrack& fastTrack, G4FastStep& fastStep,G4ThreeVector garfPos,G4double garfTime);

	G4ThreeVector garfPos;
	G4double garfTime;
	
	
	
private:
	void InitialisePhysics();

	DetectorConstruction* detCon;
	G4ThreeVector myPoint;
	G4double time;
	G4double thermalE;
   //degradPhysics* fdegradPhysics;

	Garfield::MediumMagboltz* fMediumMagboltz;
	Garfield::AvalancheMicroscopic* fAvalanche;

	GasBoxSD* fGasBoxSD;
};

void userHandle(double x, double y, double z, double t, int type, int level,Garfield::Medium * m,  double e0, double e1, double dx0, double dy0, double dz0, double dx1, double dy1, double dz1);
#endif /* GarfieldVUVPhotonModel_H_ */

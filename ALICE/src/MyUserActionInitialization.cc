#include "MyUserActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "G4SDManager.hh"
#include "GasBoxSD.hh"
#include "SteppingAction.hh"
#include "MyTrackingAction.hh"

MyUserActionInitialization::MyUserActionInitialization(){}

MyUserActionInitialization::~MyUserActionInitialization(){}

void MyUserActionInitialization::Build() const {
	PrimaryGeneratorAction* primary = new PrimaryGeneratorAction();
	SetUserAction(primary);
	SteppingAction* stepAct = new SteppingAction();
	SetUserAction(stepAct);
	EventAction* evt = new EventAction();
	SetUserAction(evt);
	SetUserAction(new RunAction());
	MyTrackingAction* trk = new MyTrackingAction();
	SetUserAction(trk);
}

void MyUserActionInitialization::BuildForMaster() const {
	SetUserAction(new RunAction());
}

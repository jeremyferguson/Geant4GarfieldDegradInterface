#ifndef GasBoxSD_hh
#define GasBoxSD_hh

#include "G4VSensitiveDetector.hh"
#include "G4String.hh"
#include "G4Region.hh"
#include "XenonHit.hh"
#include "GarfieldExcitationHit.hh"
#include "DegradExcitationHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;


class GasBoxSD : public G4VSensitiveDetector{
	public:
	
	GasBoxSD(G4String);
	~GasBoxSD();
	
	virtual void 	Initialize (G4HCofThisEvent *);
	virtual void 	EndOfEvent (G4HCofThisEvent *);
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
	virtual void DrawAll();
    void InsertXenonHit(XenonHit* xh){fXenonHitsCollection->insert(xh);};
    void InsertGarfieldExcitationHit(GarfieldExcitationHit* geh){fGarfieldExcitationHitsCollection->insert(geh);};
    void InsertDegradExcitationHit(DegradExcitationHit* dh){fDegradExcitationHitsCollection->insert(dh);};
	private:
	
    XenonHitsCollection* fXenonHitsCollection;
    GarfieldExcitationHitsCollection* fGarfieldExcitationHitsCollection;
    DegradExcitationHitsCollection* fDegradExcitationHitsCollection;
    G4int XHCID;
    G4int GEHCID;
    G4int DEHCID;
    
	
};

#endif


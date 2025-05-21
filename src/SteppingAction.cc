#include "SteppingAction.hh"
#include "Constructor.hh"
#include "EventAction.hh"

SteppingAction::SteppingAction(EventAction *eventAction)
    : G4UserSteppingAction(), fEventAction(eventAction),
      physicalDetector(nullptr) {
  // Initialize the stepping action
  G4cout << "Stepping Action" << G4endl;
}

SteppingAction::~SteppingAction() {
  // Finalize the stepping action
}

void SteppingAction::UserSteppingAction(const G4Step *step) {
  // Process the step
  G4cout << "Stepping Action" << G4endl;
  fEventAction->AddStepTimes(1);

  // get detector logicalvolume
  if (physicalDetector == nullptr) {
    // get Constructor
    const Constructor *detectorConstruction = static_cast<const Constructor *>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    physicalDetector = detectorConstruction->GetPhysicalVolume();
  }

  // get current logical volume
  G4VPhysicalVolume *volume =
      step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

  // check if we are in scoring volume
  if (volume != physicalDetector) {
    return;
  }
  // Get copyNo
  G4int copyNo = physicalDetector->GetCopyNo();
  G4double edep = step->GetTotalEnergyDeposit();

}
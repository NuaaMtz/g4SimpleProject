#include "SteppingAction.hh"
#include "Constructor.hh"
#include "EventAction.hh"

SteppingAction::SteppingAction(EventAction *eventAction)
    : G4UserSteppingAction(), fEventAction(eventAction),
      physicalDetector(nullptr),logicalDetector(nullptr) {
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
  // test: AnalysisManager could be work on step
  // auto man = G4AnalysisManager::Instance();
  // man->FillNtupleIColumn(3, 0, 1);    // ntupleId 3, column 0
  // man->FillNtupleIColumn(3, 1, 1);    // ntupleId 3, column 1
  // man->FillNtupleDColumn(3, 2, 1); // ntupleId 3, column 2
  // man->AddNtupleRow(3);

  // get detector logicalvolume
  if (logicalDetector == nullptr) {
    // get Constructor
    const Constructor *detectorConstruction = static_cast<const Constructor *>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        logicalDetector = detectorConstruction->GetLogicalVolume();
  }

  // get current logical volume
  G4LogicalVolume *volume =
      step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  // check if we are in scoring volume
  if (volume != logicalDetector) {
    return;
  }
  // Get copyNo and  energy deposit
  G4int copyNo = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetCopyNo();
  G4double edep = step->GetTotalEnergyDeposit();
  G4int i = copyNo / RunAction::ncols;
  G4int j = copyNo % RunAction::ncols;

  // store 
  auto man = G4AnalysisManager::Instance();
  man->FillNtupleIColumn(3, 0, i);    // ntupleId 3, column 0
  man->FillNtupleIColumn(3, 1, j);    // ntupleId 3, column 1
  man->FillNtupleDColumn(3, 2, edep); // ntupleId 3, column 2
  man->AddNtupleRow(3);
  
}
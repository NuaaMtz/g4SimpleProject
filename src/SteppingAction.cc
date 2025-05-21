#include "SteppingAction.hh"

SteppingAction::SteppingAction(EventAction* eventAction):G4UserSteppingAction(),fEventAction(eventAction) {
  // Initialize the stepping action
  G4cout << "Stepping Action" << G4endl;
}

SteppingAction::~SteppingAction() {
  // Finalize the stepping action
}

void SteppingAction::UserSteppingAction(const G4Step* ) {
  // Process the step
  G4cout << "Stepping Action" << G4endl;
  fEventAction->AddStepTimes(1);
}
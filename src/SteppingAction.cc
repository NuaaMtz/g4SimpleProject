/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 15:33:00
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-22 17:21:47
 * @FilePath: /betatron/src/SteppingAction.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE//
 */
#include "SteppingAction.hh"
#include "Constructor.hh"
#include "EventAction.hh"
#include <G4Types.hh>
#include <algorithm>
#include <iostream>

SteppingAction::SteppingAction(EventAction *eventAction)
    : G4UserSteppingAction(), fEventAction(eventAction),
      physicalDetector(nullptr),logicalDetector(nullptr) {
  // Initialize the stepping action
  // G4cout << "Stepping Action" << G4endl;
}

SteppingAction::~SteppingAction() {
  // Finalize the stepping action
}

void SteppingAction::UserSteppingAction(const G4Step *step) {
  // Process the step
  // G4cout << "Stepping Action" << G4endl;
  fEventAction->AddStepTimes(1);

  // Get life time of primary particle
  G4Track *track = step->GetTrack();
  //G4int n_particles =fEventAction->fRunAction->fPrimaryGenerator->GetParticleGun()->GetNumberOfParticles();
  if (track->GetParentID()==0 && track->GetTrackStatus() == fStopAndKill) {
    G4double endTime = track->GetGlobalTime();
    fEventAction->SetSimTime(endTime);
  }
  



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

  G4int ncols=6;
  G4int i = copyNo / ncols;
  G4int j = copyNo % ncols;

  //Get position X and Y
  G4double x = step->GetPreStepPoint()->GetPosition().x();
  G4double y = step->GetPreStepPoint()->GetPosition().y();

  // store 
  auto man = G4AnalysisManager::Instance();
  man->FillNtupleIColumn(3, 0, i);    // ntupleId 3, column 0
  man->FillNtupleIColumn(3, 1, j);    // ntupleId 3, column 1
  man->FillNtupleDColumn(3, 2, edep); // ntupleId 3, column 2
  man->AddNtupleRow(3);

  man->FillNtupleDColumn(4, 0, x);    // ntupleId 4, column
  man->FillNtupleDColumn(4, 1, y);    // ntupleId 4, column
  man->FillNtupleDColumn(4, 2, edep); // ntupleId 4, column
  man->FillNtupleDColumn(4,3,edep); // ntupleId 4, column
  man->AddNtupleRow(4) ;
  
}
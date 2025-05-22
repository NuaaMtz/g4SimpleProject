/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 14:06:54
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-22 12:04:06
 * @FilePath: /betatron/src/RunAction.cc
 * @Description: run action
 */
#include "RunAction.hh"
#include <G4Types.hh>
#include <G4UserRunAction.hh>

RunAction::RunAction() : G4UserRunAction(), fEventTimes(0), fStepTimes(0) {

  // Create root structor
  auto man = G4Root::G4AnalysisManager::Instance();
  // auto merge file
  man->SetNtupleMerging(true);

  man->CreateH1(
      "run", "RunAction", 100, 0.,
      100.); // RunAction runs times (beginofrunaction and endofrunaction)

  man->CreateNtuple("event",
                    "EventAction"); // EventAction runs times (beginofrunaction
                                    // and endofrunaction)
  man->CreateNtupleIColumn("event");
  man->FinishNtuple(0);

  man->CreateNtuple("step", "SteppingAction"); // SteppingAction runs times
                                               // (beginofrunaction and endofrun
  man->CreateNtupleIColumn("step");
  man->FinishNtuple(1);

  man->CreateNtuple("primary particle",
                    "PrimaryParticle"); // primary particle momontumn
  man->CreateNtupleDColumn("Px");
  man->CreateNtupleDColumn("Py");
  man->CreateNtupleDColumn("Pz");
  man->FinishNtuple(2);

  man->CreateNtuple("stepDataDec", "Step Data Detector");
  man->CreateNtupleIColumn("i");
  man->CreateNtupleIColumn("j");
  man->CreateNtupleDColumn("edep");
  man->FinishNtuple(3);

  man->CreateNtuple("SetpData", "Step Data");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->CreateNtupleDColumn("edep");
  man->FinishNtuple(4);
}
RunAction::~RunAction() {
  
}
void RunAction::BeginOfRunAction(const G4Run *run) {
  // Initialize the run action
  // G4cout << "Begin of Run" << G4endl;

  // create root files
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  auto man = G4Root::G4AnalysisManager::Instance();
  G4int runNum = run->GetRunID();
  std::stringstream strRunID;
  strRunID << runNum;
  man->OpenFile("../rt/output_target" + strRunID.str() +
                ".root"); // while this project is runing, how many times
                          // RunAction is runing how many files are created
}
void RunAction::EndOfRunAction(const G4Run *run) {
  // Finalize the run action
  // G4cout << "End of Run" << G4endl;
  auto man = G4Root::G4AnalysisManager::Instance();
  if (!G4Threading::IsMasterThread()) {
    man->FillH1(0, 1);
  }

  // make sure the run is not empty
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) {
    return;
  }

  // prepare the root data（merge only alpply on work thread!）
  G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
  if (G4Threading::IsMasterThread()) {
    accumulableManager->Merge();
  }

  // calculate somethings
  G4int eventTimes = fEventTimes.GetValue();
  G4int stepTimes = fStepTimes.GetValue();

  // save the root file
  if (!G4Threading::IsMasterThread()) {
    man->FillNtupleIColumn(0, 0, eventTimes); // ntupleId 0, columnId 0
    man->AddNtupleRow(0);
    man->FillNtupleIColumn(1, 0, stepTimes); // ntupleId 1, columnId 0
    man->AddNtupleRow(1);

  }
  man->Write();
  man->CloseFile();
}



/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 15:11:57
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-22 17:27:03
 * @FilePath: /betatron/src/EventAction.cc
 * @Description: Event Action(begin and end of event)
 */
#include "EventAction.hh"
#include "RunAction.hh"
#include <G4AccumulableManager.hh>
#include <G4UserRunAction.hh>

EventAction::EventAction(RunAction *runAction)
    : G4UserEventAction(),fRunAction(runAction), fStepTimes(0){
  G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fStepTimes);
}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event *) {
  // Initialize the event action
  // G4cout << "Begin of Event" << G4endl;
  // get primary particle
  

  

}

void EventAction::EndOfEventAction(const G4Event *) {
  // Finalize the event action
  // G4cout << "End of Event" << G4endl;
  fRunAction->AddStepTimes(fStepTimes.GetValue());
  fRunAction->AddEventTimes(1);
  fRunAction->AddSimTime(fSimTime);
  
  
  // merge eventEdep
}
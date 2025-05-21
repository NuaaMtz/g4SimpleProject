/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 12:20:58
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-21 15:52:02
 * @FilePath: /betatron/src/InitializationAction.cc
 * @Description: manage the action of the simulation
 */
#include "InitializationAction.hh"


InitializationAction::InitializationAction() {}
InitializationAction::~InitializationAction() {}

void InitializationAction::BuildForMaster() const {
  // Define the master thread action
  RunAction* runAction = new RunAction;
  SetUserAction(runAction);
  
}
void InitializationAction::Build() const {
    // primary particle gun
    PrimaryGeneratorAction* primaryGeneratorAction = new PrimaryGeneratorAction();
    SetUserAction(primaryGeneratorAction);

  // Define the worker thread action
    RunAction* runAction = new RunAction;
    SetUserAction(runAction);

    // Define the event action
    EventAction* eventAction = new EventAction(runAction);
    SetUserAction(eventAction);

    // Define the stepping action
    SteppingAction* steppingAction = new SteppingAction(eventAction);
    SetUserAction(steppingAction);


}
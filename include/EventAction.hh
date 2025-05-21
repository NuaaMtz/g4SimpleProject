/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 15:10:35
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-21 15:35:55
 * @FilePath: /betatron/include/EventAction.hh
 * @Description: Event Action(begin and end of event)
 */
#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4Accumulable.hh"
#include "G4RunManager.hh"
#include "G4UserEventAction.hh"
#include <G4RunManager.hh>
#include <G4UserEventAction.hh>
#include "RunAction.hh"
class EventAction : public G4UserEventAction {

public:
  EventAction(RunAction* runAction);
  virtual ~EventAction();
  virtual void BeginOfEventAction(const G4Event *event);
  virtual void EndOfEventAction(const G4Event *event);

  void AddStepTimes(G4int time) { fStepTimes += time; } // counts step times

private:
  G4Accumulable<G4int> fStepTimes; // counts step times
  RunAction* fRunAction; // run action
};

#endif
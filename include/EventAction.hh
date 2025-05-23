/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 15:10:35
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-22 17:19:10
 * @FilePath: /betatron/include/EventAction.hh
 * @Description: Event Action(begin and end of event)
 */
#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4Accumulable.hh"
#include "G4RunManager.hh"
#include "G4UserEventAction.hh"
#include "RunAction.hh"
#include <G4RunManager.hh>
#include <G4Types.hh>
#include <G4UserEventAction.hh>
#include <array>
#include <map>
#include <vector>
class EventAction : public G4UserEventAction {

public:
  EventAction(RunAction *runAction);
  virtual ~EventAction();
  virtual void BeginOfEventAction(const G4Event *event);
  virtual void EndOfEventAction(const G4Event *event);

  void AddStepTimes(G4int time) { fStepTimes += time; } // counts step times
  RunAction *fRunAction;           // run action

  void SetSimTime(G4double time) {  
    if(fSimTime<time){
      fSimTime = time;
    }
  } // counts simulation time

private:
  G4Accumulable<G4int> fStepTimes; // counts step times
  G4double fSimTime;// counts simulation time
  
};

#endif
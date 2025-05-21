/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 14:06:49
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-22 00:17:52
 * @FilePath: /betatron/include/RunAction.hh
 * @Description: run action
 */

#ifndef RUNACTION_HH
#define RUNACTION_HH
#include "G4UserRunAction.hh"
#include "Constructor.hh"
#include "g4root.hh"
#include "G4RunManager.hh"
#include <G4Run.hh>
#include <G4Types.hh>
#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"
#include <map>

class RunAction : public G4UserRunAction {
public:
static const G4int nrows = 10;
static const G4int ncols = 6;
  RunAction();
  ~RunAction();

  virtual void BeginOfRunAction(const G4Run *run);
  virtual void EndOfRunAction(const G4Run *run);

  void AddEventTimes(G4int time){fEventTimes+=time;}// counts event times
  void AddStepTimes(G4int time){fStepTimes+=time;}// counts step times

  void AddDetectorEdepMap(const std::map<G4int, G4double>& eventMap);


private:
    G4Accumulable<G4int> fEventTimes;// counts event times
    G4Accumulable<G4int> fStepTimes;// counts step times
   
};
#endif
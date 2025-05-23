/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 14:06:49
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-22 17:13:06
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
#include "PrimaryGeneratorAction.hh"

class RunAction : public G4UserRunAction {
public:

  RunAction(PrimaryGeneratorAction*);
  ~RunAction();

  virtual void BeginOfRunAction(const G4Run *run);
  virtual void EndOfRunAction(const G4Run *run);

  void AddEventTimes(G4int time){fEventTimes+=time;}// counts event times
  void AddStepTimes(G4int time){fStepTimes+=time;}// counts step times

  void AddSimTime(G4double time){fSimTime+=time;}// counts simulation time


  PrimaryGeneratorAction*  fPrimaryGenerator;

  
private:
    G4Accumulable<G4int> fEventTimes;// counts event times
    G4Accumulable<G4int> fStepTimes;// counts step times
    G4Accumulable<G4double> fSimTime;// counts simulation time

   
};
#endif
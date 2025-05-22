/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 15:33:08
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-22 10:22:44
 * @FilePath: /betatron/include/SteppingAction.hh
 * @Description: Stepping Action
 */
 #ifndef SteppingAction_h
 #define SteppingAction_h 1
 
 #include "G4UserSteppingAction.hh"
 #include "EventAction.hh"
 
 class SteppingAction : public G4UserSteppingAction
 {
   public:
     SteppingAction(EventAction* eventAction);
     virtual ~SteppingAction();
     virtual void UserSteppingAction(const G4Step*);
    private:
    EventAction* fEventAction;
    G4VPhysicalVolume *physicalDetector;
    G4LogicalVolume *logicalDetector;


     
 };
 #endif
 
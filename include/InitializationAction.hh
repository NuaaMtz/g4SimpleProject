/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 12:20:03
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-21 15:26:08
 * @FilePath: /betatron/include/InitializationAction.hh
 * @Description: manage the action of the simulation
 */
#ifndef INITIALIZATIONACTION_HH
#define INITIALIZATIONACTION_HH
#include "G4VUserActionInitialization.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
class InitializationAction : public G4VUserActionInitialization
{
public:
    InitializationAction();
    virtual ~InitializationAction();

    virtual void BuildForMaster() const override;// master thread
    virtual void Build() const override;// worker thread
};


#endif
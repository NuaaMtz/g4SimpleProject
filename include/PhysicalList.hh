/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 12:07:27
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-21 12:10:09
 * @FilePath: /betatron/include/PhysicalList.hh
 * @Description: register all the physics processes
 */
#ifndef PHYSICALLIST_HH
#define PHYSICALLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"


class PhysicalList : public G4VModularPhysicsList
{
public:
    PhysicalList();
    virtual ~PhysicalList();
};

#endif
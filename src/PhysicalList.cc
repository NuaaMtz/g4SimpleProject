#include "PhysicalList.hh"

PhysicalList::PhysicalList(){
    // Register electromagnetic physics
    RegisterPhysics(new G4EmStandardPhysics_option4());
    
    RegisterPhysics(new G4OpticalPhysics());

    // Register decay physics
    RegisterPhysics(new G4DecayPhysics());

    RegisterPhysics(new G4RadioactiveDecayPhysics());
    
    // high energy
    RegisterPhysics(new G4HadronPhysicsQGSP_BIC_HP());
}
PhysicalList::~PhysicalList(){

}


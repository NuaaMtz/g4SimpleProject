/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 11:55:29
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-22 10:20:35
 * @FilePath: /betatron/include/Constructor.hh
 * @Description: define world volume and all the volumes in the world
 */
#ifndef CONSTRUCTOR_HH
#define CONSTRUCTOR_HH
#include "G4VUserDetectorConstruction.hh"
#include <cstdio>
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Orb.hh"
#include "G4USphere.hh"
#include "G4Sphere.hh"
#include "G4PVPlacement.hh"


class Constructor : public G4VUserDetectorConstruction {
public:
  Constructor();
  virtual ~Constructor();

  virtual G4VPhysicalVolume *Construct() override;

  void DefineBTO();
  G4Material *worldMaterial ;
  G4LogicalVolume *worldLog;

  void DefineDetector();

  G4VPhysicalVolume *GetPhysicalVolume() const {
    return physicalDetector;
  }
  G4LogicalVolume *GetLogicalVolume() const {
    return logicalDetector;
  }

  
  //virtual void ConstructSDandField() override;
private:
  
  G4VPhysicalVolume *physicalDetector;
  G4LogicalVolume *logicalDetector;


};
#endif
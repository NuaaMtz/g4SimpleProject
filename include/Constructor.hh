/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 11:55:29
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-21 12:00:42
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


class Constructor : public G4VUserDetectorConstruction {
public:
  Constructor();
  virtual ~Constructor();

  virtual G4VPhysicalVolume *Construct() override;

  //virtual void ConstructSDandField() override;

};
#endif
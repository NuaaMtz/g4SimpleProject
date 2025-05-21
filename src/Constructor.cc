/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 11:55:44
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-21 15:59:49
 * @FilePath: /betatron/src/Constructor.cc
 * @Description: define world volume and all the volumes in the world
 */

#include "Constructor.hh"
#include <G4Material.hh>

Constructor::Constructor() {}
Constructor::~Constructor() {}
G4VPhysicalVolume *Constructor::Construct() {
  // Define the world volume
  G4double worldSize = 1.0 * m;
  G4Box *worldBox = new G4Box("World", worldSize, worldSize, worldSize);
  G4Element *elN = new G4Element("Nitrogen", "N", 7.,
                                 14.01 * g / mole); // Define nitrogen element
  G4Element *elO = new G4Element("Oxygen", "O", 8., 16.00 * g / mole);
  G4Element *elAr = new G4Element("Argon", "Ar", 18., 39.95 * g / mole);
  G4double worldDensity = 1.293e-3 * g / cm3;
  G4Material *worldMaterial = new G4Material("Air", worldDensity, 3);
  worldMaterial->AddElement(elN, 0.7808);
  worldMaterial->AddElement(elO, 0.2095);
  worldMaterial->AddElement(elAr, 0.0093);
  G4LogicalVolume *worldLog =
      new G4LogicalVolume(worldBox,worldMaterial , "World");
  G4VPhysicalVolume *worldPhys =
      new G4PVPlacement(0, G4ThreeVector(), worldLog, "World", 0, false, 0);

  return worldPhys;
}
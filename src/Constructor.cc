/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 11:55:44
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-22 14:58:47
 * @FilePath: /betatron/src/Constructor.cc
 * @Description: define world volume and all the volumes in the world
 */

#include "Constructor.hh"
#include <G4Material.hh>
#include <G4Types.hh>

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
  worldMaterial = new G4Material("Air", worldDensity, 3);
  worldMaterial->AddElement(elN, 0.7808);
  worldMaterial->AddElement(elO, 0.2095);
  worldMaterial->AddElement(elAr, 0.0093);
  worldLog = new G4LogicalVolume(worldBox, worldMaterial, "World");
  G4VPhysicalVolume *worldPhys =
      new G4PVPlacement(0, G4ThreeVector(), worldLog, "World", 0, false, 0);

  // Define BTO
  DefineBTO();
  // Define Nuaa
  //DefineNuaa();

  // Define detector
  DefineDetector();

  return worldPhys;
}

void Constructor::DefineBTO() {
  G4NistManager *nist = G4NistManager::Instance();
  G4Material *U238_material;
  G4Material *Be_material;
  G4Material *W_material;
  G4Material *Al_material;
  G4Material *U235_material;

  U238_material = nist->FindOrBuildMaterial("G4_U");
  Be_material = nist->FindOrBuildMaterial("G4_Be");
  W_material = nist->FindOrBuildMaterial("G4_W");
  Al_material = nist->FindOrBuildMaterial("G4_Al");

  // SOMETHING
  // U-235
  U235_material = new G4Material("U235_material", 18.95 * g / cm3, 1);
  G4Element *U235 = new G4Element("U235", "U235", 92, 235.04 * g / mole);
  U235_material->AddElement(U235, 1);

  G4bool checkOverlaps = true;
  G4LogicalVolume *logicalU;
  G4LogicalVolume *logicalBe;
  G4LogicalVolume *logicalWu;
  G4LogicalVolume *logicalAl;

  G4Orb *solidVac = new G4Orb("solidVac", 6.0 * cm);
  G4LogicalVolume *logicalVac =
      new G4LogicalVolume(solidVac, worldMaterial, "logicalVac");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 0), logicalVac, "physicalVac",
                    worldLog, false, 0, checkOverlaps);

  // WP_U
  G4Sphere *solidU = new G4Sphere("solidU", 6.0 * cm, 7.0 * cm, 0 * deg,
                                  360 * deg, 0 * deg, 180 * deg);
  logicalU = new G4LogicalVolume(solidU,        // its solid
                                 U238_material, // its material
                                 "logicalU");   // its name
  new G4PVPlacement(0,                          // no rotation
                    G4ThreeVector(0, 0, 0),     // at position
                    logicalU,                   // its logical volume
                    "physicalU",                // its name
                    worldLog,                   // its mother  volume
                    false,                      // no boolean operation
                    0,                          // copy number
                    checkOverlaps);             // overlaps checking

  // Reflective Be layer
  G4Sphere *solidBe = new G4Sphere("solidBe", 7.0 * cm, 9.0 * cm, 0 * deg,
                                   360 * deg, 0 * deg, 180 * deg);
  logicalBe = new G4LogicalVolume(solidBe,      // its solid
                                  Be_material,  // its material
                                  "logicalBe"); // its name
  new G4PVPlacement(0,                          // no rotation
                    G4ThreeVector(0, 0, 0),     // at position
                    logicalBe,                  // its logical volume
                    "physicalBe",               // its name
                    worldLog,                   // its mother  volume
                    false,                      // no boolean operation
                    0,                          // copy number
                    checkOverlaps);             // overlaps checking

  // Inert tungsten layer
  G4Sphere *solidWu = new G4Sphere("solidWu", 9.0 * cm, 11.0 * cm, 0 * deg,
                                   360 * deg, 0 * deg, 180 * deg);
  logicalWu = new G4LogicalVolume(solidWu,      // its solid
                                  W_material,   // its material
                                  "logicalWu"); // its name
  new G4PVPlacement(0,                          // no rotation
                    G4ThreeVector(0, 0, 0),     // at position
                    logicalWu,                  // its logical volume
                    "physicalWu",               // its name
                    worldLog,                   // its mother  volume
                    false,                      // no boolean operation
                    0,                          // copy number
                    checkOverlaps);             // overlaps checking

  // Housing aluminum layer
  G4Sphere *solidAl = new G4Sphere("solidAl", 11.0 * cm, 12.0 * cm, 0 * deg,
                                   360 * deg, 0 * deg, 180 * deg);
  logicalAl = new G4LogicalVolume(solidAl,      // its solid
                                  Al_material,  // its material
                                  "logicalAl"); // its name
  new G4PVPlacement(0,                          // no rotation
                    G4ThreeVector(0, 0, 0),     // at position
                    logicalAl,                  // its logical volume
                    "physicalAl",               // its name
                    worldLog,                   // its mother  volume
                    false,                      // no boolean operation
                    0,                          // copy number
                    checkOverlaps);             // overla
}

void Constructor::DefineDetector() {
  G4NistManager *nist = G4NistManager::Instance();
  G4int nrows = 10;
  G4int ncols = 6;
  G4double xDetec = 0.5 * m;// >0.24m
  G4double yDetec = 0.5 * m;
  G4double xDetecHalf = (xDetec / ncols) / 2.0;
  G4double yDetecHalf = (yDetec / nrows) / 2.0;

  G4Material *detectorMat;                // material of detector
  G4double densityOfNaI = 3.67 * g / cm3; // Density of Sodium Iodide
  detectorMat =
      new G4Material("SodiumIodide", densityOfNaI, 2);   // Sodium Iodide
  G4Element *elementNa = nist->FindOrBuildElement("Na"); // Sodium
  G4Element *elementI = nist->FindOrBuildElement("I");   // Iodine
  detectorMat->AddElement(elementNa, 1); // 1 Sodium atom
  detectorMat->AddElement(elementI, 1);  // 1 Iodine atom
  G4Box *solidDetector = new G4Box("solidDetector", xDetecHalf, yDetecHalf,
                                   0.01 * m); // x,y,z (half)
                                  
  logicalDetector =
      new G4LogicalVolume(solidDetector, detectorMat, "logicalDetector");

  for (G4int i = 0; i < nrows; i++) {
    for (G4int j = 0; j < ncols; j++) {
      G4double xPos = -xDetec / 2.0 + (j + 0.5) * 2.0 * xDetecHalf;
      G4double yPos = yDetec / 2.0 - (i + 0.5) * 2.0 * yDetecHalf;

      physicalDetector=new G4PVPlacement(0, G4ThreeVector(xPos, yPos, 0.25 * m),
                                      logicalDetector, "phyDetector",
                                      worldLog, false, j + i * ncols, true);
    }
  }
}


void Constructor::DefineNuaa() {
  G4NistManager *nist = G4NistManager::Instance();
  G4Material *mat = nist->FindOrBuildMaterial("G4_W"); // 用钨材料

  G4double thick = 1.0 * cm; // 字母笔画厚度
  G4double height = 12.0 * cm; // 字母高度
  G4double width = 2.0 * cm;   // 单个字母宽度
  G4double gap = 1.5 * cm;     // 字母间距

  // N
  new G4PVPlacement(0, G4ThreeVector(-13*cm, 0, 0), 
      new G4LogicalVolume(new G4Box("N_left", thick/2, height/2, thick/2), mat, "N_left_log"), 
      "N_left_phys", worldLog, false, 0);
  new G4PVPlacement(0, G4ThreeVector(-11*cm, 0, 0), 
      new G4LogicalVolume(new G4Box("N_right", thick/2, height/2, thick/2), mat, "N_right_log"), 
      "N_right_phys", worldLog, false, 0);
  new G4PVPlacement(0, G4ThreeVector(-12*cm, 0, 0), 
      new G4LogicalVolume(new G4Box("N_diag", thick/2, height/2*0.98, thick/2), mat, "N_diag_log"), 
      "N_diag_phys", worldLog, false, 0, 
      new G4RotationMatrix(0,0,atan(height/(width+gap))));

  // U
  new G4PVPlacement(0, G4ThreeVector(-8*cm, 0, 0), 
      new G4LogicalVolume(new G4Box("U_left", thick/2, height/2, thick/2), mat, "U_left_log"), 
      "U_left_phys", worldLog, false, 0);
  new G4PVPlacement(0, G4ThreeVector(-6*cm, 0, 0), 
      new G4LogicalVolume(new G4Box("U_right", thick/2, height/2, thick/2), mat, "U_right_log"), 
      "U_right_phys", worldLog, false, 0);
  new G4PVPlacement(0, G4ThreeVector(-7*cm, -height/2+thick/2, 0), 
      new G4LogicalVolume(new G4Box("U_bottom", width/2+gap/2, thick/2, thick/2), mat, "U_bottom_log"), 
      "U_bottom_phys", worldLog, false, 0);

  // A
  for(int k=0; k<2; ++k) {
      G4double xA = -2*cm + k*2*cm;
      new G4PVPlacement(0, G4ThreeVector(xA, 0, 0), 
          new G4LogicalVolume(new G4Box("A_leg", thick/2, height/2, thick/2), mat, "A_leg_log"), 
          "A_leg_phys", worldLog, false, 0);
  }
  new G4PVPlacement(0, G4ThreeVector(-1*cm, 0, 0), 
      new G4LogicalVolume(new G4Box("A_cross", width/2+gap/2, thick/2, thick/2), mat, "A_cross_log"), 
      "A_cross_phys", worldLog, false, 0);

  // A2
  for(int k=0; k<2; ++k) {
      G4double xA = 3*cm + k*2*cm;
      new G4PVPlacement(0, G4ThreeVector(xA, 0, 0), 
          new G4LogicalVolume(new G4Box("A2_leg", thick/2, height/2, thick/2), mat, "A2_leg_log"), 
          "A2_leg_phys", worldLog, false, 0);
  }
  new G4PVPlacement(0, G4ThreeVector(4*cm, 0, 0), 
      new G4LogicalVolume(new G4Box("A2_cross", width/2+gap/2, thick/2, thick/2), mat, "A2_cross_log"), 
      "A2_cross_phys", worldLog, false, 0);
}
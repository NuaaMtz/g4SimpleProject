/*
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 10:00:13
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-21 15:05:28
 * @FilePath: /mtz-sPaper/xRayImage.cc
 * @Description: 主函数
 */
#include "iostream"

#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "Constructor.hh"
#include "PhysicalList.hh"
#include "InitializationAction.hh"

int main(int argc, char **argv) {

  std::cout << "Hello World!" << std::endl;

  // accoring value to judge  open runmanager or mtrunmanager
  #ifdef G4MULTITHREADED
    G4MTRunManager *runManager = new G4MTRunManager;
  #else
    G4RunManager *runManager = new G4RunManager;
  #endif

  // initialize the run manager
  runManager->SetUserInitialization(new Constructor());
  runManager->SetUserInitialization(new PhysicalList());
  runManager->SetUserInitialization(new InitializationAction());

  // Process macro or start UI session
  G4UIExecutive *ui = 0;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }
  G4VisManager *visManager = new G4VisExecutive;
  visManager->Initialize();

  G4int verboseLevel = 0;
  G4RunManager::GetRunManager()->SetVerboseLevel(verboseLevel);


  G4UImanager *UImanager = G4UImanager::GetUIpointer();

  if (!ui) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  } else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // free the memory
  delete visManager;
  delete runManager;

  return 0;
}

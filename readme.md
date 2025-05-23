<!--
 * @Author: mtz nuaamzt@nuaa.edu.cn
 * @Date: 2025-05-21 11:36:54
 * @LastEditors: mtz nuaamzt@nuaa.edu.cn
 * @LastEditTime: 2025-05-23 14:58:01
 * @FilePath: /betatron/readme.md
 * @Description: 
-->
# G4程序模板

1. G4的基本模块都实现了
2. 只创建了世界
3. 在runAction中定义了root文件，把run,event和step的运行次数以His和Tree的方式保存下来

一个完整通用的g4模拟就完成了。  
## 重要的提示有:  
1. 因为要用到多线程，所以main函数中的SetUserInitialization完成之后，没有马上initialize这个runManager。而是在mac文件第一行先改了多线程后在initialize。因此自己写
新的mac的时候，下面两句开头是必须的：
   ```
   /run/numberOfThreads 10
   /run/initialize
   ```
强调：必须启用多线程模式，/run/numberOfThreads至少为2
1. Run-Event-Step的关系如下：

   ![alt text](./image/readme/relationship.jpg)
   本项目还没有遇到需要用到track的情形

2. 使用G4AnalysisManager来创建和保存root文件的时候，
   一定一定要注意线程问题，因为工作线程只创建了文件，所以所有的填充都在工作线程，最后的合并是在工作线程！

3. 两个action之间进行数据交换的时候一定保证要用到G4Accumulable这个容器作为中间变量，这样才能保证多线程的情况下，数据不会出错！！！这很重要！除非你不用多线程！！！


## 编程日记
### 1. 粒子枪粒子个数问题
不做特殊处理的话，粒子枪一次生成n_particle个粒子，而且这些粒子初始属性一模一样。为了能够一次性发射多个不同方向（所有属性都可以）
的粒子，要把粒子生成都放在GeneratePrimaries中如下：(各项同性)
```C++
void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
  auto man = G4Root::G4AnalysisManager::Instance();

  // particle gun counts
  G4int n_particles = 3;
  fParticleGun = new G4ParticleGun(n_particles);

  // Set the particle type
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "gamma";
  G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);

  for (G4int i = 0; i < n_particles; ++i) {
    // direction
    G4ThreeVector dir = IsotropicSource();
    fParticleGun->SetParticleMomentumDirection(dir);

    // Energy
    G4double energy = 4 * MeV + (7.5 * MeV - 4 * MeV) * G4UniformRand();
    fParticleGun->SetParticleEnergy(energy);

    // position
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0., -0.25 * m));

    // Fill to Roor files

    man->FillNtupleDColumn(2, 0, energy * dir.x());
    man->FillNtupleDColumn(2, 1, energy * dir.y());
    man->FillNtupleDColumn(2, 2, energy * dir.z());
    man->AddNtupleRow(2);

    // Generate the primary vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }
}

```

### 2. evnet、run、step
这个项目输出每次都输出begin和end，通过观察一个核内这些begin和end可以看出
它们的运行顺序

### 3. 圆锥体源
数学上，点源发射、方向在锥体内随机，就是所有粒子都从同一个点（如原点）出发，方向矢量分布在以z轴为轴心、极角θ在 $[0, \theta_{max}]$ 的锥体内，并且在锥体内均匀分布。三维空间中，单位方向矢量可用球坐标表示：  

- $\theta：极角（与z轴夹角），范围 $[0, \theta_{max}]$
- $\phi$：方位角（绕z轴旋转），范围 $[0, 2\pi]$  
- 直角坐标为： 
$$\begin{align*} x &= \sin\theta \cos\phi \\ y &= \sin\theta \sin\phi \\ z &= \cos\theta \end{align*}$$
如果直接均匀采样 $\theta$，会导致方向在球面上分布不均匀（靠近z轴密集）
- 均匀采样 $\cos\theta$ 在 $[\cos\theta_{max}, 1]$ 区间
- 均匀采样 $\phi$ 在 $[0, 2\pi]$ 区间
源设置如下：
```C++
    // 设定最大发散角（单位：弧度）
    G4double theta_min = 0.0;
    G4double theta_max = 90 * CLHEP::deg; // 10度

    // 均匀采样cos(theta)以保证各向同性
    G4double cosThetaMin = std::cos(theta_min);
    G4double cosThetaMax = std::cos(theta_max);
    G4double cosTheta = cosThetaMin + (cosThetaMax - cosThetaMin) * G4UniformRand();
    G4double theta = std::acos(cosTheta);
    G4double phi = 2. * CLHEP::pi * G4UniformRand();

    G4ThreeVector dir(std::sin(theta) * std::cos(phi),
                      std::sin(theta) * std::sin(phi),
                      std::cos(theta));

    fParticleGun->SetParticleMomentumDirection(dir);
```

### 4. 圆锥圆和球如何覆盖
假设BTO中心在原点，最大半径为$R_{BTO}$
放射源位于z轴上  $z_{source}$ ，其中$z_{source}$<0。
锥体要覆盖整个BTO，需满足：

$$\theta_{\text{max}} = \arctan\left(\frac{R_{\text{BTO}}}{|z_{\text{source}}|}\right) $$

### 5. 在event和run中的root文件写入

在runAction中创建文件后，直接就在evnet或者step中实例化g4root，再写入即可。如下面写在step：
```C++
  auto man = G4AnalysisManager::Instance();
  man->FillNtupleIColumn(3, 0, i);    // ntupleId 3, column 0
  man->FillNtupleIColumn(3, 1, j);    // ntupleId 3, column 1
  man->FillNtupleDColumn(3, 2, edep); // ntupleId 3, column 2
  man->AddNtupleRow(3);

```

### 6. 在step中判断所在位置
一定要用逻辑体来判断是否进入了探测器！  
copyNo必须用物理体获得

```C++
  // get detector logicalvolume
  if (logicalDetector == nullptr) {
    // get Constructor
    const Constructor *detectorConstruction = static_cast<const Constructor *>(
        G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        logicalDetector = detectorConstruction->GetLogicalVolume();
  }

  // get current logical volume
  G4LogicalVolume *volume =
      step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  // check if we are in scoring volume
  if (volume != logicalDetector) {
    return;
  }
```

###  7. BTO物体结构
. 最内层：真空球（Vacuum Sphere）
类型：球体（G4Orb）
半径：6.0 cm
材料：worldMaterial（空气）
作用：中心空腔，通常用于放置源或留空
2. 第二层：铀-238 球壳（U-238 Shell）
类型：球壳（G4Sphere）
内半径：6.0 cm
外半径：7.0 cm
材料：U238_material（铀-238）
作用：包裹在真空球外的第一层致密材料
3. 第三层：铍球壳（Be Shell）
类型：球壳（G4Sphere）
内半径：7.0 cm
外半径：9.0 cm
材料：Be_material（铍）
作用：反射层或中子反射体
4. 第四层：钨球壳（W Shell）
类型：球壳（G4Sphere）
内半径：9.0 cm
外半径：11.0 cm
材料：W_material（钨）
作用：惰性屏蔽层
5. 第五层：铝球壳（Al Shell）
类型：球壳（G4Sphere）
内半径：11.0 cm
外半径：12.0 cm
材料：Al_material（铝）
作用：外部包壳/机械支撑

总体结构：
真空球（半径6cm，空气/真空）
U-238球壳（6~7cm，铀-238）
Be球壳（7~9cm，铍）
W球壳（9~11cm，钨）
Al球壳（11~12cm，铝）

### 8. 获取模拟的时间

剂量率 = 总能量沉积 / (质量 × 总模拟时间)

剂量率计算中的时间是辐射源实际照射该区域的有效时间（照射时间）。
获取的总模拟时间是所有事件初始粒子从产生到消失的时间之和，
比如，一个事件发射3个粒子，那么取这三个初始粒子的最大寿命作为模拟时间。这段实际上得到的粒子在当前步骤结束时的全局时间。和模拟时间不是一个概念
```C++
  // Get life time of primary particle
  G4Track *track = step->GetTrack();
  //G4int n_particles =fEventAction->fRunAction->fPrimaryGenerator->GetParticleGun()->GetNumberOfParticles();
  if (track->GetParentID()==0 && track->GetTrackStatus() == fStopAndKill) {
    G4double endTime = track->GetGlobalTime();
    fEventAction->SetSimTime(endTime);
  }
```
```
在Geant4中使用粒子枪一次性发射多个粒子，然后计算探测器内的剂量率时，可以遵循以下步骤：

#### 1. 模拟设置

**粒子枪设置**：
- 设置粒子枪每次发射10个粒子。

**探测器参数**：
- 确定探测器的质量 \(m\)，通常以千克（kg）为单位。

#### 2. 运行模拟

**事件模拟**：
- 运行模拟以产生多个事件（`G4Event`）。每个事件中发射10个粒子。

**计算能量沉积**：
- 在每个事件中，使用`G4Step`对象记录在探测器中沉积的能量。累积所有事件的沉积能量，得到总能量沉积 \(E_{\text{total}}\)，单位通常是电子伏特（eV）或焦耳（J）。

#### 3. 时间定义

**定义时间间隔**：
- 如果粒子枪每秒发射一次，这意味着每秒发射10个粒子。这可以认为是一个概念化的活动性，即10 Bq。

**估算模拟的物理时间**：
- 如果你运行了 \(N\) 个事件，并假设每个事件代表1秒的物理时间（因为每秒发射一次），则模拟的物理时间段为：
  \[
  t_{\text{simulated}} = N
  \]
- 这里假设每次发射代表1秒的时间间隔。

#### 4. 计算剂量率

**计算剂量率**：
- 使用总能量沉积和估算的物理时间计算剂量率 \(D_{\text{rate}}\)：
  \[
  D_{\text{rate}} = \frac{E_{\text{total}}}{m \times t_{\text{simulated}}}
  \]
- 确保单位一致性。常见的剂量率单位是戈瑞每秒（Gy/s），其中 \(1 \, \text{Gy} = 1 \, \text{J/kg}\)。

#### 5. 注意事项

- **单位转换**：确保所有计算中的单位一致，特别是在能量沉积和质量的单位转换上。
- **统计不确定性**：通过增加事件数量 \(N\) 来减少统计不确定性，提高计算的准确性。
- **验证模拟结果**：与实验数据或理论预期结果进行比较，以验证模拟的准确性。

通过这些步骤，你可以在Geant4中有效地计算探测器的剂量率。确保在模拟设置中正确定义时间间隔和探测器的几何与材料特性，以获得可靠的结果。

总得来说，粒子枪的个数被视为放射性活度，一秒钟发射的粒子数，
事件数N视为秒

在使用加速器源时，剂量率的计算依赖于粒子束的束流强度或流率。以下是如何使用这些概念计算剂量率的步骤：

#### 1. 获取束流强度

**束流强度定义**：
- 束流强度（或流率）指的是单位时间内通过某个截面的粒子数，通常以粒子每秒（particles per second, pps）为单位。

#### 2. 模拟设置

**探测器参数**：
- 确定探测器的质量 \(m\)，通常以千克（kg）为单位。

**能量沉积计算**：
- 在Geant4模拟中，运行多个事件来记录粒子在探测器中沉积的能量。累积所有事件的沉积能量，得到总能量沉积 \(E_{\text{total}}\)，单位通常是电子伏特（eV）或焦耳（J）。

#### 3. 时间定义

**定义时间间隔**：
- 如果束流强度是 \(I\) pps（粒子每秒），并且模拟运行了 \(N\) 个事件，那么可以定义模拟的物理时间段：
  \[
  t_{\text{simulated}} = \frac{N}{I}
  \]
- 这里假设每个事件代表的时间由束流强度决定。

#### 4. 计算剂量率

**计算剂量率**：
- 使用总能量沉积和估算的物理时间计算剂量率 \(D_{\text{rate}}\)：
  \[
  D_{\text{rate}} = \frac{E_{\text{total}}}{m \times t_{\text{simulated}}}
  \]
- 确保单位一致性。常见的剂量率单位是戈瑞每秒（Gy/s），其中 \(1 \, \text{Gy} = 1 \, \text{J/kg}\)。

#### 5. 注意事项

- **单位转换**：确保所有计算中的单位一致，特别是在能量沉积和质量的单位转换上。
- **统计不确定性**：通过增加事件数量 \(N\) 来减少统计不确定性，提高计算的准确性。
- **验证模拟结果**：与实验数据或理论预期结果进行比较，以验证模拟的准确性。

通过这些步骤，你可以在Geant4中有效地计算探测器的剂量率，基于加速器源的束流强度或流率。确保在模拟设置中正确定义时间间隔和探测器的几何与材料特性，以获得可靠的结果。
对于加速器源，通常使用的概念是“束流强度”或“流率”，即单位时间内通过某一截面的粒子数，通常以粒子每秒（particles per second）为单位。直接用束流强度替代前面的活度

```
### 9. 一次run和多次run的区别？
单次run的随机数序列连续生成10个事件的随机数，无中断。
多次run的情况下，若两次命令之间未手动重置随机数种子（如未执行/control/random/resetEngine），则第二次的run的事件会延续第一次的随机数序列（即第6-10个事件的随机数与单次运行的后5个完全一致）。
只要“不搞额外操作”，分两次打5个粒子和一次打10个粒子，最终的物理结果（统计量、累积数据）没有区别。

### 10.
#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4NistManager *nist = G4NistManager::Instance();
	const G4int iNbEntries = 3; //Number of entries used in the optical arrays

	//================================== elements ===================================
	G4Element* Xe = new G4Element("Xenon", "Xe", 54., 131.293 * g / mole);
	G4Element* H = new G4Element("Hydrogen", "H", 1., 1.0079 * g / mole);
	G4Element* C = new G4Element("Carbon", "C", 6., 12.011 * g / mole);
	G4Element* N = new G4Element("Nitrogen", "N", 7., 14.007 * g / mole);
	G4Element* O = new G4Element("Oxygen", "O", 8., 15.999 * g / mole);
	G4Element* F = new G4Element("Fluorine", "F", 9., 18.998 * g / mole);
	G4Element* Al = new G4Element("Aluminium", "Al", 13., 26.982 * g / mole);
	G4Element* Si = new G4Element("Silicon", "Si", 14., 28.086 * g / mole);
	G4Element* Cr = new G4Element("Chromium", "Cr", 24., 51.996 * g / mole);
	G4Element* Mn = new G4Element("Manganese", "Mn", 25., 54.938 * g / mole);
	G4Element* Fe = new G4Element("Iron", "Fe", 26., 55.85 * g / mole);
	G4Element* Ni = new G4Element("Nickel", "Ni", 28., 58.693 * g / mole);
	G4Element* Cu = new G4Element("Copper", "Cu", 29., 63.546 * g / mole);
	G4Element* Pb = new G4Element("Lead", "Pb", 82., 207.2 * g / mole);
	G4Element* Sn = new G4Element("Tin", "Sn", 50., 120.0 * g / mole);
	G4Element* B = nist->FindOrBuildElement("B");
	G4Element* Gd = nist->FindOrBuildElement("Gd");

	G4Element* Ca = new G4Element("Calcium", "Ca", 20., 40.078 * g / mole);

	G4Element* Mg = new G4Element("Mg", "Mg", 12., 24.3050 * g / mole);
	G4Element* K = new G4Element("K", "K", 19., 39.0983 * g / mole);
	G4Element* Na = new G4Element("Na", "Na", 11., 22.989769 * g / mole);
	G4Element* P = new G4Element("P", "P", 15., 30.973762 * g / mole);
	G4Element* S = new G4Element("S", "S", 16., 32.065 * g / mole);
	G4Element* Ti = new G4Element("Ti", "Ti", 22., 47.867 * g / mole);

	G4Element* Au = new G4Element("Au", "Au", 79., 196.96657 * g / mole);
	//================================== materials ==================================

	//----------------------------------- air ---------------------------------------
	G4Material *Air = nist->FindOrBuildMaterial("G4_AIR");

	//----------------------------------- water -------------------------------------
	G4Material *Water = new G4Material("Water", 1. * g / cm3, 2, kStateLiquid);
	Water->AddElement(H, 2);
	Water->AddElement(O, 1);

	//----------------------------------- vacuum ------------------------------------
	G4Material *Vacuum = new G4Material("Vacuum", 1.e-20 * g / cm3, 2, kStateGas);
	Vacuum->AddElement(N, 0.755);
	Vacuum->AddElement(O, 0.245);
	
	//------------------------------------ teflon -----------------------------------
	G4Material *Teflon = new G4Material("Teflon", 2.2 * g / cm3, 2, kStateSolid);
	Teflon->AddElement(C, 0.240183);
	Teflon->AddElement(F, 0.759817);

	G4double pdTeflonPhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV,
                                                 7.05 * eV};
	G4double pdTeflonRefractiveIndex[iNbEntries] = {1.63, 1.61, 1.58};
	G4double pdTeflonReflectivity[iNbEntries] = {0.99, 0.99, 0.99};
	G4double pdTeflonSpecularLobe[iNbEntries] = {0.01, 0.01, 0.01};
	G4double pdTeflonSpecularSpike[iNbEntries] = {0.01, 0.01, 0.01};
	G4double pdTeflonBackscatter[iNbEntries] = {0.01, 0.01, 0.01};
	G4double pdTeflonEfficiency[iNbEntries] = {1.0, 1.0, 1.0};
	G4double pdTeflonAbsorbtionLength[iNbEntries] = {0.1 * cm, 0.1 * cm,
													0.1 * cm};
	G4MaterialPropertiesTable *pTeflonPropertiesTable =
		new G4MaterialPropertiesTable();
	pTeflonPropertiesTable->AddProperty("RINDEX", pdTeflonPhotonMomentum,
										pdTeflonRefractiveIndex, iNbEntries);
	pTeflonPropertiesTable->AddProperty("REFLECTIVITY", pdTeflonPhotonMomentum,
										pdTeflonReflectivity, iNbEntries);
	pTeflonPropertiesTable->AddProperty("ABSLENGTH", pdTeflonPhotonMomentum,
										pdTeflonAbsorbtionLength, iNbEntries);
	pTeflonPropertiesTable->AddProperty("SPECULARLOBECONSTANT",
										pdTeflonPhotonMomentum,
										pdTeflonSpecularLobe, iNbEntries);
	pTeflonPropertiesTable->AddProperty("SPECULARSPIKECONSTANT",
										pdTeflonPhotonMomentum,
										pdTeflonSpecularSpike, iNbEntries);
	pTeflonPropertiesTable->AddProperty("BACKSCATTERCONSTANT",
										pdTeflonPhotonMomentum,
										pdTeflonBackscatter, iNbEntries);
	pTeflonPropertiesTable->AddProperty("EFFICIENCY", pdTeflonPhotonMomentum,
										pdTeflonEfficiency, iNbEntries);
	
	//==== Default optics if no OpticalSurface is given
	Teflon->SetMaterialPropertiesTable(pTeflonPropertiesTable);
	G4double pdTeflonSufraceTransmittance[iNbEntries] = {1e-12,1e-12,1e-12}; // 1e-12 because Geant4 is stupid
	//==== LXe Teflon ====
	G4OpticalSurface *pLXeTeflonOpticalSurface = new G4OpticalSurface("LXeTeflonOpticalSurface", 
		unified, ground, dielectric_dielectric, 0.1);

	G4MaterialPropertiesTable *pLXeTeflonPropertiesTable =
		new G4MaterialPropertiesTable();
	pLXeTeflonPropertiesTable->AddProperty("RINDEX", 
		pTeflonPropertiesTable->GetProperty("RINDEX"));
	pLXeTeflonPropertiesTable->AddProperty("REFLECTIVITY",
		pTeflonPropertiesTable->GetProperty("REFLECTIVITY"));
	pLXeTeflonPropertiesTable->AddProperty("ABSLENGTH", 
		pTeflonPropertiesTable->GetProperty("ABSLENGTH"));
	pLXeTeflonPropertiesTable->AddProperty("SPECULARLOBECONSTANT", 
		pTeflonPropertiesTable->GetProperty("SPECULARLOBECONSTANT"));
	pLXeTeflonPropertiesTable->AddProperty("SPECULARSPIKECONSTANT", 
		pTeflonPropertiesTable->GetProperty("SPECULARSPIKECONSTANT"));
	pLXeTeflonPropertiesTable->AddProperty("BACKSCATTERCONSTANT", 
		pTeflonPropertiesTable->GetProperty("BACKSCATTERCONSTANT"));
	pLXeTeflonPropertiesTable->AddProperty("EFFICIENCY", 
		pTeflonPropertiesTable->GetProperty("EFFICIENCY"));
	pLXeTeflonPropertiesTable->AddProperty("TRANSMITTANCE", pdTeflonPhotonMomentum, 
											pdTeflonSufraceTransmittance, iNbEntries);  
	pLXeTeflonOpticalSurface->SetMaterialPropertiesTable(
		pLXeTeflonPropertiesTable);

	//----------------------------------- quartz ------------------------------------
	// ref: http://www.sciner.com/Opticsland/FS.htm
	G4Material *Quartz = new G4Material("Quartz", 2.201 * g / cm3, 2, kStateSolid,
										168.15 * kelvin, 1.5 * atmosphere);
	Quartz->AddElement(Si, 1);
	Quartz->AddElement(O, 2);

	// Optical properties Quartz
	const G4int iNbEntriesMatch = 5;
	G4double pdQuartzPhotonMomentum[iNbEntriesMatch] = {
		1. * eV, 6.9 * eV, 6.91 * eV, 6.98 * eV,
		7.05 * eV};  // SERENA: changed  2.*eV to 1.*eV otherwise it gets stuck
					// "Out of Range - Attempt to retrieve information below
					// range!"
	G4double pdQuartzRefractiveIndex[iNbEntriesMatch] = {1.50, 1.50, 1.50, 1.56,
														1.60};
	G4double pdQuartzAbsorbtionLength[iNbEntriesMatch] = {30 * m, 30 * m, 30 * m,
															30 * m, 30 * m};
	G4MaterialPropertiesTable *pQuartzPropertiesTable =
		new G4MaterialPropertiesTable();

	/*
	// Masatoshi Kobayashi for ID PMT photocathode:  For debug. Set same RINDEX with LXe to ignore reflection etc between PMT Window and LXe.
	pQuartzPropertiesTable->AddProperty("RINDEX", pdLXePhotonMomentum,
										pdLXeRefractiveIndex, iNbEntriesMatch);
	*/


	pQuartzPropertiesTable->AddProperty("RINDEX", pdQuartzPhotonMomentum,
										pdQuartzRefractiveIndex, iNbEntriesMatch);
	pQuartzPropertiesTable->AddProperty("ABSLENGTH", pdQuartzPhotonMomentum,
										pdQuartzAbsorbtionLength,
										iNbEntriesMatch);
	Quartz->SetMaterialPropertiesTable(pQuartzPropertiesTable);


	/**********Stainless Steel**********/
	// stainlessSteel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");

	// G4Material *stainlessSteel =
	// 	new G4Material("SS304LSteel", 8.00 * g / cm3, 5, kStateSolid);
	// stainlessSteel->AddElement(Fe, 0.65);
	// stainlessSteel->AddElement(Cr, 0.20);
	// stainlessSteel->AddElement(Ni, 0.12);
	// stainlessSteel->AddElement(Mn, 0.02);
	// stainlessSteel->AddElement(Si, 0.01);

	// G4double pdLXeSSPhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV,
	// 												7.05 * eV};
	// G4double pdLXeSSReflectivity[iNbEntries] = {0.05, 0.05, 0.05};
	// G4MaterialPropertiesTable *pLXeSSPropertiesTable = 
	// 			new G4MaterialPropertiesTable();
	// pLXeSSPropertiesTable->AddProperty("REFLECTIVITY",
	// 		pdLXeSSPhotonMomentum, pdLXeSSReflectivity, iNbEntries);
	
	// pLXeSSSurface = new G4OpticalSurface("LXeSSSurface", 
	// 	unified, polished, dielectric_metal, 0.1);   
	// pLXeSSSurface->SetMaterialPropertiesTable(pLXeSSPropertiesTable);

	/**********Gold**********/

	// G4Material *Gold = new G4Material("Au", 19.3 * g / cm3, 1, kStateSolid);
	// Gold->AddElement(Au, 1.);

	// G4double pdLXeAuPhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV,
	// 												7.05 * eV};
	// G4double pdLXeAuReflectivity[iNbEntries] = {0.23, 0.23, 0.23};
	// G4MaterialPropertiesTable *pLXeAuPropertiesTable = 
	// 			new G4MaterialPropertiesTable();
	// pLXeAuPropertiesTable->AddProperty("REFLECTIVITY",
	// 		pdLXeAuPhotonMomentum, pdLXeAuReflectivity, iNbEntries);
	
	// pLXeAuSurface = new G4OpticalSurface("LXeAuSurface", 
	// 	unified, polished, dielectric_metal, 0.1);   
	// pLXeAuSurface->SetMaterialPropertiesTable(pLXeAuPropertiesTable);

	/**********Liquid Xenon**********/
	G4Material *LXe = new G4Material("LXe", 2.85 * g / cm3, 1, kStateLiquid, 177.05 * kelvin, 1.8 * atmosphere);
	LXe->AddElement(Xe, 1);

	G4double pdLXePhotonMomentum[iNbEntries] = { 6.91 * eV, 6.98 * eV, 7.05 * eV };
	G4double pdLXeScintillation[iNbEntries] = { 0.1,     1.0,     0.1 };
	G4double pdLXeRefractiveIndex[iNbEntries] = { 1.63,    1.61,    1.58 };
	G4double pdLXeAbsorbtionLength[iNbEntries] = { 5000. * cm, 5000. * cm, 5000. * cm };
	G4double pdLXeScatteringLength[iNbEntries] = { 30. * cm,  30. * cm,  30. * cm };

	G4MaterialPropertiesTable* pLXePropertiesTable = new G4MaterialPropertiesTable();

	pLXePropertiesTable->AddProperty("SCINTILLATIONCOMPONENT1", pdLXePhotonMomentum, pdLXeScintillation, iNbEntries);
	pLXePropertiesTable->AddProperty("SCINTILLATIONCOMPONENT2", pdLXePhotonMomentum, pdLXeScintillation, iNbEntries);
	pLXePropertiesTable->AddProperty("RINDEX", pdLXePhotonMomentum, pdLXeRefractiveIndex, iNbEntries);
	pLXePropertiesTable->AddProperty("ABSLENGTH", pdLXePhotonMomentum, pdLXeAbsorbtionLength, iNbEntries);
	pLXePropertiesTable->AddProperty("RAYLEIGH", pdLXePhotonMomentum, pdLXeScatteringLength, iNbEntries);

	pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 0. / keV);
	pLXePropertiesTable->AddConstProperty("RESOLUTIONSCALE", 0);
	pLXePropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 3. * ns);
	pLXePropertiesTable->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 27. * ns);
	pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD1", 1.0);

	LXe->SetMaterialPropertiesTable(pLXePropertiesTable);

	//-------------------------------- gaseous xenon --------------------------------
	// G4Material *GXe = new G4Material("GXe", 0.005887 * g / cm3, 1, kStateGas, 173.15 * kelvin, 1.5 * atmosphere);
	// GXe->AddElement(Xe, 1);

	// G4double pdGXePhotonMomentum[iNbEntries] = { 6.91 * eV, 6.98 * eV, 7.05 * eV };
	// G4double pdGXeScintillation[iNbEntries] = { 0.1,     1.0,     0.1 };
	// G4double pdGXeRefractiveIndex[iNbEntries] = { 1.00,    1.00,    1.00 };
	// G4double pdGXeAbsorbtionLength[iNbEntries] = { 100 * m,   100 * m,   100 * m };
	// G4double pdGXeScatteringLength[iNbEntries] = { 100 * m,   100 * m,   100 * m };

	// G4MaterialPropertiesTable* pGXePropertiesTable = new G4MaterialPropertiesTable();

	//pGXePropertiesTable->AddProperty("FASTCOMPONENT", pdGXePhotonMomentum, pdGXeScintillation, iNbEntries);
	//pGXePropertiesTable->AddProperty("SLOWCOMPONENT", pdGXePhotonMomentum, pdGXeScintillation, iNbEntries);
	//pGXePropertiesTable->AddProperty("RINDEX", pdGXePhotonMomentum, pdGXeRefractiveIndex, iNbEntries);
	//pGXePropertiesTable->AddProperty("ABSLENGTH", pdGXePhotonMomentum, pdGXeAbsorbtionLength, iNbEntries);
	//pGXePropertiesTable->AddProperty("RAYLEIGH", pdGXePhotonMomentum, pdGXeScatteringLength, iNbEntries);

	//pGXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 0. / (keV));
	//pGXePropertiesTable->AddConstProperty("RESOLUTIONSCALE", 0);
	//pGXePropertiesTable->AddConstProperty("FASTTIMECONSTANT", 3. * ns);
	//pGXePropertiesTable->AddConstProperty("SLOWTIMECONSTANT", 27. * ns);
	//pGXePropertiesTable->AddConstProperty("YIELDRATIO", 1.0);

	//GXe->SetMaterialPropertiesTable(pGXePropertiesTable);

    G4Material *worldMat = Vacuum;
    
    G4Box *solidWorld = new G4Box("solidWorld", 0.05*m, 0.05*m, 0.05*m);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

	//teflon shell in PET cell
	G4Box *solidTeflonShell = new G4Box("teflonShell", 0.03*m, 0.03*m, 0.0275*m);
	G4LogicalVolume *logicTeflonShell = new G4LogicalVolume(solidTeflonShell, Teflon, "logicTeflon");
	G4VPhysicalVolume *physTeflonShell = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicTeflonShell, "physTeflonShell", logicWorld, false, 0, true);

	//liquid xenon in PET cell
	G4Box *solidLiquidXenon = new G4Box("liquidXenon", 0.025*m, 0.025*m, 0.025*m);
	//G4LogicalVolume *logicLiquidXenon = new G4LogicalVolume(solidLiquidXenon, G4Material::GetMaterial("LXe"), "logicLiquidXenon");
	G4LogicalVolume *logicLiquidXenon = new G4LogicalVolume(solidLiquidXenon, LXe, "logicLiquidXenon");
	G4VPhysicalVolume *physLiquidXenon = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.0025*m), logicLiquidXenon, "physLiquidXenon", logicTeflonShell, false, 0, true);

	//setting border between teflon and liquid xenon
	G4LogicalBorderSurface *teflonLXeBorder = new G4LogicalBorderSurface("teflonLXeBorder", physLiquidXenon, physTeflonShell, pLXeTeflonOpticalSurface);

	//SiPMs in PET cell
	//only have to detect photons so made of LXe
	//made of LXe because it can't detect the photons otherwise (idk why)
	G4Box *solidDetector = new G4Box("solidDetector", 0.0075*m, 0.0075*m, 0.001*m);
    logicDetector = new G4LogicalVolume(solidDetector, LXe, "logicDetector");
    for (G4int i = 0; i < 3; i++) {
        for (G4int j = 0; j < 3; j++) {
            G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector((0.01625-i*0.01625)*m, (0.01625-j*0.01625)*m, 0.0285*m), logicDetector, "physDetector", logicWorld, false, 10*i+j, true);
        }
    }
	
    return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
    MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

    logicDetector->SetSensitiveDetector(sensDet);
}

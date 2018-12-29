// -*- C++ -*-
//
// Package:    AdvancedMultifitCMSSW/TreeProducerNoise
// Class:      TreeProducerNoise
// 
/**\class TreeProducerNoise TreeProducerNoise.cc AdvancedMultifitCMSSW/TreeProducerNoise/plugins/TreeProducerNoise.cc
 * 
 * Description: [one line class summary]
 * 
 * Implementation:
 *     [Notes on implementation]
 */
//
// Original Author:  Andrea Massironi
//         Created:  Thu, 27 Dec 2018 10:09:05 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"



// ECAL specific

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"

#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbService.h"
#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbRecord.h"
#include "CondFormats/EcalObjects/interface/EcalADCToGeVConstant.h"
#include "CondFormats/DataRecord/interface/EcalADCToGeVConstantRcd.h"
#include "CondFormats/EcalObjects/interface/EcalIntercalibConstants.h"
#include "CondFormats/EcalObjects/interface/EcalIntercalibConstantsMC.h"
#include "CondFormats/DataRecord/interface/EcalIntercalibConstantsRcd.h"
#include "CondFormats/DataRecord/interface/EcalIntercalibConstantsMCRcd.h"


#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"

#include "DataFormats/EcalRecHit/interface/EcalUncalibratedRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"



#include "FWCore/Framework/interface/ESHandle.h"



#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"   //     ----> CLHEP/Geometry/Point3D.h issue
// #include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"    ----> CLHEP/Geometry/Point3D.h issue
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
// #include "Geometry/EcalAlgo/interface/EcalBarrelGeometry.h"      ----> CLHEP/Geometry/Point3D.h issue
// #include "Geometry/EcalAlgo/interface/EcalEndcapGeometry.h"      ----> CLHEP/Geometry/Point3D.h issue




// #include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
// #include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "CondFormats/EcalObjects/interface/EcalMGPAGainRatio.h"
#include "CondFormats/EcalObjects/interface/EcalGainRatios.h"
#include "CondFormats/DataRecord/interface/EcalGainRatiosRcd.h"


#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"




//---- pfrechit
#include "DataFormats/ParticleFlowReco/interface/PFRecHitFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHit.h"

//--- pfcluster
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"



//---- for TP

#include "CondFormats/EcalObjects/interface/EcalTPGLutIdMap.h"
#include "CondFormats/EcalObjects/interface/EcalTPGLutGroup.h"
#include "CondFormats/EcalObjects/interface/EcalTPGPhysicsConst.h"
#include "CondFormats/DataRecord/interface/EcalTPGLutIdMapRcd.h"
#include "CondFormats/DataRecord/interface/EcalTPGLutGroupRcd.h"
#include "CondFormats/DataRecord/interface/EcalTPGPhysicsConstRcd.h"


#include "Geometry/CaloTopology/interface/EcalTrigTowerConstituentsMap.h"


//---- for Laser Correction 
#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbService.h"
#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbRecord.h"




#include "TTree.h"




//---- for Zee part
#include "DataFormats/PatCandidates/interface/Electron.h"



//---- for SR flags
#include "CalibCalorimetry/EcalTPGTools/interface/EcalReadoutTools.h"




//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TreeProducerNoise : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit TreeProducerNoise(const edm::ParameterSet&);
  ~TreeProducerNoise();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  // ----------member data ---------------------------
 
  edm::EDGetTokenT<EcalRecHitCollection> _token_ebrechits;
  edm::EDGetTokenT<EcalRecHitCollection> _token_eerechits;
  
  
  
  TTree *outTree;
  
  float _LaserCorrection_EB[61200];
  float _energy_EB[61200];
  int   _ieta[61200];
  int   _iphi[61200];

  float _LaserCorrection_EE[14648];
  float _energy_EE[14648];
  int   _ix[14648];
  int   _iy[14648];
  int   _iz[14648];
  
  
  //---- reconstructed energy
  TH1F* histo_energy[61200+14648];
  
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TreeProducerNoise::TreeProducerNoise(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
  usesResource("TFileService");
  
  
  //now do what ever initialization is needed
  usesResource("TFileService");
  edm::Service<TFileService> fs;
  
  _token_ebrechits = consumes<EcalRecHitCollection>(iConfig.getParameter<edm::InputTag>("EcalRecHitsEBCollection"));
  _token_eerechits = consumes<EcalRecHitCollection>(iConfig.getParameter<edm::InputTag>("EcalRecHitsEECollection"));
  
  
  outTree = fs->make<TTree>("tree","tree");
  
  outTree->Branch("LaserCorrection_EB",   _LaserCorrection_EB,    "LaserCorrection_EB[61200]/F");
  outTree->Branch("energy_EB",   _energy_EB,    "energy_EB[61200]/F");
  outTree->Branch("ieta",             _ieta,    "ieta[61200]/I");
  outTree->Branch("iphi",             _iphi,    "iphi[61200]/I");
  
  outTree->Branch("LaserCorrection_EE",   _LaserCorrection_EE,    "LaserCorrection_EE[14648]/F");
  outTree->Branch("energy_EE",   _energy_EE,    "energy_EE[14648]/F");
  outTree->Branch("ix",                 _ix,    "ix[14648]/I");
  outTree->Branch("iy",                 _iy,    "iy[14648]/I");
  outTree->Branch("iz",                 _iz,    "iz[14648]/I");
  
  
}


TreeProducerNoise::~TreeProducerNoise()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called for each event  ------------
void
TreeProducerNoise::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  
  
  //---- rechits
  
  edm::Handle<EcalRecHitCollection> ebrechithandle;
  const EcalRecHitCollection *ebrechits = NULL;
  edm::Handle<EcalRecHitCollection> eerechithandle;
  const EcalRecHitCollection *eerechits = NULL;
  
  iEvent.getByToken(_token_ebrechits,ebrechithandle);
  ebrechits = ebrechithandle.product();
  iEvent.getByToken(_token_eerechits,eerechithandle);
  eerechits = eerechithandle.product();
  
  //---- setup default
  for (int ixtal=0; ixtal < 61200; ixtal++) {
    _LaserCorrection_EB[ixtal] = -999;
    _energy_EB[ixtal] = -999;
    _ieta[ixtal] = -999;
    _iphi[ixtal] = -999;
  }
  for (int ixtal=0; ixtal < 14648; ixtal++) {
    _LaserCorrection_EE[ixtal] = -999;
    _energy_EE[ixtal] = -999;
    _ix[ixtal] = -999;
    _iy[ixtal] = -999;
    _iz[ixtal] = -999;
  }
  
  
  //---- geometry 
  
//   edm::ESHandle<CaloGeometry> pGeometry;
//   iSetup.get<CaloGeometryRecord>().get(pGeometry);
//   const CaloGeometry *geometry = pGeometry.product();
  
  
  // Laser corrections
  edm::ESHandle<EcalLaserDbService> pLaser;
  iSetup.get<EcalLaserDbRecord>().get( pLaser );
  
  
  
  for (EcalRecHitCollection::const_iterator itrechit = ebrechits->begin(); itrechit != ebrechits->end(); itrechit++ ) {
//     _energy_EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitude();  //----> only in EcalUncalibratedRecHit
    _energy_EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->energy();
    _ieta[EBDetId(itrechit->id()).hashedIndex()] = EBDetId(itrechit->id()).ieta();
    _iphi[EBDetId(itrechit->id()).hashedIndex()] = EBDetId(itrechit->id()).iphi();    
    _LaserCorrection_EB[EBDetId(itrechit->id()).hashedIndex()] = pLaser -> getLaserCorrection( EBDetId(itrechit->id()), iEvent.time() );
    
    
  }
  
  
  for (EcalRecHitCollection::const_iterator itrechit = eerechits->begin(); itrechit != eerechits->end(); itrechit++ ) {
//     _energy_EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitude();  //----> only in EcalUncalibratedRecHit
    _energy_EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->energy();
    _ix[EEDetId(itrechit->id()).hashedIndex()] = EEDetId(itrechit->id()).ix();
    _iy[EEDetId(itrechit->id()).hashedIndex()] = EEDetId(itrechit->id()).iy();
    _iz[EEDetId(itrechit->id()).hashedIndex()] = EEDetId(itrechit->id()).zside();
    _LaserCorrection_EE[EEDetId(itrechit->id()).hashedIndex()] = pLaser -> getLaserCorrection( EEDetId(itrechit->id()), iEvent.time() );
  }
  
  outTree->Fill();
  
}




// ------------ method called once each job just before starting event loop  ------------
void 
TreeProducerNoise::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TreeProducerNoise::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TreeProducerNoise::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeProducerNoise);

// -*- C++ -*-
//
// Package:    AdvancedMultifitCMSSW/TreeProducerNoiseUncalib
// Class:      TreeProducerNoiseUncalib
// 
/**\class TreeProducerNoiseUncalib TreeProducerNoiseUncalib.cc AdvancedMultifitCMSSW/TreeProducerNoiseUncalib/plugins/TreeProducerNoiseUncalib.cc
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

#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"



#include "FWCore/Framework/interface/ESHandle.h"



#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"   //     ----> CLHEP/Geometry/Point3D.h issue
// #include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"    ----> CLHEP/Geometry/Point3D.h issue
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
// #include "Geometry/EcalAlgo/interface/EcalBarrelGeometry.h"      ----> CLHEP/Geometry/Point3D.h issue
// #include "Geometry/EcalAlgo/interface/EcalEndcapGeometry.h"      ----> CLHEP/Geometry/Point3D.h issue




// #include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "CondFormats/EcalObjects/interface/EcalMGPAGainRatio.h"
#include "CondFormats/EcalObjects/interface/EcalGainRatios.h"
#include "CondFormats/DataRecord/interface/EcalGainRatiosRcd.h"


#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"


//---- EcalUncalibratedRecHit
#include "DataFormats/EcalRecHit/interface/EcalUncalibratedRecHit.h"




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

class TreeProducerNoiseUncalib : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
  explicit TreeProducerNoiseUncalib(const edm::ParameterSet&);
  ~TreeProducerNoiseUncalib();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  
  // ----------member data ---------------------------
 
  edm::EDGetTokenT<EcalUncalibratedRecHitCollection> _token_ebrechits;
  edm::EDGetTokenT<EcalUncalibratedRecHitCollection> _token_eerechits;
  
  edm::EDGetTokenT<EcalUncalibratedRecHitCollection> _token_second_ebrechits;
  edm::EDGetTokenT<EcalUncalibratedRecHitCollection> _token_second_eerechits;
  
  
  edm::EDGetTokenT<EBDigiCollection> _token_ebdigi;
  edm::EDGetTokenT<EEDigiCollection> _token_eedigi;
  
  
  
  TTree *_outTree;
  
  float _amplitude_EB[61200];
  float _amplitude_second_EB[61200];
  float _rms_EB[61200];
  int   _ieta[61200];
  int   _iphi[61200];

  float _amplitude_EE[14648];
  float _amplitude_second_EE[14648];
  float _rms_EE[14648];
  int   _ix[14648];
  int   _iy[14648];
  int   _iz[14648];
  
  
  //---- rms for EE and EB
  TH1F* _histo_0_rms_EB[61200];
  TH1F* _histo_0_rms_EE[14648];
  
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
TreeProducerNoiseUncalib::TreeProducerNoiseUncalib(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
  usesResource("TFileService");
  
  
  //now do what ever initialization is needed
  usesResource("TFileService");
  edm::Service<TFileService> fs;
  
  _token_ebrechits = consumes<EcalUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("EcalRecHitsEBCollection"));
  _token_eerechits = consumes<EcalUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("EcalRecHitsEECollection"));

  _token_second_ebrechits = consumes<EcalUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("EcalRecHitsEBCollectionSecond"));
  _token_second_eerechits = consumes<EcalUncalibratedRecHitCollection>(iConfig.getParameter<edm::InputTag>("EcalRecHitsEECollectionSecond"));
  
  _token_ebdigi = consumes<EBDigiCollection>(iConfig.getParameter<edm::InputTag>("EBDigiCollection"));
  _token_eedigi = consumes<EEDigiCollection>(iConfig.getParameter<edm::InputTag>("EEDigiCollection"));
  
  
  for (int i=0; i<61200; i++) {
    std::string name = "histo_0_rms_EB_" + std::to_string(i);
    _histo_0_rms_EB[i] = fs->make<TH1F>(name.c_str(), "", 1000, 0, 1000);
  }
  for (int i=0; i<14648; i++) {
    std::string name = "histo_0_rms_EE_" + std::to_string(i);
    _histo_0_rms_EE[i] = fs->make<TH1F>(name.c_str(), "", 1000, 0, 1000);
  }
  
  _outTree = fs->make<TTree>("tree","tree");
  
  _outTree->Branch("rms_EB",              _rms_EB,              "rms_EB[61200]/F");
  _outTree->Branch("amplitude_EB",        _amplitude_EB,        "amplitude_EB[61200]/F");
  _outTree->Branch("amplitude_second_EB", _amplitude_second_EB, "amplitude_second_EB[61200]/F");
  _outTree->Branch("ieta",                _ieta,                "ieta[61200]/I");
  _outTree->Branch("iphi",                _iphi,                "iphi[61200]/I");
  
  _outTree->Branch("rms_EE",              _rms_EE,              "rms_EE[14648]/F");
  _outTree->Branch("amplitude_EE",        _amplitude_EE,        "amplitude_EE[14648]/F");
  _outTree->Branch("amplitude_second_EE", _amplitude_second_EE, "amplitude_second_EE[14648]/F");
  _outTree->Branch("ix",                  _ix,                  "ix[14648]/I");
  _outTree->Branch("iy",                  _iy,                  "iy[14648]/I");
  _outTree->Branch("iz",                  _iz,                  "iz[14648]/I");
  
  
}


TreeProducerNoiseUncalib::~TreeProducerNoiseUncalib()
{
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called for each event  ------------
void
TreeProducerNoiseUncalib::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  
  
  //---- uncalibrated rechits
  
 
  edm::Handle<EcalUncalibratedRecHitCollection> ebrechithandle;
  const EcalUncalibratedRecHitCollection *ebrechits = NULL;
  edm::Handle<EcalUncalibratedRecHitCollection> eerechithandle;
  const EcalUncalibratedRecHitCollection *eerechits = NULL;
  
  iEvent.getByToken(_token_ebrechits,ebrechithandle);
  ebrechits = ebrechithandle.product();
  iEvent.getByToken(_token_eerechits,eerechithandle);
  eerechits = eerechithandle.product();
  
  
  edm::Handle<EcalUncalibratedRecHitCollection> ebrechit_second_handle;
  const EcalUncalibratedRecHitCollection *ebrechits_second = NULL;
  edm::Handle<EcalUncalibratedRecHitCollection> eerechit_second_handle;
  const EcalUncalibratedRecHitCollection *eerechits_second = NULL;
  
  iEvent.getByToken(_token_second_ebrechits,ebrechit_second_handle);
  ebrechits_second = ebrechit_second_handle.product();
  iEvent.getByToken(_token_second_eerechits,eerechit_second_handle);
  eerechits_second = eerechit_second_handle.product();
  
  
  //---- digis
  edm::Handle<EBDigiCollection> ebdigihandle;
  const EBDigiCollection *ebdigis = NULL;
  edm::Handle<EEDigiCollection> eedigihandle;
  const EEDigiCollection *eedigis = NULL;
  
  iEvent.getByToken(_token_ebdigi,ebdigihandle);
  ebdigis = ebdigihandle.product();
  iEvent.getByToken(_token_eedigi,eedigihandle);
  eedigis = eedigihandle.product();
  
  
  
  //---- setup default
  for (int ixtal=0; ixtal < 61200; ixtal++) {
    _rms_EB[ixtal] = -999;
    _amplitude_EB[ixtal] = -999;
    _amplitude_second_EB[ixtal] = -999;
    _ieta[ixtal] = -999;
    _iphi[ixtal] = -999;
  }
  for (int ixtal=0; ixtal < 14648; ixtal++) {
    _rms_EE[ixtal] = -999;
    _amplitude_EE[ixtal] = -999;
    _amplitude_second_EE[ixtal] = -999;
    _ix[ixtal] = -999;
    _iy[ixtal] = -999;
    _iz[ixtal] = -999;
  }
  
  
  //---- geometry 
  
  for (EcalUncalibratedRecHitCollection::const_iterator itrechit = ebrechits->begin(); itrechit != ebrechits->end(); itrechit++ ) {
    _amplitude_EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitude();  //----> only in EcalUncalibratedRecHit
    _ieta[EBDetId(itrechit->id()).hashedIndex()] = EBDetId(itrechit->id()).ieta();
    _iphi[EBDetId(itrechit->id()).hashedIndex()] = EBDetId(itrechit->id()).iphi();    
  }
  
  
  for (EcalUncalibratedRecHitCollection::const_iterator itrechit = eerechits->begin(); itrechit != eerechits->end(); itrechit++ ) {
    _amplitude_EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitude();  //----> only in EcalUncalibratedRecHit
    _ix[EEDetId(itrechit->id()).hashedIndex()] = EEDetId(itrechit->id()).ix();
    _iy[EEDetId(itrechit->id()).hashedIndex()] = EEDetId(itrechit->id()).iy();
    _iz[EEDetId(itrechit->id()).hashedIndex()] = EEDetId(itrechit->id()).zside();
  }
  
  
  
  for (EcalUncalibratedRecHitCollection::const_iterator itrechit = ebrechits_second->begin(); itrechit != ebrechits_second->end(); itrechit++ ) {
    _amplitude_second_EB[EBDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitude();  //----> only in EcalUncalibratedRecHit
    _ieta[EBDetId(itrechit->id()).hashedIndex()] = EBDetId(itrechit->id()).ieta();
    _iphi[EBDetId(itrechit->id()).hashedIndex()] = EBDetId(itrechit->id()).iphi();    
  }
  
  
  for (EcalUncalibratedRecHitCollection::const_iterator itrechit = eerechits_second->begin(); itrechit != eerechits_second->end(); itrechit++ ) {
    _amplitude_second_EE[EEDetId(itrechit->id()).hashedIndex()] =  itrechit->amplitude();  //----> only in EcalUncalibratedRecHit
    _ix[EEDetId(itrechit->id()).hashedIndex()] = EEDetId(itrechit->id()).ix();
    _iy[EEDetId(itrechit->id()).hashedIndex()] = EEDetId(itrechit->id()).iy();
    _iz[EEDetId(itrechit->id()).hashedIndex()] = EEDetId(itrechit->id()).zside();
  }
  
  
  
 //---- get RMS noise
 
 for (EBDigiCollection::const_iterator itdigi = ebdigis->begin(); itdigi != ebdigis->end(); itdigi++ ) {
   
   float sum_square = 0;
   float sum        = 0;
   
   //                                                           0xFFF = 4095
   for (int iSample = 0; iSample < 10; iSample++) {
     float value = ( int( (*itdigi) [iSample] ) & 0xFFF );
     sum_square += (value*value) ;
     sum        +=  value ;
   }
   _rms_EB[ ((EBDetId&)((*itdigi))).hashedIndex() ] =  sqrt(sum_square/10. - sum/10.*sum/10.);
   _histo_0_rms_EB[ ((EBDetId&)((*itdigi))).hashedIndex() ] -> Fill (  ( int( (*itdigi) [0] ) & 0xFFF ) );    
 }
 
 
 for (EEDigiCollection::const_iterator itdigi = eedigis->begin(); itdigi != eedigis->end(); itdigi++ ) {

   float sum_square = 0;
   float sum        = 0;
   
   //                                                           0xFFF = 4095
   for (int iSample = 0; iSample < 10; iSample++) {
     float value = ( int( (*itdigi) [iSample] ) & 0xFFF );
     sum_square += (value*value) ;
     sum        +=  value ;
   }
   _rms_EE[ ((EEDetId&)((*itdigi))).hashedIndex() ] =  sqrt(sum_square/10. - sum/10.*sum/10.);
   _histo_0_rms_EE[ ((EEDetId&)((*itdigi))).hashedIndex() ] -> Fill (  ( int( (*itdigi) [0] ) & 0xFFF ) );    
   
 }
 
  _outTree->Fill();
  
}




// ------------ method called once each job just before starting event loop  ------------
void 
TreeProducerNoiseUncalib::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TreeProducerNoiseUncalib::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TreeProducerNoiseUncalib::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TreeProducerNoiseUncalib);

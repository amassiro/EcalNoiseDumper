# test reco and dump into a tree

import FWCore.ParameterSet.Config as cms

from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('analysis')
options.parseArguments()

process = cms.Process('ECALNoise')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(options.maxEvents)
)

process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)

process.TFileService = cms.Service("TFileService",
     fileName = cms.string(options.outputFile)
)

process.options = cms.untracked.PSet(
#    SkipEvent = cms.untracked.vstring('ProductNotFound'),
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('reco nevts:1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '92X_dataRun2_Prompt_v8', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '90X_upgrade2017_realistic_v20', '')


# 2018
process.GlobalTag = GlobalTag(process.GlobalTag, '101X_dataRun2_Prompt_v9', '')


process.TreeProducerNoiseUncalib = cms.EDAnalyzer('TreeProducerNoiseUncalib',

                            EBDigiCollection = cms.InputTag("ecalDigis",  "ebDigis"),
                            EEDigiCollection = cms.InputTag("ecalDigis",  "eeDigis"),

                            EcalRecHitsEBCollection = cms.InputTag("ecalMultiFitUncalibRecHit",  "EcalUncalibRecHitsEB"),
                            EcalRecHitsEECollection = cms.InputTag("ecalMultiFitUncalibRecHit",  "EcalUncalibRecHitsEE"),

                            EcalRecHitsEBCollectionSecond = cms.InputTag("ecalUncalibRecHit",  "EcalUncalibRecHitsEB"),
                            EcalRecHitsEECollectionSecond = cms.InputTag("ecalUncalibRecHit",  "EcalUncalibRecHitsEE"),

                            
                            # EBDigiCollection                      "ecalDigis"                 "ebDigis"         "PulseTree"     
                            # EEDigiCollection                      "ecalDigis"                 "eeDigis"         "PulseTree"     
                            
                            #
                            # edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> >    "ecalMultiFitUncalibRecHit"   "EcalUncalibRecHitsEB"   "PulseTree"   
                            # edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> >    "ecalUncalibRecHit"         "EcalUncalibRecHitsEB"   "PulseTree"   
                            # edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> >    "ecalMultiFitUncalibRecHit"   "EcalUncalibRecHitsEE"   "PulseTree"   
                            # edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> >    "ecalUncalibRecHit"         "EcalUncalibRecHitsEE"   "PulseTree"   
                            # 
                           )



process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(50)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(options.inputFiles),
                                secondaryFileNames = cms.untracked.vstring()
                                )


process.TreeProducerNoiseUncalib_step = cms.Path(process.TreeProducerNoiseUncalib)
process.endjob_step = cms.EndPath(process.endOfProcess)


process.schedule = cms.Schedule(
                                process.TreeProducerNoiseUncalib_step, 
                                process.endjob_step
                                )





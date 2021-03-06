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


# 2018 MC
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v12', '')


process.TreeProducerNoise = cms.EDAnalyzer('TreeProducerNoise',
                            #EcalRecHitsEBCollection = cms.InputTag("ecalRecHit",  "EcalRecHitsEB"),
                            #EcalRecHitsEECollection = cms.InputTag("ecalRecHit",  "EcalRecHitsEE"),

                            EcalRecHitsEBCollection = cms.InputTag("hltEcalRecHit",  "EcalRecHitsEB"),
                            EcalRecHitsEECollection = cms.InputTag("hltEcalRecHit",  "EcalRecHitsEE"),

#edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >    "hltEcalRecHit"             "EcalRecHitsEB"   "HLT"         
#edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> >    "hltEcalRecHit"             "EcalRecHitsEE"   "HLT"         


                            
                            #EBDigiCollection = cms.InputTag("selectDigi",  "selectedEcalEBDigiCollection"),
                            #EEDigiCollection = cms.InputTag("selectDigi",  "selectedEcalEEDigiCollection"),

                            EBDigiCollection = cms.InputTag("ecalDigis",  "ebDigis"),
                            EEDigiCollection = cms.InputTag("ecalDigis",  "eeDigis"),
                            
                            #
                            # this is not the collection I am looking for! They should be NOT selected or you bias the estimation of the RMS!
                            #
                            #EBDigiCollection                      "selectDigi"                "selectedEcalEBDigiCollection"   "RECO"    
                            #EEDigiCollection                      "selectDigi"                "selectedEcalEEDigiCollection"   "RECO"    
                            # 
                            # I want these ones!
                            #
                            # EBDigiCollection                      "ecalDigis"                 "ebDigis"         "PulseTree"   
                            # EEDigiCollection                      "ecalDigis"                 "eeDigis"         "PulseTree"   
                            #
                            #
                            

                            )


#reducedEgamma"             "reducedEBRecHits



#edm::SortedCollection<EBSrFlag,edm::StrictWeakOrdering<EBSrFlag> >    "ecalDigis"                 ""                "RECO"    
#edm::SortedCollection<EESrFlag,edm::StrictWeakOrdering<EESrFlag> >    "ecalDigis"                 ""                "RECO"    



process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(50)

process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring(options.inputFiles),
                                secondaryFileNames = cms.untracked.vstring()
                                )


process.TreeProducerNoise_step = cms.Path(process.TreeProducerNoise)
process.endjob_step = cms.EndPath(process.endOfProcess)


process.schedule = cms.Schedule(
                                process.TreeProducerNoise_step, 
                                process.endjob_step
                                )




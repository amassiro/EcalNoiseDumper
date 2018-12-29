Instructions:
    
    ### step1: GENSIM step (se non avete gia' i GENSIM su cui girare)
    
    cmsDriver.py ZEE_13TeV_TuneCUETP8M1_cfi --conditions    \
    auto:phase1_2018_realistic -n 10 --era Run2_2018 --eventcontent \
    FEVTDEBUG -s GEN,SIM --datatier GEN-SIM --beamspot \
    Realistic25ns13TeVEarly2017Collision --geometry DB:Extended  \
    --python ZEE_13TeV_TuneCUETP8M1_2018_GenSimFull.py --fileout \
    file:step1.root --nThreads 8

    cmsRun ZEE_13TeV_TuneCUETP8M1_2018_GenSimFull.py
    
    
Then modify to have neutrino gun
    
    
    process.generator = cms.EDProducer("FlatRandomEGunProducer",
        PGunParameters = cms.PSet(
            PartID = cms.vint32(12),
            MaxEta = cms.double(2.5),
            MaxPhi = cms.double(3.14159265359),
            MinEta = cms.double(-2.5),
            MinE = cms.double(9.99),
            MinPhi = cms.double(-3.14159265359), ## in radians

            MaxE = cms.double(10.01)
        ),
        Verbosity = cms.untracked.int32(0), ## set to 1 (or greater)  for printouts

        psethack = cms.string('single Nu E 10'),
        AddAntiParticle = cms.bool(False),
        firstRun = cms.untracked.uint32(1)
    )
        
Step 2:


     cmsDriver.py step2 --conditions auto:phase1_2018_realistic -n 100 --era \
     Run2_2018 --eventcontent FEVTDEBUGHLT  \
     -s DIGI:pdigi_valid,L1,DIGI2RAW,HLT:@relval2018   \
     --datatier GEN-SIM-DIGI-RAW   \
     --geometry DB:Extended  --python DigiFull_2018.py   \
     --filein file:step1.root --fileout file:step2.root --nThreads 8  \
     --mc
     
     
     --dump_python
     
Apply full readout:

     #
     # Full readout
     #  https://twiki.cern.ch/twiki/bin/view/CMS/EcalSelectiveReadout#How_to_digitize_without_selectiv
     #
     process.GlobalTag.toGet = cms.VPSet(
         cms.PSet(record = cms.string("EcalSRSettingsRcd"),
                  tag = cms.string('EcalSRSettings_fullreadout_v01_mc'),
                  connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS")
     ))
     
     
     cmsRun DigiFull_2018.py
     
     
Reco, Step 3 with keep *

    cmsRun ../reco.py  inputFiles=file:step2.root
    
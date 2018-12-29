Run
====

    /eos/cms/store/group/dpg_ecal/comm_ecal/cmkuo/PhoGunNoPU/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_caseA.root

    cmsRun runDumpMC.py  inputFiles=file:/eos/cms/store/group/dpg_ecal/comm_ecal/cmkuo/PhoGunNoPU/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_caseA.root   outputFile=test.root   maxEvents=10
    cmsRun runDumpMC.py  inputFiles=file:/tmp/amassiro/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_caseA.root   outputFile=test.root   maxEvents=10

    
    
    
    /eos/cms/store/group/dpg_ecal/comm_ecal/cmkuo/NuGun/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_PAT_VALIDATION_DQM_PhoStat_2.root
    
    cmsRun runDumpMC.py  inputFiles=file:/eos/cms/store/group/dpg_ecal/comm_ecal/cmkuo/NuGun/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_PAT_VALIDATION_DQM_PhoStat_2.root   outputFile=test.root   maxEvents=10
    cmsRun runDumpMC.py  inputFiles=file:/eos/cms/store/group/dpg_ecal/comm_ecal/cmkuo/NuGun/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_EI_PAT_VALIDATION_DQM_PhoStat_2.root   outputFile=test.root

    
    r99t test_numEvent10.root
    
    r99t test.root
    
    TTree* tree = (TTree*) _file0->Get("TreeProducerNoise/tree")
    
    tree ->Draw("iphi:ieta>>h(170,-85,85,360,0,360", "energy_EB*(energy_EB>=0)", "colz");
    tree ->Draw("iphi:ieta>>h_num(170,-85,85,360,0,360", "(energy_EB>=0)", "colz");
    
    TH2F *h_noise = (TH2F*)h->Clone("h_noise");
    h_noise->Divide(h_num);
    h_noise->Draw("colz");


    tree ->Draw("iy:(ix+100*(iz>0))>>h(200,0,200,100,0,100", "energy_EE*(energy_EE>=0)", "colz");
    tree ->Draw("iy:(ix+100*(iz>0))>>h_num(200,0,200,100,0,100", "(energy_EE>=0)", "colz");

    
    tree ->Draw("iphi:ieta>>h(170,-85,85,360,0,360", "LaserCorrection_EB*(energy_EB>=0)", "colz");
    tree ->Draw("iphi:ieta>>h_num(170,-85,85,360,0,360", "(energy_EB>=0)", "colz");
    
    tree ->Draw("iy:(ix+100*(iz>0))>>h(200,0,200,100,0,100", "LaserCorrection_EE*(LaserCorrection_EE>=0)", "colz");
    tree ->Draw("iy:(ix+100*(iz>0))>>h_num(200,0,200,100,0,100", "(LaserCorrection_EE>=0)", "colz");

    
    tree ->Draw("iphi:ieta>>h(170,-85,85,360,0,360", "energy_EB/LaserCorrection_EB*(energy_EB>=0)", "colz");
    tree ->Draw("iphi:ieta>>h_num(170,-85,85,360,0,360", "(energy_EB>=0)", "colz");

    tree ->Draw("iy:(ix+100*(iz>0))>>h(200,0,200,100,0,100", "energy_EE/LaserCorrection_EE*(energy_EE>=0)", "colz");
    tree ->Draw("iy:(ix+100*(iz>0))>>h_num(200,0,200,100,0,100", "(energy_EE>=0)", "colz");

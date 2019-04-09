Local run
====

Pedestal run: already used for 'rms' extraction

Run reconstruction up to uncalibrated rechit:

    cmsRun recoLocal.py

Input

    /eos/cms/store/group/dpg_ecal/comm_ecal/fromP5/

    ECAL Pedestal: Run 325427

    cmsRun recoLocal.py  inputFiles=file:/eos/cms/store/group/dpg_ecal/comm_ecal/fromP5/run325427/run325427_ls0009_streamDQM_pid30095.dat   outputFile=reco.root
    
    
Then run the dumper of uncalibrated rechit:

    cmsRun dumpUncalibRechit.py  inputFiles=file:reco.root       outputFile=tree_localRun.root

And now draw:

    TTree* tree = (TTree*) _file0->Get("TreeProducerNoiseUncalib/tree")

    tree ->Draw("iphi:ieta>>h(170,-85,85,360,0,360", "rms_EB*(rms_EB>=0)", "colz");
    tree ->Draw("iphi:ieta>>h_num(170,-85,85,360,0,360", "(rms_EB>=0)", "colz");

    
    tree ->Draw("iphi:ieta>>h(170,-85,85,360,0,360", "amplitude_EB/amplitude_second_EB*(amplitude_second_EB>=-99)", "colz");
    tree ->Draw("iphi:ieta>>h_num(170,-85,85,360,0,360", "(amplitude_second_EB>=-99)", "colz");

    tree ->Draw("iy:(ix+100*(iz>0))>>h(200,0,200,100,0,100", "amplitude_EE/amplitude_second_EE*(amplitude_second_EE>=-99)", "colz");
    tree ->Draw("iy:(ix+100*(iz>0))>>h_num(200,0,200,100,0,100", "(amplitude_second_EE>=-99)", "colz");

       
    TTree* tree = (TTree*) _file0->Get("TreeProducerNoiseUncalib/tree")
    tree ->Draw("amplitude_EB/amplitude_second_EB>>h(200,0,5)", "(amplitude_second_EB>=-99)", "");
    tree ->Draw("amplitude_EE/amplitude_second_EE>>h(200,0,5)", "(amplitude_second_EE>=-99)", "");

    tree ->Draw("amplitude_EB/amplitude_second_EB:amplitude_EB", "(amplitude_second_EB>=-99)", "colz");
    tree ->Draw("amplitude_EE/amplitude_second_EE:amplitude_EE", "(amplitude_second_EE>=-99)", "colz");

    tree ->Draw("amplitude_EB/amplitude_second_EB:amplitude_EB", "(amplitude_second_EB>=-99) && abs(amplitude_EB/amplitude_second_EB)<100 && amplitude_EB<200", "colz");
    tree ->Draw("amplitude_EE/amplitude_second_EE:amplitude_EE", "(amplitude_second_EE>=-99) && abs(amplitude_EE/amplitude_second_EE)<100 && amplitude_EE<200", "colz");

    tree ->Draw("amplitude_EB:amplitude_second_EB", "(amplitude_second_EB>=-10)", "colz");
    tree ->Draw("amplitude_EE:amplitude_second_EE", "(amplitude_second_EE>=-10)", "colz");
    
    tree ->Draw("amplitude_EB:amplitude_second_EB", "(amplitude_second_EB>=-10) && (amplitude_second_EB<400)", "colz");
    tree ->Draw("amplitude_EE:amplitude_second_EE", "(amplitude_second_EE>=-10) && (amplitude_second_EE<400)", "colz");


    
Now chi2 comparison:

    pedestal run vs Zee RawReco
    
    
    Zee:
    /EGamma/CMSSW_10_2_0-ZElectron-102X_dataRun2_PromptLike_v4_gcc7_RelVal_EGamma2018A-v1/RAW-RECO
    /EGamma/CMSSW_10_2_0-ZElectron-102X_dataRun2_PromptLike_v4_RelVal_EGamma2018B-v1/RAW-RECO
    
    
    cmsRun recoRaw.py  inputFiles=/store/relval/CMSSW_10_2_0/EGamma/RAW-RECO/ZElectron-102X_dataRun2_PromptLike_v4_RelVal_EGamma2018B-v1/10000/E8D00776-1D8F-E811-B1C3-0CC47A74524E.root     outputFile=reco_zeeRawReco.root

    cmsRun dumpUncalibRechit.py  inputFiles=file:reco_zeeRawReco.root       outputFile=tree_ZeeRawReco.root

    
    
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"amplitude_EB\",400,0,10\)
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"amplitude_EB\",1000,0,1000,\"amplitude_EB\>-10\"\)
    
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"chi2_EB\",100,0,100,\"chi2_EB\>-10\"\)
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"chi2_EB\",100,0,100,\"chi2_EB\>-10\",\"amplitude_EB\>-10\",\"amplitude_EB\>100\"\)
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"chi2_EB\",100,0,100,\"chi2_EB\>-10\",\"amplitude_EB\>100\",\"amplitude_EB\>100\"\)
    
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"chi2_EB\",100,0,100,\"chi2_EB\>-10\",\"amplitude_EB\>-10\",\"amplitude_EB\>10\"\)
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"chi2_EB\",100,0,100,\"chi2_EB\>-10\",\"amplitude_EB\>0.5\",\"amplitude_EB\>0.5\"\)
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"chi2_EB/amplitude_EB\",100,0,10,\"chi2_EB\>-10\",\"amplitude_EB\>0.5\",\"amplitude_EB\>0.5\"\)
    
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"chi2_EE\",100,0,100,\"chi2_EE\>-10\",\"amplitude_EE\>0.5\",\"amplitude_EE\>0.5\"\)
    
    
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"amplitudeError_EB\",100,0,10,\"chi2_EB\>-10\",\"amplitude_EB\>-10\",\"amplitude_EB\>-10\"\)
    
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"amplitudeError_EB\",100,0,10,\"chi2_EB\>-10\",\"amplitude_EB\>1\",\"amplitude_EB\>1\"\)
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"amplitudeError_EE\",100,0,10,\"chi2_EE\>-10\",\"amplitude_EE\>1\",\"amplitude_EE\>1\"\)
    
    
    
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"amplitude_EB/rms_EB\",100,0,10,\"amplitude_EB\>-1\"\)
    r99t tree_localRun.root    tree_ZeeRawReco.root    compare.cxx\(\"amplitude_second_EB/rms_EB\",100,0,10,\"amplitude_EB\>-1\"\)
    
    
    r99t tree_localRun.root    draw.cxx\(\"amplitude_EB/rms_EB\",100,0,10,\"amplitude_EB\>-1\"\)
    r99t tree_localRun.root    draw.cxx\(\"amplitude_second_EB/rms_EB\",100,0,10,\"amplitude_EB\>-1\"\)
    r99t tree_localRun.root    draw.cxx\(\"amplitude_second_EB/rms_EB\",200,-10,10,\"amplitude_EB\>-1\"\)
    r99t tree_localRun.root    draw.cxx\(\"amplitude_second_EE/rms_EE\",200,-10,10,\"amplitude_EE\>-1\"\)
    
    
    r99t tree_localRun.root    draw.cxx\(\"rms_EB\",100,0,10,\"amplitude_EB\>-1\"\)
    
    
    r99t tree_localRun.root    draw.cxx\(\"size_EB\",1000,0,100000\)
    r99t tree_localRun.root    draw.cxx\(\"size_EE\",1000,0,100000\)
    
    

    r99t tree_localRun.root    draw.cxx\(\"amplitude_EB\",100,0,10,\"amplitude_EB\>-10\"\)
    r99t tree_localRun.root    draw.cxx\(\"amplitude_second_EB\",200,0-10,10,\"amplitude_second_EB\>-10\"\)

    
    
    r99t tree_localRun.root    draw.cxx\(\"chi2_EB/amplitude_EB\",100,0,10,\"amplitude_EB\>-10\"\)
    
    
    
    
    TTree* tree_0 = (TTree*) _file0->Get("TreeProducerNoiseUncalib/tree");
    tree_0->Draw("chi2_EB:amplitudeError_EB", "amplitude_EB<100 && amplitude_EB>-1 && chi2_EB<10 && amplitudeError_EB<5", "colz")

    
    
    
    
    
    
    
    
    
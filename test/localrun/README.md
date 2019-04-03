Local run
====

Pedestal run: already used for 'rms' extraction

Run reconstruction up to uncalibrated rechit:

    cmsRun recoLocal.py

Input

    /eos/cms/store/group/dpg_ecal/comm_ecal/fromP5/
    
    cmsRun recoLocal.py  inputFiles=file:/eos/cms/store/group/dpg_ecal/comm_ecal/fromP5/run327271/run327271_ls0009_streamDQM_pid86622.dat   outputFile=reco.root
    
    
Then run the dumper of uncalibrated rechit:

    cmsRun dumpUncalibRechit.py  inputFiles=file:reco.root       outputFile=tree.root

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


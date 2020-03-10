{
  
  
  TTree* tree = (TTree*) _file0->Get("TreeProducerNoise/tree");
 
  
  TCanvas* cc_EB = new TCanvas ("cc_EB", "", 800, 600);
  tree ->Draw("rms_EB:runNumber >> histo_EB(30, 315000, 325000, 200, 0, 40 )", "(energy_EB>=0) && (energy_EB/LaserCorrection_EB<10) && rms_EB>=0 && rms_EB<=40");
  histo_EB->Draw("colz");
  histo_EB->GetXaxis()->SetTitle("Run number");
  histo_EB->GetYaxis()->SetTitle("RMS adc");
  histo_EB->Draw("colz");
  TH1D *projh2X_EB = histo_EB->ProfileX();
  
  TCanvas* ccnew_EB = new TCanvas ("ccnew_EB", "", 800, 600);
  projh2X_EB->Draw();
  
 
  
  
  TCanvas* cc_EE = new TCanvas ("cc_EE", "", 800, 600);
  tree ->Draw("rms_EE:runNumber >> histo_EE(30, 315000, 325000, 200, 0, 40 )", "(energy_EE>=0) && (energy_EB/LaserCorrection_EB<10) && rms_EE>=0 && rms_EE<=40");
  histo_EE->Draw("colz");
  histo_EE->GetXaxis()->SetTitle("Run number");
  histo_EE->GetYaxis()->SetTitle("RMS adc");
  histo_EE->Draw("colz");
  TH1D *projh2X_EE = histo_EE->ProfileX();
  
  TCanvas* ccnew_EE = new TCanvas ("ccnew_EE", "", 800, 600);
  projh2X_EE->Draw();
  
  
  
}

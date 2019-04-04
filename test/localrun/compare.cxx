

void compare (std::string name, int numbin, float min, float max, std::string cut = "1", std::string cut_0 = "1", std::string cut_1 = "1") {
  
  TTree* tree_0 = (TTree*) _file0->Get("TreeProducerNoiseUncalib/tree");
  TTree* tree_1 = (TTree*) _file1->Get("TreeProducerNoiseUncalib/tree");
 
  float integral = 1.;
  TString plot;
  
  cut_0 = cut_0 + " && " + cut;
  cut_1 = cut_1 + " && " + cut;
  
  TCanvas* cc_histo = new TCanvas ("cc_histo", "", 800, 600);
  
  TH1F* histo_0 = new TH1F("histo_0", "noise",   numbin, min, max);
  TH1F* histo_1 = new TH1F("histo_1", "pulses",  numbin, min, max);
  
  
  plot = Form ("%s >> histo_0", name.c_str());
  tree_0->Draw(plot.Data(), cut_0.c_str(), "goff");
  
  histo_0->SetLineColor(kBlue);
  histo_0->SetLineWidth(2);
  integral = histo_0->Integral();  histo_0->Scale (1. / integral );
  
  histo_0->Draw();
  histo_0->GetXaxis()->SetTitle(name.c_str());
  
  
  plot = Form ("%s >> histo_1", name.c_str());
  tree_1->Draw(plot.Data(), cut_1.c_str(), "goff");
  
  histo_1->SetLineColor(kRed);
  histo_1->SetLineWidth(2);
  integral = histo_1->Integral();  histo_1->Scale (1. / integral );
  
  histo_1->Draw("same");
  
  
  TLegend* leg = new TLegend ( 0.70, 0.70, 0.90, 0.90 );
  leg->AddEntry("histo_0","noise", "l");
  leg->AddEntry("histo_1","pulses","l");
  leg->Draw();
  
  cc_histo->SetLogy();
  
 
  
  
  
  
}






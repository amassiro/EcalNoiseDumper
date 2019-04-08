

void draw (std::string name, int numbin, float min, float max, std::string cut = "1") {
  
  TTree* tree_0 = (TTree*) _file0->Get("TreeProducerNoiseUncalib/tree");
 
  float integral = 1.;
  TString plot;
  
  
  std::string cut_0 = cut;
  
  TCanvas* cc_histo = new TCanvas ("cc_histo", "", 800, 600);
  
  TH1F* histo_0 = new TH1F("histo_0", "noise",   numbin, min, max);
  
  
  plot = Form ("%s >> histo_0", name.c_str());
  tree_0->Draw(plot.Data(), cut_0.c_str(), "goff");
  
  integral = histo_0->Integral();  histo_0->Scale (1. / integral );
  
  histo_0->SetFillStyle(3004);
  histo_0->SetFillColor(kBlue);
  histo_0->SetLineColor(kBlue);
  histo_0->SetLineWidth(2);
  histo_0->Draw("histo");
  histo_0->GetXaxis()->SetTitle(name.c_str());
  
  
  TLegend* leg = new TLegend ( 0.50, 0.70, 0.70, 0.90 );
  leg->AddEntry("histo_0","noise", "l");
  leg->Draw();
  
  cc_histo->SetLogy();
  
 
  
  
  
  
}






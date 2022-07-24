#define MyClass_cxx
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void MyClass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MyClass.C
//      root> MyClass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
 
TH1D *hlambdaplus = new TH1D("hlambdaplus","pT_hlambdaplus; pT ; dN/dpT",20,0.5,10.5);
TH1D *hlambdaMinus = new TH1D("hlambdaMinus","pT_lambdaMinus; pT ; dN/dpT",20,0.5,10.5);

TH1D *hzaiplus = new TH1D("hzaiplus","pT_zaiplus; pT ; dN/dpT",10,0.5,5.5);/////////
TH1D *hzaiMinus = new TH1D("hzaiMinus","pT_zaiMinus; pT ; dN/dpT",10,0.5,5.5);///////////////

TH1D *fHistEtaLamb = new TH1D("fHistEtaLamb", "#eta; #eta ; Events", 8, -0.8, 0.8);
TH1D *fHistEtaALamb = new TH1D("fHistEtaALamb", "#eta; #eta ; Events",8, -0.8, 0.8);
TH1D *fHistEtaZai = new TH1D("fHistEtaZai", "#eta; #eta ; Events", 8, -0.8, 0.8);/////////////////
TH1D *fHistEtaAZai = new TH1D("fHistEtaAZai", "#eta; #eta ; Events", 8, -0.8, 0.8);////////////////////


      	if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
       if (Cut(ientry) < 0) continue;
       for(int j=0;j<nPart;j++) {
           double ID = pdgid[j];
          // cout << "ID = " << ID << endl;
           double pt = TMath::Sqrt(px[j]*px[j]+py[j]*py[j]);
          // cout << "pt = " << pt<< endl;
            //fHistAllTracksPt->Fill(pt);
           double pt2 = (px[j]+py[j]);

           double rapidity = 0.5*log((E[j]+pz[j])/(E[j]-pz[j]));
               if(pt == 0) continue;

           //fHistEtaBFcut->Fill(rapidity);


           if(TMath::Abs(rapidity) >= 0.8)continue;

	   if(ID == 3122)    //continue;//Lambda
           { if(0.5<pt<10.5){
                  hlambdaplus->Fill(pt);
                  fHistEtaLamb->Fill(rapidity);
                            }

             //  nch_top[0]++; sumpt_top[0]+= pt;
              // hmeanproton->Fill(sumpt_top[0]/nch_top[0]);
           }
           else if(ID == -3122)      //ALambda
                     { if(0.5<pt<10.5){

                            hlambdaMinus->Fill(pt);
                            fHistEtaALamb->Fill(rapidity);
                                      }


                 //        nch_top[1]++; sumpt_top[1]+= pt;
                     }
            if(ID == -3312)              //ZaiPlus
                  {
                         hzaiplus->Fill(pt);
                         if(0.5<pt<5.5){
                                  fHistEtaAZai->Fill(rapidity);}
                //      nch_top[9]++; sumpt_top[9]+= pt;
                  }
                  else if(ID == 3312)     //ZaiMinus
                            {
                                   hzaiMinus->Fill(pt);
                                   if(0.5<pt<5.5){

					    fHistEtaZai->Fill(rapidity);}
                      //          nch_top[10]++; sumpt_top[10]+= pt;
                            }

   }
}

TH1::AddDirectory(kFALSE);
TFile *localcorection = new TFile("Model_pt_dpmjet10.root","RECREATE"); // create root file
localcorection->Write();
    localcorection->cd();
    hlambdaplus->Write("");
    hlambdaMinus->Write("");
    hzaiplus->Write("");
    hzaiMinus->Write("");


    fHistEtaAZai->Write("");///////////////////////
    fHistEtaZai->Write("");
    fHistEtaLamb->Write("");
    fHistEtaALamb->Write("");
localcorection->Close();
}


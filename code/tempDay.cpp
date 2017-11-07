#include <iostream>
#include "tempTrender.h"
#include <sstream> // maybe include in tempTrender.h instead
// ROOT library objects
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TGraph.h>
#include <TLegend.h>
// Left to do: probability to observe a certain temperature

void tempTrender::tempOnDay(int monthToCalculate, int dayToCalculate){
    cout << endl;
    cout << "Calculating the temperature for a certain date in Lund" << endl;
    
    vector <vector <string> > dataOnDay;
    readData("smhi-opendata_Lund.csv", dataOnDay);
    
    
    vector <float> tempCalculatedDay; // Vector to store temperatures for the chosen day
    // Create histogram
    TH1F* histogram = new TH1F("histogram", "Temperature;Temperature [#circC];Entries", 200, -20, 40);
    
    
    // Find the right day, month and time in the data
    for (int i = 1 ; i < (int)dataOnDay.size(); i++ ) {
        if ( (stoi(dataOnDay.at(i).at(1)) == monthToCalculate) && (stoi(dataOnDay.at(i).at(2)) == dayToCalculate) && (dataOnDay.at(i).at(3) == "12") ) {
            tempCalculatedDay.push_back(strtof((dataOnDay.at(i).at(6)).c_str(),0)); // Vector with temperatures for chosen day
            
        }
    }
    // Fill the histogram
    for(Int_t i = 0; i < (int)tempCalculatedDay.size(); i++) {
        histogram->Fill(tempCalculatedDay[i]);
    }
    
    //gStyle->SetOptStat(1111);
    
    histogram->SetFillColor(kRed + 1);
    double mean = histogram->GetMean(); //The mean of the distribution
    double stdev = histogram->GetRMS(); //The standard deviation
    TCanvas* c1 = new TCanvas("c1", "Date");
    histogram->Draw();

    histogram->Fit("gaus");
    gStyle->SetOptStat(0);
    
    TLegend* legen = new TLegend(0.7,0.8,0.9,0.9);
    legen->SetFillStyle(0); //Hollow fill (transparent)
    legen->SetBorderSize(0); //Get rid of the border
    //leg->SetHeader("The Legend Title");
    legen->AddEntry(histogram,"Temperature on..","f");
    legen->Draw();
    
    // Save the canvas as a picture
    c1->SaveAs("tempOnDay.png");
    
}





/*
 Int_t n = 200;
 Double_t x[n], y[n];
 for (Int_t i=0; i<n; i++) {
 x[i] = i*60/200;
 y[i] = 1/(mean*TMath::Sqrt(2*stdev))*TMath::Exp(-TMath::Power((x[i]-mean),2)/(2*TMath::Power(stdev,2)));
 }
 */
/*
 TF1 *gr1 = new TF1 ("gr1","1/(mean*TMath::Sqrt(2*stdev))*TMath::Exp(-TMath::Power(((x)-mean),2)/(2*TMath::Power(stdev,2)))",-20, 40);
 gr1->SetLineColor(kGreen);
 gr1->Draw();
 */


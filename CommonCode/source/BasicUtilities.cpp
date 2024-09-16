#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "TauHelperFunctions3.h"

#include "BasicUtilities.h"

double GetRho(std::vector<double> *EtaMax, std::vector<double> *Rho, double Eta, bool SuppressMessage)
{
   if(EtaMax == NULL || Rho == NULL || EtaMax->size() != Rho->size()
      || EtaMax->size() == 0)
   {
      if(SuppressMessage == false)
         std::cerr << "[GetRho] Input is invalid!  Return zero..." << std::endl;
      return 0;
   }

   for(int i = 0; i < (int)EtaMax->size(); i++)
   {
      if(Eta >= (*EtaMax)[i])
         continue;
      else
         return (*Rho)[i];
   }

   return (*Rho)[Rho->size()-1];
}

double GetCentrality(int Bin)
{
   return Bin * 0.005 + 0.00001;
}

bool IsDataFromTag(std::string Tag)
{
   if(Tag.find("Data") != std::string::npos)
      return true;
   if(Tag.find("DATA") != std::string::npos)
      return true;
   if(Tag.find("data") != std::string::npos)
      return true;
   return false;
}

bool IsPPFromTag(std::string Tag)
{
   if(Tag.find("PP") != std::string::npos)
      return true;
   if(Tag.find("pp") != std::string::npos)
      return true;
   return false;
}

bool IsPPHiRecoFromTag(std::string Tag)
{
   bool IsPP = IsPPFromTag(Tag);

   if(Tag.find("HiReco") != std::string::npos)
      return true && IsPP;
   if(Tag.find("HIReco") != std::string::npos)
      return true && IsPP;
   if(Tag.find("hireco") != std::string::npos)
      return true && IsPP;
   return false;
}

bool IsPAFromTag(std::string Tag)
{
   if(Tag.find("PA") != std::string::npos)
      return true;
   if(Tag.find("pa") != std::string::npos)
      return true;
   if(Tag.find("pA") != std::string::npos)
      return true;
   return false;
}

template<class T, class U>
   std::vector<int> DRMatching(int BaseN, T BaseEta, T BasePhi,
      int TargetN, U TargetEta, U TargetPhi)
{
   std::vector<int> Result(BaseN);

   for(int i = 0; i < BaseN; i++)
   {
      int Best = -1;
      double BestDR2 = -1;

      for(int j = 0; j < TargetN; j++)
      {
         double DEta = BaseEta[i] - TargetEta[j];
         double DPhi = BasePhi[i] - TargetPhi[i];
         if(DPhi < -PI)   DPhi = DPhi + 2 * PI;
         if(DPhi > +PI)   DPhi = DPhi - 2 * PI;
         double DR2 = DEta * DEta + DPhi * DPhi;

         if(DR2 < BestDR2 || BestDR2 < 0)
         {
            Best = j;
            BestDR2 = DR2;
         }
      }

      Result[i] = Best;
   }

   return Result;
}

template std::vector<int> DRMatching<float *, float *>(int, float *, float *,
   int, float *, float *);
template std::vector<int> DRMatching<std::vector<float>, std::vector<float> >
   (int, std::vector<float>, std::vector<float>,
   int, std::vector<float>, std::vector<float>);
template std::vector<int> DRMatching<float *, std::vector<float> >
   (int, float *, float *, int, std::vector<float>, std::vector<float>);
template std::vector<int> DRMatching<std::vector<float>, float *>
   (int, std::vector<float>, std::vector<float>, int, float *, float *);
template std::vector<int> DRMatching<std::vector<double>, float *>
   (int, std::vector<double>, std::vector<double>, int, float *, float *);

int GetIndex(double X, double *Begin, double *End)
{
   if(Begin == NULL)
      return -1;
   if(End == NULL)
      return -1;

   int Index = 0;
   double *Current = Begin;
   while(Current != End && X > *Current)
   {
      Index = Index + 1;
      Current = Current + 1;
   }

   return Index;
}

double GetDR2(double Eta1, double Phi1, double Eta2, double Phi2)
{
   double DEta = Eta1 - Eta2;
   double DPhi = Phi1 - Phi2;
   while(DPhi < -PI)
      DPhi = DPhi + 2 * PI;
   while(DPhi > +PI)
      DPhi = DPhi - 2 * PI;

   return DEta * DEta + DPhi * DPhi;
}

double GetDR(double Eta1, double Phi1, double Eta2, double Phi2)
{
   return std::sqrt(GetDR2(Eta1, Phi1, Eta2, Phi2));
}

XY::XY() : X(0), Y(0)
{
}

XY::XY(double x, double y, bool DoPrimary) : X(x), Y(y)
{
   if(DoPrimary)
      PrimaryY();
}

XY::XY(FourVector J, bool DoPrimary) : X(J.GetEta()), Y(J.GetPhi())
{
   if(DoPrimary)
      PrimaryY();
}
   
XY::XY(Matrix22 M, XY &C, FourVector J)
{
   *this = XY(J) - C;
   PrimaryY();
   *this = M * *this;
}

XY XY::operator +(XY other)
{
   return XY(X + other.X, Y + other.Y);
}

XY XY::operator -(XY other)
{
   return XY(X - other.X, Y - other.Y);
}

XY XY::operator -()
{
   return XY(-X, -Y);
}
   
XY XY::operator *(double c)
{
   return XY(X * c, Y * c);
}

XY XY::operator /(double c)
{
   return XY(X / c, Y / c);
}
   
double XY::Norm()
{
   return std::sqrt(X * X + Y * Y);
}

double XY::Norm2()
{
   return X * X + Y * Y;
}

void XY::SetAsAverage(FourVector J1, FourVector J2)
{
   XY A1(J1);
   XY A2(J2);

   *this = (A1 + A2) / 2;
   PrimaryY();
}

void XY::PrimaryY()
{
   while(Y < -PI)   Y = Y + 2 * PI;
   while(Y > +PI)   Y = Y - 2 * PI;
}

XY::~XY()
{
}

Matrix22::Matrix22()
{
   T[0][0] = 0;
   T[0][1] = 0;
   T[1][0] = 0;
   T[1][1] = 0;
}

Matrix22::Matrix22(double T11, double T12, double T21, double T22)
{
   T[0][0] = T11;
   T[0][1] = T12;
   T[1][0] = T21;
   T[1][1] = T22;
}

Matrix22::Matrix22(FourVector J1, FourVector J2)
{
   Initialize(J1, J2);
}

Matrix22 &Matrix22::operator =(Matrix22 &other)
{
   T[0][0] = other.T[0][0];
   T[0][1] = other.T[0][1];
   T[1][0] = other.T[1][0];
   T[1][1] = other.T[1][1];

   return *this;
}

double *Matrix22::operator [](int Index)
{
   if(Index == 0)
      return T[0];
   return T[1];
}
   
XY Matrix22::operator *(XY A)
{
   XY Result;

   Result.X = T[0][0] * A.X + T[0][1] * A.Y;
   Result.Y = T[1][0] * A.X + T[1][1] * A.Y;

   return Result;
}

Matrix22 Matrix22::Inverse()
{
   double Det = T[0][0] * T[1][1] - T[0][1] * T[1][0];

   Matrix22 Result;

   Result.T[0][0] = T[1][1] / Det;
   Result.T[0][1] = -T[1][0] / Det;
   Result.T[1][0] = -T[0][1] / Det;
   Result.T[1][1] = T[0][0] / Det;

   return Result;
}

void Matrix22::Initialize(FourVector J1, FourVector J2)
{
   XY L1(J1);
   XY L2(J2);

   XY D = L1 - L2;
   D.PrimaryY();

   T[0][0] = D.X / 2;
   T[0][1] = D.Y / 2;
   T[1][0] = -D.Y / 2;
   T[1][1] = D.X / 2;

   Matrix22 M = Inverse();
   *this = M;
}

Matrix22::~Matrix22()
{
}



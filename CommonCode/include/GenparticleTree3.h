#ifndef GenparticleTree_6563_ASNDVRHISGHFHSF
#define GenparticleTree_6563_ASNDVRHISGHFHSF

#include <vector>
#include <cmath>
#include <deque>
#include <algorithm>
#include <ostream>
#include <istream>
using namespace std;

#include "TauHelperFunctions3.h"

#define DEFAULT_VALUE -999999
#define PI 3.14159265358979323846264338327950288479716939937510

union SaveHelper;
class GenParticle;
class GenParticleTree;

bool HasTau(GenParticleTree &Tree);
vector<int> FindAllIndices(GenParticleTree &Tree, int PDGID, int StatusCode = 0);
vector<int> TraceChildren(GenParticleTree &Tree, int SourceIndex);
vector<int> KeepStableParticle(GenParticleTree &Tree, vector<int> &Indices);
vector<int> ListStableParticle(GenParticleTree &Tree);

union SaveHelper
{
   double Value;
   long long IntValue;
   char CharValue[20];
};

class GenParticle
{
public:
   FourVector P;
   FourVector V;
   int PDGID;
   int StatusCode;
   vector<int> Mothers;
   vector<int> Daughters;

public:
   GenParticle();
   GenParticle(double p0, double p1, double p2, double p3, int pdgid, int status, vector<int> mothers = vector<int>(), vector<int> daughters = vector<int>());
   void AddMother(int index);
   void AddDaughter(int index);
   
   void SaveToStream(ostream &out, bool ASCII = false);
   void LoadFromStream(istream &in, bool ASCII = false);

public:
   struct SortByPhi : public binary_function<GenParticle, GenParticle, bool>
   {
      bool operator()(const GenParticle &First, const GenParticle &Second) const
      {
         double Phi1 = First.P.InnerGetPhi();
         double Phi2 = Second.P.InnerGetPhi();

         if(Phi1 < Phi2)   return true;
         if(Phi1 > Phi2)   return false;

         return false;
      }
   };
   struct SortByDR : public binary_function<GenParticle, GenParticle, bool>
   {
      double ReferenceEta;
      double ReferencePhi;
      SortByDR(double Eta, double Phi)
      {
         ReferenceEta = Eta;
         ReferencePhi = Phi;
      }
      bool operator()(const GenParticle &First, const GenParticle &Second) const
      {
         double Phi1 = acos(First.P[1] / sqrt(First.P[1] * First.P[1] + First.P[2] * First.P[2]));
         if(First.P[2] < 0)
            Phi1 = -Phi1;
         double P1 = sqrt(First.P[1] * First.P[1] + First.P[2] * First.P[2] + First.P[3] * First.P[3]);
         double Eta1 = 0.5 * log((P1 - First.P[3]) / (P1 + First.P[3]));

         double DPhi1 = Phi1 - ReferencePhi;
         if(DPhi1 > PI)
            DPhi1 = 2 * PI - DPhi1;
         if(DPhi1 < -PI)
            DPhi1 = DPhi1 + 2 * PI;
         double DEta1 = Eta1 - ReferenceEta;
         
         double Phi2 = acos(Second.P[1] / sqrt(Second.P[1] * Second.P[1] + Second.P[2] * Second.P[2]));
         if(Second.P[2] < 0)
            Phi2 = -Phi2;
         double P2 = sqrt(Second.P[1] * Second.P[1] + Second.P[2] * Second.P[2] + Second.P[3] * Second.P[3]);
         double Eta2 = 0.5 * log((P2 - Second.P[3]) / (P2 + Second.P[3]));

         double DPhi2 = Phi2 - ReferencePhi;
         if(DPhi2 > PI)
            DPhi2 = 2 * PI - DPhi2;
         if(DPhi2 < -PI)
            DPhi2 = DPhi2 + 2 * PI;
         double DEta2 = Eta2 - ReferenceEta;

         if(DPhi1 * DPhi1 + DEta1 * DEta1 < DPhi2 * DPhi2 + DEta2 * DEta2)
            return true;
         if(DPhi1 * DPhi1 + DEta1 * DEta1 > DPhi2 * DPhi2 + DEta2 * DEta2)
            return false;

         return false;
      }
   };
};

GenParticle::GenParticle()
{
   P[0] = 0;   P[1] = 0;   P[2] = 0;   P[3] = 0;
   V[0] = 0;   V[1] = 0;   V[2] = 0;   V[3] = 0;
   PDGID = 0;
   Mothers.clear();
   Daughters.clear();
}

GenParticle::GenParticle(double p0, double p1, double p2, double p3, int pdgid, int status, vector<int> mothers, vector<int> daughters)
{
   P[0] = p0;   P[1] = p1;   P[2] = p2;   P[3] = p3;
   V[0] = 0;   V[1] = 0;   V[2] = 0;   V[3] = 0;
   
   StatusCode = status;
   
   PDGID = pdgid;
   Mothers = mothers;
   Daughters = daughters;
}

void GenParticle::AddMother(int index)
{
   Mothers.push_back(index);
}

void GenParticle::AddDaughter(int index)
{
   Daughters.push_back(index);
}

void GenParticle::SaveToStream(ostream &out, bool ASCII)
{
   if(ASCII == true)
   {
      out << " " << P[0] << " " << P[1] << " " << P[2] << " " << P[3];
      out << " " << V[0] << " " << V[1] << " " << V[2] << " " << V[3];
   
      out << " " << PDGID;
      out << " " << StatusCode;
   
      out << " " << Mothers.size();
      for(int i = 0; i < (int)Mothers.size(); i++)
         out << " " << Mothers[i];

      out << " " << Daughters.size();
      for(int i = 0; i < (int)Daughters.size(); i++)
         out << " " << Daughters[i];
      
      out << endl;
   }
   else
   {
      SaveHelper Helper;
      Helper.Value = P[0];  out.write(Helper.CharValue, 16);
      Helper.Value = P[1];  out.write(Helper.CharValue, 16);
      Helper.Value = P[2];  out.write(Helper.CharValue, 16);
      Helper.Value = P[3];  out.write(Helper.CharValue, 16);
      
      Helper.Value = V[0];  out.write(Helper.CharValue, 16);
      Helper.Value = V[1];  out.write(Helper.CharValue, 16);
      Helper.Value = V[2];  out.write(Helper.CharValue, 16);
      Helper.Value = V[3];  out.write(Helper.CharValue, 16);

      Helper.IntValue = PDGID;   out.write(Helper.CharValue, 16);
      Helper.IntValue = StatusCode;   out.write(Helper.CharValue, 16);
      
      Helper.IntValue = Mothers.size();   out.write(Helper.CharValue, 16);
      for(int i = 0; i < (int)Mothers.size(); i++)
      {
         Helper.IntValue = Mothers[i];
         out.write(Helper.CharValue, 16);
      }
      
      Helper.IntValue = Daughters.size();   out.write(Helper.CharValue, 16);
      for(int i = 0; i < (int)Daughters.size(); i++)
      {
         Helper.IntValue = Daughters[i];
         out.write(Helper.CharValue, 16);
      }
   }
}

void GenParticle::LoadFromStream(istream &in, bool ASCII)
{
   if(ASCII == true)
   {
      in >> P[0] >> P[1] >> P[2] >> P[3];
      in >> V[0] >> V[1] >> V[2] >> V[3];
   
      in >> PDGID;
      in >> StatusCode;
   
      int Size = 0;
   
      in >> Size;
      Mothers.resize(Size);
      for(int i = 0; i < Size; i++)
         in >> Mothers[i];

      in >> Size;
      Daughters.resize(Size);
      for(int i = 0; i < Size; i++)
         in >> Daughters[i];
   }
   else
   {
      SaveHelper Helper;
      in.read(Helper.CharValue, 16);   P[0] = Helper.Value;
      in.read(Helper.CharValue, 16);   P[1] = Helper.Value;
      in.read(Helper.CharValue, 16);   P[2] = Helper.Value;
      in.read(Helper.CharValue, 16);   P[3] = Helper.Value;
      
      in.read(Helper.CharValue, 16);   V[0] = Helper.Value;
      in.read(Helper.CharValue, 16);   V[1] = Helper.Value;
      in.read(Helper.CharValue, 16);   V[2] = Helper.Value;
      in.read(Helper.CharValue, 16);   V[3] = Helper.Value;

      in.read(Helper.CharValue, 16);   PDGID = Helper.IntValue;
      in.read(Helper.CharValue, 16);   StatusCode = Helper.IntValue;

      int Size = 0;
      in.read(Helper.CharValue, 16);   Size = Helper.IntValue;
      Mothers.resize(Size);
      for(int i = 0; i < Size; i++)
      {
         in.read(Helper.CharValue, 16);
         Mothers[i] = Helper.IntValue;
      }
      
      Size = 0;
      in.read(Helper.CharValue, 16);   Size = Helper.IntValue;
      Daughters.resize(Size);
      for(int i = 0; i < Size; i++)
      {
         in.read(Helper.CharValue, 16);
         Daughters[i] = Helper.IntValue;
      }
   }
}

class GenParticleTree
{
private:
   vector<GenParticle> Particles;
   vector<int> Rank;
   vector<int> TreeIndex;
   int NumberOfTrees;
   int RunNumber;
   int EventNumber;
   double Weight;
   vector<int> IntegerProperties;
   vector<double> DoubleProperties;
public:
   GenParticleTree();
   GenParticleTree(vector<GenParticle> &particles, int run, int event, bool IgnoreInfrastructure = false);
   ~GenParticleTree();
   void Initialize(vector<GenParticle> &particles, bool IgnoreInfrastructure = false);
   void Initialize();
   GenParticle &operator [](int index);
   int GetRank(int index);
   int GetTreeIndex(int index);
   int ParticleCount();
   int TreeCount();
   int TreeMultiplicityCount(int index);
   void Dump(ostream &out);
   int RecommendTree();
   GenParticleTree operator +(const GenParticleTree &other) const;
public:
   int GetRunNumber() { return RunNumber; }
   int GetEventNumber() { return EventNumber; }
   double GetWeight() { return Weight; }
   void SetRunNumber(int run) { RunNumber = run; }
   void SetEventNumber(int event) { EventNumber = event; }
   void SetWeight(double weight) { Weight = weight; }
public:
   int GetIntegerPropertiesCount() { return IntegerProperties.size(); }
   int GetIntegerProperties(int index) { return index < (int)IntegerProperties.size() ? IntegerProperties[index] : -1; }
   int GetDoublePropertiesCount() { return DoubleProperties.size(); }
   double GetDoubleProperties(int index) { return index < (int)DoubleProperties.size() ? DoubleProperties[index] : -1; }
   void SetIntegerProperties(int index, int value) { if(index < (int)IntegerProperties.size()) IntegerProperties[index] = value; }
   void AppendIntegerProperties(int value) { IntegerProperties.push_back(value); }
   void RemoveIntegerProperties(int index) { if(index < (int)IntegerProperties.size()) IntegerProperties.erase(IntegerProperties.begin() + index); }
   void SetDoubleProperties(int index, double value) { if(index < (int)DoubleProperties.size()) DoubleProperties[index] = value; }
   void AppendDoubleProperties(double value) { DoubleProperties.push_back(value); }
   void RemoveDoubleProperties(int index) { if(index < (int)DoubleProperties.size()) DoubleProperties.erase(DoubleProperties.begin() + index); }
public:
   void SaveToStream(ostream &out, bool ASCII = false);
   void LoadFromStream(istream &in, bool ASCII = false);
private:
   void RemoveDuplicates();
   void RepairReciprocalLinking();
   void RebuildTreeIndex();
   void RebuildRank();
};

GenParticleTree::GenParticleTree()
{
   Particles.clear();
   Rank.clear();
   TreeIndex.clear();
}

GenParticleTree::GenParticleTree(vector<GenParticle> &particles, int run, int event, bool IgnoreInfrastructure)
{
   Initialize(particles, IgnoreInfrastructure);
   
   RunNumber = run;
   EventNumber = event;
}

GenParticleTree::~GenParticleTree()
{
}

void GenParticleTree::Initialize(vector<GenParticle> &particles, bool IgnoreInfrastructure)
{
   Particles = particles;

   if(IgnoreInfrastructure == false)
      Initialize();
}
   
void GenParticleTree::Initialize()
{
   RemoveDuplicates();
   RepairReciprocalLinking();
   RebuildTreeIndex();
   RebuildRank();
}

GenParticle &GenParticleTree::operator [](int index)
{
   if(Particles.size() == 0)
   {
      GenParticle newparticle;
      Particles.push_back(newparticle);
      return Particles[0];
   }

   if(index >= (int)Particles.size() || index < 0)
      index = 0;
   
   return Particles[index];
}

int GenParticleTree::ParticleCount()
{
   return Particles.size();
}

int GenParticleTree::TreeCount()
{
   return NumberOfTrees;
}

int GenParticleTree::TreeMultiplicityCount(int index)
{
   if(TreeIndex.size() == 0)
      return -1;
   
   int Count = 0;
   
   for(int i = 0; i < (int)TreeIndex.size(); i++)
      if(TreeIndex[i] == index)
         Count = Count + 1;
   
   return Count;
}

int GenParticleTree::GetRank(int index)
{
   if(index >= (int)Particles.size() || index < 0)
      return -99999;
   
   return Rank[index];
}

int GenParticleTree::GetTreeIndex(int index)
{
   if(index >= (int)Particles.size() || index < 0)
      return DEFAULT_VALUE;
   
   return TreeIndex[index];
}

void GenParticleTree::Dump(ostream &out)
{
   out << "Particle count: " << Particles.size() << endl;
   out << "Index: PDGID TreeIndex Rank (P[4]) (V[4])" << endl;
   
   for(int i = 0; i < (int)Particles.size(); i++)
      out << "#" << i << ": " << Particles[i].PDGID << " "
         << TreeIndex[i] << " " << Rank[i] << " "
         << "(" << Particles[i].P[0] << ", "
         << Particles[i].P[1] << ", "
         << Particles[i].P[2] << ", "
         << Particles[i].P[3] << ")  "
         << "(" << Particles[i].V[0] << ", "
         << Particles[i].V[1] << ", "
         << Particles[i].V[2] << ", "
         << Particles[i].V[3] << ")" << endl;
}

int GenParticleTree::RecommendTree()
{
   vector<int> ParticleCounts(NumberOfTrees);
   
   for(int i = 0; i < (int)Particles.size(); i++)
      ParticleCounts[TreeIndex[i]] = ParticleCounts[TreeIndex[i]] + 1;
   
   int MostPopulatedTree = 0;
   for(int i = 1; i < NumberOfTrees; i++)
      if(ParticleCounts[i] > ParticleCounts[MostPopulatedTree])
         MostPopulatedTree = i;
   
   return MostPopulatedTree;
}

GenParticleTree GenParticleTree::operator +(const GenParticleTree &other) const
{
   vector<GenParticle> NewParticles = Particles;
   NewParticles.insert(NewParticles.end(), other.Particles.begin(), other.Particles.end());

   for(int i = (int)Particles.size(); i < (int)NewParticles.size(); i++)
   {
      for(int j = 0; j < (int)NewParticles[i].Mothers.size(); j++)
         NewParticles[i].Mothers[j] += Particles.size();
      for(int j = 0; j < (int)NewParticles[i].Daughters.size(); j++)
         NewParticles[i].Daughters[j] += Particles.size();
   }

   return GenParticleTree(NewParticles, RunNumber, EventNumber, true);
}

void GenParticleTree::SaveToStream(ostream &out, bool ASCII)
{
   if(ASCII == true)
   {
      out << RunNumber << " " << EventNumber << " " << Weight << endl;

      out << IntegerProperties.size();
      for(int i = 0; i < (int)IntegerProperties.size(); i++)
         out << " " << IntegerProperties[i];

      out << " " << DoubleProperties.size();
      for(int i = 0; i < (int)DoubleProperties.size(); i++)
         out << " " << DoubleProperties[i];
      out << endl;

      out << " " << Particles.size() << endl;
      for(int i = 0; i < (int)Particles.size(); i++)
         Particles[i].SaveToStream(out, true);
   }
   else
   {
      SaveHelper Helper;
      Helper.IntValue = RunNumber;   out.write(Helper.CharValue, 16);
      Helper.IntValue = EventNumber;   out.write(Helper.CharValue, 16);
      Helper.Value = Weight;   out.write(Helper.CharValue, 16);
      
      Helper.IntValue = IntegerProperties.size();   out.write(Helper.CharValue, 16);
      for(int i = 0; i < (int)IntegerProperties.size(); i++)
      {
         Helper.IntValue = IntegerProperties[i];
         out.write(Helper.CharValue, 16);
      }
      
      Helper.Value = DoubleProperties.size();   out.write(Helper.CharValue, 16);
      for(int i = 0; i < (int)DoubleProperties.size(); i++)
      {
         Helper.Value = DoubleProperties[i];
         out.write(Helper.CharValue, 16);
      }
      
      Helper.IntValue = Particles.size();   out.write(Helper.CharValue, 16);
      for(int i = 0; i < (int)Particles.size(); i++)
         Particles[i].SaveToStream(out, false);
   }
}

void GenParticleTree::LoadFromStream(istream &in, bool ASCII)
{
   vector<GenParticle> particles;

   if(ASCII == true)
   {
      in >> RunNumber >> EventNumber >> Weight;

      int Size = 0;
      in >> Size;
      IntegerProperties.resize(Size);
      for(int i = 0; i < Size; i++)
         in >> IntegerProperties[i];
   
      Size = 0;
      in >> Size;
      DoubleProperties.resize(Size);
      for(int i = 0; i < Size; i++)
         in >> DoubleProperties[i];
  
      Size = 0;
      in >> Size;
      particles.resize(Size);
      for(int i = 0; i < Size; i++)
         particles[i].LoadFromStream(in, true);   
   }
   else
   {
      SaveHelper Helper;

      in.read(Helper.CharValue, 16);   RunNumber = Helper.IntValue;
      in.read(Helper.CharValue, 16);   EventNumber = Helper.IntValue;
      in.read(Helper.CharValue, 16);   Weight = Helper.Value;

      int Size = 0;
      in.read(Helper.CharValue, 16);   Size = Helper.IntValue;
      IntegerProperties.resize(Size);
      for(int i = 0; i < Size; i++)
      {
         in.read(Helper.CharValue, 16);
         IntegerProperties[i] = Helper.IntValue;
      }
      
      in.read(Helper.CharValue, 16);   Size = Helper.IntValue;
      DoubleProperties.resize(Size);
      for(int i = 0; i < Size; i++)
      {
         in.read(Helper.CharValue, 16);
         DoubleProperties[i] = Helper.Value;
      }

      in.read(Helper.CharValue, 16);   Size = Helper.IntValue;

      particles.resize(Size);
      for(int i = 0; i < Size; i++)
         particles[i].LoadFromStream(in, false);
   }
   
   Initialize(particles);
}

void GenParticleTree::RemoveDuplicates()
{
   vector<int>::iterator iter;

   for(int i = 0; i < (int)Particles.size(); i++)
   {
      iter = unique(Particles[i].Mothers.begin(), Particles[i].Mothers.end());
      Particles[i].Mothers.erase(iter, Particles[i].Mothers.end());
      
      iter = unique(Particles[i].Daughters.begin(), Particles[i].Daughters.end());
      Particles[i].Daughters.erase(iter, Particles[i].Daughters.end());
   }
}

void GenParticleTree::RepairReciprocalLinking()
{
   for(int i = 0; i < (int)Particles.size(); i++)
   {
      // daughter and back
      for(int j = 0; j < (int)Particles[i].Daughters.size(); j++)
      {
         if(Particles[i].Daughters[j] >= (int)Particles.size() || Particles[i].Daughters[j] < 0)
         {
            Particles[i].Daughters.erase(Particles[i].Daughters.begin() + j);
            j = j - 1;
            
            continue;
         }
         
         if(find(Particles[Particles[i].Daughters[j]].Mothers.begin(), Particles[Particles[i].Daughters[j]].Mothers.end(), i) == Particles[Particles[i].Daughters[j]].Mothers.end())
            Particles[Particles[i].Daughters[j]].Mothers.push_back(i);
      }
      
      // mother and back
      for(int j = 0; j < (int)Particles[i].Mothers.size(); j++)
      {
         if(Particles[i].Mothers[j] >= (int)Particles.size() || Particles[i].Mothers[j] < 0)
         {
            Particles[i].Mothers.erase(Particles[i].Mothers.begin() + j);
            j = j - 1;
            
            continue;
         }
         
         if(find(Particles[Particles[i].Mothers[j]].Daughters.begin(), Particles[Particles[i].Mothers[j]].Daughters.end(), i) == Particles[Particles[i].Mothers[j]].Daughters.end())
            Particles[Particles[i].Mothers[j]].Daughters.push_back(i);
      }      
   }
}

void GenParticleTree::RebuildTreeIndex()
{
   NumberOfTrees = 0;

   // we need at least one particle
   if(Particles.size() == 0)
      return;
   
   TreeIndex.resize(Particles.size());
   for(int i = 0; i < (int)Particles.size(); i++)
      TreeIndex[i] = -1;
      
   int CurrentTreeIndex = 0;
   for(int i = 0; i < (int)Particles.size(); i++)
   {
      if(TreeIndex[i] >= 0)
         continue;
      
      deque<int> ToBeProcessed;
      ToBeProcessed.push_back(i);
      
      while(ToBeProcessed.size() > 0)
      {
         int CurrentIndex = ToBeProcessed[0];
         ToBeProcessed.pop_front();
         
         if(TreeIndex[CurrentIndex] >= 0)
            continue;
         
         TreeIndex[CurrentIndex] = CurrentTreeIndex;
         
         for(int j = 0; j < (int)Particles[CurrentIndex].Mothers.size(); j++)
            if(TreeIndex[Particles[CurrentIndex].Mothers[j]] < 0)
               ToBeProcessed.push_back(Particles[CurrentIndex].Mothers[j]);
         for(int j = 0; j < (int)Particles[CurrentIndex].Daughters.size(); j++)
            if(TreeIndex[Particles[CurrentIndex].Daughters[j]] < 0)
               ToBeProcessed.push_back(Particles[CurrentIndex].Daughters[j]);
      }
      
      CurrentTreeIndex = CurrentTreeIndex + 1;
   }
   
   NumberOfTrees = CurrentTreeIndex;
}

void GenParticleTree::RebuildRank()
{
   // assume tree index already filled
   if(TreeIndex.size() != Particles.size())
      return;
   
   // we need at least one tree to begin with
   if(NumberOfTrees == 0)
      return;

   // initialize
   Rank.resize(Particles.size());
   for(int i = 0; i < (int)Particles.size(); i++)
      Rank[i] = DEFAULT_VALUE;

   // build rank tree-by-tree
   for(int i = 0; i < NumberOfTrees; i++)
   {
      deque<int> ToBeProcessed;

      // find first one in the tree
      for(int j = 0; j < (int)Particles.size(); j++)
      {
         if(TreeIndex[j] == i)
         {
            ToBeProcessed.push_back(j);
            Rank[j] = 0;
            break;
         }
      }
      
      // fill!
      while(ToBeProcessed.size() > 0)
      {
         int CurrentIndex = ToBeProcessed[0];
         ToBeProcessed.pop_front();

         for(int j = 0; j < (int)Particles[CurrentIndex].Mothers.size(); j++)
         {
            if(Rank[Particles[CurrentIndex].Mothers[j]] == DEFAULT_VALUE)
               ToBeProcessed.push_back(Particles[CurrentIndex].Mothers[j]);
            Rank[Particles[CurrentIndex].Mothers[j]] = Rank[CurrentIndex] - 1;
         }
         for(int j = 0; j < (int)Particles[CurrentIndex].Daughters.size(); j++)
         {
            if(Rank[Particles[CurrentIndex].Daughters[j]] == DEFAULT_VALUE)
               ToBeProcessed.push_back(Particles[CurrentIndex].Daughters[j]);
            Rank[Particles[CurrentIndex].Daughters[j]] = Rank[CurrentIndex] + 1;
         }
      }

      // find choke point current rank and later-on set it to zero      
      int ChokePointTemporaryRank = DEFAULT_VALUE;

      // first find sources
      vector<int> SourceIndex;
      for(int j = 0; j < (int)Particles.size(); j++)
      {
         if(TreeIndex[j] != i)
            continue;
            
         if(Particles[j].Mothers.size() == 0)
            SourceIndex.push_back(j);
      }

      // if only one source, choke point is the source
      if(SourceIndex.size() == 1)
         ChokePointTemporaryRank = Rank[SourceIndex[0]];
      else
      {
         // otherwise, find daughters common to all
         vector<int> DaughterList = Particles[SourceIndex[0]].Daughters;
         for(int j = 0; j < (int)DaughterList.size(); j++)
            DaughterList.insert(DaughterList.end(), Particles[DaughterList[j]].Daughters.begin(), Particles[DaughterList[j]].Daughters.end());
         
         sort(DaughterList.begin(), DaughterList.end());
         vector<int>::iterator iter = unique(DaughterList.begin(), DaughterList.end());
         DaughterList.erase(iter, DaughterList.end());
         
         for(int j = 1; j < (int)SourceIndex.size(); j++)   // loop over other sources
         {
            vector<int> DaughterList2 = Particles[SourceIndex[j]].Daughters;
            for(int k = 0; k < (int)DaughterList2.size(); k++)
               DaughterList2.insert(DaughterList2.end(), Particles[DaughterList2[k]].Daughters.begin(), Particles[DaughterList2[k]].Daughters.end());
         
            sort(DaughterList2.begin(), DaughterList2.end());
            vector<int>::iterator iter2 = unique(DaughterList2.begin(), DaughterList2.end());
            DaughterList2.erase(iter2, DaughterList2.end());
            
            int index1 = 0;
            int index2 = 0;
            
            vector<int> DaughterList1 = DaughterList;
            DaughterList.clear();
            
            while(index1 < (int)DaughterList1.size() && index2 < (int)DaughterList2.size())
            {
               if(DaughterList1[index1] < DaughterList2[index2])
               {
                  index1 = index1 + 1;
                  continue;
               }

               if(DaughterList1[index1] > DaughterList2[index2])
               {
                  index2 = index2 + 1;
                  continue;
               }
               
               DaughterList.push_back(DaughterList1[index1]);               
               index1 = index1 + 1;
               index2 = index2 + 1;
            }
         }
         
         // and the choke point(s) is (are) the one(s) with smallest rank
         int SmallestRank = Rank[DaughterList[0]];
         for(int j = 1; j < (int)DaughterList.size(); j++)
            if(Rank[DaughterList[j]] < SmallestRank)
               SmallestRank = Rank[DaughterList[j]];

         ChokePointTemporaryRank = SmallestRank;
      }
      
      // set choke point rank to zero
      for(int j = 0; j < (int)Particles.size(); j++)
      {
         if(TreeIndex[j] != i)
            continue;
            
         Rank[j] = Rank[j] - ChokePointTemporaryRank;
      }
   }
}

bool HasTau(GenParticleTree &Tree)
{
   for(int i = 0; i < Tree.ParticleCount(); i++)
      if(Tree[i].PDGID == 15 || Tree[i].PDGID == -15)
         return true;

   return false;
}

vector<int> FindAllIndices(GenParticleTree &Tree, int PDGID, int StatusCode)
{
   vector<int> Result;

   for(int i = 0; i < (int)Tree.ParticleCount(); i++)
   {
      if(StatusCode > 0 && Tree[i].StatusCode != StatusCode)
         continue;
      if(Tree[i].PDGID != PDGID)
         continue;

      Result.push_back(i);
   }

   return Result;
}

vector<int> TraceChildren(GenParticleTree &Tree, int SourceIndex)
{
   vector<int> AllChildren;

   deque<int> ToBeProcessed;
   ToBeProcessed.push_back(SourceIndex);

   while(ToBeProcessed.size() > 0)
   {
      int Current = ToBeProcessed[0];
      ToBeProcessed.pop_front();

      for(int i = 0; i < (int)Tree[Current].Daughters.size(); i++)
      {
         if(find(AllChildren.begin(), AllChildren.end(), Tree[Current].Daughters[i]) == AllChildren.end())
         {
            ToBeProcessed.push_back(Tree[Current].Daughters[i]);
            AllChildren.push_back(Tree[Current].Daughters[i]);
         }
      }
   }

   return AllChildren;
}

vector<int> KeepStableParticle(GenParticleTree &Tree, vector<int> &Indices)
{
   vector<int> StableIndices;

   for(int i = 0; i < (int)Indices.size(); i++)
   {
      if(Indices[i] < 0 || Indices[i] >= Tree.ParticleCount())
         continue;
      if(Tree[Indices[i]].StatusCode != 1)
         continue;

      StableIndices.push_back(Indices[i]);
   }

   return StableIndices;
}

vector<int> ListStableParticle(GenParticleTree &Tree)
{
   vector<int> StableIndices;

   for(int i = 0; i < Tree.ParticleCount(); i++)
   {
      if(Tree[i].StatusCode != 1)
         continue;

      StableIndices.push_back(i);
   }

   return StableIndices;
}


#endif







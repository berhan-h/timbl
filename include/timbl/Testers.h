#ifndef TESTERS_H
#define TESTERS_H

namespace Timbl{

  static const int maxSimilarity = INT_MAX;
  

  class metricTester {
  public:
    virtual ~metricTester(){};
    virtual double test( FeatureValue *, 
			 FeatureValue *, 
			 Feature * ) const = 0;
  };

  class overlapTester: public metricTester {
  public:
    double test( FeatureValue *FV,
		 FeatureValue *G,
		 Feature *Feat ) const;
  };

  class numericOverlapTester: public metricTester {
  public:
    double test( FeatureValue *FV,
		 FeatureValue *G,
		 Feature *Feat ) const;
  };
  

  class valueTester: public metricTester {
  public:
  valueTester( int t ): metricTester(), threshold( t ){};
  protected:
    int threshold;
  private:
    valueTester();
  };
  
  class valueDiffTester: public valueTester {
  public:
  valueDiffTester( int t ): valueTester( t){};
    double test( FeatureValue *F,
		 FeatureValue *G,
		 Feature *Feat ) const;
  };
  
  class jeffreyDiffTester: public valueTester {
  public:
  jeffreyDiffTester( int t ): valueTester( t){};
    double test( FeatureValue *F,
		 FeatureValue *G,
		 Feature *Feat ) const;
  };
  
  class levenshteinTester: public valueTester {
  public:
  levenshteinTester( int t ): valueTester( t){};
    double test( FeatureValue *F,
		 FeatureValue *G,
		 Feature *Feat ) const;
  };
  
  class TesterClass {
  public:
    TesterClass( const std::vector<Feature*>&, 
		 const std::vector<size_t> & );
    virtual ~TesterClass();
    void reset( MetricType, int );
    void init( const Instance&, size_t, size_t );
    virtual size_t test( std::vector<FeatureValue *>&, 
			 size_t,
			 double ) = 0;
    virtual double getDistance( size_t ) const = 0;
  protected:
    size_t _size;
    size_t effSize;
    size_t offSet;
    const std::vector<FeatureValue *> *FV;
    metricTester **test_feature_val;
    const std::vector<Feature *> &features;
    std::vector<Feature *> permFeatures;
    const std::vector<size_t> &permutation;
    std::vector<double> distances;
  };
  
  class DefaultTester: public TesterClass {
  public:
  DefaultTester( const std::vector<Feature*>& pf, 
		 const std::vector<size_t>& p ): 
    TesterClass( pf, p ){};  
    double getDistance( size_t ) const;
    size_t test( std::vector<FeatureValue *>&, 
		 size_t,
		 double ); 
  };
  
  class ExemplarTester: public TesterClass {
  public:
  ExemplarTester( const std::vector<Feature*>& pf,
		  const std::vector<size_t>& p ): 
    TesterClass( pf, p ){};  
    double getDistance( size_t ) const;
    size_t test( std::vector<FeatureValue *>&, 
		 size_t,
		 double );
  };

  class CosineTester: public TesterClass {
  public:
  CosineTester( const std::vector<Feature*>& pf,
		const std::vector<size_t>& p ): 
    TesterClass( pf, p ){};  
    double getDistance( size_t ) const;
    size_t test( std::vector<FeatureValue *>&, 
		 size_t,
		 double );
  };
  
  class DotProductTester: public TesterClass {
  public:
  DotProductTester( const std::vector<Feature*>& pf,
		    const std::vector<size_t>& p ): 
    TesterClass( pf, p ){};  
    double getDistance( size_t ) const;
    size_t test( std::vector<FeatureValue *>&, 
		 size_t,
		 double );
  };
}  

#endif // TESTERS_H

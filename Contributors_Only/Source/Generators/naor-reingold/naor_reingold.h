#ifndef NAOR_REINGOLD
#define NAOR_REINGOLD

// Singleton class, meant to be used without constructing
// NaorReingold::generate()
// NaorReingold::set_seed()
class NaorReingold {
public:
  // Function to set the seed
  static void set_seed(int seed);

  // Function to generate a random number (between 0 and ~10,000,000)
  static int generate();

private:
  // Returns a static instance of the class
  static NaorReingold &get();

  // Private generate function
  int p_generate();

  // Private set seed function
  void p_set_seed(int p_seed);
  int seed;
  NaorReingold();
};
#endif

#ifndef NAOR_REINGOLD
#define NAOR_REINGOLD

class NaorReingold {
public:
  static void set_seed(int seed);
  static int generate();

private:
  static NaorReingold &get();
  int p_generate();
  void p_set_seed(int p_seed);
  int seed;
  NaorReingold();
};
#endif

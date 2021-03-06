#include <stdio.h>
#include <cgraph.h>
#include "bla.h"

int main(int argc, char **argv) {
  Agraph_t *g;
  Agnode_t *n, *n0;
  Agsubnode_t *sn;
  int sum = 0, i, sum1;
  int sz = (argc > 1) ? atoi(argv[1]) : 1;
  int run, nruns = (argc > 2) ? atoi(argv[2]) : 1;
  int opt = (argc > 3) ? atoi(argv[3]) : 0;
  Agnode_t *N[sz];

  if (argc == 1)
    fprintf(stderr,
            "%s nnodes nruns opt\n\topt = 0 for agfstnode/agnxtnode\n\topt = 1 "
            "for dtflatten/dtlink\n\topt = 2 for flat array\n",
            argv[0]);
  g = agopen("g", Agdirected, 0);
  for (i = 0; i < sz; i++) {
    n = agnode(g, 0, TRUE);
    N[i] = n;
    sum = sum + AGSEQ(n);
  }
  switch (opt) {
    default:
    case 0:
      for (run = 0; run < nruns; run++) {
        sum1 = 0;
        for (n = agfstnode(g); n; n = agnxtnode(g, n)) {
          sum1 = sum1 + AGSEQ(n);
        }
        if (sum != sum1) fprintf(stderr, "error\n");
      }
      break;
    case 1:
      for (run = 0; run < nruns; run++) {
        Agnoderef_t *nref;
        sum1 = 0;
        for (nref = FIRSTNREF(g); nref; nref = NEXTNREF(nref)) {
          n = NODEOF(nref);
          sum1 = sum1 + AGSEQ(n);
          n0 = agnxtnode(g, n);
        }
        if (sum != sum1) fprintf(stderr, "error %x %x\n", sum, sum1);
      }
      break;
    case 2:
      for (run = 0; run < nruns; run++) {
        sum1 = 0;
        for (i = 0; i < sz; i++) {
          n = N[i];
          sum1 = sum1 + AGSEQ(n);
        }
        if (sum != sum1) fprintf(stderr, "error\n");
      }
      break;
  }
  return 1;
}

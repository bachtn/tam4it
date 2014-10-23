#include "neuron.h"

double neuron (struct vector *value, struct vector *poids)
{
  double r = 0;
  for(int i = 0; i < value->size; i++)
    r = r + value->data[i]*poids->data[i];
  return 1 /(1 + exp(-(r - poids[poids->value])));
}

double xorNeuro (double input1, double input2, struct vector *poid)
{
  struct vector *input = malloc (sizeof (struct vector)), 
    *tempo = malloc (sizeof (struct vector));
  
  input->size = 2;
  input->data = malloc (sizeof (double) * 2);
  input->data[1] = input1;
  input->data[2] = input2;
  
  tempo->size = 3;
  tempo->data = malloc (sizeof (double) * 3);
  tempo->data[0] = neuron (input, poid);
  tempo->data[1] = neuron (input, poid);
  tempo->data[2] = neuron (input, poid);

  return neuron (tempo, poid);
}

void improve (double input1, double input2, double result);

struct vector get_poid ()
{
  FILE *poid_txt = fopen ("poid.txt", "r+");
  //FIX ME
}

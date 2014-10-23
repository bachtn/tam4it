#include "neuron.h"

#define LEARNING_RATE 0.7

double neuron (struct vector *value, struct vector *weight)
{
  double r = 0;
  for(int i = 0; i < value->size; i++)
    r = r + value->data[i]*weight->data[i];
  return 1 /(1 + exp(-(r - weight[weight->value])));
}

double xorNeuro (double input1, double input2, struct vector *weight)
{
  struct vector *input = malloc (sizeof (struct vector)), 
    *tempo = malloc (sizeof (struct vector));
  
  input->size = 2;
  input->data = malloc (sizeof (double) * 2);
  input->data[1] = input1;
  input->data[2] = input2;
  
  tempo->size = 3;
  tempo->data = malloc (sizeof (double) * 3);
  tempo->data[0] = neuron (input, weight);
  tempo->data[1] = neuron (input, weight);
  tempo->data[2] = neuron (input, weight);

  return neuron (tempo, weight);
}

void improveWeight (struct vector *inputs, double result, struct vector *weight)
{
	
	double error, out;
	out=  xorNeuro(inputs->data[0], inputs->data[1], weight);
	error = result - out;
	double dif;
	dif = out * (1 - out) * error;
	struct vector R;
	R = malloc (sizeof(struct vector));
	R->data = malloc(sizeof(double) *3);
	R->size = 3;
	R->data[0] = dif * weight->data[9];   //1er poid de sortie
	R->data[1] = dif * weight->data[10];  //2eme " "
	R->data[2] = dif * weight->data[11];  //3eme  " "
	weight->data[9] = R->data[0];
	weight->data[10] = R->data[1];  //mise a jour effectuee et remplacee.
	weight->data[11] = R->data[2];
	
        double f;
	f = R->data[0] + R->data[1] + R->data[2];
	dif = neuron(inputs, weight) * (1 - neuron(inputs, weight)) * f;
	weight->data[0] += LEARNING_RATE * dif * inputs->data[0];
	weight->data[1] += LEARNING_RATE * dif * inputs->data[1];
	weight->data[3] += LEARNING_RATE * dif * inputs->data[0];
	weight->data[4] += LEARNING_RATE * dif * inputs->data[1];   //DOUTE pour mettre a jour les poids.
}

struct vector get_poid ()
{
  FILE *poid_txt = fopen ("poid.txt", "r+");
  //FIX ME
}

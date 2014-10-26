#include "neuron.h"

#define LEARNING_RATE 0.7

double neuron (struct vector *value, struct vector *weight, int start, int end) //std neuron
{
  double r = 0;
  for(int i = start; i < end; i++)
    r = r + value->data[i]*weight->data[i];
  return 1 /(1 + exp(-(r - weight->data[0])));
}

double xorNeuro (double input1, double input2, struct vector *weight) //XOR neural network
{
  struct vector *input = malloc (sizeof (struct vector)),  *tempo = malloc (sizeof (struct vector));

  input->size = 2;
  input->data = malloc (sizeof (double) * 5);
  input->data[1] = input1;
  input->data[2] = input2;
  input->data[3] = input1;
  input->data[4] = input2;
  
  tempo->size = 2;
  tempo->data = malloc (sizeof (double) * 7);
  tempo->data[5] = neuron (input, weight, 1, 2);
  tempo->data[6] = neuron (input, weight, 3, 4);

  return neuron (tempo, weight, 5, 6);
}

void improveWeight (struct vector *inputs, double result) //improve weight for XOR
{
  struct vector *weight = get_weight();
  double error, out, dif, f;

  out=  xorNeuro(inputs->data[0], inputs->data[1], weight);
  error = result - out;
  
  dif = out * (1 - out) * error;

  weight->data[5] *= dif;
  weight->data[6] *= dif;  //mise a jour effectuee et remplacee.
        
  f = weight->data[5] + weight->data[6];

  dif = xorNeuro(inputs->data[0], inputs->data[1], weight) * (1 - xorNeuro(inputs->data[0], inputs->data[1], weight)) * f;

  weight->data[1] += LEARNING_RATE * dif * inputs->data[0];
  weight->data[2] += LEARNING_RATE * dif * inputs->data[1];
  weight->data[3] += LEARNING_RATE * dif * inputs->data[0];
  weight->data[4] += LEARNING_RATE * dif * inputs->data[1];   //DOUTE pour mettre a jour les poids.

  set_weight (weight);
}

struct vector *get_weight () // get weight from poid.txt FOR XOR ONLY
{
  FILE *weight_txt = fopen ("poid.txt", "r");

  struct vector *weight = malloc (sizeof(struct vector));
  weight->data = malloc(sizeof(int)*700);
  weight->size = 0;

  fscanf(weight_txt, "%lf/n%lf %lf/n%lf %lf/n%lf %lf", &weight->data[0], &weight->data[1], &weight->data[2], &weight->data[3], &weight->data[4], &weight->data[5], &weight->data[6]);

  fclose(weight_txt);
  return weight;
}

void set_weight (struct vector *weight) //change weight in poid.txt
{
  FILE *txt = fopen ("poid.txt", "w+");
  
  fprintf(txt, "%lf/n%lf %lf/n%lf %lf/n%lf %lf", weight->data[0],  weight->data[1], weight->data[2], weight->data[3], weight->data[4], weight->data[5], weight->data[6]);

  fclose(txt);
}

int main(int argc, char* argv[])
{
  if (argc != 3)
    return 1;
  printf ("%lf\n", xorNeuro (atof (argv [1]), atof(argv [2]), get_weight()));
  return 0;
}

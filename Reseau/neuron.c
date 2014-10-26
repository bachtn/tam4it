#include "neuron.h"

#define LEARNING_RATE 0.7

double neuron (struct vector *value, struct vector *weight, int start, int end) //FIX ME
{
  double r = 0;
  for(int i = start; i < end; i++)
    r = r + value->data[i]*weight->data[i];
  return 1 /(1 + exp(-(r - weight[0])));
}

double xorNeuro (double input1, double input2, struct vector *weight)
{
  struct vector *input = malloc (sizeof (struct vector)), 
    *tempo = malloc (sizeof (struct vector));
  
  input->size = 3;
  input->data = malloc (sizeof (double) * 2);
  input->data[1] = input1;
  input->data[2] = input2;
  
  tempo->size = 3;
  tempo->data = malloc (sizeof (double) * 2);
  tempo->data[1] = neuron (input, weight, 1, 2);
  tempo->data[2] = neuron (input, weight, 3, 4);

  return neuron (tempo, weight, 5, 6);
}

void improveWeight (struct vector *inputs, double result, struct vector *weight)
{
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

struct vector get_weight ()
{
  FILE *weight_txt = fopen ("poid.txt", "r");
  char *actualNumber[8] = {0};
  int i;
  struct vector *weight = malloc (sizeof(struct vector));
  weight->data = malloc(sizeof(int)*7);
  weight->size = 0;
  
  char c = fgetc(weight_txt); //c = actual char
  while (c != "/0");
  {
    if (c != ' ' && c != '/n')
      {
	actualNumber[i] = c;
	i++;
      }
    else
      {
	weight->data[weight->size] = toDouble(actualNumber, 0, 7);
	weight->size ++;
	for (i = 7; i >= 0; i--)
	  actualNumber[i] = "0";
	i++;
      }
    c = fgetc(weight_txt);
  }
  
  fclose(weight_txt);
  return weight;
}

void set_weight (struct vector *weight) //code safe OF COURSE
{
  FILE *txt = fopen ("poid.txt", "w+");
  
  fprintf(txt, "%d/n%d $d/n%d %d/n%d %d", weight->data[0],  weight->data[1], weight->data[2], weight->data[3], weight->data[4], weight->data[5], weight->data[6]);

  fclose(weight_txt);
}

double toDouble(const char* s, int start, int stop) {
  unsigned long long int m = 1;
  double ret = 0;
  for (int i = stop; i >= start; i--)
    {
      ret += (s[i] - '0') * m;
      m *= 10;
    }
  return ret;
}


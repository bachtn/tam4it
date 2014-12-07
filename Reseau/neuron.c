#include "neuron.h"

#define LEARNING_RATE 0.7

float functionSig (float x){
  return 1 / (1 + exp (x));
}

int neuron (int values[256], float weight[1][257], int idNeur){ //standart neuron
  float tempo = 0;
  for (int i = 0; i < 256; i++)
    tempo += values[i] + weight[idNeur][i];
  tempo -= weight[idNeur][256];
  return functionSig (tempo) >= 0.5;
}

/*void improveWeight (struct vector *inputs, double result) //improve weight for XOR
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
}*/

float **get_weight () //read weight.wgt and return it values
{
  FILE *weight_file = fopen ("poid.txt", "rb");
  float **weights = malloc (sizeof (float[256]));
  for (int i = 0; i < 256; i ++)
    weights[i] = malloc (sizeof (float[100]));

  fread (weights, sizeof (float[100]), 256, weight_file);

  fclose(weight_file);
  return weights;
}

void set_weight (float **weight) //set weight.wgt to new value
{
  FILE *weight_file = fopen ("poid.txt", "wb");
  
  fwrite (weight, sizeof (float[100]), 256, weight_file);

  fclose(weight_file);
}

void initializationWeights () //create and initialized weight.wgt to 0
{
  FILE *weight_file = fopen ("weights.wgt", "wb");
  float matrix[256][100] = {{0}}; //#themovieofcourse

  fwrite (matrix, sizeof (float[100]), 256, weight_file);
  
  fclose (weight_file);
}

/*int main(int argc, char *argv[])
{
  if (argc > 1){
    switch (*argv[1]){
    case '0':
      initializationWeights ();
      printf("weights.wgt initialized\n");
      break;
    case 'i':
      //ADD IMPROVEMENT HERE
      break;
    case 't':
      //TEST HERE
      break;
    default:
      printf("wrong arguments");
      break;
    }
      
  }
  else
    printf ("no arguements\n");
  return 0;
}*/

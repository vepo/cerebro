#include <iostream>
#include <cstring>

#include "dataset/dataset.hpp"
#include "nn/multi-layer-perceptron-trainer.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    string outpuFile;
    string datasetFile;
    vector<string> inputNames;
    vector<string> outputNames;
    vector<int> layers;

    for (size_t index = 0; index < argc; ++index)
    {
        if ((strcmp(argv[index], "-o") == 0 ||
             strcmp(argv[index], "--output-file") == 0) &&
            index + 1 < argc)
        {
            outpuFile = argv[index + 1];
            index += 2;
        }

        if ((strcmp(argv[index], "-d") == 0 ||
             strcmp(argv[index], "--dataset") == 0) &&
            index + 1 < argc)
        {
            datasetFile = argv[index + 1];
            index += 2;
        }

        if ((strcmp(argv[index], "-in") == 0 ||
             strcmp(argv[index], "--input") == 0) &&
            index + 1 < argc)
        {
            char *key = strtok(argv[index + 1], ",");
            while (NULL != key)
            {
                inputNames.push_back(key);
                key = strtok(NULL, ",");
            }
            index += 2;
        }

        if ((strcmp(argv[index], "-out") == 0 ||
             strcmp(argv[index], "--output") == 0) &&
            index + 1 < argc)
        {
            char *key = strtok(argv[index + 1], ",");
            while (NULL != key)
            {
                outputNames.push_back(key);
                key = strtok(NULL, ",");
            }
            index += 2;
        }

        if ((strcmp(argv[index], "-l") == 0 ||
             strcmp(argv[index], "--layers") == 0) &&
            index + 1 < argc)
        {
            char *layerSize = strtok(argv[index + 1], ",");
            while (NULL != layerSize)
            {
                layers.push_back(atoi(layerSize));
                layerSize = strtok(NULL, ",");
            }
            index += 2;
        }
    }

    Dataset dataset(datasetFile);
    MultiLayerPerceptronTrainerParams params(&dataset,
                                             inputNames,
                                             outputNames);
    cout << "Training House Predictor..." << endl;
    return 0;
}
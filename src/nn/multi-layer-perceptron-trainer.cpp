#include "nn/multi-layer-perceptron-trainer.hpp"
#include "nn/multi-layer-perceptron.hpp"
#include <iostream>
#include <iomanip>

MultiLayerPerceptronTrainerParams::MultiLayerPerceptronTrainerParams(const Dataset &dataset,
                                                                     std::vector<std::string> xNames,
                                                                     std::vector<std::string> yNames,
                                                                     std::vector<int> layers,
                                                                     int epochs,
                                                                     double testSize,
                                                                     double validationSize) : dataset(dataset),
                                                                                              xNames(xNames),
                                                                                              yNames(yNames),
                                                                                              layers(layers),
                                                                                              epochs(epochs),
                                                                                              testSize(testSize),
                                                                                              validationSize(validationSize)
{
}

MultiLayerPerceptronTrainer::MultiLayerPerceptronTrainer(const MultiLayerPerceptronTrainerParams &params) : params(params)
{
}

void print_valuee(std::string paramName, int value)
{
    std::cout << "    o " << paramName << ": " << value << std::endl;
}

template <class T>
void print_vector(std::string paramName, std::vector<T> v)
{
    std::cout << "    o " << paramName << ": {";
    for (size_t index = 0; index < v.size(); ++index)
    {
        if (index > 0)
        {
            std::cout << ", ";
        }

        std::cout << v[index];
    }
    std::cout << "}" << std::endl;
}

#include <limits>

void MultiLayerPerceptronTrainer::train()
{
    Pair<Dataset> trainPair = params.dataset.split(params.testSize + params.validationSize);
    Pair<Dataset> validationPair = trainPair.first.split(params.validationSize / (params.testSize + params.validationSize));

    Dataset trainDataset = trainPair.second,
            validationDataset = validationPair.first,
            testDataset = validationPair.second;

    std::cout
        << "-------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "                Starting NN Train                " << std::endl;
    std::cout << std::endl;
    std::cout << "Parameters:" << std::endl;
    print_vector("Layers                 ", params.layers);
    print_vector("Input names            ", params.xNames);
    print_vector("Output names           ", params.yNames);
    print_valuee("Total dataset size     ", params.dataset.rows());
    print_valuee("Train dataset size     ", trainDataset.rows());
    print_valuee("Validation dataset size", validationDataset.rows());
    print_valuee("Test dataset size      ", testDataset.rows());
    print_valuee("Epocs                  ", params.epochs);
    std::cout << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;
    MultiLayerPerceptron mlp = MultiLayerPerceptron(params.layers);
    NormalizedDataset trainInput = trainDataset.split(params.xNames).normalize();
    NormalizedDataset trainOutput = trainDataset.split(params.yNames).normalize();

    NormalizedDataset testInput = testDataset.split(params.xNames).normalize();
    NormalizedDataset testOutput = testDataset.split(params.yNames).normalize();

    double MSE;
    double lastTestError = std::numeric_limits<double>::max();
    for (int epoch = 0; epoch < params.epochs; ++epoch)
    {
        MSE = 0.0;
        for (int row = 0; row < trainDataset.rows(); ++row)
        {
            MSE += mlp.bp(trainInput.rowData(row), trainOutput.rowData(row));
        }
        MSE = MSE / (double)trainDataset.rows();
        if (epoch % 100 == 0)
        {
            double testError = MultiLayerPerceptronTrainer::MSE(&mlp, testInput, testOutput);
            if (testError > lastTestError)
            {
                std::cout << "Warning: error is increasing... delta=" << std::setw(10) << std::setprecision(5) << (testError - lastTestError) << std::endl;
            }
            std::cout << "Testing  MSE = " << std::setw(10) << std::setprecision(5) << MSE << std::endl;
            std::cout << "Training MSE = " << std::setw(10) << std::setprecision(5) << testError << std::endl;
            lastTestError = testError;
        }
    }

    std::cout << std::endl
              << std::endl
              << "Trained weights (Compare to hard-coded weights):"
              << std::endl
              << std::endl;
    mlp.print_weights();
}

double MultiLayerPerceptronTrainer::MSE(MultiLayerPerceptron *mlp,
                                        const NormalizedDataset &input,
                                        const NormalizedDataset &output)
{
    double MSE = 0.0;
    for (int row = 0; row < input.rows(); ++row)
    {
        std::vector<double> expectedResult = output.rowData(row);
        std::vector<double> result = mlp->run(input.rowData(row));
        double localError = 0.0;
        for (size_t j = 0; j < result.size(); ++j)
        {
            double delta = result[j] - expectedResult[j];
            localError += delta * delta;
        }
        MSE += localError;
    }
    return MSE / input.rows();
}
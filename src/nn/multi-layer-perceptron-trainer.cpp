#include "nn/multi-layer-perceptron-trainer.hpp"
#include "nn/multi-layer-perceptron-trainee.hpp"
#include <iostream>
#include <iomanip>
#include "utils/vt100.hpp"

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
#include <cmath>

Model MultiLayerPerceptronTrainer::train()
{
    Pair<Dataset> trainPair = params.dataset.split(params.testSize + params.validationSize);
    Pair<Dataset> validationPair = trainPair.first.split(params.validationSize / (params.testSize + params.validationSize));

    Dataset trainDataset = trainPair.second,
            validationDataset = validationPair.first,
            testDataset = validationPair.second;

    WindowSize size = VT100::getWindowSize();
    VT100::clearScreen();
    VT100::fillLine('-', size.cols);
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
    VT100::fillLine('-', size.cols);
    MultiLayerPerceptronTrainee mlp = MultiLayerPerceptronTrainee(params.layers);
    NormalizedDataset trainInput = trainDataset.split(params.xNames).normalize();
    NormalizedDataset trainOutput = trainDataset.split(params.yNames).normalize();

    NormalizedDataset testInput = testDataset.split(params.xNames).normalize();
    NormalizedDataset testOutput = testDataset.split(params.yNames).normalize();

    double MSE;
    double lastTestError = std::numeric_limits<double>::max();
    double minTestError = std::numeric_limits<double>::max();
    std::vector<std::vector<std::vector<double>>> minWeights;
    for (int epoch = 0; epoch < params.epochs; ++epoch)
    {
        mlp.generateDropout();
        MSE = 0.0;
        for (int row = 0; row < trainDataset.rows(); ++row)
        {
            MSE += mlp.bp(trainInput.rowData(row), trainOutput.rowData(row));
        }
        MSE = MSE / (double)trainDataset.rows();

        mlp.disableDropout();
        double testError = MultiLayerPerceptronTrainer::MSE(&mlp, testInput, testOutput);
        if (minTestError > testError)
        {
            minTestError = testError;
            minWeights = mlp.get_weights();
        }

        if (epoch % 100 == 0)
        {
            VT100::goTo({.y = 17, .x = 0});
            std::cout << "Epoch        = " << epoch << std::endl
                      << std::endl;
            VT100::foregroundColor(Color::GREEN);
            std::cout << "Testing  MSE = " << std::setw(10) << std::setprecision(5) << MSE << std::endl;
            std::cout << "Training MSE = " << std::setw(10) << std::setprecision(5) << testError << std::endl;
            if (testError - lastTestError > 0.01 * testError)
            {
                VT100::foregroundColor(Color::RED);
                double errorPerCent = 100 * (testError - lastTestError) / lastTestError;
                std::cout << "Warning: error is increasing... " << std::setw(10) << std::setprecision(5) << errorPerCent << "%" << std::endl;
            }
            else
            {
                VT100::eraseLine();
            }
            VT100::foregroundColor(Color::DEFAULT);
            std::cout << std::endl;
            lastTestError = testError;
        }

        if (std::isnan(MSE) || std::isnan(lastTestError))
        {
            mlp = MultiLayerPerceptronTrainee(params.layers);
            epoch = -1;
        }
    }

    mlp.setWeights(minWeights);

    std::cout << "MIN MSE: " << std::setw(10) << std::setprecision(5) << minTestError << std::endl;

    std::cout << std::endl
              << std::endl
              << "Trained weights (Compare to hard-coded weights):"
              << std::endl
              << std::endl;
    mlp.printWeights();
    return Model("", params.xNames, params.yNames, minWeights, mlp.bias());
}

double MultiLayerPerceptronTrainer::MSE(MultiLayerPerceptronTrainee *mlp,
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
            std::cout << "result  : [" << row << "][" << j << "]" << result[j] << std::endl;
            std::cout << "expected: [" << row << "][" << j << "]" << expectedResult[j] << std::endl;
            std::cout << "delta   : [" << row << "][" << j << "]" << delta << std::endl;
            localError += delta * delta;
        }
        MSE += localError;
    }
    if (std::isnan(MSE / input.rows()))
    {
        std::cout << "MSE: " << MSE << std::endl;
        std::cout << "ROWS: " << input.rows() << std::endl;
        mlp->printWeights();
        exit(-1);
    }
    return MSE / input.rows();
}
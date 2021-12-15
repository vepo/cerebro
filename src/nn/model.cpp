#include "nn/model.hpp"

#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#include <fstream>
#include <cstring>

Model::Model(std::string name,
             std::vector<std::string> inputs,
             std::vector<std::string> outputs,
             std::vector<std::vector<std::vector<double>>> weights,
             double bias) : _name(name),
                            _inputs(inputs),
                            _outputs(outputs),
                            _weights(weights),
                            _bias(bias)

{
}

int mkpath(char *dir, mode_t mode)
{
    if (!dir)
    {
        errno = EINVAL;
        return 1;
    }

    // folder exists
    struct stat sb;
    if (stat(dir, &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        return 0;
    }

    // root folder
    if (strlen(dir) == 1 && dir[0] == '/')
    {
        return 0;
    }

    char *dDir = strdup(dir);
    char *pFolder = dirname(dDir);
    mkpath(pFolder, mode);
    free(dDir);
    return mkdir(dir, mode);
}

void write_string(std::ofstream *output, const std::string &value)
{
    char data[value.size() + 2];
    data[0] = 0xFF00 & value.size();
    data[1] = 0x00FF & value.size();
    memcpy(&data[2], value.c_str(), value.size());
    output->write(data, value.size() + 2);
}

void write_string_array(std::ofstream *output, const std::vector<std::string> &values)
{
    char data[2];
    data[0] = 0xFF00 & values.size();
    data[1] = 0x00FF & values.size();
    output->write(data, 2);

    for (const std::string &value : values)
    {
        write_string(output, value);
    }
}

bool Model::save(const std::string &path)
{
    char *_path = (char *)path.c_str();

    char *_path_dir = strdup(_path);
    char *_path_filename = strdup(_path);
    char *dir = dirname(_path_dir);
    char *filename = basename(_path_dir);

    struct stat sb;
    if (stat(dir, &sb) != 0)
    {
        mkpath(dir, S_IRWXU | S_IRWXG | S_IRWXO);
    }

    if (stat(_path, &sb) == 0)
    {
        int ret = unlink(_path);
    }

    std::ofstream output(path, std::ios::binary);
    if (output)
    {
        write_string(&output, _name);
        write_string_array(&output, _inputs);
        write_string_array(&output, _outputs);
        return true;
    }
    else
    {
        free(_path_dir);
        free(_path_filename);
        return false;
    }
}

std::string read_string(std::ifstream *input)
{
    char sizeData[2];
    input->read(sizeData, 2);

    int size = (sizeData[0] << 2) + sizeData[1];
    char data[size + 1];
    input->read(data, size);
    data[size] = '\0';
    return data;
}

std::vector<std::string> read_string_array(std::ifstream *input)
{
    char sizeData[2];
    input->read(sizeData, 2);
    int size = (sizeData[0] << 2) + sizeData[1];

    std::vector<std::string> data;
    for (int i = 0; i < size; ++i)
    {
        data.emplace_back(read_string(input));
    }
    return data;
}

Model Model::load(const std::string &path)
{
    std::ifstream input(path, std::ios::binary);

    std::string name = read_string(&input);
    std::vector<std::string> inputs = read_string_array(&input);
    std::vector<std::string> outputs = read_string_array(&input);
    return Model(name, inputs, outputs, {}, 0.0);
}
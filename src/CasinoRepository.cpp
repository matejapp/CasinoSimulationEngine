#include "CasinoRepository.h"

#include <fstream>
#include <utility>

CasinoRepository::CasinoRepository(std::string saveFile)
    : saveFile_(std::move(saveFile))
{
}

bool CasinoRepository::load(CasinoData &data) const
{
    std::ifstream input(saveFile_);
    if (!input.is_open() || input.peek() == std::ifstream::traits_type::eof())
    {
        return false;
    }

    CasinoData loadedData;
    input >> loadedData.budget;
    input.ignore();
    std::getline(input, loadedData.playerName);
    input >> loadedData.playerBalance;

    if (!input)
    {
        return false;
    }

    data = loadedData;
    return true;
}

bool CasinoRepository::save(const CasinoData &data) const
{
    std::ofstream output(saveFile_);
    if (!output.is_open())
    {
        return false;
    }

    output << data.budget << '\n'
           << data.playerName << '\n'
           << data.playerBalance << '\n';

    return static_cast<bool>(output);
}
#pragma once

#include "CasinoData.h"

#include <string>

class CasinoRepository
{
public:
    explicit CasinoRepository(std::string saveFile);

    bool load(CasinoData &data) const;
    bool save(const CasinoData &data) const;

private:
    std::string saveFile_;
};
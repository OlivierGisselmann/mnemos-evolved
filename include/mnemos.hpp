#ifndef MNEMOS_HPP
#define MNEMOS_HPP

#include <defines.hpp>
#include <debug.hpp>
#include <application.hpp>

#include <memory>

namespace mnm
{
    MAPI void Run(const std::unique_ptr<MnemosApplication>& app) noexcept;
}

#endif

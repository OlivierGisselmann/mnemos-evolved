#ifndef MNEMOS_HPP
#define MNEMOS_HPP

#include <application.hpp>
#include <defines.hpp>
#include <debug.hpp>
#include <input.hpp>

#include <memory>

namespace mnm
{
    MAPI void Run(const std::unique_ptr<MnemosApplication>& app) noexcept;
    MAPI void Stop() noexcept;
}

#endif

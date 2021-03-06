// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <ecst/config.hpp>
#include <ecst/tag/system.hpp>
#include <ecst/signature/system/valid.hpp>

ECST_SIGNATURE_SYSTEM_NAMESPACE
{
    /// @brief Returns the tag type stored inside a system signature.
    template <typename TSystemSignature>
    constexpr auto tag_of(TSystemSignature ss)
    {
        ECST_S_ASSERT_DT(valid(mp::unwrapped(ss)));
        return tag_type<TSystemSignature>{};
    }
}
ECST_SIGNATURE_SYSTEM_NAMESPACE_END

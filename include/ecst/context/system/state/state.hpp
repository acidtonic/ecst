// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <functional>
#include <ecst/config.hpp>
#include <ecst/aliases.hpp>
#include <ecst/utils/sparse_int_set.hpp>

ECST_CONTEXT_NAMESPACE
{
    namespace impl
    {
        namespace defer
        {
            template <typename TSettings>
            class proxy;
        }
    }
}
ECST_CONTEXT_NAMESPACE_END

ECST_CONTEXT_SYSTEM_NAMESPACE
{
    namespace impl
    {
        template <typename TSettings>
        class deferred_fns_vector
        {
        private:
            using defer_proxy_type = context::impl::defer::proxy<TSettings>;
            using fn_type = std::function<void(defer_proxy_type&)>;

            /// @brief A "deferred function" is a void-returning `std::function`
            /// that takes a "defer proxy" by reference as its only
            /// parameter.using fn_type =
            /// std::function<void(defer_proxy_type&)>;

            std::vector<fn_type> _fns;

        public:
            void clear() noexcept
            {
                _fns.clear();
            }

            template <typename TF>
            void add(TF&& f)
            {
                _fns.emplace_back(FWD(f));
            }

            template <typename TProxy>
            void execute_all(TProxy& proxy)
            {
                for(auto& f : _fns)
                {
                    f(proxy);
                }
            }
        };

        /// @brief A "system state" is a storage class bound to a particular
        /// subtask during system execution.
        /// @details Contains a vector of deferred functions and a "killed
        /// entities" sparse set.
        template <typename TSettings>
        class state
        {
        private:
            using set_type = dispatch_set<TSettings>;

        public:
            deferred_fns_vector<TSettings> _deferred_fns;
            set_type _to_kill;

            void clear() noexcept
            {
                _to_kill.clear();
                _deferred_fns.clear();
            }
        };
    }
}
ECST_CONTEXT_SYSTEM_NAMESPACE_END

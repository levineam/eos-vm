#pragma once

#if !defined(LIKELY) && !defined(UNLIKELY)
#   if defined(__GNUC__)
#      if (__GNUC__ > 5) || defined(__clang__)
#         define LIKELY(x) __builtin_expect(!!(x), 1)
#         define UNLIKELY(x) __builtin_expect(!!(x), 0)
#      else
#         define LIKELY(x) !!(x)
#         define UNLIKELY(x) !!(x)
#      endif
#   else
#      define LIKELY(x) !!(x)
#      define UNLIKELY(x) !!(x)
#   endif
#endif

namespace eosio { namespace vm {
   // helpers for std::visit
   template <class... Ts>
   struct overloaded : Ts... {
      using Ts::operator()...;
   };
   template <class... Ts>
   overloaded(Ts...)->overloaded<Ts...>;

   template<typename F>
   struct scope_guard {
      scope_guard(F&& f) : _f(static_cast<F&&>(f)) {}
      ~scope_guard() { _f(); }
      F _f;
   };
}} // namespace eosio::vm

#pragma once

namespace std {
  template<bool Condition, class TrueType, class FalseType>
  struct conditional { typedef TrueType type; };
  template<class TrueType, class FalseType>
  struct conditional<false, TrueType, FalseType> { typedef FalseType type; };

  template<bool Condition, class TrueType>
  struct enable_if {};
  template<class TrueType>
  struct enable_if<true, TrueType> { typedef TrueType type; };
}

namespace Nixie {
  template <uint8_t TUBES>
  using uint_for_tubes =
      typename std::conditional<
          TUBES <= 2,
          uint8_t,
          typename std::conditional<
              TUBES <= 4,
              uint16_t,
              typename std::conditional<
                  TUBES <= 9,
                  uint32_t,
                  typename std::enable_if<TUBES<=19, uint64_t>::type
              >::type
          >::type
      >::type;
}

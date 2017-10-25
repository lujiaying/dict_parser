#ifndef GOODCODER_UTILS_H
#define GOODCODER_UTILS_H

namespace goodcoder {

// Source from: http://www.cplusplus.com/faq/sequences/strings/split/
template <typename Container>
Container& split(
    Container&                            result,
    const typename Container::value_type& s,
    const typename Container::value_type& delimiters) {
    result.clear();
    size_t current;
    size_t next = -1;
    do {
        current = next + 1;
        next = s.find_first_of(delimiters, current);
        result.push_back(s.substr(current, next - current));
    } while (next != Container::value_type::npos);
    return result;
};

}

#endif //GOODCODER_UTILS_H
